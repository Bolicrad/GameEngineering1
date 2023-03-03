// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <Windows.h>
#include "MonsterChase.h"

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
    MonsterChase* myGame = new MonsterChase(900,900);

    Engine::Initialization(i_hInstance, i_nCmdShow, myGame);

#if defined _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG

}