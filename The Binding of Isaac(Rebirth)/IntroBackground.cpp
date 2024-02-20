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
	FilePath.MoveParent();
	FilePath.Move("Res");
	FilePath.Move("IntroLevel");
	AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);
	
	StartIter = AllFileList.begin();
	EndIter = AllFileList.end();

	intro = CreateImageRenderer(0);
	intro->SetTransform({ HalfScale, {960, 540} });

	UEngineFile& File = (*StartIter);
	UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	intro->SetImage(File.GetFileName());
	++StartIter;
}

void AIntroBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	if (StartIter == EndIter)
	{
		GEngine->ChangeLevel("TitleLevel");
	}
	
	Time += _DeltaTime;
	if (Time >= 0.06f)
	{
		UEngineFile& File = (*StartIter);
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
		intro->SetImage(File.GetFileName());
		++StartIter;
		Time = 0.0f;
	}
}
