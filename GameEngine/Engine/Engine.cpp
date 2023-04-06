#pragma once
#include <iostream>
#include <assert.h>
#include <DirectXColors.h>
#include "Engine.h"
#include "Timing.h"
#include "Renderer.h"
#include "Physics.h"
#include "Syncronization/Mutex.h"
#include "Syncronization/ScopeLock.h"
using namespace std;

void Point2DUnitTest() {
    const Point2D<int> A(0, 1);
    const Point2D<int> B(2, 3);
    // equality
    bool bEqual = A == B;
    assert(bEqual == false);
    bEqual = B == Point2D<int>(2, 3);
    assert(bEqual == true);
    // Inequality
    bool bNotEqual = A != B;
    assert(bNotEqual == true);
    bNotEqual = B != Point2D<int>(2, 3);
    assert(bNotEqual == false);
    // Point2D + Point2D
    Point2D<int> C = A + B;
    assert(C == Point2D<int>(2, 4));
    // Point2D - Point2D
    C = B - A;
    assert(C == Point2D<int>(2, 2));

    // Point2D * int
    C = A * 2;
    assert(C == Point2D<int>(0, 2));
    // Point2D / int
    C = Point2D<int>(6, 4) / 2;
    assert(C == Point2D<int>(3, 2));
    // int * Point2D
    C = 2 * B;
    assert(C == Point2D<int>(4, 6));
    // negate
    C = -B;
    assert(C == Point2D<int>(-2, -3));
    //direct assignment
    C = B;
    assert(C == Point2D<int>(2, 3));
    // Point2D += Point2D
    C += Point2D<int>(2, 1);
    assert(C == Point2D<int>(4, 4));
    // Point2D -= Point2d
    C -= Point2D<int>(2, 1);
    assert(C == Point2D<int>(2, 3));
    // Point2D *= int
    C *= 2;
    assert(C == Point2D<int>(4, 6));
    // Point2D /= int
    C /= 2;
    assert(C == Point2D<int>(2, 3));
    cout << "Point2D class unit test pass" << endl;
}

namespace Engine {

    Mutex NewEntityMutex;
    vector<SmartPtr<Entity>> NewEntities;
    // This adds a new GameObject to NewGameObjects
    void AddNewEntity(SmartPtr<Entity> i_pEntity)
    {
        if (i_pEntity)
        {
            // Acquire a scoped lock on the mutex
            Engine::ScopeLock Lock(NewEntityMutex);

            NewEntities.push_back(i_pEntity);
        }
    }

    void CheckForNewEntities(SmartPtr<Entity>& root)
    {
        Engine::ScopeLock Lock(NewEntityMutex);

        if (!NewEntities.empty())
        {
            for (SmartPtr<Entity> p : NewEntities)
            {
                if (p)
                {
                    p->SetParent(&*root);
                    p->Pos = Point2D<float>((float)(rand() % 11 - 5), (float)(rand() % 11 - 5));
                }
            }
            NewEntities.clear();
        }
    }


    void CreateEntities(uint8_t* i_pFileContents, size_t i_sizeFileContents)
    {
        assert(i_pFileContents && i_sizeFileContents);

        uint8_t* pEndFileContents = i_pFileContents + i_sizeFileContents;

        while (i_pFileContents < pEndFileContents)
        {
            size_t PathLength = 0;
            const char* i_pNextName = reinterpret_cast<const char*>(i_pFileContents);

            while ((i_pFileContents < pEndFileContents) && *i_pFileContents++ != '\n')
                PathLength++;

            if (PathLength)
            {
                std::string Path(i_pNextName, PathLength);
                SmartPtr<Entity> Master(new Entity(nullptr, Path.c_str(), false));
                AddNewEntity(Master);
            }
            //i_pFileContents++;
        }
    }

    void PrintFileByJobSys(const char* filePath) {
        using namespace std::placeholders;
        JobSystem::JobStatus status;
        Helper::ProcessFile ProcessFileInstance(filePath, std::bind(Helper::PrintFileContents, _1, _2), JobSystem::GetDefaultQueue(), &status);
        JobSystem::RunJob(JobSystem::GetDefaultQueue(), std::bind(ProcessFileInstance), &status);
        status.WaitForZeroJobsLeft();
        DEBUG_PRINT("PrintFile finished running.");
    }

    void LoadEntitiesFromFile(SmartPtr<Entity>& root, const char* filePath)
    {

        using namespace std::placeholders;
        JobSystem::JobStatus status;
        const char* CustomQueueName = "EntityLoader";
        HashedString QueueName = JobSystem::CreateQueue(CustomQueueName, 1);
        Helper::ProcessFile ProcessFileInstance(filePath, std::bind(CreateEntities, _1, _2), QueueName, &status);
        JobSystem::RunJob(QueueName, std::bind(ProcessFileInstance), &status);
        do
        {
            CheckForNewEntities(root);
            Sleep(10);
        } while (JobSystem::HasJobs(CustomQueueName));
        CheckForNewEntities(root);
        DEBUG_PRINT("LoadEntites finished running.");
    }

    void Initialization(HINSTANCE i_hInstance, int i_nCmdShow, Game* game) {
        cout << "Engine Init" << endl;
        Point2DUnitTest();

        //Init GLib
        bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, game->GetGameName(), -1, game->windowWidth, game->windowHeight, true);

        if (bSuccess) {
            //Bind Keyboard CallBack
            GLib::SetKeyStateChangeCallback(game->KeyCallBack);

            //Load Entities From File
            JobSystem::Init();
            //PrintFileByJobSys("Entities.txt");
            LoadEntitiesFromFile(game->sceneRoot, "Entities.txt");

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