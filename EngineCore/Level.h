#pragma once
#include "NameObject.h"

// ���� : U�� �׳� ���� �����ִٴ� ���� �ǹ�.
class ULevel : public UNameObject
{
public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

protected:

private:

};

