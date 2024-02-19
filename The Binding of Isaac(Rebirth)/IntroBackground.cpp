#include "IntroBackground.h"
#include "IsaacCore.h"
#include <iostream>
#include <string>

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

	intro_0 = CreateImageRenderer(0);
	intro_0->SetImage("intro");
	intro_0->SetTransform({ HalfScale, {960, 540} });
	for (int i = 0; i < 4; i += 2)
	{
		std::string AnimationName = "IntroAnimation_" + std::to_string(AniCount);
		std::vector<int> Index;
		for (size_t j = 0; j < 10; j++)
		{
			Index.push_back(i);
			Index.push_back(i + 1);
		}

		intro_0->CreateAnimation(AnimationName, "intro", Index, 0.1f, false);
		AniCount++;
	}

	fadeout = CreateImageRenderer(0);
	fadeout->SetImage("fadeout");
	fadeout->SetTransform({ HalfScale, {960, 540} });
	fadeout->CreateAnimation("Fade", "fadeout", 0, 15, 0.05f, false);

	intro_1 = CreateImageRenderer(0);
	intro_1->SetImage("intro");
	intro_1->SetTransform({ HalfScale, {960, 540} });
	for (int i = 4; i < TotalAniCount * 2; i += 2)
	{
		std::string AnimationName = "IntroAnimation_" + std::to_string(AniCount);
		std::vector<int> Index;
		for (size_t j = 0; j < 10; j++)
		{
			Index.push_back(i);
			Index.push_back(i + 1);
		}

		intro_1->CreateAnimation(AnimationName, "intro", Index, 0.1f, false);
		AniCount++;
	}

	intro_1->ChangeAnimation("IntroAnimation_" + std::to_string(CurAniCount));
}

void AIntroBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (intro_0->IsCurAnimationEnd())
	{
		if (CurAniCount == TotalAniCount - 1)
		{
			GEngine->ChangeLevel("TitleLevel");
		}
		else
		{
			CurAniCount++;
			intro_0->ChangeAnimation("IntroAnimation_" + std::to_string(CurAniCount));
		}
	}
}
