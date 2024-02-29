#include "IsaacCore.h"
#include "Player.h"
#include "IntroLevel.h"
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
	UEngineCore::BeginPlay();

	MainWindow.SetWindowScale(WindowSize);
	MainWindow.SetWindowPosition({ 0, 0 });

	CreateLevel<UIntroLevel>("IntroLevel");
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void UIsaacCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}