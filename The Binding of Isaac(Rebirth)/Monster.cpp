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

		Player->SetHitPower(MonsterToPlayerDirNormal * 400.0f);
		Player->HeadStateChange(EPlayerHeadState::GetHit);
	}

	MonsterStateUpdate(_DeltaTime);

	MonsterMoveUpdate(_DeltaTime);
}

void AMonster::GetHit()
{
	MonsterHp--;
	if (MonsterHp <= 0)
	{
		MonsterStateChange(EMonsterState::Die);
	}
}

void AMonster::MonsterMoveUpdate(float _DeltaTime)
{
	CalHitPower(_DeltaTime);
	CalLastMoveVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime);
}

void AMonster::CalHitPower(float _DeltaTime)
{
	HitPower -= HitPower * _DeltaTime * 10.0f;
	if (HitPower.Size2D() < 100.0f)
	{
		HitPower = FVector::Zero;
	}
}

void AMonster::CalLastMoveVector(float _DeltaTime)
{
	MonsterLastMoveVector = FVector::Zero;
	MonsterLastMoveVector += HitPower;
	MonsterLastMoveVector += MonsterMoveVector;
}

void AMonster::MoveLastMoveVector(float _DeltaTime)
{
	UPlayLevel* Level = dynamic_cast<UPlayLevel*>(GetWorld());

	FVector CurRoomPos = Level->GetCurRoom()->GetActorLocation();

	FVector MonsterPos = GetActorLocation();
	FVector MonsterNextPos = MonsterPos + MonsterMoveVector * _DeltaTime;
	if (MonsterNextPos.X < CurRoomPos.X - 320)
	{
		MonsterTouchWall(_DeltaTime, EActorDir::Left);
	}
	if (MonsterNextPos.Y < CurRoomPos.Y - 170)
	{
		MonsterTouchWall(_DeltaTime, EActorDir::Up);
	}
	if (MonsterNextPos.X > CurRoomPos.X + 320)
	{
		MonsterTouchWall(_DeltaTime, EActorDir::Right);
	}
	if (MonsterNextPos.Y > CurRoomPos.Y + 170)
	{
		MonsterTouchWall(_DeltaTime, EActorDir::Down);
	}

	AddActorLocation(MonsterLastMoveVector * _DeltaTime);
}