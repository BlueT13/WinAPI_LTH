#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class AMonster : public AActor
{
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void MonsterDirCheck();
	//std::string GetAnimationName(std::string _Name);

	//void StateChange(EMonsterState _State);
	//void StateUpdate(float _DeltaTime);

	//void Idle(float _DeltaTime);
	//void Move(float _DeltaTime);
	//void Attack(float _DeltaTime);

	EMonsterState State = EMonsterState::None;
	EActorDir DirState = EActorDir::None;
	
	UImageRenderer* MonsterRenderer = nullptr;
	UCollision* MonsterCollision = nullptr;
private:
};

