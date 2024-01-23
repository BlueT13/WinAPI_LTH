#pragma once
#include <EngineCore\EngineCore.h>

// Ό³Έν :
class IsaacCore : public EngineCore
{
public:
	// constrcuter destructer
	IsaacCore();
	~IsaacCore();

	// delete Function
	IsaacCore(const IsaacCore& _Other) = delete;
	IsaacCore(IsaacCore&& _Other) noexcept = delete;
	IsaacCore& operator=(const IsaacCore& _Other) = delete;
	IsaacCore& operator=(IsaacCore&& _Other) noexcept = delete;

protected:
	void EngineStart() override;
	void EngineUpdate() override;
	void EngineEnd() override;
private:

};

