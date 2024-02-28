#include "PlayLevel.h"
#include "Player.h"
#include "Map.h"
#include "Fly.h"
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
	FilePath.MoveToSearchChild("Res");
	FilePath.Move("PlayLevel");
	std::list<UEngineFile> AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}
	UEngineResourcesManager::GetInst().CuttingImage("Head.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Body.png", 5, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Tears.png", 5, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Fly.png", 5, 3);

	SpawnActor<APlayer>();
	SpawnActor<AMap>();
	SpawnActor<AFly>();
}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->ChangeLevel("TitleLevel");
	}
}
