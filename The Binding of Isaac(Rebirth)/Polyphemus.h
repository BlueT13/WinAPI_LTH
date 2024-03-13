#pragma once
#include "Item.h"

// Ό³Έν :
class APolyphemus : public AItem
{
public:
	// constrcuter destructer
	APolyphemus();
	~APolyphemus();

	// delete Function
	APolyphemus(const APolyphemus& _Other) = delete;
	APolyphemus(APolyphemus&& _Other) noexcept = delete;
	APolyphemus& operator=(const APolyphemus& _Other) = delete;
	APolyphemus& operator=(APolyphemus&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:

};

