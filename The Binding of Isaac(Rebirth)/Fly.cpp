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

	MonsterHp = 2;
	MonsterMoveSpeed = 80.f;

	SpawnRenderer = CreateImageRenderer(IsaacRenderOrder::SpawnEffect);
	SpawnRenderer->SetImage("SpawnEffect_Small.png");
	SpawnRenderer->AutoImageScale();
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Small.png", 0, 14, 0.05f, false);

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("Fly.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("Move", "Fly.png", 0, 3, 0.05f, true);
	//MonsterRenderer->CreateAnimation("GetHit", "Fly.png", 0, 3, 0.05f, true);
	MonsterRenderer->CreateAnimation("Die", "Fly.png", 4, 14, 0.03f, false);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 30, 30 });
	MonsterCollision->SetColType(ECollisionType::CirCle);
}

void AFly::Tick(float _DeltaTime)
{
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal 받아온다.
	// MonsterStateUpdate(_DeltaTime), MonsterMoveUpdate(_DeltaTime)를 실행
	AMonster::Tick(_DeltaTime);
}

void AFly::MonsterStateUpdate(float _DeltaTime)
{
	switch (MonsterState)
	{
	case EMonsterState::Spawn:
		Spawn(_DeltaTime);
		break;
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::Die:
		Die(_DeltaTime);
		break;
	default:
		break;
	}
}

void AFly::Spawn(float _DeltaTime)
{
	MonsterCollision->SetActive(false);
	if (SpawnRenderer->IsCurAnimationEnd())
	{
		SpawnRenderer->Destroy();
		MonsterCollision->SetActive(true);
		MonsterStateChange(EMonsterState::Move);
	}
}

void AFly::Move(float _DeltaTime)
{
	MonsterMoveVector = MonsterToPlayerDirNormal * MonsterMoveSpeed;
}

void AFly::Die(float _DeltaTime)
{
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
		case EMonsterState::Spawn:
			SpawnStart();
			break;
		case EMonsterState::Move:
			MoveStart();
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

void AFly::SpawnStart()
{
	SpawnRenderer->ChangeAnimation("Spawn");
	MonsterRenderer->ChangeAnimation("Move");
}

void AFly::MoveStart()
{
	MonsterRenderer->ChangeAnimation("Move");
}

void AFly::DieStart()
{
	MonsterCollision->SetActive(false);
	MonsterRenderer->ChangeAnimation("Die");
}
