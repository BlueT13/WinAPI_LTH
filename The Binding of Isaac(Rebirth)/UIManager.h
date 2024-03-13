#pragma once
#include <EngineCore/Actor.h>

// ���� :
class UIManager : public AActor
{
public:
	// constrcuter destructer
	UIManager();
	~UIManager();

	// delete Function
	UIManager(const UIManager& _Other) = delete;
	UIManager(UIManager&& _Other) noexcept = delete;
	UIManager& operator=(const UIManager& _Other) = delete;
	UIManager& operator=(UIManager&& _Other) noexcept = delete;

	static UImageRenderer* DeathPortrait;
	static UImageRenderer* PauseScreen;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

