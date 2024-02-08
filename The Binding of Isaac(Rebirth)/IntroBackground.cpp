#include "IntroBackground.h"

AIntroBackground::AIntroBackground()
{
}

AIntroBackground::~AIntroBackground()
{
}

void AIntroBackground::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Background = CreateImageRenderer(0);
	Background->SetImage("intro_bg.png");
	UWindowImage* Image = Background->GetImage();
	FVector BackgroundScale = Image->GetScale();
	Background->SetTransform({ BackgroundScale.Half2D(), BackgroundScale });

	UImageRenderer* intro_1 = CreateImageRenderer(1);
	intro_1->SetImage("intro_1.png");
	intro_1->SetTransform({ {480,270}, {512, 512} });
	intro_1->CreateAnimation("intro_1", "intro_1.png", 0, 1, 0.1f, true);
	intro_1->SetActive(true, 1.0f);
	intro_1->Destroy(2.0f);

	intro_1->ChangeAnimation("intro_1");
}

void AIntroBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}