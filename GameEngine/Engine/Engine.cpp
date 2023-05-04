#pragma once
#include <iostream>
#include <assert.h>
#include <DirectXColors.h>
#include "Vector4.h"
#include "Engine.h"
#include "Timing.h"
#include "Renderer.h"
#include "Physics.h"
#include "Syncronization/Mutex.h"
#include "Syncronization/ScopeLock.h"
using namespace std;
using json = nlohmann::json;

namespace Engine {

    Mutex NewEntityMutex;
    vector<SmartPtr<Entity>> NewEntities;
    // This adds a new GameObject to NewGameObjects
    void AddNewEntity(json & data)
    {
        if (data.contains("renderer") && data.contains("physics")) {

            // Acquire a scoped lock on the mutex
            Engine::ScopeLock Lock(NewEntityMutex);
            bool isPlayer = data.at("isPlayer");
            bool hasPhysics = data.at("physics").at("valid");
            string spritePath = data.at("renderer").at("sprite");
            SmartPtr<Entity> Master(new Entity(isPlayer, spritePath.c_str(), hasPhysics));
            
            Master->Pos = Point2D<float>(data.at("initial_position")[0], data.at("initial_position")[1]);
            if (hasPhysics) {
                Master->physicsComp->mass = data.at("physics").at("mass");
                Master->physicsComp->fraction = data.at("physics").at("fraction");
            }
            NewEntities.push_back(Master);
        }
    }

    void CheckForNewEntities(Game* game)
    {
        Engine::ScopeLock Lock(NewEntityMutex);

        if (!NewEntities.empty())
        {
            for (SmartPtr<Entity> p : NewEntities)
            {
                if (p)
                {
                    p->SetParent(&*(game->sceneRoot));
                    if (p->isPlayer) game->player = p;
                }
            }
            NewEntities.clear();
        }
    }


    void CreateEntities(uint8_t* i_pFileContents, size_t i_sizeFileContents)
    {
        assert(i_pFileContents && i_sizeFileContents);

        uint8_t* pEndFileContents = i_pFileContents + i_sizeFileContents;
        const char* i_pNextName = reinterpret_cast<const char*>(i_pFileContents);
        size_t length = 0;
        while ((i_pFileContents < pEndFileContents) && *i_pFileContents++ != EOF) length++;
        string source(i_pNextName, length);

        json entities = json::parse(source);
        assert(entities.contains("list") && entities["list"].is_array());

        for (auto& entity : entities["list"]) {
            AddNewEntity(entity);
        }



        //{
        //    size_t PathLength = 0;
        //    const char* i_pNextName = reinterpret_cast<const char*>(i_pFileContents);

        //    while ((i_pFileContents < pEndFileContents) && *i_pFileContents++ != '\n')
        //        PathLength++;

        //    if (PathLength)
        //    {
        //        std::string Path(i_pNextName, PathLength);
        //        SmartPtr<Entity> Master(new Entity(nullptr, Path.c_str(), false));
        //        AddNewEntity(Master);
        //    }
        //}
    }

    void PrintFileByJobSys(const char* filePath) {
        using namespace std::placeholders;
        JobSystem::JobStatus status;
        Helper::ProcessFile ProcessFileInstance(filePath, std::bind(Helper::PrintFileContents, _1, _2), JobSystem::GetDefaultQueue(), &status);
        JobSystem::RunJob(JobSystem::GetDefaultQueue(), std::bind(ProcessFileInstance), &status);
        status.WaitForZeroJobsLeft();
        DEBUG_PRINT("PrintFile finished running.");
    }

    void LoadEntitiesFromFile(Game* game, const char* filePath)
    {

        using namespace std::placeholders;
        JobSystem::JobStatus status;
        const char* CustomQueueName = "EntityLoader";
        HashedString QueueName = JobSystem::CreateQueue(CustomQueueName, 1);
        Helper::ProcessFile ProcessFileInstance(filePath, std::bind(CreateEntities, _1, _2), QueueName, &status);
        JobSystem::RunJob(QueueName, std::bind(ProcessFileInstance), &status);
        do
        {
            CheckForNewEntities(game);
            Sleep(10);
        } while (JobSystem::HasJobs(CustomQueueName));
        CheckForNewEntities(game);
        DEBUG_PRINT("LoadEntites finished running.");
    }

    void Initialization(HINSTANCE i_hInstance, int i_nCmdShow, Game* game) {
        cout << "Engine Init..." << endl;
        DEBUG_PRINT("Testing Vector4...");
        bool vector4UnitTestResult = Vector4::UnitTest();
        DEBUG_PRINT(vector4UnitTestResult ? "Result: Pass!" : "Result: Not Pass...");

        //Init GLib
        bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, game->GetGameName(), -1, game->windowWidth, game->windowHeight, true);

        if (bSuccess) {
            //Bind Keyboard CallBack
            GLib::SetKeyStateChangeCallback(game->KeyCallBack);

            //Load Entities From File
            JobSystem::Init();
            //PrintFileByJobSys("data\\Entities.json");
            LoadEntitiesFromFile(game, "data\\Entities.json");

            //Initialize Custom Game Logic
            game->OnInit();

            auto RenderList = vector<WeakPtr<Renderer::Component>>();
            Renderer::BuildListFromNodeTree(game->sceneRoot, RenderList);

            auto RigidBodies = vector<WeakPtr<Physics::Component>>();
            Physics::BuildListFromNodeTree(game->sceneRoot, RigidBodies);

            bool bQuit = false;

            //Main Game Loop
            do {
                GLib::Service(bQuit);

                if (!bQuit) {
                    //Calculate Frame Time
                    float dt = Timing::GetLastFrameTime_ms();
                    
                    //Update Custom Game Logic
                    game->OnUpdate(dt);

                    //Calculate all Physics
                    Physics::UpdateAll(dt, RigidBodies);

                    //Render all Sprites
                    GLib::BeginRendering(DirectX::Colors::Blue);
                    GLib::Sprites::BeginRendering();
                    
                    //Custom Render Logic
                    game->OnBeforeRender();
                    //Render All Valid Render Components
                    Renderer::RenderAll(RenderList);

                    GLib::Sprites::EndRendering();
                    GLib::EndRendering();
                }

            } while (bQuit == false);

            //Custom Game Logic on Game Ends
            game->OnDestroy();

            //delete game instance
            delete game;
            
            //Kill GLib
            GLib::Shutdown();

            //Kill JobSystem
            JobSystem::RequestShutdown();
        }
    }
}