#pragma once
#include <EngineCore\EngineCore.h>

// Ό³Έν :
class UIsaacCore : public UEngineCore
{
public:
	// constrcuter destructer
	UIsaacCore();
	~UIsaacCore();

	// delete Function
	UIsaacCore(const UIsaacCore& _Other) = delete;
	UIsaacCore(UIsaacCore&& _Other) noexcept = delete;
	UIsaacCore& operator=(const UIsaacCore& _Other) = delete;
	UIsaacCore& operator=(UIsaacCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void End() override;
private:

};

