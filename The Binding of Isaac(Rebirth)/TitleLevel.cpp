#include "TitleLevel.h"
#include "StartImage.h"
#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineResourcesManager.h>

UTitleLevel::UTitleLevel() 
{
}

UTitleLevel::~UTitleLevel() 
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory FilePath;
	FilePath.MoveToSearchChild("Res");
	FilePath.Move("TitleLevel");
	UEngineResourcesManager::GetInst().LoadFolder(FilePath.AppendPath("Start"));

	AStartImage* StartImg = SpawnActor<AStartImage>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_SPACE))
	{
		GEngine->ChangeLevel("PlayLevel");
	}
	if (UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->MainWindow.Off();
	}
}
