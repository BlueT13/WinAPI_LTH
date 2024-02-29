#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	static APlayer* GetMainPlayer();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// Head
	void HeadStateUpdate(float _DeltaTime);
	void HeadIdle(float _DeltaTime);
	void HeadMove(float _DeltaTime);
	void Attack(float _DeltaTime);
	void CreateBullet(FVector _Dir);
	void HeadStateChange(EPlayerHeadState _State);
	void HeadIdleStart();
	void HeadMoveStart();
	void AttackStart();
	void HeadDirCheck();

	// Body
	void BodyStateUpdate(float _DeltaTime);
	void BodyIdle(float _DeltaTime);
	void BodyMove(float _DeltaTime);
	void BodyStateChange(EPlayerBodyState _State);
	void BodyIdleStart();
	void BodyMoveStart();
	void BodyDirCheck();

	std::string GetHeadAnimationName(std::string _HeadAni);
	std::string GetBodyAnimationName(std::string _BodyAni);

	EPlayerHeadState HeadState = EPlayerHeadState::None;
	EPlayerBodyState BodyState = EPlayerBodyState::None;
	EActorDir HeadDirState = EActorDir::Down;
	EActorDir BodyDirState = EActorDir::Down;
	std::string CurHeadAnimationName = "None";
	std::string CurBodyAnimationName = "None";

private:
	static APlayer* MainPlayer;

	float FireRate = 0.5f;
	float BlinkTime = 0.1f;
	float BulletCoolTime = 0.0f;

	UImageRenderer* HeadRenderer = nullptr;
	UImageRenderer* BodyRenderer = nullptr;
	FVector HeadRendererPos = { 0,-28 };
	FVector BodyRendererPos = { 0,0 };
	const FVector RendererSize = { 64,64 };

	UCollision* PlayerCollision = nullptr;

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
