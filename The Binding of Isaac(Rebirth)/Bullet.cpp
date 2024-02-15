#include "Bullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}


void ABullet::BeginPlay()
{
	UImageRenderer* Renderer = CreateImageRenderer(1);
	Renderer->SetImage("Tears.png");
	Renderer->SetTransform({ {0,0}, {30, 30} });
	Renderer->SetImageCuttingTransform({ {0,0}, {26, 25} });
	Destroy(2.0f);
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
}

