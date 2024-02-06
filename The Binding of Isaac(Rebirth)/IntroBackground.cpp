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

	UImageRenderer* Renderer = CreateImageRenderer();

	Renderer->SetImage("intro_bg.png");
	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();
	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });


}

void AIntroBackground::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}