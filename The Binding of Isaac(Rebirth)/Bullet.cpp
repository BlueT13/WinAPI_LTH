#include "Bullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include "ContentsHelper.h"
#include "PlayLevel.h"

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}


void ABullet::BeginPlay()
{
	BulletRenderer = CreateImageRenderer(IsaacRenderOrder::Bullet);
	BulletRenderer->SetImage("Tears.png", 6);
	BulletRenderer->SetTransform({ {0,-28}, RendererSize });
	BulletRenderer->CreateAnimation("DestroyBullet", "DestroyTear.png", 0, 13, 0.05f, true);

	BulletCollision = CreateCollision(IsaacCollisionOrder::Bullet);
	BulletCollision->SetPosition({ 0, -28 });
	BulletCollision->SetScale({ 30,30 });
	BulletCollision->SetColType(ECollisionType::CirCle);
}

void ABullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AddActorLocation(Dir * Speed * _DeltaTime);

	BulletLiveTime += _DeltaTime;

	if (IsCrashed())
	{
		BulletRenderer->ChangeAnimation("DestroyBullet");
		Speed = 0.0f;
		if (BulletRenderer->IsCurAnimationEnd())
		{
			Destroy();
		}
	}
}

bool ABullet::IsCrashed()
{
	UPlayLevel* Level = dynamic_cast<UPlayLevel*>(GetWorld());
	FVector CurRoomPos = Level->GetCurRoom()->GetActorLocation();
	FVector BulletPos = GetActorLocation();
	if (BulletPos.X < CurRoomPos.X - 330)
	{
		return true;
	}
	if (BulletPos.Y < CurRoomPos.Y - 190)
	{
		return true;
	}
	if (BulletPos.X > CurRoomPos.X + 330)
	{
		return true;
	}
	if (BulletPos.Y > CurRoomPos.Y + 230)
	{
		return true;
	}

	if (BulletDestroyTime < BulletLiveTime)
	{
		return true;
	}

	return false;
}