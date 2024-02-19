#include "Player.h"
#include <EngineCore/EngineCore.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include <EngineBase\EngineTime.h>
#include <vector>
#include <list>

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
		BodyRenderer->SetTransform({ { 0,10 }, ImageScale});
	}
}

void APlayer::Tick(float _DeltaTime)
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

void APlayer::DirCheck()
{
}

void APlayer::StateChange(EPlayState _State)
{
}

void APlayer::StateUpdate(float _DeltaTime)
{
}

void APlayer::CameraFreeMove(float _DeltaTime)
{
}

void APlayer::FreeMove(float _DeltaTime)
{
}

void APlayer::Idle(float _DeltaTime)
{
}

void APlayer::Run(float _DeltaTime)
{
}

void APlayer::Attack(float _DeltaTime)
{
}

void APlayer::IdleStart()
{
}

void APlayer::RunStart()
{
}

void APlayer::CalMoveVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	default:
		break;
	}

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);

	if (Color == Color8Bit(255, 0, 255, 0))
	{
		MoveVector = FVector::Zero;
	}

	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		//static int Count = 0;
		//EngineDebug::OutPutDebugText(std::to_string(++Count));
		if (0.001 <= MoveVector.Size2D())
		{
			MoveVector += (-MoveVector.Normalize2DReturn()) * _DeltaTime * MoveAcc;
		}
		else {
			MoveVector = float4::Zero;
		}
	}

	if (MoveMaxSpeed <= MoveVector.Size2D())
	{
		MoveVector = MoveVector.Normalize2DReturn() * MoveMaxSpeed;
	}
}

void APlayer::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void APlayer::CalLastMoveVector(float _DeltaTime)
{
}

void APlayer::MoveLastMoveVector(float _DeltaTime)
{
	AddActorLocation(LastMoveVector * _DeltaTime);
}

void APlayer::MoveUpdate(float _DeltaTime)
{
}
