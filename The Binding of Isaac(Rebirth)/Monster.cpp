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
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	Player = APlayer::GetMainPlayer();
	PlayerLocation = Player->GetActorLocation();

	MonsterPos = GetActorLocation();
	MonsterDir = PlayerLocation - MonsterPos;
	MonsterDirNormal = MonsterDir.Normalize2DReturn();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	MonsterStateUpdate(_DeltaTime);
}