#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// 설명 :
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

	void DirCheck();

	std::string GetAnimationName(std::string _Name);

	// 상태 주요 업데이트
	void StateChange(EPlayState _State);
	void StateUpdate(float _DeltaTime);

	// 상태 함수들
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);

	// 상태 시작 함수들
	void IdleStart();
	void MoveStart();
	void AttackStart();

	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";

private:
	float fireRate = 0.0f;

	UImageRenderer* HeadRenderer = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	UCollision* BodyCollision = nullptr;

	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
	float AlphaTime = 0.0f;
	bool Dir = false;

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = { 3000.0f, 3000.0f };
	FVector StopAcc = { 2000.0f, 2000.0f };
	float MoveMaxSpeed = 360.0f;
	void AddMoveVector(const FVector& _DirDelta);

	FVector LastMoveVector = FVector::Zero;
	void MoveUpdate(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void CalLastMoveVector(float _DeltaTime);
};
