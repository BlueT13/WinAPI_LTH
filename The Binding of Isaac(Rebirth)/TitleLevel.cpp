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
	FilePath.MoveParent();
	FilePath.Move("Res");
	FilePath.Move("TitleLevel");
	std::list<UEngineFile> AllFileList = FilePath.AllFile({ ".png",".bmp" }, true);
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}
	UEngineResourcesManager::GetInst().LoadFolder(FilePath.AppendPath("start"));

	AStartImage* StartImg = SpawnActor<AStartImage>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_SPACE))
	{
		GEngine->ChangeLevel("PlayLevel");
	}
}
