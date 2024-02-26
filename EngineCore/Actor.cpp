#include "Actor.h"
#include "ImageRenderer.h"

AActor::AActor()
{
}

AActor::~AActor()
{
	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (nullptr == ImageRenderer)
		{
			MsgBoxAssert("�̹��� �������� nullptr�� ��Ȳ�� �־����ϴ�");
		}

		delete ImageRenderer;
		ImageRenderer = nullptr;
	}

	Renderers.clear();

	for (UCollision* Collision : Collisions)
	{
		if (nullptr == Collision)
		{
			MsgBoxAssert("�̹��� �������� nullptr�� ��Ȳ�� �־����ϴ�");
		}

		delete Collision;
		Collision = nullptr;
	}

	Collisions.clear();

}

void AActor::SetActive(bool _Active, float _ActiveTime /*= 0.0f*/)
{
	UTickObject::SetActive(_Active, _ActiveTime);

	// �ڽ��� �����ϰ� �ִ� �������鵵 �� �׿��� �Ѵ�.
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->SetActive(_Active, _ActiveTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->SetActive(_Active, _ActiveTime);
	}
}

void AActor::ChildTick(float _DeltaTime)
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Tick(_DeltaTime);
	}
}

void AActor::Tick(float _DeltaTime)
{
	UTickObject::Tick(_DeltaTime);
}

UImageRenderer* AActor::CreateImageRenderer(int _Order /*= 0*/)
{
	UImageRenderer* Component = new UImageRenderer();
	UActorComponent* ActorCom = Component;
	ActorCom->SetOwner(this);
	ActorCom->SetOrder(_Order);
	ActorCom->BeginPlay();
	Renderers.push_back(Component);
	return Component;
}


UCollision* AActor::CreateCollision(int _Order /*= 0*/)
{
	UCollision* Component = new UCollision();
	UActorComponent* ActorCom = Component;
	ActorCom->SetOwner(this);
	ActorCom->SetOrder(_Order);
	ActorCom->BeginPlay();
	Collisions.push_back(Component);
	return Component;
}

void AActor::Destroy(float _DestroyTime /*= 0.0f*/)
{
	// ���ʹ� �ڽ��� ���̸鼭
	UTickObject::Destroy(_DestroyTime);

	// �ڽ��� �����ϰ� �ִ� �������鵵 �� �׿��� �Ѵ�.
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Destroy(_DestroyTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->Destroy(_DestroyTime);
	}

}

void AActor::CheckReleaseChild()
{

	{
		std::list<UImageRenderer*>::iterator StartIter = Renderers.begin();
		std::list<UImageRenderer*>::iterator EndIter = Renderers.end();

		for (; StartIter != EndIter;)
		{
			UImageRenderer* Renderer = StartIter.operator*();

			if (nullptr == Renderer)
			{
				MsgBoxAssert("Collision�� nullptr�� ��찡 �����߽��ϴ�");
				return;
			}

			if (false == Renderer->IsDestroy())
			{
				++StartIter;
				continue;
			}

			delete Renderer;
			Renderer = nullptr;
			StartIter = Renderers.erase(StartIter);
		}
	}

	{
		std::list<UCollision*>::iterator StartIter = Collisions.begin();
		std::list<UCollision*>::iterator EndIter = Collisions.end();

		for (; StartIter != EndIter;)
		{
			UCollision* Collision = StartIter.operator*();

			if (nullptr == Collision)
			{
				MsgBoxAssert("Collision�� nullptr�� ��찡 �����߽��ϴ�");
				return;
			}

			if (false == Collision->IsDestroy())
			{
				++StartIter;
				continue;
			}

			delete Collision;
			Collision = nullptr;
			StartIter = Collisions.erase(StartIter);
		}
	}
}

void AActor::DestroyUpdate(float _DeltaTime)
{
	// �θ��� �Լ��� ȣ���ϴ°� �⺻�̴�.
	UTickObject::DestroyUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->DestroyUpdate(_DeltaTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->DestroyUpdate(_DeltaTime);
	}
}

void AActor::ActiveUpdate(float _DeltaTime)
{
	// �θ��� �Լ��� ȣ���ϴ°� �⺻�̴�.
	UTickObject::ActiveUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveUpdate(_DeltaTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->ActiveUpdate(_DeltaTime);
	}
}

void AActor::AllRenderersActiveOff()
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveOff();
	}
}

void AActor::AllRenderersActiveOn()
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveOn();
	}
}