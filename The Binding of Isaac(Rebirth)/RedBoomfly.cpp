#include "RedBoomfly.h"
#include "MonsterBullet.h"

ARedBoomfly::ARedBoomfly()
{
}

ARedBoomfly::~ARedBoomfly()
{

}

void ARedBoomfly::BeginPlay()
{
	AMonster::BeginPlay();

	MonsterHp = 2.0f;
	MonsterMoveSpeed = 100.0f;

	SpawnRenderer = CreateImageRenderer(IsaacRenderOrder::SpawnEffect);
	SpawnRenderer->SetImage("SpawnEffect_Small.png");
	SpawnRenderer->AutoImageScale();
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Small.png", 0, 14, 0.03f, false);

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("RedBoomfly.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("Move", "RedBoomfly.png", 0, 1, 0.05f, true);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 50, 50 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

	MonsterMoveVector = { 1, -1 };
}

void ARedBoomfly::Tick(float _DeltaTime)
{
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal 받아온다.
	// MonsterStateUpdate(_DeltaTime);을 실행
	AMonster::Tick(_DeltaTime);
}

void ARedBoomfly::MonsterStateUpdate(float _DeltaTime)
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

void ARedBoomfly::Spawn(float _DeltaTime)
{
	MonsterCollision->SetActive(false);
	if (SpawnRenderer->IsCurAnimationEnd())
	{
		SpawnRenderer->SetActive(false);
		MonsterCollision->SetActive(true);
		MonsterStateChange(EMonsterState::Move);
	}
}

void ARedBoomfly::Move(float _DeltaTime)
{
	AddActorLocation(MonsterMoveVector * _DeltaTime * MonsterMoveSpeed);
}

void ARedBoomfly::Die(float _DeltaTime)
{
	//폭발
	CreateMonsterBullet({ -1,0 });
	CreateMonsterBullet({ -1,-1 });
	CreateMonsterBullet({ 0,-1 });
	CreateMonsterBullet({ 1,-1 });
	CreateMonsterBullet({ 1,0 });
	CreateMonsterBullet({ 1,1 });
	CreateMonsterBullet({ 0,1 });
	CreateMonsterBullet({ -1,1 });

	Destroy();
}

void ARedBoomfly::CreateMonsterBullet(FVector _Dir)
{
	AMonsterBullet* MonsterBullet = GetWorld()->SpawnActor<AMonsterBullet>(IsaacRenderOrder::Bullet);
	MonsterBullet->SetActorLocation(GetActorLocation());
	MonsterBullet->SetDir(_Dir);
}

void ARedBoomfly::MonsterStateChange(EMonsterState _State)
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

void ARedBoomfly::SpawnStart()
{
	SpawnRenderer->ChangeAnimation("Spawn");
	MonsterRenderer->ChangeAnimation("Move");
}

void ARedBoomfly::MoveStart()
{
	MonsterRenderer->ChangeAnimation("Move");
}

void ARedBoomfly::DieStart()
{
	MonsterRenderer->SetActive(false);
	MonsterCollision->SetActive(false);
	DeathSound = UEngineSound::SoundPlay("tear fire 4.wav");
}

void ARedBoomfly::MonsterTouchWall(EActorDir _Dir)
{
	float Size = MonsterMoveVector.Size2D();
	FVector Dir = MonsterMoveVector.Normalize2DReturn();

	switch (_Dir)
	{
	case EActorDir::Left:
		Dir = Reflect(Dir, FVector::Right);
		break;
	case EActorDir::Up:
		Dir = Reflect(Dir, FVector::Down);
		break;
	case EActorDir::Right:
		Dir = Reflect(Dir, FVector::Left);
		break;
	case EActorDir::Down:
		Dir = Reflect(Dir, FVector::Up);
		break;
	default:
		break;
	}

	MonsterMoveVector = Dir * Size;
}
