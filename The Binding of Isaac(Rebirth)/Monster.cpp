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

	// 몬스터끼리 충돌
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

	// 플레이어와 몬스터가 직접 충돌
	std::vector<UCollision*> Results;
	if (true == MonsterCollision->CollisionCheck(IsaacCollisionOrder::Player, Results))
	{
		Player->HeadStateChange(EPlayerHeadState::GetHit);
	}

	PlayerCollisionTrans = Player->GetPlayerCollision()->GetActorBaseTransform();
	MonsterCollisionTrans = MonsterCollision->GetActorBaseTransform();
	if (true == FTransform::CircleToCircle(PlayerCollisionTrans, MonsterCollisionTrans))
	{
		AddActorLocation((-MonsterToPlayerDirNormal) * _DeltaTime * PlayerMoveMaxSpeed);

		Player->SetHitPower(MonsterToPlayerDirNormal * 400.0f);
	}


	MonsterStateUpdate(_DeltaTime);

	MonsterMoveUpdate(_DeltaTime);
}

void AMonster::GetHit(float _Damage)
{
	MonsterHp -= _Damage;
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
	FVector MonsterNextPos = MonsterPos + MonsterLastMoveVector * _DeltaTime;
	bool OutCheck = false;
	if (MonsterNextPos.X < CurRoomPos.X - 320)
	{
		//MonsterPos.X = CurRoomPos.X - 320;
		//SetActorLocation(MonsterPos);

		OutCheck = true;
		MonsterTouchWall(EActorDir::Left);
	}
	if (MonsterNextPos.Y < CurRoomPos.Y - 170)
	{
		//MonsterPos.Y = CurRoomPos.Y - 170;
		//SetActorLocation(MonsterPos);

		OutCheck = true;
		MonsterTouchWall(EActorDir::Up);
	}
	if (MonsterNextPos.X > CurRoomPos.X + 320)
	{
		//MonsterPos.X = CurRoomPos.X + 320;
		//SetActorLocation(MonsterPos);

		OutCheck = true;
		MonsterTouchWall(EActorDir::Right);
	}
	if (MonsterNextPos.Y > CurRoomPos.Y + 170)
	{
		//MonsterPos.Y = CurRoomPos.Y + 170;
		//SetActorLocation(MonsterPos);

		OutCheck = true;
		MonsterTouchWall(EActorDir::Down);
	}

	if (OutCheck == false)
	{
		AddActorLocation(MonsterLastMoveVector * _DeltaTime);
	}
}

FVector AMonster::Ref(FVector _Dir, FVector _Nor)
{
	float Dot = (_Dir.X * _Nor.X) + (_Dir.Y * _Nor.Y);

	return _Dir + ((_Nor * 2.0f) * (-Dot));
}