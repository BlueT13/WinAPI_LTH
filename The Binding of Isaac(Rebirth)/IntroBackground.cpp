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

	CurIter = AllFileList.begin();

	intro = CreateImageRenderer(0);
	intro->SetTransform({ HalfScale, GEngine->MainWindow.GetWindowScale() });

	UEngineResourcesManager::GetInst().LoadImg((*CurIter).GetFullPath());
	intro->SetImage((*CurIter).GetFileName());
	++CurIter;
}

void AIntroBackground::Tick(float _DeltaTime)
{
	Time += _DeltaTime;

	if (UEngineInput::IsDown(VK_SPACE))
	{
		AllFileList.clear();
		GEngine->ChangeLevel("TitleLevel");
		return;
	}

	if (CurIter == AllFileList.end())
	{
		AllFileList.clear();
		GEngine->ChangeLevel("TitleLevel");
		return;
	}

	if (Time >= AnimationDurationTime)
	{
		UEngineResourcesManager::GetInst().UnloadImg(intro->GetImage()->GetName());
		UEngineResourcesManager::GetInst().LoadImg((*CurIter).GetFullPath());
		intro->SetImage((*CurIter).GetFileName());
		++CurIter;
		Time -= AnimationDurationTime;
	}
}