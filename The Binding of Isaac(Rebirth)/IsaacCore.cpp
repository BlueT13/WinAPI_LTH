#include "IsaacCore.h"
#include "Player.h"
#include "TitleLevel.h"

IsaacCore::IsaacCore()
{
}

IsaacCore::~IsaacCore()
{
}

// 게임시작
void IsaacCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("TitleLevel");

	ChangeLevel("TitleLevel");
}

void IsaacCore::Tick(float _DeltaTime)
{
}

void IsaacCore::End()
{
}