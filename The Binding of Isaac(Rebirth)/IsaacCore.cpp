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
	
	MainWindow.SetWindowScale({ 960, 540 });
	MainWindow.SetWindowPosition({ 0, 0 });


	SetFrame(60);

	CreateLevel<UIntroLevel>("IntroLevel");
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("IntroLevel");
}

void UIsaacCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}