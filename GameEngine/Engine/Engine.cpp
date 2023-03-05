#pragma once
#include <iostream>
#include <assert.h>
#include <DirectXColors.h>
#include "Engine.h"
#include "Timing.h"
#include "Renderer.h"
#include "Physics.h"
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
    void Initialization(HINSTANCE i_hInstance, int i_nCmdShow, Game* game) {
        cout << "Engine Init" << endl;
        Point2DUnitTest();

        //Init GLib
        bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, game->GetGameName(), -1, game->windowWidth, game->windowHeight, true);

        if (bSuccess) {
            //Bind Keyboard CallBack
            GLib::SetKeyStateChangeCallback(game->KeyCallBack);

            //Initialize Custom Game Logic
            game->OnInit();

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
                    Physics::UpdateNodeTree(game->sceneRoot, dt);

                    //Render all Sprites
                    GLib::BeginRendering(DirectX::Colors::Blue);
                    GLib::Sprites::BeginRendering();
                    
                    //Custom Render Logic
                    game->OnBeforeRender();
                    //Default Render All nodes on node tree.
                    Renderer::RenderNodeTree(game->sceneRoot);

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
        }
    }
}