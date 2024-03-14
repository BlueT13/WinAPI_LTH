#pragma once
#include "Monster.h"
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class ABossFly : public AMonster
{
	friend class ADukeOfFlies;
public:
	// constrcuter destructer
	ABossFly();
	~ABossFly();

	// delete Function
	ABossFly(const ABossFly& _Other) = delete;
	ABossFly(ABossFly&& _Other) noexcept = delete;
	ABossFly& operator=(const ABossFly& _Other) = delete;
	ABossFly& operator=(ABossFly&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MonsterStateUpdate(float _DeltaTime) override;
	void Spawn(float _DeltaTime);
	void Move(float _DeltaTime);
	void Die(float _DeltaTime);
	void MonsterStateChange(EMonsterState _State) override;
	void SpawnStart();
	void MoveStart();
	void DieStart();

	void MonsterTouchWall(float _DeltaTime, EActorDir _Dir) override;

private:

};

