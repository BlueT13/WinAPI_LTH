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
	{
		UImageRenderer* FlyRenderer = CreateImageRenderer(IsaacRenderOrder::Monster);
		FlyRenderer->SetImage("Fly.png");
		FlyRenderer->SetTransform({ FVector::Zero, RendererSize });
		FlyRenderer->CreateAnimation("Idle", "Fly.png", 0, 1, 0.1f, true);
		FlyRenderer->CreateAnimation("Dead", "Fly.png", 2, 12, 0.1f, true);
	}

	{
		FlyCollision = CreateCollision(IsaacCollisionOrder::Monster);
		FlyCollision->SetScale({ 50, 50 });
		FlyCollision->SetColType(ECollisionType::CirCle);
	}
}

void AFly::Tick(float _DeltaTime)
{
}
