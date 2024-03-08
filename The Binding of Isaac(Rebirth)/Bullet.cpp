#include "Bullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include "ContentsHelper.h"
#include "PlayLevel.h"
#include "Monster.h"

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
	BulletRenderer->CreateAnimation("DestroyBullet", "DestroyTear.png", 0, 13, 0.03f, true);

	BulletCollision = CreateCollision(IsaacCollisionOrder::Bullet);
	BulletCollision->SetPosition({ 0, -28 });
	BulletCollision->SetScale({ 20, 20 });
	BulletCollision->SetColType(ECollisionType::CirCle);

	BulletStateChange(EBulletState::Move);
}

void ABullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == BulletCollision->CollisionCheck(IsaacCollisionOrder::Monster, Result))
	{
		UCollision* Collision = Result[0];
		AActor* MonsterPtr = Collision->GetOwner();
		AMonster* Monster = dynamic_cast<AMonster*>(MonsterPtr);

		Monster->MonsterStateChange(EMonsterState::GetHit);
		
		BulletStateChange(EBulletState::Crashed);
	}
	
	BulletStateUpdate(_DeltaTime);

	BulletLiveTime += _DeltaTime;
}

void ABullet::IsCrashed()
{
	UPlayLevel* Level = dynamic_cast<UPlayLevel*>(GetWorld());
	FVector CurRoomPos = Level->GetCurRoom()->GetActorLocation();
	FVector BulletPos = GetActorLocation();
	if (BulletPos.X < CurRoomPos.X - 330)
	{
		IsDestroy = true;
	}
	if (BulletPos.Y < CurRoomPos.Y - 180)
	{
		IsDestroy = true;
	}
	if (BulletPos.X > CurRoomPos.X + 330)
	{
		IsDestroy = true;
	}
	if (BulletPos.Y > CurRoomPos.Y + 230)
	{
		IsDestroy = true;
	}

	if (BulletDestroyTime < BulletLiveTime)
	{
		IsDestroy = true;
	}
}

void ABullet::BulletStateUpdate(float _DeltaTime)
{
	switch (BulletState)
	{
	case EBulletState::Move:
		BulletMove(_DeltaTime);
		break;
	case EBulletState::Crashed:
		BulletCrashed(_DeltaTime);
		break;
	}
}

void ABullet::BulletMove(float _DeltaTime)
{
	IsCrashed();
	if (IsDestroy)
	{
		BulletStateChange(EBulletState::Crashed);
	}

	AddActorLocation(Dir * Speed * _DeltaTime);
}

void ABullet::BulletCrashed(float _DeltaTime)
{
	Speed = 0.0f;
	BulletRenderer->ChangeAnimation("DestroyBullet");
	BulletCollision->SetActive(false);
	if (BulletRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void ABullet::BulletStateChange(EBulletState _State)
{
	BulletState = _State;
}
