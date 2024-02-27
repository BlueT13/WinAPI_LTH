#include "Bullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include "ContentsHelper.h"

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}


void ABullet::BeginPlay()
{
	UImageRenderer* Renderer = CreateImageRenderer(IsaacRenderOrder::Bullet);
	Renderer->SetImage("Tears.png");
	Renderer->SetTransform({ {0,-28}, {30, 30} });
	Renderer->SetImageCuttingTransform({ {0,0}, {26, 25} });
	Destroy(2.0f);
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
}

