#pragma once
#include "Monster.h"
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class ADukeOfFlies : public AMonster
{
public:
	// constrcuter destructer
	ADukeOfFlies();
	~ADukeOfFlies();

	// delete Function
	ADukeOfFlies(const ADukeOfFlies& _Other) = delete;
	ADukeOfFlies(ADukeOfFlies&& _Other) noexcept = delete;
	ADukeOfFlies& operator=(const ADukeOfFlies& _Other) = delete;
	ADukeOfFlies& operator=(ADukeOfFlies&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MonsterStateUpdate(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void Move(float _DeltaTime);
	void SpawnFly(float _DeltaTime);
	void SendFly(float _DeltaTime);
	void Die(float _DeltaTime);
	void MonsterStateChange(EMonsterState _State) override;
	void SpawnStart();
	void MoveStart();
	void SpawnFlyStart();
	void SendFlyStart();
	void DieStart();

private:
	float SpawnFlyCoolTime = 0.0f;
	float SpawnFlyRate = 10.0f;
};

