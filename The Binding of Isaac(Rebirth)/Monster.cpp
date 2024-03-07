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
		MsgBoxAssert("�÷��̾ �������� �ʽ��ϴ�.");
	}

	MonsterStateUpdate(_DeltaTime);
}