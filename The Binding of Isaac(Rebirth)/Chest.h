#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AChest : public AActor
{
public:
	// constrcuter destructer
	AChest();
	~AChest();

	// delete Function
	AChest(const AChest& _Other) = delete;
	AChest(AChest&& _Other) noexcept = delete;
	AChest& operator=(const AChest& _Other) = delete;
	AChest& operator=(AChest&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* ChestRenderer = nullptr;
	UCollision* ChestCollision = nullptr;
};

