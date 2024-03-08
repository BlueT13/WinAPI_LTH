#include "Fly.h"
#include "Bullet.h"

AFly::AFly()
{
}

AFly::~AFly()
{
}

void AFly::BeginPlay()
{
	AMonster::BeginPlay();

	MonsterHp = 2.0f;
	MonsterMoveSpeed = 50.f;

	SpawnRenderer = CreateImageRenderer(IsaacRenderOrder::SpawnEffect);
	SpawnRenderer->SetImage("SpawnEffect_Small.png");
	SpawnRenderer->AutoImageScale();
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Small.png", 0, 14, 0.03f, false);

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("Fly.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("Move", "Fly.png", 0, 3, 0.05f, true);
	//MonsterRenderer->CreateAnimation("GetHit", "Fly.png", 0, 3, 0.05f, true);
	MonsterRenderer->CreateAnimation("Die", "Fly.png", 4, 14, 0.03f, true);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 30, 30 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

	if (IsActive())
	{
		SpawnRenderer->ChangeAnimation("Spawn");
	}
}

void AFly::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal 받아온다.
	// MonsterStateUpdate(_DeltaTime);을 실행
	if (SpawnRenderer->IsCurAnimationEnd())
	{
		SpawnRenderer->Destroy();
	}
}

void AFly::MonsterStateUpdate(float _DeltaTime)
{
	switch (MonsterState)
	{
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::GetHit:
		GetHit(_DeltaTime);
		break;
	case EMonsterState::Die:
		Die(_DeltaTime);
		break;
	default:
		break;
	}
}

void AFly::Move(float _DeltaTime)
{
	AddActorLocation(MonsterToPlayerDirNormal * _DeltaTime * MonsterMoveSpeed);
}

void AFly::GetHit(float _DeltaTime)
{
	MonsterHp -= 1.0f;

	// 뒤로 밀려나야 함
	//

	if (MonsterHp <= 0.0f)
	{
		MonsterStateChange(EMonsterState::Die);
	}
	else
	{
		MonsterStateChange(EMonsterState::Move);
	}
}

void AFly::Die(float _DeltaTime)
{
	MonsterCollision->SetActive(false);
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void AFly::MonsterStateChange(EMonsterState _State)
{
	if (MonsterState != _State)
	{
		switch (_State)
		{
		case EMonsterState::Move:
			MoveStart();
			break;
		case EMonsterState::GetHit:
			GetHitStart();
			break;
		case EMonsterState::Die:
			DieStart();
			break;
		default:
			break;
		}
	}
	MonsterState = _State;
}

void AFly::MoveStart()
{
	MonsterRenderer->ChangeAnimation("Move");
}

void AFly::GetHitStart()
{
	//MonsterRenderer->ChangeAnimation("GetHit");
}

void AFly::DieStart()
{
	MonsterRenderer->ChangeAnimation("Die");
}
