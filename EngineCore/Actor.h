#pragma once
#include <EngineBase\Transform.h>
#include "TickObject.h"
#include <EngineBase\NameObject.h>
#include "ImageRenderer.h"
#include "Collision.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class UImageRenderer;
class UCollision;

// ���� : A�� ���� ������Ʈ�� ȭ�鿡 ��ġ�� �����ؾ��Ѵ�.
// Level->SpawnActor�� ���ؼ� �����
// ������ �ڿ������� �ڽ��� �����Ͽ� �ΰ� ������ Tick�� �������ش�.
class AActor : public UNameObject, public UTickObject
{
	friend ULevel;

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	FVector GetActorLocation()
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value)
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value)
	{
		Transform.AddPosition(_Value);
	}

	FTransform GetTransform()
	{
		return Transform;
	}

	ULevel* GetWorld()
	{
		return World;
	}

	template<typename EnumType>
	UCollision* CreateCollision(EnumType _Order = 0)
	{
		return CreateCollision(static_cast<int>(_Order));
	}

	template<typename EnumType>
	UImageRenderer* CreateImageRenderer(EnumType _Order = 0)
	{
		return CreateImageRenderer(static_cast<int>(_Order));
	}

	UCollision* CreateCollision(int _Order = 0);
	UImageRenderer* CreateImageRenderer(int _Order = 0);

	void Destroy(float _DestroyTime = 0.0f) override;
	void DestroyUpdate(float _DeltaTime) override;

	void ActiveUpdate(float _DeltaTime) override;

	void CheckReleaseChild();

	void AllRenderersActiveOff();
	void AllRenderersActiveOn();

	void SetActive(bool _Active, float _ActiveTime = 0.0f) override;

protected:
	void Tick(float _DeltaTime) override;
	void ChildTick(float _DeltaTime);

private:
	std::list<UImageRenderer*> Renderers;
	std::list<UCollision*> Collisions;

	ULevel* World = nullptr;
	FTransform Transform = FTransform();

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};

