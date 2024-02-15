#include "Map.h"

Map::Map() 
{
}

Map::~Map() 
{
}

void Map::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Background = CreateImageRenderer(0);
	Background->SetImage("01_map.png");
	UWindowImage* Image = Background->GetImage();
	FVector BackgroundScale = Image->GetScale();
	Background->SetTransform({ BackgroundScale.Half2D(), BackgroundScale });

}

void Map::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

