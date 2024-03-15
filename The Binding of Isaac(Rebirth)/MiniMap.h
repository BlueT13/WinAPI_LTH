#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AMiniMap : public AActor
{
	friend class UPlayLevel;
public:
	// constrcuter destructer
	AMiniMap();
	~AMiniMap();

	// delete Function
	AMiniMap(const AMiniMap& _Other) = delete;
	AMiniMap(AMiniMap&& _Other) noexcept = delete;
	AMiniMap& operator=(const AMiniMap& _Other) = delete;
	AMiniMap& operator=(AMiniMap&& _Other) noexcept = delete;

	static UImageRenderer* MiniMapS;
	static UImageRenderer* MiniMapL;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

