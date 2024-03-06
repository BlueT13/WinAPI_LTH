#include "Monster.h"

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();

	MonsterStateChange(EMonsterState::Idle);
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime); 

	Player = APlayer::GetMainPlayer();
	PlayerLocation = Player->GetActorLocation();

	MonsterStateUpdate(_DeltaTime);
}

void AMonster::MonsterStateUpdate(float _DeltaTime)
{
}

void AMonster::MonsterIdle(float _DeltaTime)
{
}

void AMonster::MonsterMove(float _DeltaTime)
{
}

void AMonster::MonsterAttack(float _DeltaTime)
{
}

void AMonster::MonsterDie(float _DeltaTime)
{
}

void AMonster::MonsterStateChange(EMonsterState _State)
{
}

void AMonster::MonsterIdleStart()
{
}

void AMonster::MonsterMoveStart()
{
}

void AMonster::MonsterAttackStart()
{
}

void AMonster::MonsterDirCheck()
{
}

std::string AMonster::GetMonsterAnimationName(std::string _Name)
{
	return std::string();
}
