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
	ColRenderer = CreateImageRenderer(IsaacRenderOrder::Map);
	ColRenderer->SetActive(false);

	SetMapImage("Map_01.png");
	SetColMapImage("Map_col.png");
}

void AMap::SetMapImage(std::string_view _MapImageName)
{
	Renderer->SetImage(_MapImageName);
	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();
	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void AMap::SetColMapImage(std::string_view _MapImageName)
{
	ColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = ColRenderer->GetImage();
	UContentsHelper::ColMapImage = Image;
	FVector ImageScale = Image->GetScale();
	ColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void AMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}

void AMap::SwitchDebug()
{
	if (true == Renderer->IsActive())
	{
		Renderer->SetActive(false);
		ColRenderer->SetActive(true);
	}
	else
	{
		Renderer->SetActive(true);
		ColRenderer->SetActive(false);
	}

}