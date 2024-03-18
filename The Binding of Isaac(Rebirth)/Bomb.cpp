#include "Bomb.h"
#include "Monster.h"
#include "Player.h"
#include "ContentsHelper.h"

ABomb::ABomb()
{
}

ABomb::~ABomb()
{
}

void ABomb::BeginPlay()
{
	AActor::BeginPlay();

	BombRenderer = CreateImageRenderer(IsaacRenderOrder::Bomb);
	BombRenderer->SetImage("Bomb.png", 0);
	BombRenderer->AutoImageScale();
	BombRenderer->CreateAnimation("Explosion", "Explosion.png", 0, 10, 0.03f, false);

	BombCollision = CreateCollision(IsaacCollisionOrder::Bomb);
	BombCollision->SetScale({ 30, 30 });
	BombCollision->SetColType(ECollisionType::Rect);

	ExplosionCollision = CreateCollision(IsaacCollisionOrder::Bomb);
	ExplosionCollision->SetScale({ 250, 250 });
	ExplosionCollision->SetColType(ECollisionType::CirCle);
	ExplosionCollision->SetActive(false);

	BombStateChange(EBombState::Idle);
}

void ABomb::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Results;
	if (true == BombCollision->CollisionCheck(IsaacCollisionOrder::Bomb, Results))
	{
		for (UCollision* Result : Results)
		{
			AActor* OtherBombPtr = Result->GetOwner();
			ABomb* OtherBomb = dynamic_cast<ABomb*>(OtherBombPtr);
			FVector OtherPos = OtherBomb->GetActorLocation();
			FVector OtherToThisDir = GetActorLocation() - OtherPos;
			FVector OtherToThisDirNormal = OtherToThisDir.Normalize2DReturn();
			FTransform OtherCollisionTrans = OtherBomb->BombCollision->GetActorBaseTransform();
			FTransform ThisCollisionTrans = BombCollision->GetActorBaseTransform();
			if (FTransform::RectToRect(OtherCollisionTrans, ThisCollisionTrans))
			{
				AddActorLocation(OtherToThisDirNormal * _DeltaTime * 100);
			}
		}
	}

	if (true == BombCollision->CollisionCheck(IsaacCollisionOrder::Monster, Results))
	{
		for (UCollision* Result : Results)
		{
			AActor* MonsterPtr = Result->GetOwner();
			AMonster* Monster = dynamic_cast<AMonster*>(MonsterPtr);
			FVector OtherPos = Monster->GetActorLocation();
			FVector OtherToThisDir = GetActorLocation() - OtherPos;
			FVector OtherToThisDirNormal = OtherToThisDir.Normalize2DReturn();
			FTransform OtherCollisionTrans = Monster->MonsterCollision->GetActorBaseTransform();
			FTransform ThisCollisionTrans = BombCollision->GetActorBaseTransform();
			if (FTransform::CircleToRect(OtherCollisionTrans, ThisCollisionTrans))
			{
				AddActorLocation(OtherToThisDirNormal * _DeltaTime * Monster->MonsterMoveSpeed);
			}
		}
	}

	if (true == BombCollision->CollisionCheck(IsaacCollisionOrder::Player, Results))
	{
		AActor* PlayerPtr = Results[0]->GetOwner();
		APlayer* Player = APlayer::GetMainPlayer();
		FVector OtherPos = Player->GetActorLocation();
		FVector OtherToThisDir = GetActorLocation() - OtherPos;
		FVector OtherToThisDirNormal = OtherToThisDir.Normalize2DReturn();
		FTransform OtherCollisionTrans = Player->PlayerCollision->GetActorBaseTransform();
		FTransform ThisCollisionTrans = BombCollision->GetActorBaseTransform();
		if (FTransform::CircleToRect(OtherCollisionTrans, ThisCollisionTrans) && false == PlayerCheck)
		{
			AddActorLocation(OtherToThisDirNormal * _DeltaTime * Player->GetPlayerMaxSpeed());
		}
	}
	else
	{
		PlayerCheck = false;
	}

	BombStateUpdate(_DeltaTime);
}

void ABomb::BombStateUpdate(float _DeltaTime)
{
	switch (BombState)
	{
	case EBombState::Idle:
		Idle(_DeltaTime);
		break;
	case EBombState::Explosion:
		Explosion(_DeltaTime);
		break;
	case EBombState::Destroy:
		BombDestroy(_DeltaTime);
		break;
	}
}


void ABomb::Idle(float _DeltaTime)
{
	BoomTime -= _DeltaTime;
	if (BoomTime < 0)
	{
		BombStateChange(EBombState::Explosion);
	}
}

void ABomb::Explosion(float _DeltaTime)
{
	BombRenderer->ChangeAnimation("Explosion");
	BombCollision->SetActive(false);
	ExplosionCollision->SetActive(true);
	ExplosionSound = UEngineSound::SoundPlay("explosion_weak1.wav");

	std::vector<UCollision*> Results;
	if (ExplosionCollision->CollisionCheck(IsaacCollisionOrder::Monster, Results))
	{
		for (UCollision* Result : Results)
		{
			AActor* MonsterPtr = Result->GetOwner();
			AMonster* Monster = dynamic_cast<AMonster*>(MonsterPtr);
			if (Monster == nullptr)
			{
				MsgBoxAssert("충돌된 Collision의 몬스터가 nullptr입니다.");
			}

			FVector Dir = (Monster->GetActorLocation() - GetActorLocation()).Normalize2DReturn();
			Monster->HitPower = Dir * BombPower;
			Monster->GetHit(BombDamage);
		}
	}
	
	if (ExplosionCollision->CollisionCheck(IsaacCollisionOrder::Player, Results))
	{
		APlayer* Player = APlayer::GetMainPlayer();
		if (Player == nullptr)
		{
			MsgBoxAssert("충돌된 Collision의 Player가 nullptr입니다.");
		}

		FVector Dir = (Player->GetActorLocation() - GetActorLocation()).Normalize2DReturn();
		Player->HitPower = Dir * BombPower;
		Player->HeadStateChange(EPlayerHeadState::GetHit);
	}

	BombStateChange(EBombState::Destroy);
}

void ABomb::BombDestroy(float _DeltaTime)
{
	if (BombRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void ABomb::BombStateChange(EBombState _State)
{
	BombState = _State;
}
