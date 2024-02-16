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

	intro = CreateImageRenderer(0);
	
	intro->SetImage("intro");
	intro->SetTransform({ HalfScale, {960, 540} });
	
	int count = 0;
	for (int i = 0; i < 10; i += 2)
	{
		std::string AnimationName = "IntroAnimation_" + std::to_string(count);

		std::vector<int> Index;

		for (size_t j = 0; j < 10; j++)
		{
			Index.push_back(i);
			Index.push_back(i + 1);
		}

		intro->CreateAnimation(AnimationName, "intro", Index, 0.1f, false);
		count++;
	}


	
	intro->ChangeAnimation("IntroAnimation_" + std::to_string(CurAniCount));


	/*intro->ChangeAnimation("IntroAnimation_1");
	intro->SetActive(true, 2.0f);
	intro->Destroy(4.0f);*/
}

void AIntroBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (intro->IsCurAnimationEnd())
	{
		intro->ChangeAnimation("IntroAnimation_" + std::to_string(++CurAniCount));
	}
}
