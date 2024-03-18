#include "HpUI.h"
#include "Player.h"
#include "ContentsHelper.h"

UImageRenderer* AHpUI::HpUI;

AHpUI::AHpUI()
{
}

AHpUI::~AHpUI()
{
}

void AHpUI::BeginPlay()
{
	AActor::BeginPlay();

	HpUI = CreateImageRenderer(IsaacRenderOrder::UI);
	HpUI->CameraEffectOff();
	HpUI->SetImage("hp6.png");
	HpUI->AutoImageScale();
	HpUI->SetPosition({ 160,40 });
}

void AHpUI::Tick(float _DeltaTime)
{
	switch (APlayer::PlayerHp)
	{
	case 0:
		HpUI->SetImage("hp0.png");
		break;
	case 1:
		HpUI->SetImage("hp1.png");
		break;
	case 2:
		HpUI->SetImage("hp2.png");
		break;
	case 3:
		HpUI->SetImage("hp3.png");
		break;
	case 4:
		HpUI->SetImage("hp4.png");
		break;
	case 5:
		HpUI->SetImage("hp5.png");
		break;
	case 6:
		HpUI->SetImage("hp6.png");
		break;
	default:
		break;
	}
}