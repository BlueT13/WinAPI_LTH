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

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("Fly.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("Move", "Fly.png", 0, 3, 0.05f, true);
	//MonsterRenderer->CreateAnimation("GetHit", "Fly.png", 0, 3, 0.05f, true);
	MonsterRenderer->CreateAnimation("Die", "Fly.png", 4, 14, 0.03f, true);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 30, 30 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

	MonsterStateChange(EMonsterState::Move);
}

void AFly::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal �޾ƿ´�.
	// MonsterStateUpdate(_DeltaTime);�� ����
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
	AddActorLocation(MonsterDirNormal * _DeltaTime * MoveSpeed);
}

void AFly::GetHit(float _DeltaTime)
{
	MonsterHp -= 1.0f;

	// �ڷ� �з����� ��
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
