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

	{
		UImageRenderer* Renderer = CreateImageRenderer(IsaacRenderOrder::Monster);
		Renderer->SetTransform({ {0,0}, {100, 100} });
		Renderer->SetImage("");
	}

	{
		FlyCollision = CreateCollision(IsaacCollisionOrder::Monster);
		FlyCollision->SetScale({ 100, 100 });
		FlyCollision->SetColType(ECollisionType::Rect);
	}
}

void AFly::Tick(float _DeltaTime)
{
}

