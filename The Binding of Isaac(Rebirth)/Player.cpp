#include "Player.h"
#include "Bullet.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineDebug.h>
#include "ContentsHelper.h"

namespace
{
	FVector MakeDirectionToFVector(EDirection _Direction)
	{
		FVector DirectionVector;

		switch (_Direction)
		{
		case EDirection::Left:
			DirectionVector = FVector::Left;
			break;
		case EDirection::Right:
			DirectionVector = FVector::Right;
			break;
		case EDirection::Up:
			DirectionVector = FVector::Up;
			break;
		case EDirection::Down:
			DirectionVector = FVector::Down;
			break;
		default:
			DirectionVector = FVector::Zero;
			break;
		}

		return DirectionVector;
	}

	std::string MakeDirectionToString(EDirection _Direction)
	{
		std::string DirectionName;

		switch (_Direction)
		{
		case EDirection::Left:
			DirectionName = "Left";
			break;
		case EDirection::Right:
			DirectionName = "Right";
			break;
		case EDirection::Up:
			DirectionName = "Up";
			break;
		case EDirection::Down:
			DirectionName = "Down";
			break;
		default:
			DirectionName = "Null";
			break;
		}

		return DirectionName;
	}
}

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();

	FVector HalfScale = GEngine->MainWindow.GetWindowScale().Half2D();
	SetActorLocation(HalfScale);

	{
		HeadRenderer = CreateImageRenderer(IsaacRenderOrder::PlayerHead);
		HeadRenderer->SetImage("Head.png");
		HeadRenderer->SetTransform({ HeadRendererPos, RendererSize });
		HeadRenderer->CreateAnimation("HeadIdle", "Head.png", 7, 7, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Left", "Head.png", 1, 1, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Right", "Head.png", 3, 3, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Up", "Head.png", 5, 5, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Down", "Head.png", 7, 7, 0.1f, false);

		HeadRenderer->CreateAnimation("Attack_Left", "Head.png", 0, 1, 0.5f, false);
		HeadRenderer->CreateAnimation("Attack_Right", "Head.png", 2, 3, 0.5f, false);
		HeadRenderer->CreateAnimation("Attack_Up", "Head.png", 4, 5, 0.5f, false);
		HeadRenderer->CreateAnimation("Attack_Down", "Head.png", 6, 7, 0.5f, false);
	}

	{
		BodyRenderer = CreateImageRenderer(IsaacRenderOrder::PlayerBody);
		BodyRenderer->SetImage("Body.png");
		BodyRenderer->SetTransform({ BodyRendererPos, RendererSize });
		BodyRenderer->CreateAnimation("BodyIdle", "Body.png", 24, 24, 0.1f, false);
		BodyRenderer->CreateAnimation("BodyMove_Left", "Body.png", 0, 9, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Right", "Body.png", 10, 19, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_UP", "Body.png", 20, 29, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Down", "Body.png", 20, 29, 0.1f, true);
	}

	{
		BodyCollision = CreateCollision(IsaacCollisionOrder::Player);
		BodyCollision->SetColType(ECollisionType::CirCle);
		BodyCollision->SetScale({ 30,30 });
	}

	AttackStateChange(EPlayerAttackState::AttackIdle);
	PlayAttackIdleAnimation();
	MoveStateChange(EPlayerMoveState::Idle);
	PlayMoveIdleAnimation();
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AttackStateUpdate(_DeltaTime);
	MoveStateUpdate(_DeltaTime);
}

// Head
void APlayer::AttackStateUpdate(float _DeltaTime)
{
	switch (AttackState)
	{
	case EPlayerAttackState::AttackIdle:
		AttackIdle(_DeltaTime);
		break;
	case EPlayerAttackState::Attack:
		Attack(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::AttackIdle(float _DeltaTime)
{
	EDirection AttackDirection = GetAttackDirection();

	if (AttackDirection != EDirection::None)
	{
		AttackStateChange(EPlayerAttackState::Attack);
	}
}

EDirection APlayer::GetAttackDirection()
{
	EDirection AttackDirection = EDirection::None;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AttackDirection = EDirection::Left;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AttackDirection = EDirection::Right;
	}
	if (UEngineInput::IsPress(VK_UP))
	{
		AttackDirection = EDirection::Up;
	}
	if (UEngineInput::IsPress(VK_DOWN))
	{
		AttackDirection = EDirection::Down;
	}

	return AttackDirection;
}

void APlayer::Attack(float _DeltaTime)
{
	EDirection AttackDirection = GetAttackDirection();
	FireTime += _DeltaTime;

	if (AttackDirection != EDirection::None)
	{
		if (FireTime >= FireRate)
		{
			std::string AttackAnimationName = "Attack_" + MakeDirectionToString(AttackDirection);
			HeadRenderer->ChangeAnimation(AttackAnimationName);
			CreateBullet(AttackDirection);

			FireTime -= FireRate;
		}

		AttackIdleTime = 0;
	}
	else
	{
		AttackIdleTime += _DeltaTime;
		if (AttackIdleTime > AttackFinishTime)
		{
			AttackStateChange(EPlayerAttackState::AttackIdle);
			PlayAttackIdleAnimation();

			AttackIdleTime = 0;
		}
	}
}

void APlayer::CreateBullet(EDirection Direction)
{
	ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
	NewBullet->SetActorLocation(GetActorLocation());
	NewBullet->SetDir(MakeDirectionToFVector(Direction));
}

void APlayer::PlayAttackIdleAnimation()
{
	std::string MoveAnimationName = "HeadMove_" + MakeDirectionToString(MoveDirection);
	HeadRenderer->ChangeAnimation(MoveAnimationName);
}

void APlayer::AttackStateChange(EPlayerAttackState _State)
{
	AttackState = _State;
}

void APlayer::MoveStateUpdate(float _DeltaTime)
{
	switch (MoveState)
	{
	case EPlayerMoveState::Idle:
		MoveIdle(_DeltaTime);
		break;
	case EPlayerMoveState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::MoveIdle(float _DeltaTime)
{
	EDirection PushedDirection = GetPushedKeyMoveDirection();

	if (PushedDirection != EDirection::None)
	{
		MoveStateChange(EPlayerMoveState::Move);
		return;
	}

	BodyMoveUpdate(_DeltaTime);
}

void APlayer::Move(float _DeltaTime)
{
	EDirection PushedDirection = GetPushedKeyMoveDirection();

	if (PushedDirection != EDirection::None)
	{
		MoveDirection = PushedDirection;

		//if문 임시코드 : 공격중이 아닐때만, 머리 몸방향으로 움직이도록
		if (AttackState == EPlayerAttackState::AttackIdle)
		{
			std::string HeadMoveAnimationName = "HeadMove_" + MakeDirectionToString(MoveDirection);
			HeadRenderer->ChangeAnimation(HeadMoveAnimationName);
		}
		std::string BodyMoveAnimationName = "BodyMove_" + MakeDirectionToString(MoveDirection);
		BodyRenderer->ChangeAnimation(BodyMoveAnimationName);
	}

	if (UEngineInput::IsPress('A'))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}
	if (UEngineInput::IsPress('D'))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}
	if (UEngineInput::IsPress('W'))
	{
		AddMoveVector(FVector::Up * _DeltaTime);
	}
	if (UEngineInput::IsPress('S'))
	{
		AddMoveVector(FVector::Down * _DeltaTime);
	}

	BodyMoveUpdate(_DeltaTime);

	if (UEngineInput::IsFree('A') && UEngineInput::IsFree('D') && UEngineInput::IsFree('W') && UEngineInput::IsFree('S'))
	{
		MoveStateChange(EPlayerMoveState::Idle);
		MoveDirection = EDirection::Down;
		PlayMoveIdleAnimation();
	}
}

void APlayer::PlayMoveIdleAnimation()
{
	HeadRenderer->ChangeAnimation("HeadIdle");
	BodyRenderer->ChangeAnimation("BodyIdle");
}

void APlayer::MoveStateChange(EPlayerMoveState _State)
{
	MoveState = _State;
}

EDirection APlayer::GetPushedKeyMoveDirection()
{
	//TODO: 키가 여러개 같이 눌렸을때는, 먼저 눌린키를 반환값으로 하도록 수정해야함

	EDirection InputDirection = EDirection::None;
	if (UEngineInput::IsPress('A'))
	{
		InputDirection = EDirection::Left;
	}
	if (UEngineInput::IsPress('D'))
	{
		InputDirection = EDirection::Right;
	}
	if (UEngineInput::IsPress('W'))
	{

		InputDirection = EDirection::Up;
	}
	if (UEngineInput::IsPress('S'))
	{
		InputDirection = EDirection::Down;
	}

	return InputDirection;
}

void APlayer::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void APlayer::BodyMoveUpdate(float _DeltaTime)
{
	CalLastMoveVector(_DeltaTime);
	CalMoveVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime);
}

void APlayer::CalMoveVector(float _DeltaTime)
{
	if (UEngineInput::IsFree('A') && UEngineInput::IsFree('D') && UEngineInput::IsFree('W') && UEngineInput::IsFree('S'))
	{
		if (100 <= MoveVector.Size2D())
		{
			MoveVector += (-MoveVector.Normalize2DReturn()) * _DeltaTime * StopAcc;
		}
		else
		{
			MoveVector = float4::Zero;
		}
	}

	if (MoveMaxSpeed <= MoveVector.Size2D())
	{
		MoveVector = MoveVector.Normalize2DReturn() * MoveMaxSpeed;
	}
}

void APlayer::CalLastMoveVector(float _DeltaTime)
{
	LastMoveVector = FVector::Zero;
	LastMoveVector = LastMoveVector + MoveVector;
}

void APlayer::MoveLastMoveVector(float _DeltaTime)
{
	FVector PlayerPos = GetActorLocation();
	FVector PlayerNextPos = PlayerPos + MoveVector * _DeltaTime;
	if (PlayerNextPos.X < 138)
	{
		LastMoveVector.X = 0.0f;
	}
	if (PlayerNextPos.Y < 80)
	{
		LastMoveVector.Y = 0.0f;
	}
	if (PlayerNextPos.X > 820)
	{
		LastMoveVector.X = 0.0f;
	}
	if (PlayerNextPos.Y > 460)
	{
		LastMoveVector.Y = 0.0f;
	}

	AddActorLocation(LastMoveVector * _DeltaTime);
}