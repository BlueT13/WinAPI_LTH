#include "IsaacCore.h"
#include "Player.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

UIsaacCore::UIsaacCore()
{
}

UIsaacCore::~UIsaacCore()
{
}

// 게임시작
void UIsaacCore::BeginPlay()
{
	MainWindow.SetWindowScale({ 1280, 720 });

	UEngineCore::BeginPlay();

	SetFrame(60);

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void UIsaacCore::Tick(float _DeltaTime)
{
}

void UIsaacCore::End()
{
}