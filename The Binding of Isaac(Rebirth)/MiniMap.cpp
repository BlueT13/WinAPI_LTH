#include "MiniMap.h"
#include "IsaacCore.h"
#include "ContentsHelper.h"

UImageRenderer* AMiniMap::MiniMapS = nullptr;
UImageRenderer* AMiniMap::MiniMapL = nullptr;

AMiniMap::AMiniMap()
{
}

AMiniMap::~AMiniMap()
{
}

void AMiniMap::BeginPlay()
{
	AActor::BeginPlay();

	MiniMapS = CreateImageRenderer(IsaacRenderOrder::UI);
	MiniMapS->CameraEffectOff();
	MiniMapS->SetImage("MiniMap_Small.png");
	MiniMapS->AutoImageScale();
	MiniMapS->SetPosition({ 850,80 });
	MiniMapS->SetActive(true);

	MiniMapL = CreateImageRenderer(IsaacRenderOrder::UI);
	MiniMapL->CameraEffectOff();
	MiniMapL->SetImage("MiniMap_Large.png");
	MiniMapL->AutoImageScale();
	MiniMapL->SetPosition({ 795,129 });
	MiniMapL->SetActive(false);
}

void AMiniMap::Tick(float _DeltaTime)
{
}
