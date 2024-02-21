#include "PlayLevel.h"
#include "Player.h"
#include "Map.h"
#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory FilePath;
	FilePath.MoveParent();
	FilePath.Move("Res");
	FilePath.Move("PlayLevel");
	std::list<UEngineFile> AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	SpawnActor<APlayer>();
	SpawnActor<AMap>();
	
}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->ChangeLevel("TitleLevel");
	}
}
