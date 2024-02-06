#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum IsaacRenderOrder
{
	Map,
	Monster,
	Player
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EPlayState
{
	None,
	FreeMove,
	Idle,
	Move
};



// Ό³Έν :
class UContentsHelper
{
public:
	static UWindowImage* ColMapImage;

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

