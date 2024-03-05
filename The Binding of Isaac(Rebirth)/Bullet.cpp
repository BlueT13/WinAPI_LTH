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
	{
		UImageRenderer* BulletRenderer = CreateImageRenderer(IsaacRenderOrder::Bullet);
		BulletRenderer->SetImage("Tears.png", 6);
		BulletRenderer->SetTransform({ {0,-28}, RendererSize });
		Destroy(0.8f);
	}

	{
		BulletCollision = CreateCollision(IsaacCollisionOrder::Bullet);
		BulletCollision->SetPosition({ 0, -28 });
		BulletCollision->SetScale({ 30,30 });
		BulletCollision->SetColType(ECollisionType::CirCle);
	}
}

void ABullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AddActorLocation(Dir * Speed * _DeltaTime);
}

