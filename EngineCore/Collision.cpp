#include "Collision.h"
#include <map>
#include <list>
#include "Level.h"
#include "Actor.h"
#include "EngineCore.h"

UCollision::UCollision()
{
}

UCollision::~UCollision()
{
}

void UCollision::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UCollision*>>& Collisions = Level->Collisions;
	// ���� ������ �ٲ������ Ȥ�ó� ���� � �׷쿡 �����ִٸ�
	// �� �׷쿡�� ���� ���´�.
	Collisions[GetOrder()].remove(this);

	// ���� ������ �ٲ��.
	UTickObject::SetOrder(_Order);

	Collisions[GetOrder()].push_back(this);
}

void UCollision::BeginPlay()
{
	USceneComponent::BeginPlay();
}

// true �浹�� ��ü�� �ִ�.
bool UCollision::CollisionCheck(int _Order, std::vector<UCollision*>& _Result)
{
	if (false == IsActive())
	{
		return false;
	}

	// ���� Ư�������� �ݸ����̶� �浹�ؾ� �Ѵ�.
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::list<UCollision*>& Collisions = Level->Collisions[_Order];

	FTransform ThisTransform = GetActorBaseTransform();

	for (UCollision* _OtherCollision : Collisions)
	{
		if (this == _OtherCollision) {
			continue;
		}

		if (false == _OtherCollision->IsActive())
		{
			continue;
		}

		FTransform OtherTransform = _OtherCollision->GetActorBaseTransform();

		if (true == ThisTransform.Collision(ColType, _OtherCollision->ColType, OtherTransform))
		{
			_Result.push_back(_OtherCollision);
		}
	}

	return false == _Result.empty();
}

void UCollision::DebugRender(FVector _CameraPos)
{
	FTransform ThisTransform = GetActorBaseTransform();
	ThisTransform.AddPosition(-_CameraPos);

	switch (ColType)
	{
	case ECollisionType::Point:
	{
		ThisTransform.SetScale({10, 10});
		GEngine->MainWindow.GetBackBufferImage()->DrawEllipse(ThisTransform);
		break;
	}
	case ECollisionType::CirCle:
	{
		ThisTransform.SetScale({ ThisTransform.GetScale().X, ThisTransform.GetScale().X });
		GEngine->MainWindow.GetBackBufferImage()->DrawEllipse(ThisTransform);
		break;
	}
	case ECollisionType::Rect:
	{
		GEngine->MainWindow.GetBackBufferImage()->DrawRectangle(ThisTransform);
		break;
	}
	default:
		break;
	}
}