#include "Monster.h"

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//MonsterStateUpdate(_DeltaTime);
}
