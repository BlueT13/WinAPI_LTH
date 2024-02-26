#include "IntroBackground.h"
#include "IsaacCore.h"
#include <iostream>
#include <string>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineResourcesManager.h>

AIntroBackground::AIntroBackground()
{
}

AIntroBackground::~AIntroBackground()
{
}

void AIntroBackground::BeginPlay()
{
	AActor::BeginPlay();

	FVector HalfScale = GEngine->MainWindow.GetWindowScale().Half2D();

	UEngineDirectory FilePath;
	FilePath.MoveToSearchChild("Res");
	FilePath.Move("IntroLevel");
	AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);

	StartIter = AllFileList.begin();
	EndIter = AllFileList.end();

	intro = CreateImageRenderer(0);
	intro->SetTransform({ HalfScale, GEngine->MainWindow.GetWindowScale() });

	UEngineFile& File = (*StartIter);
	FileName = File.GetFileName();
	UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	intro->SetImage(FileName);
	++StartIter;
}

void AIntroBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_SPACE))
	{
		AllFileList.clear();
		GEngine->ChangeLevel("TitleLevel");
		return;
	}

	if (StartIter == EndIter)
	{
		AllFileList.clear();
		GEngine->ChangeLevel("TitleLevel");
		return;
	}

	Time += _DeltaTime;
	if (Time >= FrameTime)
	{

		UEngineFile& File = (*StartIter);
		UEngineResourcesManager::GetInst().UnloadImg(FileName);
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
		FileName = File.GetFileName();
		intro->SetImage(FileName);
		++StartIter;
		Time = _DeltaTime - FrameTime;
	}
}