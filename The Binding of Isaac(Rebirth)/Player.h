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

	void BodyDirCheck();
	void HeadDirCheck();

	std::string GetHeadAnimationName(std::string _HeadAni);
	std::string GetBodyAnimationName(std::string _BodyAni);

	// 상태 주요 업데이트
	void HeadStateChange(EPlayerHeadState _State);
	void HeadStateUpdate(float _DeltaTime);
	void BodyStateChange(EPlayerBodyState _State);
	void BodyStateUpdate(float _DeltaTime);


	// 상태 함수들
	void HeadIdle(float _DeltaTime);
	void BodyIdle(float _DeltaTime);
	void BodyMove(float _DeltaTime);
	void Attack(float _DeltaTime);

	// 상태 시작 함수들
	void HeadIdleStart();
	void BodyIdleStart();
	void HeadMoveStart();
	void BodyMoveStart();
	void HeadAttackStart();

	EPlayerHeadState HeadState = EPlayerHeadState::None;
	EPlayerBodyState BodyState = EPlayerBodyState::None;
	EActorDir BodyDirState = EActorDir::Down;
	EActorDir HeadDirState = EActorDir::Down;
	std::string CurHeadAnimationName = "None";
	std::string CurBodyAnimationName = "None";

private:
	float fireRate = 1.0f;

	UImageRenderer* HeadRenderer = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	FVector HeadRendererPos = { 0,-28 };

	UCollision* BodyCollision = nullptr;

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
};
