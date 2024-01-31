#pragma once
#include <EngineBase\Transform.h>
#include "ActorComponent.h"

// ���� : �ڽŸ��� ��ġ���� ������ �־�� �ϴ� ������Ʈ
//        ���� ���Ϳ��� �����ְ� �ű� ������ ����� ��ġ���� ������ �־�� �Ѵ�.
class USceneComponent : public UActorComponent
{
public:
	// constrcuter destructer
	USceneComponent();
	~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	void SetPosition(const FVector& _Value)
	{
		Transform.SetPosition(_Value);
	}

	void SetScale(const FVector& _Value)
	{
		Transform.SetScale(_Value);
	}

	void SetTransform(const FTransform& _Value)
	{
		Transform = _Value;
	}

	FTransform GetTransform()
	{
		return Transform;
	}


protected:


private:
	FTransform Transform;

};

