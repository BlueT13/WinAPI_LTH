#include "IntroLevel.h"
#include "IntroBackground.h"
#include "EngineCore/EngineCore.h"
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

	UEngineDirectory FilePath;

	FilePath.MoveParent();
	FilePath.Move("Res");
	FilePath.Move("IntroLevel");

	std::list<UEngineFile> AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	AIntroBackground* Background = SpawnActor<AIntroBackground>();



}
void UIntroLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (EngineInput::IsDown(VK_SPACE))
	{
		GEngine->ChangeLevel("TitleLevel");
	}

}

void UIntroLevel::LevelStart(ULevel* _Level)
{

}
void UIntroLevel::LevelEnd(ULevel* _Level)
{

}