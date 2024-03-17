#include "Pooter.h"
#include "MonsterBullet.h"

APooter::APooter()
{
}

APooter::~APooter()
{
}

void APooter::BeginPlay()
{
	AMonster::BeginPlay();

	MonsterHp = 2;
	MonsterMoveSpeed = 30.f;
	MonsterBulletCoolTime = 0.0f;

	SpawnRenderer = CreateImageRenderer(IsaacRenderOrder::SpawnEffect);
	SpawnRenderer->SetImage("SpawnEffect_Small.png");
	SpawnRenderer->AutoImageScale();
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Small.png", 0, 14, 0.03f, false);

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("Pooter.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("Move", "Pooter.png", 0, 1, 0.05f, true);
	MonsterRenderer->CreateAnimation("Attack", "Pooter.png", 0, 15, 0.03f, false);
	MonsterRenderer->CreateAnimation("Die", "Fly.png", 4, 14, 0.03f, false);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 30, 30 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

	PlayerCheckCollision = CreateCollision(IsaacCollisionOrder::PlayerCheckCollision);
	PlayerCheckCollision->SetScale({ 400,400 });
	PlayerCheckCollision->SetColType(ECollisionType::CirCle);
}

void APooter::Tick(float _DeltaTime)
{
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal 받아온다.
	// MonsterStateUpdate(_DeltaTime);을 실행
	AMonster::Tick(_DeltaTime);

	MonsterMoveVector = MonsterToPlayerDirNormal * MonsterMoveSpeed;

	PlayerCheckCollisionTrans = PlayerCheckCollision->GetActorBaseTransform();

	MonsterBulletCoolTime -= _DeltaTime;
}

void APooter::MonsterStateUpdate(float _DeltaTime)
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

void APooter::Spawn(float _DeltaTime)
{
	MonsterCollision->SetActive(false);
	PlayerCheckCollision->SetActive(false);
	if (SpawnRenderer->IsCurAnimationEnd())
	{
		SpawnRenderer->Destroy();
		MonsterCollision->SetActive(true);
		PlayerCheckCollision->SetActive(true);
		MonsterStateChange(EMonsterState::Move);
	}
}

void APooter::Move(float _DeltaTime)
{
	if (FTransform::CircleToCircle(PlayerCollisionTrans, PlayerCheckCollisionTrans) && MonsterBulletCoolTime <= 0)
	{
		MonsterStateChange(EMonsterState::Attack);
	}
}

void APooter::Attack(float _DeltaTime)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		CreateMonsterBullet(MonsterToPlayerDirNormal);
		MonsterBulletCoolTime = MonsterFireRate;
		MonsterStateChange(EMonsterState::Move);
	}
}

void APooter::CreateMonsterBullet(FVector _Dir)
{
	AttackSound = UEngineSound::SoundPlay("tear fire 4.wav");
	AMonsterBullet* MonsterBullet = GetWorld()->SpawnActor<AMonsterBullet>(IsaacRenderOrder::Bullet);
	MonsterBullet->SetActorLocation(GetActorLocation());
	MonsterBullet->SetDir(MonsterToPlayerDirNormal);
}

void APooter::Die(float _DeltaTime)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void APooter::MonsterStateChange(EMonsterState _State)
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

void APooter::SpawnStart()
{
	SpawnRenderer->ChangeAnimation("Spawn");
	MonsterRenderer->ChangeAnimation("Move");
}

void APooter::MoveStart()
{
	MonsterRenderer->ChangeAnimation("Move");
}

void APooter::AttackStart()
{
	MonsterRenderer->ChangeAnimation("Attack");
}

void APooter::DieStart()
{
	MonsterCollision->SetActive(false);
	MonsterRenderer->ChangeAnimation("Die");
	DeathSound = UEngineSound::SoundPlay("death burst small.wav");
}

void APooter::MonsterTouchWall(EActorDir _Dir)
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
