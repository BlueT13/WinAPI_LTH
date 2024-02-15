#include "StartImage.h"
#include "IsaacCore.h"

AStartImage::AStartImage() 
{
}

AStartImage::~AStartImage() 
{
}

void AStartImage::BeginPlay()
{
	AActor::BeginPlay();

	FVector HalfScale = GEngine->MainWindow.GetWindowScale().Half2D();

	UImageRenderer* Background = CreateImageRenderer(0);
	Background->SetImage("start");
	UWindowImage* Image = Background->GetImage();
	FVector BackgroundScale = Image->GetScale();
	Background->SetTransform({ BackgroundScale.Half2D(), BackgroundScale });
	Background->CreateAnimation("StartAnimation", "start", 0, 1, 0.2f, true);
	Background->ChangeAnimation("StartAnimation");
	
}

void AStartImage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

