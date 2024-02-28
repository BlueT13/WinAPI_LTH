#include "Map.h"
#include "ContentsHelper.h"
//#include <EngineCore\EngineResourcesManager.h>

AMap::AMap()
{
}

AMap::~AMap()
{
}

void AMap::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(IsaacRenderOrder::Map);
	Renderer->SetImage("Map_01.png");
	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();
	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void AMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
