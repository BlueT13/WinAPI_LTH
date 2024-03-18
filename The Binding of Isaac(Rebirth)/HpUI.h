#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AHpUI : public AActor
{
public:
	// constrcuter destructer
	AHpUI();
	~AHpUI();

	// delete Function
	AHpUI(const AHpUI& _Other) = delete;
	AHpUI(AHpUI&& _Other) noexcept = delete;
	AHpUI& operator=(const AHpUI& _Other) = delete;
	AHpUI& operator=(AHpUI&& _Other) noexcept = delete;

	static UImageRenderer* HpUI;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

