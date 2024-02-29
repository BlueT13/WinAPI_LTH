#include "Fly.h"

AFly::AFly()
{
}

AFly::~AFly()
{
}

void AFly::BeginPlay()
{
	AActor::BeginPlay();

	SetActorLocation({ 800,270 });

	UImageRenderer* FlyRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
	FlyRenderer->SetImage("Fly.png");
	FlyRenderer->SetTransform({ FVector::Zero, RendererSize });
	FlyRenderer->CreateAnimation("Move", "Fly.png", 0, 3, 0.05f, true);
	FlyRenderer->CreateAnimation("Dead", "Fly.png", 4, 14, 0.05f, true);


	MonsterCollision = CreateCollision(IsaacCollisionOrder::Monster);
	MonsterCollision->SetScale({ 50, 50 });
	MonsterCollision->SetColType(ECollisionType::CirCle);


	FlyRenderer->ChangeAnimation("Move");
}

void AFly::Tick(float _DeltaTime)
{
}
