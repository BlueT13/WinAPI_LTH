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

// ���ӽ���
void IsaacCore::BeginPlay()
{
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