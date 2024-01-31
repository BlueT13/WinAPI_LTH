#include "Level.h"
#include "Actor.h"
#include <EngineBase\EngineDebug.h>

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
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			// Ranged for�� �߰��� ����Ʈ�� ������ ������ ����Ǹ� ������ �Ҿ���������
			// ġ������ ������ �߻��� ���ɼ��� ��������.
			// ����� �ı����� 
			if (false == Actor->IsActive())
			{
				continue;
			}

			Actor->Tick(_DeltaTime);
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


	for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
	{
		std::list<UImageRenderer*>& RendererList = OrderListPair.second;

		std::list<UImageRenderer*>::iterator StartIter = RendererList.begin();
		std::list<UImageRenderer*>::iterator EndIter = RendererList.end();

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

			StartIter = RendererList.erase(StartIter);
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


