#pragma once
#include <Windows.h>
#include <assert.h>

namespace EngineDebug
{
	#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	#define MsgBoxAssert(TEXT) MessageBoxA(nullptr, TEXT, "ġ���� ����", MB_OK); assert(false);
}

