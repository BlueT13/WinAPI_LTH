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

	int count = 0;
	/*intro0 = CreateImageRenderer(0);
	intro0->SetImage("intro0_");
	intro0->SetTransform({ HalfScale, {960, 540} });
	for (int i = 0; i < 4; i += 2)
	{
		std::string AnimationName = "Intro0_" + std::to_string(count);
		std::vector<int> Index;
		for (size_t j = 0; j < 10; j++)
		{
			Index.push_back(i);
			Index.push_back(i + 1);
		}
		intro0->CreateAnimation(AnimationName, "intro0_", Index, 0.1f, false);
		count++;
	}

	fadeout = CreateImageRenderer(0);
	fadeout->SetImage("fadeout");
	fadeout->SetTransform({ HalfScale, {960, 540} });
	fadeout->CreateAnimation("Fade", "fadeout", 0, 15, 0.1f, false);*/

	intro1 = CreateImageRenderer(0);
	intro1->SetImage("intro1_");
	intro1->SetTransform({ HalfScale, {960, 540} });
	count = 0;
	for (int i = 0; i < 5 * 2; i += 2)
	{
		std::string AnimationName = "Intro1_" + std::to_string(count);
		std::vector<int> Index;
		for (size_t j = 0; j < 10; j++)
		{
			Index.push_back(i);
			Index.push_back(i + 1);
		}
		intro1->CreateAnimation(AnimationName, "intro1_", Index, 0.1f, false);
		count++;
	}

	intro1->ChangeAnimation("Intro1_" + std::to_string(CurAniCount));
}

void AIntroBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//if (intro0->IsCurAnimationEnd())
	//{
	//	if (CurAniCount == 2)
	//	{
	//		GEngine->ChangeLevel("TitleLevel");
	//	}
	//	else
	//	{
	//		intro0->ChangeAnimation("Intro0_" + std::to_string(CurAniCount));
	//		CurAniCount++;
	//	}
	//}

	//if (fadeout->IsCurAnimationEnd())
	//{
	//	fadeout->ChangeAnimation("Intro1_" + std::to_string(CurAniCount));
	//}

	if (intro1->IsCurAnimationEnd())
	{
		if (CurAniCount == Intro1AniCount)
		{
			GEngine->ChangeLevel("TitleLevel");
		}
		else
		{
			intro1->ChangeAnimation("Intro1_" + std::to_string(CurAniCount));
			CurAniCount++;
		}
	}


}
