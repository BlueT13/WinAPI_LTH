#pragma once
#include "Monster.h"
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class AFly : public AMonster
{
public:
	// constrcuter destructer
	AFly();
	~AFly();

	// delete Function
	AFly(const AFly& _Other) = delete;
	AFly(AFly&& _Other) noexcept = delete;
	AFly& operator=(const AFly& _Other) = delete;
	AFly& operator=(AFly&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	const FVector RendererSize = { 256,256 };
};

