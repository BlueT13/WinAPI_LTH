#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum IsaacRenderOrder
{
	Map,
	Monster,
	PlayerBody,
	Bullet,
	PlayerHead,
};

enum class IsaacCollisionOrder
{
	Bullet,
	Monster,
	Player
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
};

enum class EPlayerBodyState
{
	None,
	Idle,
	Move,
};

enum class EMonsterState
{
	None,
	Idle,
	Move,
	Attack,
};

// Ό³Έν :
class UContentsHelper
{
public:
	static class APlayer* MainPlayer;

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

