#include "IsaacCore.h"
#include "Isaac.h"
#include "TitleLevel.h"

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

	ChangeLevel("TitleLevel");
}

void IsaacCore::Tick(float _DeltaTime)
{
}

void IsaacCore::End()
{
}