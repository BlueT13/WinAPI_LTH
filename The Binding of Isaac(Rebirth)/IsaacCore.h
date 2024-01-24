#pragma once
#include <EngineCore\EngineCore.h>

// ���� :
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
	void Start() override;
	void Update() override;
	void End() override;
private:

};

