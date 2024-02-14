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

	SetActorLocation({ 300, 300 });

	{
		HeadRenderer = CreateImageRenderer(0);
		HeadRenderer->SetImage("Head.png");
		HeadRenderer->SetTransform({ { 0,0 }, { 30,30 } });
		HeadRenderer->SetImageCuttingTransform({ {0,0}, {30, 30} });
	}
}

void Player::Tick(float _DeltaTime)
{
	if (true == UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}

	if (true == UEngineInput::IsDown('T'))
	{
		BodyRenderer->Destroy();
	}

	if (true == UEngineInput::IsDown('Q'))
	{
		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
		NewBullet->SetActorLocation(GetActorLocation());
		NewBullet->SetDir(FVector::Right);
	}
}