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

	MonsterHp = 5.0f;
	MonsterMoveSpeed = 100.f;
	SpawnFlyCoolTime = 0.0f;

	SpawnRenderer = CreateImageRenderer(IsaacRenderOrder::SpawnEffect);
	SpawnRenderer->SetImage("SpawnEffect_Small.png");
	SpawnRenderer->AutoImageScale();
	SpawnRenderer->CreateAnimation("Spawn", "SpawnEffect_Large.png", 0, 14, 0.05f, false);

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("DukeOfFlies_SpawnFly.png");
	MonsterRenderer->AutoImageScale();
	MonsterRenderer->CreateAnimation("SpawnFly", "DukeOfFlies_SpawnFly.png", { 0,1,2 }, { 1.0f,2.0f,1.0f }, false);
	MonsterRenderer->CreateAnimation("SendFly", "DukeOfFlies_SendFly.png", { 0,1,2 }, { 1.0f,2.0f,1.0f }, false);
	//MonsterRenderer->CreateAnimation("GetHit", ".png", 0, 3, 0.05f, true);
	MonsterRenderer->CreateAnimation("Die", "LargeBloodExplosion.png", 0, 9, 0.05f, false);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 150, 150 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

}

void ADukeOfFlies::Tick(float _DeltaTime)
{
	// Player, PlayerLocation, MonsterPos, MonsterDir, MonsterDirNormal 받아온다.
	// MonsterStateUpdate(_DeltaTime);을 실행
	AMonster::Tick(_DeltaTime);

	MonsterMoveVector = (-MonsterToPlayerDirNormal);

	AddActorLocation(MonsterMoveVector * _DeltaTime * MonsterMoveSpeed);

	SpawnFlyCoolTime -= _DeltaTime;
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
		SpawnFly(_DeltaTime);
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

	if (FTransform::CircleToCircle(PlayerCollisionTrans, PlayerCheckCollisionTrans) && SpawnFlyCoolTime <= 0)
	{
		MonsterStateChange(EMonsterState::Attack);
	}

}

void ADukeOfFlies::SpawnFly(float _DeltaTime)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		AFly* Fly = GetWorld()->SpawnActor<AFly>(IsaacRenderOrder::Monster);
		SpawnFlyCoolTime = SpawnFlyRate;
		MonsterStateChange(EMonsterState::Move);
	}
}

void ADukeOfFlies::SendFly(float _DeltaTime)
{
}

void ADukeOfFlies::Die(float _DeltaTime)
{
	if (MonsterRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
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
			SpawnFlyStart();
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
}

void ADukeOfFlies::SpawnFlyStart()
{
	MonsterRenderer->ChangeAnimation("SpawnFly");
}

void ADukeOfFlies::SendFlyStart()
{
	MonsterRenderer->ChangeAnimation("SendFly");
}

void ADukeOfFlies::DieStart()
{
	MonsterCollision->SetActive(false);
	MonsterRenderer->ChangeAnimation("Die");
}