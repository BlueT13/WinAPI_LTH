#include "Monster.h"

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::SetMonsterRoom(ARoom* _Room)
{
	CurRoom = _Room;
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
	PlayerCollision = Player->GetPlayerCollision();
	PlayerMoveMaxSpeed = Player->GetPlayerMoveMaxSpeed();

	MonsterPos = GetActorLocation();
	MonsterToPlayerDir = PlayerLocation - MonsterPos;
	MonsterToPlayerDirNormal = MonsterToPlayerDir.Normalize2DReturn();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	std::vector<AMonster*> Monsters = CurRoom->GetAllMonsters();

	for (size_t i = 0; i < Monsters.size(); i++)
	{
		AMonster* OtherMonster = Monsters[i];

		if (OtherMonster == this)
		{
			continue;
		}

		FVector OtherMonsterPos = OtherMonster->MonsterPos;
		FVector ThisPos = MonsterPos;
		FVector MonsterToMonsterDir = OtherMonsterPos - ThisPos;
		FVector MonsterToMonsterDirNormal = MonsterToMonsterDir.Normalize2DReturn();
		FTransform OtherTrans = OtherMonster->MonsterCollision->GetActorBaseTransform();
		FTransform ThisTrans = MonsterCollision->GetActorBaseTransform();
		if (true == FTransform::CircleToCircle(OtherTrans, ThisTrans))
		{
			AddActorLocation((-MonsterToMonsterDirNormal) * _DeltaTime * MonsterMoveSpeed);
		}
	}

	FTransform PlayerTrans = Player->GetPlayerCollision()->GetActorBaseTransform();
	FTransform ThisTrans = MonsterCollision->GetActorBaseTransform();
	if (true == FTransform::CircleToCircle(PlayerTrans, ThisTrans))
	{
		AddActorLocation((-MonsterToPlayerDirNormal) * _DeltaTime * PlayerMoveMaxSpeed);

		Player->SetHitPower(MonsterToPlayerDirNormal * 200.0f);
		Player->HeadStateChange(EPlayerHeadState::GetHit);
	}

	MonsterStateUpdate(_DeltaTime);
}