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
	AMonster::BeginPlay();

	MonsterRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	MonsterRenderer->SetImage("Fly.png");
	MonsterRenderer->SetTransform({ FVector::Zero, RendererSize });
	MonsterRenderer->CreateAnimation("Move", "Fly.png", 0, 3, 0.05f, true);
	MonsterRenderer->CreateAnimation("Dead", "Fly.png", 4, 14, 0.05f, true);

	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 30, 30 });
	MonsterCollision->SetColType(ECollisionType::CirCle);

	MonsterRenderer->ChangeAnimation("Move");
}

void AFly::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);

	FVector MonsterPos = GetActorLocation();
	FVector MonsterDir = PlayerLocation - MonsterPos;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	AddActorLocation(MonsterDirNormal * _DeltaTime * MoveSpeed);
}
