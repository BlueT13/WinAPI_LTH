#include "IsaacCore.h"
#include "Player.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

IsaacCore::IsaacCore()
{
}

IsaacCore::~IsaacCore()
{
}

// 게임시작
void IsaacCore::BeginPlay()
{
	SetFrame(60);

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void IsaacCore::Tick(float _DeltaTime)
{
}

void IsaacCore::End()
{
}