#include "Player.h"
#include "Bullet.h"
#include "Bomb.h"
#include "UIManager.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineDebug.h>
#include "ContentsHelper.h"
#include "PlayLevel.h"

bool APlayer::IsFreeCamera = false;

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

APlayer* APlayer::MainPlayer = nullptr;
APlayer* APlayer::GetMainPlayer()
{
	return MainPlayer;
}
UCollision* APlayer::GetPlayerCollision()
{
	return PlayerCollision;
}

float APlayer::GetPlayerMaxSpeed()
{
	return PlayerMaxSpeed;
}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();
	MainPlayer = this;

	FireRate = 0.5f;
	BlinkTime = 0.1f;
	BulletCoolTime = 0.0f;

	// Renderer
	{
		HeadRenderer = CreateImageRenderer(IsaacRenderOrder::PlayerHead);
		HeadRenderer->SetImage("Head.png");
		HeadRenderer->SetTransform({ HeadRendererPos, RendererSize });
		HeadRenderer->CreateAnimation("HeadIdle", "Head.png", 7, 7, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Left", "Head.png", 1, 1, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Right", "Head.png", 3, 3, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Up", "Head.png", 5, 5, 0.1f, false);
		HeadRenderer->CreateAnimation("HeadMove_Down", "Head.png", 7, 7, 0.1f, false);

		HeadRenderer->CreateAnimation("Attack_Left", "Head.png", { 0, 0, 1 }, { BlinkTime, FireRate - BlinkTime * 2, BlinkTime }, true);
		HeadRenderer->CreateAnimation("Attack_Right", "Head.png", { 2, 3, 3 }, { BlinkTime, FireRate - BlinkTime * 2, BlinkTime }, true);
		HeadRenderer->CreateAnimation("Attack_Up", "Head.png", { 4, 5, 5 }, { BlinkTime, FireRate - BlinkTime * 2, BlinkTime }, true);
		HeadRenderer->CreateAnimation("Attack_Down", "Head.png", { 6, 7, 7 }, { BlinkTime, FireRate - BlinkTime * 2, BlinkTime }, true);
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
	{
		PlayerStateRenderer = CreateImageRenderer(IsaacRenderOrder::PlayerState);
		PlayerStateRenderer->SetImage("PlayerState.png");
		PlayerStateRenderer->SetTransform({ PlayerStateRendererPos ,PlayerStateRendererSize });
		PlayerStateRenderer->CreateAnimation("GetHit", "PlayerState.png", 6, 6, 1.0f, false);
		PlayerStateRenderer->CreateAnimation("Die", "PlayerState.png", { 0, 3 }, 0.3f, false);
	}

	// Collision
	{
		PlayerCollision = CreateCollision(IsaacCollisionOrder::Player);
		PlayerCollision->SetColType(ECollisionType::CirCle);
		PlayerCollision->SetTransform({ {0, -14} ,{ 40, 40 } });
	}

	HeadStateChange(EPlayerHeadState::Idle);
	BodyStateChange(EPlayerBodyState::Idle);
	PlayerStateRenderer->SetActive(false);
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UContentsHelper::MainPlayerLocation = this->GetActorLocation();

	if (UEngineInput::IsDown('Q'))
	{
		if (PlayerCollision->IsActive())
		{
			PlayerCollision->SetActive(false);
		}
		else
		{
			PlayerCollision->SetActive(true);
		}
	}

	if (UEngineInput::IsDown('F'))
	{
		IsFreeCamera = !IsFreeCamera;
	}

	if (true == IsFreeCamera)
	{
		if (UEngineInput::IsPress(VK_LEFT))
		{
			GetWorld()->AddCameraPos(FVector::Left * 10);
			IsFreeCamera = true;
		}

		if (UEngineInput::IsPress(VK_RIGHT))
		{
			GetWorld()->AddCameraPos(FVector::Right * 10);
			IsFreeCamera = true;
		}

		if (UEngineInput::IsPress(VK_UP))
		{
			GetWorld()->AddCameraPos(FVector::Up * 10);
			IsFreeCamera = true;
		}

		if (UEngineInput::IsPress(VK_DOWN))
		{
			GetWorld()->AddCameraPos(FVector::Down * 10);
			IsFreeCamera = true;
		}

		return;
	}

	HeadStateUpdate(_DeltaTime);
	BodyStateUpdate(_DeltaTime);
	CreateBomb();

	BulletCoolTime -= _DeltaTime;
}

// Head
void APlayer::HeadStateUpdate(float _DeltaTime)
{
	switch (HeadState)
	{
	case EPlayerHeadState::Idle:
		HeadIdle(_DeltaTime);
		break;
	case EPlayerHeadState::Move:
		HeadMove(_DeltaTime);
		break;
	case EPlayerHeadState::Attack:
		Attack(_DeltaTime);
		break;
	case EPlayerHeadState::GetHit:
		GetHit(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::HeadIdle(float _DeltaTime)
{
	if (UEngineInput::IsPress('A') || UEngineInput::IsPress('D') || UEngineInput::IsPress('W') || UEngineInput::IsPress('S'))
	{
		HeadStateChange(EPlayerHeadState::Move);
		return;
	}

	if (UEngineInput::IsDown(VK_LEFT) || UEngineInput::IsDown(VK_RIGHT) || UEngineInput::IsDown(VK_UP) || UEngineInput::IsDown(VK_DOWN))
	{
		HeadStateChange(EPlayerHeadState::Attack);
		return;
	}
}

void APlayer::HeadMove(float _DeltaTime)
{
	HeadDirCheck();

	if (UEngineInput::IsDown(VK_LEFT) || UEngineInput::IsDown(VK_RIGHT) || UEngineInput::IsDown(VK_UP) || UEngineInput::IsDown(VK_DOWN))
	{
		HeadStateChange(EPlayerHeadState::Attack);
		return;
	}

	if (UEngineInput::IsFree('A') && UEngineInput::IsFree('D') && UEngineInput::IsFree('W') && UEngineInput::IsFree('S'))
	{
		HeadStateChange(EPlayerHeadState::Idle);
		return;
	}
}

void APlayer::Attack(float _DeltaTime)
{
	HeadDirCheck();

	if (BulletCoolTime < 0)
	{
		if (UEngineInput::IsPress(VK_LEFT))
		{
			CreateBullet(FVector::Left);
		}
		else if (UEngineInput::IsPress(VK_RIGHT))
		{
			CreateBullet(FVector::Right);
		}
		else if (UEngineInput::IsPress(VK_UP))
		{
			CreateBullet(FVector::Up);
		}
		else if (UEngineInput::IsPress(VK_DOWN))
		{
			CreateBullet(FVector::Down);
		}
		BulletCoolTime = FireRate;
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT) && UEngineInput::IsFree(VK_UP) && UEngineInput::IsFree(VK_DOWN))
	{
		HeadStateChange(EPlayerHeadState::Move);
		return;
	}

}

void APlayer::CreateBullet(FVector _Dir)
{
	ABullet* Tear = GetWorld()->SpawnActor<ABullet>(IsaacUpdateOrder::Bullet);
	Tear->SetActorLocation(GetActorLocation());
	Tear->SetDir(_Dir);
}

void APlayer::GetHit(float _DeltaTime)
{
	if (PlayerHp <= 0)
	{
		BodyStateChange(EPlayerBodyState::Die);
		return;
	}

	HitTime -= _DeltaTime;
	if (HitTime <= 0.0f)
	{
		PlayerStateRenderer->SetActive(false);
		HeadRenderer->SetActive(true);
		BodyRenderer->SetActive(true);
		HeadStateChange(EPlayerHeadState::Attack);
		BodyStateChange(EPlayerBodyState::Idle);
		HitTime = 0.3f;
	}
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
		case EPlayerHeadState::Move:
			HeadMoveStart();
			break;
		case EPlayerHeadState::Attack:
			AttackStart();
			break;
		case EPlayerHeadState::GetHit:
			GetHitStart();
			break;
		default:
			break;
		}
	}

	HeadState = _State;
}

void APlayer::HeadIdleStart()
{
	HeadRenderer->ChangeAnimation("HeadIdle");
}

void APlayer::HeadMoveStart()
{
	HeadRenderer->ChangeAnimation(GetHeadAnimationName("HeadMove"));

	HeadDirCheck();
}

void APlayer::AttackStart()
{
	HeadRenderer->ChangeAnimation(GetHeadAnimationName("Attack"));

	HeadDirCheck();
}

void APlayer::GetHitStart()
{
	PlayerHp--;
	HeadRenderer->SetActive(false);
	BodyRenderer->SetActive(false);
	PlayerStateRenderer->SetActive(true);
	PlayerStateRenderer->ChangeAnimation("GetHit");
	GetHitSound = UEngineSound::SoundPlay("hurt grunt .wav");
}

void APlayer::HeadDirCheck()
{
	EActorDir HeadDir = HeadDirState;

	if (UEngineInput::IsPress('A'))
	{
		HeadDir = EActorDir::Left;
	}
	if (UEngineInput::IsPress('D'))
	{
		HeadDir = EActorDir::Right;
	}
	if (UEngineInput::IsPress('W'))
	{
		HeadDir = EActorDir::Up;
	}
	if (UEngineInput::IsPress('S'))
	{
		HeadDir = EActorDir::Down;
	}

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

		HeadRenderer->ChangeAnimation(Name);
	}
}

// Body
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
	case EPlayerBodyState::Wait:
		BodyWait(_DeltaTime);
		break;
	case EPlayerBodyState::Die:
		Die(_DeltaTime);
		break;
	default:
		break;
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

void APlayer::BodyWait(float _DeltaTime)
{
	MoveVector = FVector::Zero;
	ChangeRoomTime -= _DeltaTime;
	if (ChangeRoomTime < 0.0f)
	{
		BodyStateChange(EPlayerBodyState::Idle);
		ChangeRoomTime = 0.3f;
	}
}

void APlayer::Die(float _DeltaTime)
{

	MoveVector = FVector::Zero;

	if (PlayerStateRenderer->IsCurAnimationEnd())
	{
		// 사망 이미지 랜더러 create
		UPlayLevel* Level = dynamic_cast<UPlayLevel*>(GetWorld());
		FVector CurRoomPos = Level->GetCurRoom()->GetActorLocation();

		UIManager::DeathPortrait->SetActive(true);
		Level->SetAllTimeScale(0.0f);
		if (UEngineInput::IsDown(VK_SPACE))
		{
			GEngine->DestroyLevel("PlayLevel");
		}
	}
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
		case EPlayerBodyState::Die:
			DieStart();
			break;
		default:
			break;
		}
	}

	BodyState = _State;
}

void APlayer::BodyIdleStart()
{
	BodyRenderer->ChangeAnimation("BodyIdle");
}

void APlayer::BodyMoveStart()
{
	BodyRenderer->ChangeAnimation(GetBodyAnimationName("BodyMove"));

	BodyDirCheck();
}

void APlayer::DieStart()
{
	HeadRenderer->SetActive(false);
	BodyRenderer->SetActive(false);
	PlayerStateRenderer->SetActive(true);
	PlayerStateRenderer->ChangeAnimation("Die");
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
		BodyRenderer->ChangeAnimation(Name);
	}
}

void APlayer::CreateBomb()
{
	if (UEngineInput::IsDown('E'))
	{
		ABomb* Bomb = GetWorld()->SpawnActor<ABomb>(IsaacUpdateOrder::Bomb);
		Bomb->SetActorLocation(GetActorLocation());
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

void APlayer::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void APlayer::BodyMoveUpdate(float _DeltaTime)
{
	CalLastMoveVector(_DeltaTime);
	CalMoveVector(_DeltaTime);
	CalHitPower(_DeltaTime);
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

	if (PlayerMaxSpeed <= MoveVector.Size2D())
	{
		MoveVector = MoveVector.Normalize2DReturn() * PlayerMaxSpeed;
	}
}

void APlayer::CalHitPower(float _DeltaTime)
{
	HitPower -= HitPower * _DeltaTime * 4;
	if (HitPower.Size2D() < 100.0f)
	{
		HitPower = FVector::Zero;
	}
}

void APlayer::CalLastMoveVector(float _DeltaTime)
{
	LastMoveVector = FVector::Zero;
	LastMoveVector += HitPower;
	LastMoveVector += MoveVector;
}

void APlayer::MoveLastMoveVector(float _DeltaTime)
{
	UPlayLevel* Level = dynamic_cast<UPlayLevel*>(GetWorld());

	FVector CurRoomPos = Level->GetCurRoom()->GetActorLocation();

	FVector PlayerPos = GetActorLocation();
	FVector PlayerNextPos = PlayerPos + LastMoveVector * _DeltaTime;
	if (PlayerNextPos.X < CurRoomPos.X - 320)
	{
		LastMoveVector.X = 0.0f;
	}
	if (PlayerNextPos.Y < CurRoomPos.Y - 170)
	{
		LastMoveVector.Y = 0.0f;
	}
	if (PlayerNextPos.X > CurRoomPos.X + 320)
	{
		LastMoveVector.X = 0.0f;
	}
	if (PlayerNextPos.Y > CurRoomPos.Y + 170)
	{
		LastMoveVector.Y = 0.0f;
	}

	AddActorLocation(LastMoveVector * _DeltaTime);
}