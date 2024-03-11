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
		MsgBoxAssert("�÷��̾ �������� �ʽ��ϴ�.");
	}

	std::vector<AMonster*> Monsters = CurRoom->GetAllMonsters();

	// ���ͳ��� �浹
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
		FTransform OtherMonsterTrans = OtherMonster->MonsterCollisionTrans;
		FTransform ThisTrans = MonsterCollision->GetActorBaseTransform();
		if (FTransform::CircleToCircle(OtherMonsterTrans, MonsterCollisionTrans))
		{
			AddActorLocation((-MonsterToMonsterDirNormal) * _DeltaTime * MonsterMoveSpeed);
		}
	}

	// �÷��̾�� ���Ͱ� ���� �浹
	PlayerCollisionTrans = Player->GetPlayerCollision()->GetActorBaseTransform();
	MonsterCollisionTrans = MonsterCollision->GetActorBaseTransform();
	if (true == FTransform::CircleToCircle(PlayerCollisionTrans, MonsterCollisionTrans))
	{
		AddActorLocation((-MonsterToPlayerDirNormal) * _DeltaTime * PlayerMoveMaxSpeed);

		Player->SetHitPower(MonsterToPlayerDirNormal * 200.0f);
		Player->HeadStateChange(EPlayerHeadState::GetHit);
	}

	MonsterStateUpdate(_DeltaTime);
}