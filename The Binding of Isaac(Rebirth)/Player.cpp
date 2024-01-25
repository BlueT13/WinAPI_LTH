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

	if (true == EngineInput::IsDown('Q'))
	{
		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
		NewBullet->SetActorLocation(GetActorLocation());
		NewBullet->SetDir(FVector::Right);
	}

	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}