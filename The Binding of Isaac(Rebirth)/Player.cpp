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
		HeadRenderer->SetTransform({ HeadRendererPos, RendererSize });
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
		BodyRenderer->SetTransform({ BodyRendererPos, RendererSize });
		BodyRenderer->CreateAnimation("BodyIdle", "Body.png", 24, 24, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Left", "Body.png", 0, 9, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Right", "Body.png", 10, 19, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_UP", "Body.png", 20, 29, 0.1f, true);
		BodyRenderer->CreateAnimation("BodyMove_Down", "Body.png", 20, 29, 0.1f, true);
	}

	HeadStateChange(EPlayerHeadState::Idle);
	BodyStateChange(EPlayerBodyState::Idle);
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	HeadStateUpdate(_DeltaTime);
	BodyStateUpdate(_DeltaTime);
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
		std::string Name = GetHeadAnimationName(CurHeadAnimationName);

		HeadRenderer->ChangeAnimation(Name, true, HeadRenderer->GetCurAnimationFrame(), HeadRenderer->GetCurAnimationTime());
	}
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
		std::string Name = GetBodyAnimationName(CurBodyAnimationName);

		BodyRenderer->ChangeAnimation(Name, true, BodyRenderer->GetCurAnimationFrame(), BodyRenderer->GetCurAnimationTime());
	}
}

std::string APlayer::GetHeadAnimationName(std::string _HeadAni)
{
	std::string DirName = "";

	switch (HeadDirState)
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

	CurHeadAnimationName = _HeadAni;

	return _HeadAni + DirName;
}

std::string APlayer::GetBodyAnimationName(std::string _BodyAni)
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

	CurBodyAnimationName = _BodyAni;

	return _BodyAni + DirName;
}

void APlayer::HeadStateChange(EPlayerHeadState _State)
{
	if (HeadState != _State)
	{
		switch (_State)
		{
		case EPlayerHeadState::Idle:
			HeadIdleStart();
			break;
		case EPlayerHeadState::Attack:
			HeadAttackStart();
			break;
		default:
			break;
		}
	}

	HeadState = _State;
}

void APlayer::BodyStateChange(EPlayerBodyState _State)
{
	if (BodyState != _State)
	{
		switch (_State)
		{
		case EPlayerBodyState::Idle:
			BodyIdleStart();
			break;
		case EPlayerBodyState::Move:
			BodyMoveStart();
			break;
		default:
			break;
		}
	}

	BodyState = _State;
}

void APlayer::HeadStateUpdate(float _DeltaTime)
{
	switch (HeadState)
	{
	case EPlayerHeadState::Idle:
		HeadIdle(_DeltaTime);
		break;
	case EPlayerHeadState::Attack:
		Attack(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::BodyStateUpdate(float _DeltaTime)
{
	switch (BodyState)
	{
	case EPlayerBodyState::Idle:
		BodyIdle(_DeltaTime);
		break;
	case EPlayerBodyState::Move:
		BodyMove(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::HeadIdle(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT) || UEngineInput::IsPress(VK_UP) || UEngineInput::IsPress(VK_DOWN))
	{
		HeadStateChange(EPlayerHeadState::Attack);
		return;
	}
}

void APlayer::BodyIdle(float _DeltaTime)
{
	if (UEngineInput::IsPress('A') || UEngineInput::IsPress('D') || UEngineInput::IsPress('W') || UEngineInput::IsPress('S'))
	{
		BodyStateChange(EPlayerBodyState::Move);
		return;
	}

	BodyMoveUpdate(_DeltaTime);
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
	if (PlayerNextPos.X < 100 || PlayerNextPos.Y < 100)
	{
		PlayerNextPos.X = 0.0f;
		return;
	}

	AddActorLocation(LastMoveVector * _DeltaTime);
}

void APlayer::BodyMove(float _DeltaTime)
{
	BodyDirCheck();

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
		BodyStateChange(EPlayerBodyState::Idle);
		return;
	}
}

void APlayer::Attack(float _DeltaTime)
{
	HeadDirCheck();

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT) && UEngineInput::IsFree(VK_UP) && UEngineInput::IsFree(VK_DOWN))
	{
		HeadStateChange(EPlayerHeadState::Idle);
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

	// MoveUpdate(_DeltaTime);
}

void APlayer::HeadIdleStart()
{
	HeadRenderer->ChangeAnimation("HeadIdle");

	HeadDirCheck();
}

void APlayer::BodyIdleStart()
{
	BodyRenderer->ChangeAnimation("BodyIdle");

	BodyDirCheck();
}

void APlayer::HeadMoveStart()
{
	HeadRenderer->ChangeAnimation(GetHeadAnimationName("HeadMove"));

	HeadDirCheck();
}

void APlayer::BodyMoveStart()
{
	BodyRenderer->ChangeAnimation(GetBodyAnimationName("BodyMove"));

	BodyDirCheck();
}

void APlayer::HeadAttackStart()
{
	HeadRenderer->ChangeAnimation(GetHeadAnimationName("Attack"));

	HeadDirCheck();
}

