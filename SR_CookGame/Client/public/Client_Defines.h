#pragma once

enum LEVEL { LEVEL_STATIC, LEVEL_LOGO, LEVEL_LOADING, LEVEL_GAMEPLAY0, LEVEL_CLEAR, LEVEL_GAMEOVER, LEVEL_END };

const unsigned short		g_nWinCX = 1280;
const unsigned short		g_nWinCY = 720;

extern HINSTANCE g_hInst;
extern HWND g_hWnd;

namespace Client {}

using namespace Client;

#define TRASH 5
