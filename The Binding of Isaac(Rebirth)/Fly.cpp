#include "Fly.h"
#include "Bullet.h"

AFly::AFly()
{
}

AFly::~AFly()
{
}

void AFly::BeginPlay()
{
	AActor::BeginPlay();

	SetActorLocation({ 300,0 });

	UImageRenderer* FlyRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	FlyRenderer->SetImage("Fly.png");
	FlyRenderer->SetTransform({ FVector::Zero, RendererSize });
	FlyRenderer->CreateAnimation("Move", "Fly.png", 0, 3, 0.05f, true);
	FlyRenderer->CreateAnimation("Dead", "Fly.png", 4, 14, 0.05f, true);


	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 30, 30 });
	MonsterCollision->SetColType(ECollisionType::CirCle);


	FlyRenderer->ChangeAnimation("Move");
}

void AFly::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(IsaacCollisionOrder::Bullet, Result))
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		ABullet* Bullet = dynamic_cast<ABullet*>(Ptr);

		Bullet->BulletStateChange(EBulletState::Crashed);
		Destroy();
	}

	APlayer* Player = APlayer::GetMainPlayer();
	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterPos = GetActorLocation();

	FVector MonsterDir = PlayerPos - MonsterPos;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	AddActorLocation(MonsterDirNormal * _DeltaTime * MoveSpeed);
}
