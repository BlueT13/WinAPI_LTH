#include "IntroBackground.h"
#include "IsaacCore.h"
#include <iostream>
#include <string>
#include <EngineCore/EngineResourcesManager.h>
#include "IntroLevel.h"

bool AIntroBackground::IntroEnd = false;

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
	SoundFileList = FilePath.AllFile({ ".wav" }, true);
	for (UEngineFile& File : SoundFileList)
	{
		UEngineSound::Load(File.GetFullPath());
	}
	IntroSound = UEngineSound::SoundPlay("Intro.wav");

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
		IntroSound.Off();
		IntroEnd = true;
		GEngine->ChangeLevel("TitleLevel");
		return;
	}

	if (CurIter == AllFileList.end())
	{
		AllFileList.clear();
		IntroSound.Off();
		IntroEnd = true;
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