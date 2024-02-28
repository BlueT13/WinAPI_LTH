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

enum class EActorDir
{
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

// ���� :
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

