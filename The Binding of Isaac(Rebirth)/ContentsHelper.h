#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum IsaacRenderOrder
{
	Map,
	Monster,
	PlayerBody,
	PlayerHead,
	Bullet,
};

enum class IsaacCollisionOrder
{
	Bullet,
	Monster,
	Player
};

enum class EDirection
{
	None,
	Left,
	Right,
	Up,
	Down,
};

enum class EPlayerAttackState
{
	None,
	AttackIdle,
	Attack,
};

enum class EPlayerMoveState
{
	None,
	Idle,
	Move,
};

// Ό³Έν :
class UContentsHelper
{
public:
	static class APlayer* MainPlayer;
	static UWindowImage* ColMapImage;

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};
