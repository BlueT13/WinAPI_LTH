#include "Boomfly.h"


ABoomfly::ABoomfly()
{
}

ABoomfly::~ABoomfly()
{

}

void ABoomfly::BeginPlay()
{
	AMonster::BeginPlay();

	MonsterHp = 2.0f;
	MonsterMoveSpeed = 100.0f;

	SpawnRenderer = CreateImageRenderer(IsaacRenderOrder::SpawnEffect);
	SpawnRenderer->SetImage("SpawnEffect_Small.png");
	SpawnRenderer->AutoImageScale();
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Small.png", 0, 14, 0.03f, false);

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("Boomfly.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("Move", "Boomfly.png", 0, 1, 0.05f, true);
	MonsterRenderer->CreateAnimation("Die", "Explosion.png", 0, 10, 0.03f, false);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 30, 30 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

	ExplosionCollision = CreateCollision(IsaacCollisionOrder::Bomb);
	ExplosionCollision->SetScale({ 150, 150 });
	ExplosionCollision->SetColType(ECollisionType::CirCle);
	ExplosionCollision->SetActive(false);

	MonsterMoveVector = { 1, 1 };
}

void ABoomfly::Tick(float _DeltaTime)
{
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal 받아온다.
	// MonsterStateUpdate(_DeltaTime);을 실행
	AMonster::Tick(_DeltaTime);
}

void ABoomfly::MonsterStateUpdate(float _DeltaTime)
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

void ABoomfly::Spawn(float _DeltaTime)
{
	MonsterCollision->SetActive(false);
	if (SpawnRenderer->IsCurAnimationEnd())
	{
		SpawnRenderer->SetActive(false);
		MonsterCollision->SetActive(true);
		MonsterStateChange(EMonsterState::Move);
	}
}

void ABoomfly::Move(float _DeltaTime)
{
	AddActorLocation(MonsterMoveVector * _DeltaTime * MonsterMoveSpeed);
}

void ABoomfly::Die(float _DeltaTime)
{
	//폭발
	std::vector<UCollision*> Results;
	if (ExplosionCollision->CollisionCheck(IsaacCollisionOrder::Player, Results))
	{
		FVector Dir = (PlayerLocation - GetActorLocation()).Normalize2DReturn();
		Player->SetHitPower(Dir * BombPower);
		Player->HeadStateChange(EPlayerHeadState::GetHit);
	}

	if (MonsterRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void ABoomfly::MonsterStateChange(EMonsterState _State)
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

void ABoomfly::SpawnStart()
{
	SpawnRenderer->ChangeAnimation("Spawn");
	MonsterRenderer->ChangeAnimation("Move");
}

void ABoomfly::MoveStart()
{
	MonsterRenderer->ChangeAnimation("Move");
}

void ABoomfly::DieStart()
{
	MonsterRenderer->ChangeAnimation("Die");
	MonsterCollision->SetActive(false);
	ExplosionCollision->SetActive(true);
	DeathSound = UEngineSound::SoundPlay("explosion_weak1.wav");
}

void ABoomfly::MonsterTouchWall(EActorDir _Dir)
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
