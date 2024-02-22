#include "Player.h"
#include "Bullet.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineDebug.h>
#include "ContentsHelper.h"

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
		HeadRenderer->SetTransform({ { 0,0 }, { 64,64 } });
		HeadRenderer->CreateAnimation("HeadIdle", "Head.png", 7, 7, 0.1f, true);
		HeadRenderer->CreateAnimation("HeadMove_Left", "Head.png", 1, 1, 0.1f, true);
		HeadRenderer->CreateAnimation("HeadMove_Right", "Head.png", 3, 3, 0.1f, true);
		HeadRenderer->CreateAnimation("HeadMove_Up", "Head.png", 5, 5, 0.1f, true);
		HeadRenderer->CreateAnimation("HeadMove_Down", "Head.png", 7, 7, 0.1f, true);
		
		HeadRenderer->CreateAnimation("Attack_Left", "Head.png", 0, 1, fireRate, true);
		HeadRenderer->CreateAnimation("Attack_Right", "Head.png", 2, 3, fireRate, true);
		HeadRenderer->CreateAnimation("Attack_Up", "Head.png", 4, 5, fireRate, true);
		HeadRenderer->CreateAnimation("Attack_Down", "Head.png", 6, 7, fireRate, true);
	}

	{
		BodyRenderer = CreateImageRenderer(IsaacRenderOrder::PlayerBody);
		BodyRenderer->SetImage("Body.png");
		BodyRenderer->SetTransform({ { 0,28 }, {64,64} });
		BodyRenderer->CreateAnimation("BodyIdle", "Body.png", 24, 24, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Left", "Body.png", 0, 9, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Right", "Body.png", 10, 19, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_UP", "Body.png", 20, 29, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Down", "Body.png", 20, 29, 0.1f, true);
	}

	StateChange(EPlayState::Idle);
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void APlayer::BodyDirCheck()
{
	EActorDir BodyDir = BodyDirState;
	if (UEngineInput::IsPress('A'))
	{
		BodyDir = EActorDir::Left;
	}
	if (UEngineInput::IsPress('D'))
	{
		BodyDir = EActorDir::Right;
	}
	if (UEngineInput::IsPress('W'))
	{
		BodyDir = EActorDir::Up;
	}
	if (UEngineInput::IsPress('S'))
	{
		BodyDir = EActorDir::Down;
	}

	if (BodyDir != BodyDirState)
	{
		BodyDirState = BodyDir;
		std::string Name = GetAnimationName(CurAnimationName);

		BodyRenderer->ChangeAnimation(Name, true, BodyRenderer->GetCurAnimationFrame(), BodyRenderer->GetCurAnimationTime());
	}
}

void APlayer::HeadDirCheck()
{
	EActorDir HeadDir = HeadDirState;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		HeadDir = EActorDir::Left;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		HeadDir = EActorDir::Right;
	}
	if (UEngineInput::IsPress(VK_UP))
	{
		HeadDir = EActorDir::Up;
	}
	if (UEngineInput::IsPress(VK_DOWN))
	{
		HeadDir = EActorDir::Down;
	}

	if (HeadDir != HeadDirState)
	{
		HeadDirState = HeadDir;
		std::string Name = GetAnimationName(CurAnimationName);

		BodyRenderer->ChangeAnimation(Name, true, BodyRenderer->GetCurAnimationFrame(), BodyRenderer->GetCurAnimationTime());
	}
}

std::string APlayer::GetAnimationName(std::string _Name)
{
	std::string DirName = "";

	switch (BodyDirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	case EActorDir::Up:
		DirName = "_Up";
		break;
	case EActorDir::Down:
		DirName = "_Down";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + DirName;
}

void APlayer::StateChange(EPlayState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Move:
			MoveStart();
			break;
		case EPlayState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void APlayer::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Move:
		Move(_DeltaTime);
		break;
	case EPlayState::Attack:
		Attack(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::Idle(float _DeltaTime)
{
	if (true == BodyRenderer->IsCurAnimationEnd())
	{
	}

	if (UEngineInput::IsPress('A') || UEngineInput::IsPress('D') || UEngineInput::IsPress('W') || UEngineInput::IsPress('S'))
	{
		StateChange(EPlayState::Move);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT) || UEngineInput::IsPress(VK_UP) || UEngineInput::IsPress(VK_DOWN))
	{
		StateChange(EPlayState::Attack);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void APlayer::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void APlayer::MoveUpdate(float _DeltaTime)
{
	CalLastMoveVector(_DeltaTime);
	CalMoveVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime);
}

void APlayer::CalMoveVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();
	switch (BodyDirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	case EActorDir::Up:
		CheckPos.Y -= 30;
		break;
	case EActorDir::Down:
		CheckPos.Y += 30;
		break;
	default:
		break;
	}
	
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		MoveVector = FVector::Zero;
	}

	if (UEngineInput::IsFree('A') && UEngineInput::IsFree('D') && UEngineInput::IsFree('W') && UEngineInput::IsFree('S') &&
		UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT) && UEngineInput::IsFree(VK_UP) && UEngineInput::IsFree(VK_DOWN))
	{
		if (10 <= MoveVector.Size2D())
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
	AddActorLocation(LastMoveVector * _DeltaTime);
}

void APlayer::Move(float _DeltaTime)
{
	BodyDirCheck();

	if (UEngineInput::IsFree('A') && UEngineInput::IsFree('D') && UEngineInput::IsFree('W') && UEngineInput::IsFree('S') &&
		UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT) && UEngineInput::IsFree(VK_UP) && UEngineInput::IsFree(VK_DOWN))
	{
		StateChange(EPlayState::Idle);
		return;
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

	MoveUpdate(_DeltaTime);
}

void APlayer::Attack(float _DeltaTime)
{
	BodyDirCheck();

	if (UEngineInput::IsFree('A') && UEngineInput::IsFree('D') && UEngineInput::IsFree('W') && UEngineInput::IsFree('S') &&
		UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT) && UEngineInput::IsFree(VK_UP) && UEngineInput::IsFree(VK_DOWN))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	//if (true == UEngineInput::IsDown(VK_LEFT))
	//{
	//	ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
	//	NewBullet->SetActorLocation(GetActorLocation());
	//	NewBullet->SetDir(FVector::Left);
	//}
	//if (true == UEngineInput::IsDown(VK_RIGHT))
	//{
	//	ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
	//	NewBullet->SetActorLocation(GetActorLocation());
	//	NewBullet->SetDir(FVector::Right);
	//}
	//if (true == UEngineInput::IsDown(VK_UP))
	//{
	//	ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
	//	NewBullet->SetActorLocation(GetActorLocation());
	//	NewBullet->SetDir(FVector::Up);
	//}
	//if (true == UEngineInput::IsDown(VK_DOWN))
	//{
	//	ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
	//	NewBullet->SetActorLocation(GetActorLocation());
	//	NewBullet->SetDir(FVector::Down);
	//}

	MoveUpdate(_DeltaTime);
}

void APlayer::IdleStart()
{
	BodyDirCheck();
	HeadRenderer->ChangeAnimation("HeadIdle");
	BodyRenderer->ChangeAnimation("BodyIdle");
}

void APlayer::MoveStart()
{
	BodyDirCheck();
	HeadRenderer->ChangeAnimation(GetAnimationName("HeadMove"));
	BodyRenderer->ChangeAnimation(GetAnimationName("BodyMove"));
}

void APlayer::AttackStart()
{
	BodyDirCheck();
	HeadRenderer->ChangeAnimation(GetAnimationName("Attack"));
}

