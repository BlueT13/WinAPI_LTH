#include "StartImage.h"
#include "IsaacCore.h"
#include "ContentsHelper.h"

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

	UImageRenderer* Background = CreateImageRenderer(IsaacRenderOrder::Background);
	Background->SetImage("start");
	Background->AutoImageScale();
	Background->SetPosition(HalfScale);
	Background->CreateAnimation("StartAnimation", "start", 0, 1, 0.2f, true);
	Background->ChangeAnimation("StartAnimation");

}

void AStartImage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

