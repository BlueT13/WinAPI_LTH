#include "IntroImage.h"
#include "IsaacCore.h"

AIntroImage::AIntroImage()
{
}

AIntroImage::~AIntroImage()
{
}

void AIntroImage::BeginPlay()
{
	AActor::BeginPlay();

	FVector HalfScale = GEngine->MainWindow.GetWindowScale().Half2D();

	UImageRenderer* Background = CreateImageRenderer(0);
	Background->SetImage("intro");
	Background->SetTransform({ HalfScale, { 960,540 } });
	Background->CreateAnimation("Intro_0", "intro", 0, 1, 0.1f, false);
	Background->ChangeAnimation("Intro_0");
}

void AIntroImage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}