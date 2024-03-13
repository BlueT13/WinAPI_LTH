#include "UIManager.h"
#include "IsaacCore.h"
#include "ContentsHelper.h"

UImageRenderer* UIManager::DeathPortrait = nullptr;
UImageRenderer* UIManager::PauseScreen = nullptr;

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::BeginPlay()
{
	AActor::BeginPlay();

	FVector HalfScale = GEngine->MainWindow.GetWindowScale().Half2D();

	UIManager::DeathPortrait = CreateImageRenderer(IsaacRenderOrder::UI);
	DeathPortrait->CameraEffectOff();
	DeathPortrait->SetImage("DeathPortrait.png");
	DeathPortrait->AutoImageScale();
	DeathPortrait->SetPosition(HalfScale);
	DeathPortrait->SetActive(false);

	PauseScreen = CreateImageRenderer(IsaacRenderOrder::UI);
	PauseScreen->CameraEffectOff();
	PauseScreen->SetImage("PauseScreen.png");
	PauseScreen->AutoImageScale();
	PauseScreen->SetPosition(HalfScale);
	PauseScreen->SetActive(false);
}

void UIManager::Tick(float _DeltaTime)
{
}

