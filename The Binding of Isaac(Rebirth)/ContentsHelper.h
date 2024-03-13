#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum class IsaacUpdateOrder
{
	Player,
	Monster,
	Bullet,
	Bomb,
	Door,
	Room,
	UI,
};

enum class IsaacRenderOrder
{
	Background,
	Room,
	Door,
	Boss,
	Monster,
	Bomb,
	SpawnEffect,
	PlayerBody,
	Bullet,
	PlayerHead,
	PlayerState,
	UI,
};

enum class IsaacCollisionOrder
{
	Door,
	Bullet,
	Bomb,
	Monster,
	PlayerCheckCollision,
	Player,
};

enum class EActorDir
{
	None,
	Left,
	Right,
	Up,
	Down,
};

enum class EPlayerHeadState
{
	None,
	Idle,
	Move,
	Attack,
	Wait,
	GetHit,
};

enum class EPlayerBodyState
{
	None,
	Idle,
	Move,
	Wait,
	Die,
};

enum class EMonsterState
{
	None,
	Spawn,
	Idle,
	Move,
	Attack,
	Die,
};

enum class EBulletState
{
	None,
	Move,
	Crashed,
};

enum class EBombState
{
	None,
	Idle,
	Explosion,
	Destroy,
};

enum class EMonsterType
{
	None,
	Fly,
	Pooter,
	DukeOfFlies,
};

// Ό³Έν :
class UContentsHelper
{
public:
	static class APlayer* MainPlayer;
	static FVector MainPlayerLocation;

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

