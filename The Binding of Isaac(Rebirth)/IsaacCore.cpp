#include "IsaacCore.h"
#include "Player.h"
#include "IntroLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include <EnginePlatform/EngineSound.h>

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

	SetFrame(60);
	UEngineSound::SetGlobalVolume(1.0f);

	MainWindow.SetWindowScale(WindowSize);
	MainWindow.SetWindowPosition({ 0, 0 });

	CreateLevel<UIntroLevel>("IntroLevel");
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("IntroLevel");
}

void UIsaacCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}