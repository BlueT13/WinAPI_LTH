#include "Level.h"
#include "Actor.h"
#include <EngineBase\EngineDebug.h>
#include "EngineDebug.h"
#include "EngineCore.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			if (nullptr == Actor)
			{
				continue;
			}

			delete Actor;
			Actor = nullptr;
		}
	}
	AllActor.clear();
}

void ULevel::LevelTick(float _DeltaTime)
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		int Order = OrderListPair.first;

		if (false == TimeScale.contains(Order))
		{
			TimeScale[Order] = 1.0f;
		}

		float OrderTime = _DeltaTime * TimeScale[Order];

		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			// Ranged for�� �߰��� ����Ʈ�� ������ ������ ����Ǹ� ������ �Ҿ���������
			// ġ������ ������ �߻��� ���ɼ��� ��������.
			// ����� �ı����� 
			Actor->ActiveUpdate(_DeltaTime);
			Actor->DestroyUpdate(_DeltaTime);
			if (false == Actor->IsActive())
			{
				continue;
			}

			Actor->Tick(OrderTime);
			Actor->ChildTick(OrderTime);
		}
	}
}

void ULevel::LevelRender(float _DeltaTime)
{
	for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
	{
		std::list<UImageRenderer*>& RendererList = OrderListPair.second;
		for (UImageRenderer* Renderer : RendererList)
		{
			// Ranged for�� �߰��� ����Ʈ�� ������ ������ ����Ǹ� ������ �Ҿ���������
			// ġ������ ������ �߻��� ���ɼ��� ��������.
			// ����� �ı����� 
			if (false == Renderer->IsActive())
			{
				continue;
			}

			Renderer->Render(_DeltaTime);
		}
	}

	if (true == GEngine->IsDebug())
	{
		for (std::pair<const int, std::list<UCollision*>>& OrderListPair : Collisions)
		{
			std::list<UCollision*>& RendererList = OrderListPair.second;
			for (UCollision* Collision : RendererList)
			{
				// Ranged for�� �߰��� ����Ʈ�� ������ ������ ����Ǹ� ������ �Ҿ���������
				// ġ������ ������ �߻��� ���ɼ��� ��������.
				// ����� �ı����� 
				if (false == Collision->IsActive())
				{
					continue;
				}

				Collision->DebugRender(CameraPos);
			}
		}
		UEngineDebug::PrintDebugText(GEngine->MainWindow.GetBackBufferImage());
	}
}

void ULevel::LevelRelease(float _DeltaTime)
{
	// Tick
	// ������
	// �浹 ������ �� ������.

	// ���⼭ ����µ�.
	// Render�� �޸��� �������� �������� �����Դϴ�.
	// ������ �����͸� ������ �������� ������ ����ϴ� ��찡 �����ϴ�.
	// �׷��� ���� �̿� ���� ������ ����ؾ� �ϳ���?
	// �̰� ������ ������ �������� ������� ����.
	// new�� �� ���� �Ѵ�.


	{
		for (std::pair<const int, std::list<UCollision*>>& OrderListPair : Collisions)
		{
			std::list<UCollision*>& List = OrderListPair.second;

			std::list<UCollision*>::iterator StartIter = List.begin();
			std::list<UCollision*>::iterator EndIter = List.end();

			// ������ ����� Ranged for�� �ϸ� �ȵǴ�.
			// for (UImageRenderer* Renderer : RendererList)
			for (; StartIter != EndIter; )
			{
				UCollision* Collision = StartIter.operator*();

				if (false == Collision->IsDestroy())
				{
					++StartIter;
					continue;
				}

				StartIter = List.erase(StartIter);
			}
		}
	}

	{
		for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
		{
			std::list<UImageRenderer*>& List = OrderListPair.second;

			std::list<UImageRenderer*>::iterator StartIter = List.begin();
			std::list<UImageRenderer*>::iterator EndIter = List.end();

			// ������ ����� Ranged for�� �ϸ� �ȵǴ�.
			// for (UImageRenderer* Renderer : RendererList)
			for (; StartIter != EndIter; )
			{
				UImageRenderer* Renderer = StartIter.operator*();

				if (false == Renderer->IsDestroy())
				{
					++StartIter;
					continue;
				}

				StartIter = List.erase(StartIter);
			}
		}
	}


	// �������� ����� ���൵�� ������ ���� �ʽ��ϴ�.
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;

		std::list<AActor*>::iterator StartIter = ActorList.begin();
		std::list<AActor*>::iterator EndIter = ActorList.end();

		for (; StartIter != EndIter;)
		{
			AActor* Actor = StartIter.operator*();

			if (nullptr == Actor)
			{
				MsgBoxAssert("Actor�� nullptr�� ��찡 �����߽��ϴ�");
				return;
			}

			if (false == Actor->IsDestroy())
			{
				Actor->CheckReleaseChild();
				++StartIter;
				continue;
			}

			delete Actor;
			Actor = nullptr;
			StartIter = ActorList.erase(StartIter);
		}
	}
}


void ULevel::ActorInit(AActor* _NewActor)
{
	// �����ڿ����� ������ ���õ��� �ʾƼ� Get
	_NewActor->SetWorld(this);
	_NewActor->BeginPlay();
}


