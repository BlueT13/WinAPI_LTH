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
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Small.png", 0, 14, 0.03f, false);

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
	case EMonsterState::Idle:
		Idle(_DeltaTime);
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
		SpawnRenderer->SetActive(false);
		MonsterCollision->SetActive(true);
		if (Boss == nullptr)
		{
			MonsterStateChange(EMonsterState::Move);
		}
		else
		{
			MonsterStateChange(EMonsterState::Idle);
		}
	}
}

void AFly::Idle(float _DeltaTime)
{
	Angle = _DeltaTime * 100.0f;

	FlySpinDir.RotationZToDeg(Angle);

	SetActorLocation(Boss->GetActorLocation() + FlySpinDir);
}

void AFly::Move(float _DeltaTime)
{
	SpawnRenderer->SetActive(false);
	MonsterCollision->SetActive(true);
	UPlayLevel* Level = dynamic_cast<UPlayLevel*>(GetWorld());
	FVector CurRoomPos = Level->GetCurRoom()->GetActorLocation();

	FVector MonsterNextPos = GetActorLocation() + MonsterLastMoveVector * _DeltaTime;
	if (MonsterNextPos.X < CurRoomPos.X - 320)
	{
		MonsterPos.X = CurRoomPos.X - 320;
		SetActorLocation(MonsterPos);
	}
	if (MonsterNextPos.Y < CurRoomPos.Y - 170)
	{
		MonsterPos.Y = CurRoomPos.Y - 170;
		SetActorLocation(MonsterPos);
	}
	if (MonsterNextPos.X > CurRoomPos.X + 320)
	{
		MonsterPos.X = CurRoomPos.X + 320;
		SetActorLocation(MonsterPos);
	}
	if (MonsterNextPos.Y > CurRoomPos.Y + 170)
	{
		MonsterPos.Y = CurRoomPos.Y + 170;
		SetActorLocation(MonsterPos);
	}
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

void AFly::MonsterTouchWall(EActorDir _Dir)
{

	switch (_Dir)
	{
	case EActorDir::Left:

		MonsterLastMoveVector.X = 0.0f;
		break;
	case EActorDir::Up:
		MonsterLastMoveVector.Y = 0.0f;
		break;
	case EActorDir::Right:
		MonsterLastMoveVector.X = 0.0f;
		break;
	case EActorDir::Down:
		MonsterLastMoveVector.Y = 0.0f;
		break;
	default:
		break;
	}
}

void AFly::SetBoss(AActor* _Boss)
{
	Boss = _Boss;
	FlySpinDir = (GetActorLocation() - Boss->GetActorLocation()).Normalize2DReturn() * 80;
}