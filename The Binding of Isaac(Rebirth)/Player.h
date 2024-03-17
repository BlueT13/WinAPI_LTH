#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"
#include "PlayLevel.h"
#include <EnginePlatform/EngineSound.h>

// ¼³¸í :
class APlayer : public AActor
{
	friend class ARoom;
	friend class AMonster;
	friend class ABoomfly;
	friend class AMonsterBullet;
	friend class ABomb;
	friend class AItem;
public:
	static bool IsFreeCamera;
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	static APlayer* GetMainPlayer();
	UCollision* GetPlayerCollision();
	float GetPlayerMaxSpeed();
	void SetHitPower(const FVector& _Vector)
	{
		HitPower = _Vector;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// Head
	void HeadStateUpdate(float _DeltaTime);
	void HeadIdle(float _DeltaTime);
	void HeadMove(float _DeltaTime);
	void Attack(float _DeltaTime);
	void CreateBullet(FVector _Dir);
	void GetHit(float _DeltaTime);
	void HeadStateChange(EPlayerHeadState _State);
	void HeadIdleStart();
	void HeadMoveStart();
	void AttackStart();
	void GetHitStart();
	void HeadDirCheck();

	// Body
	void BodyStateUpdate(float _DeltaTime);
	void BodyIdle(float _DeltaTime);
	void BodyMove(float _DeltaTime);
	void BodyWait(float _DeltaTime);
	void Die(float _DeltaTime);
	void BodyStateChange(EPlayerBodyState _State);
	void BodyIdleStart();
	void BodyMoveStart();
	void DieStart();
	void BodyDirCheck();

	void CreateBomb();

	std::string GetHeadAnimationName(std::string _HeadAni);
	std::string GetBodyAnimationName(std::string _BodyAni);

	EPlayerHeadState HeadState = EPlayerHeadState::None;
	EPlayerBodyState BodyState = EPlayerBodyState::None;
	EActorDir HeadDirState = EActorDir::Down;
	EActorDir BodyDirState = EActorDir::Down;

private:
	static APlayer* MainPlayer;

	int PlayerHp = 6;
	float FireRate = 0.0f;
	float BlinkTime = 0.0f;
	float BulletCoolTime = 0.0f;

	UImageRenderer* HeadRenderer = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	UImageRenderer* PlayerStateRenderer = nullptr;
	FVector HeadRendererPos = { 0, -28 };
	FVector BodyRendererPos = { 0, 0 };
	FVector PlayerStateRendererPos = { 0, -20 };
	FVector HitPower = { 0, 0 };
	const FVector RendererSize = { 64,64 };
	const FVector PlayerStateRendererSize = { 128,128 };

	UCollision* PlayerCollision = nullptr;

	std::string CurHeadAnimationName = "None";
	std::string CurBodyAnimationName = "None";

	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
	float AlphaTime = 0.0f;
	bool Dir = false;

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = { 2500.0f, 2500.0f };
	FVector StopAcc = { 2000.0f, 2000.0f };
	float PlayerMaxSpeed = 330.0f;
	FVector LastMoveVector = FVector::Zero;

	void AddMoveVector(const FVector& _DirDelta);
	void BodyMoveUpdate(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void CalHitPower(float _DeltaTime);
	void CalLastMoveVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);

	float HitTime = 0.3f;
	float ChangeRoomTime = 0.3f;

	UEngineSoundPlayer GetHitSound;
	UEngineSoundPlayer TearFireSound;
	UEngineSoundPlayer DeathSound;
};