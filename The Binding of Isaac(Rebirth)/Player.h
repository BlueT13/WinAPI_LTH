#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class APlayer : public AActor
{
private:
	static APlayer* MainPlayer;

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// AttackState
	void AttackStateUpdate(float _DeltaTime);
	void AttackIdle(float _DeltaTime);
	void HeadMove(float _DeltaTime);
	void Attack(float _DeltaTime);
	void CreateBullet(EDirection Direction);
	void AttackStateChange(EPlayerAttackState _State);

	void PlayAttackIdleAnimation();
	void PlayAttackingAnimation();
	void AttackStart();

	EDirection GetAttackDirection();

	// MoveState
	void MoveStateUpdate(float _DeltaTime);
	void MoveIdle(float _DeltaTime);
	void Move(float _DeltaTime);
	void MoveStateChange(EPlayerMoveState _State);

	void PlayMoveIdleAnimation();
	void BodyMoveStart();
	EDirection GetPushedKeyMoveDirection();

	std::string GetHeadAnimationName(std::string _HeadAni);
	std::string GetBodyAnimationName(std::string _BodyAni);

	EPlayerAttackState AttackState = EPlayerAttackState::None;
	EPlayerMoveState MoveState = EPlayerMoveState::None;

	EDirection MoveDirection = EDirection::Down;

private:
	float FireRate = 0.2f;
	float FireTime = FireRate;

	UImageRenderer* HeadRenderer = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	FVector HeadRendererPos = { 0,-28 };
	FVector BodyRendererPos = { 0,0 };
	FVector RendererSize = { 64,64 };

	UCollision* BodyCollision = nullptr;

	float AttackIdleTime = 0.0f;
	const float AttackFinishTime = 0.25f;

	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
	float AlphaTime = 0.0f;
	bool Dir = false;

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = { 2500.0f, 2500.0f };
	FVector StopAcc = { 2000.0f, 2000.0f };
	float MoveMaxSpeed = 330.0f;
	void AddMoveVector(const FVector& _DirDelta);

	FVector LastMoveVector = FVector::Zero;
	void BodyMoveUpdate(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void CalLastMoveVector(float _DeltaTime);

	void PlayInitialAnimation();
};