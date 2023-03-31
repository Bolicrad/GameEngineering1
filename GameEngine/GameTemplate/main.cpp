// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <Windows.h>
#include "Engine.h"
#include "MyGame.h"

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
    MyGame* game = new MyGame();

    Engine::Initialization(i_hInstance, i_nCmdShow, game);

#if defined _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG

}