#include "Bomb.h"
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
	BombCollision->SetColType(ECollisionType::CirCle);

	BombStateChange(EBombState::Idle);
}

void ABomb::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

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
		Destroy();
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
	if (BombRenderer->IsCurAnimationEnd())
	{
		BombStateChange(EBombState::Destroy);
	}
}

void ABomb::BombStateChange(EBombState _State)
{
	BombState = _State;
}
