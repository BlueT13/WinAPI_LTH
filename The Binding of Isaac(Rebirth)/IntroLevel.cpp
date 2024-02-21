#include "IntroLevel.h"
#include "IntroBackground.h"
#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineResourcesManager.h>

UIntroLevel::UIntroLevel()
{
}

UIntroLevel::~UIntroLevel()
{
}

void UIntroLevel::BeginPlay()
{
	ULevel::BeginPlay();

	AIntroBackground* Background = SpawnActor<AIntroBackground>();
}

void UIntroLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->MainWindow.Off();
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		GEngine->ChangeLevel("TitleLevel");
	}
}