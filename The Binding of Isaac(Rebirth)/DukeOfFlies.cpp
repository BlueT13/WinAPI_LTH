#include "DukeOfFlies.h"
#include "Fly.h"

ADukeOfFlies::ADukeOfFlies()
{
}

ADukeOfFlies::~ADukeOfFlies()
{
}

void ADukeOfFlies::BeginPlay()
{
	AMonster::BeginPlay();

	MonsterHp = 1;
	MonsterMoveSpeed = 100.f;
	AttackCoolTime = 0.0f;

	SpawnRenderer = CreateImageRenderer(IsaacRenderOrder::SpawnEffect);
	SpawnRenderer->SetImage("SpawnEffect_Small.png");
	SpawnRenderer->AutoImageScale();
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Large.png", 0, 14, 0.03f, false);

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Boss);
	MonsterRenderer->SetImage("DukeOfFlies_SpawnFly.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("Move", "DukeOfFlies_SpawnFly.png", 0, 0, 1.0f, true);
	MonsterRenderer->CreateAnimation("SpawnFly", "DukeOfFlies_SpawnFly.png", 0, 2, 0.5f, false);
	MonsterRenderer->CreateAnimation("SendFly", "DukeOfFlies_SendFly.png", 0, 2, 0.5f, false);
	//MonsterRenderer->CreateAnimation("GetHit", ".png", 0, 3, 0.05f, true);
	MonsterRenderer->CreateAnimation("Die", "LargeBloodExplosion.png", 0, 9, 0.05f, false);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 100, 100 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

	MonsterMoveVector = { -1,-1 };
}

void ADukeOfFlies::Tick(float _DeltaTime)
{
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal 받아온다.
	// MonsterStateUpdate(_DeltaTime);을 실행
	AMonster::Tick(_DeltaTime);

	AddActorLocation(MonsterMoveVector * _DeltaTime * MonsterMoveSpeed);

	AttackCoolTime -= _DeltaTime;
}

void ADukeOfFlies::MonsterStateUpdate(float _DeltaTime)
{
	switch (MonsterState)
	{
	case EMonsterState::Spawn:
		Spawn(_DeltaTime);
		break;
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::Attack:
		Attack(_DeltaTime);
		break;
	case EMonsterState::Die:
		Die(_DeltaTime);
		break;
	default:
		break;
	}
}

void ADukeOfFlies::Spawn(float _DeltaTime)
{
	MonsterCollision->SetActive(false);
	if (SpawnRenderer->IsCurAnimationEnd())
	{
		SpawnRenderer->Destroy();
		MonsterCollision->SetActive(true);
		MonsterStateChange(EMonsterState::Move);
	}
}

void ADukeOfFlies::Move(float _DeltaTime)
{
	if (AttackCoolTime <= 0)
	{
		MonsterStateChange(EMonsterState::Attack);
	}
}

void ADukeOfFlies::Attack(float _DeltaTime)
{
	if (SpawnCount < 2)
	{
		SpawnFly(_DeltaTime);
	}
	else
	{
		SendFly(_DeltaTime);
	}
}

void ADukeOfFlies::SpawnFly(float _DeltaTime)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		ARoom* CurRoom = GetCurRoom();
		AFly* Fly = GetWorld()->SpawnActor<AFly>(IsaacRenderOrder::Monster);
		Fly->SetActorLocation(GetActorLocation() + MonsterToPlayerDirNormal * 80);
		Fly->SetMonsterRoom(CurRoom);
		Fly->SetBoss(this);
		Fly->MonsterStateChange(EMonsterState::Spawn);
		CurRoom->PushBackMonster(Fly);
		Flys.push_back(Fly);
		AttackCoolTime = AttackRate;
		MonsterStateChange(EMonsterState::Move);
		SpawnCount++;
	}
}

void ADukeOfFlies::SendFly(float _DeltaTime)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		for (size_t i = 0; i < Flys.size(); i++)
		{
			Flys[i]->MonsterStateChange(EMonsterState::Move);
		}
		SpawnCount = 0; 
		MonsterStateChange(EMonsterState::Move);
	}
}

void ADukeOfFlies::Die(float _DeltaTime)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}

	for (size_t i = 0; i < Flys.size(); i++)
	{
		Flys[i]->MonsterStateChange(EMonsterState::Move);
	}

	return;
}

void ADukeOfFlies::MonsterStateChange(EMonsterState _State)
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
		case EMonsterState::Attack:
			AttackStart();
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

void ADukeOfFlies::SpawnStart()
{
	SpawnRenderer->ChangeAnimation("Spawn");
}

void ADukeOfFlies::MoveStart()
{
	MonsterRenderer->ChangeAnimation("Move");
}

void ADukeOfFlies::AttackStart()
{
	if (SpawnCount < 2)
	{
		MonsterRenderer->ChangeAnimation("SpawnFly");
	}
	else
	{
		MonsterRenderer->ChangeAnimation("SendFly");
	}
}

void ADukeOfFlies::DieStart()
{
	MonsterCollision->SetActive(false);
	MonsterRenderer->ChangeAnimation("Die");
}

void ADukeOfFlies::MonsterTouchWall(EActorDir _Dir)
{
	float Size = MonsterMoveVector.Size2D();
	FVector Dir = MonsterMoveVector.Normalize2DReturn();

	switch (_Dir)
	{
	case EActorDir::Left:
		Dir = Ref(Dir, FVector::Right);
		break;
	case EActorDir::Up:
		Dir = Ref(Dir, FVector::Down);
		break;
	case EActorDir::Right:
		Dir = Ref(Dir, FVector::Left);
		break;
	case EActorDir::Down:
		Dir = Ref(Dir, FVector::Up);
		break;
	default:
		break;
	}

	MonsterMoveVector = Dir * Size;
}
