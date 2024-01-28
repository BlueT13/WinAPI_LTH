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
	{
		UImageRenderer* Renderer = CreateImageRenderer(0);
		Renderer->SetScale({ 10, 50 });
	}

	{
		UImageRenderer* Renderer = CreateImageRenderer(0);
		Renderer->SetScale({ 50, 10 });
	}

	Destroy(2.0f);
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}

