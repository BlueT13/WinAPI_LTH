#include "Player.h"
#include <EngineCore/EngineCore.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>

Player::Player()
{
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	AActor::BeginPlay();

	{
		BodyRenderer = CreateImageRenderer(0);
		BodyRenderer->SetPosition({ 0, 30 });
		BodyRenderer->SetScale({ 80, 80 });
	}

	{
		HeadRenderer = CreateImageRenderer(0);
		HeadRenderer->SetPosition({ 0, -25 });
		HeadRenderer->SetScale({ 60, 60 });
	}

	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

void Player::Tick(float _DeltaTime)
{
	if (true == EngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsDown('T'))
	{
		BodyRenderer->Destroy();
	}

	if (true == EngineInput::IsDown('Q'))
	{
		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
		NewBullet->SetActorLocation(GetActorLocation());
		NewBullet->SetDir(FVector::Right);
	}
}