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

	SetActorLocation({ 300, 300 });

	/*{
		HeadRenderer = CreateImageRenderer(IsaacRenderOrder::Player);
		HeadRenderer->SetImage("Head.png");
		HeadRenderer->SetTransform({ { 0,0 }, { 50,50 } });
		HeadRenderer->SetImageCuttingTransform({ {0,0}, {30, 30} });
	}*/

	{
		BodyRenderer = CreateImageRenderer(IsaacRenderOrder::Player);
		BodyRenderer->SetImage("IsaacRight_0.png");
		UWindowImage* Image = BodyRenderer->GetImage();
		FVector ImageScale = Image->GetScale();
		BodyRenderer->SetTransform({ { 0,10 }, ImageScale });
	}
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

	//if (true == UEngineInput::IsPress('A'))
	//{
	//	AddActorLocation(FVector::Left * 500.0f * _DeltaTime);

	//}

	//if (true == UEngineInput::IsPress('D'))
	//{
	//	AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	//}

	//if (true == UEngineInput::IsPress('W'))
	//{
	//	AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	//}

	//if (true == UEngineInput::IsPress('S'))
	//{
	//	AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	//}

	//if (true == UEngineInput::IsDown('T'))
	//{
	//	BodyRenderer->Destroy();
	//}

	//if (true == UEngineInput::IsDown('Q'))
	//{
	//	ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
	//	NewBullet->SetActorLocation(GetActorLocation());
	//	NewBullet->SetDir(FVector::Right);
	//}
}

void APlayer::DirCheck()
{
	EActorDir Dir = DirState;
	if (UEngineInput::IsPress('A'))
	{
		Dir = EActorDir::Left;
	}
	if (UEngineInput::IsPress('D'))
	{
		Dir = EActorDir::Right;
	}
	if (UEngineInput::IsPress('W'))
	{
		Dir = EActorDir::Up;
	}
	if (UEngineInput::IsPress('S'))
	{
		Dir = EActorDir::Down;
	}
}

std::string APlayer::GetAnimationName(std::string _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
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

void APlayer::Move(float _DeltaTime)
{
	DirCheck();

	if (UEngineInput::IsFree('A') && UEngineInput::IsFree('D') && UEngineInput::IsFree('W') && UEngineInput::IsFree('S') &&
		UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsPress(VK_UP) && UEngineInput::IsPress(VK_DOWN))
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
}

