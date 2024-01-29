#include "PlayLevel.h"
#include "Player.h"
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
	UEngineDirectory FilePath;

	FilePath.MoveParent();
	FilePath.Move("Res");
	FilePath.Move("gfx");

	std::list<UEngineFile> AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);

	this->SpawnActor<Player>();
}