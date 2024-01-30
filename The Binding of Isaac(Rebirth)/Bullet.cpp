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
	UImageRenderer* Renderer = CreateImageRenderer(-10);
	Renderer->SetImageToScale("Tears.png");

	Destroy(2.0f);
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
}

