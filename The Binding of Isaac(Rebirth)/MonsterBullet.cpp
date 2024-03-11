#include "MonsterBullet.h"
#include "ContentsHelper.h"
#include "PlayLevel.h"

AMonsterBullet::AMonsterBullet()
{
}

AMonsterBullet::~AMonsterBullet()
{
}

void AMonsterBullet::BeginPlay()
{
	AActor::BeginPlay();

	MonsterBulletRenderer = CreateImageRenderer(IsaacRenderOrder::Bullet);
	MonsterBulletRenderer->SetImage("MonsterTear", 0);
	MonsterBulletRenderer->SetTransform({ {0,0}, RendererSize });
	MonsterBulletRenderer->CreateAnimation("DestroyMonsterBullet", "MonsterTear.png", 0, 13, 0.03f, true);

	MonsterBulletCollision = CreateCollision(IsaacCollisionOrder::Bullet);
	MonsterBulletCollision->SetPosition({ 0, -28 });
	MonsterBulletCollision->SetScale({ 20, 20 });
	MonsterBulletCollision->SetColType(ECollisionType::CirCle);

	MonsterBulletStateChange(EBulletState::Move);
}

void AMonsterBullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == MonsterBulletCollision->CollisionCheck(IsaacCollisionOrder::Player, Result))
	{
		Player = APlayer::GetMainPlayer();

		Player->HeadStateChange(EPlayerHeadState::GetHit);

		MonsterBulletStateChange(EBulletState::Crashed);
	}

	MonsterBulletStateUpdate(_DeltaTime);

	MonsterBulletLiveTime += _DeltaTime;
}

void AMonsterBullet::IsCrashed()
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

	if (MonsterBulletDestroyTime < MonsterBulletLiveTime)
	{
		IsDestroy = true;
	}
}

void AMonsterBullet::MonsterBulletStateUpdate(float _DeltaTime)
{
	switch (MonsterBulletState)
	{
	case EBulletState::Move:
		MonsterBulletMove(_DeltaTime);
		break;
	case EBulletState::Crashed:
		MonsterBulletCrashed(_DeltaTime);
		break;
	}
}

void AMonsterBullet::MonsterBulletMove(float _DeltaTime)
{
	IsCrashed();
	if (IsDestroy)
	{
		MonsterBulletStateChange(EBulletState::Crashed);
	}

	AddActorLocation(Dir * Speed * _DeltaTime);
}

void AMonsterBullet::MonsterBulletCrashed(float _DeltaTime)
{
	Speed = 0.0f;
	MonsterBulletRenderer->ChangeAnimation("DestroyMonsterBullet");
	MonsterBulletCollision->SetActive(false);
	if (MonsterBulletRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void AMonsterBullet::MonsterBulletStateChange(EBulletState _State)
{
	MonsterBulletState = _State;
}