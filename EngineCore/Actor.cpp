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
}

void AActor::Tick(float _DeltaTime)
{
	UTickObject::Tick(_DeltaTime);
	DestroyUpdate(_DeltaTime);
}

UImageRenderer* AActor::CreateImageRenderer(int Order /*= 0*/)
{
	UImageRenderer* NewRenderer = new UImageRenderer();
	UActorComponent* ActorCom = NewRenderer;
	ActorCom->SetOwner(this);
	ActorCom->SetOrder(Order);
	ActorCom->BeginPlay();
	Renderers.push_back(NewRenderer);
	return NewRenderer;
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
}

void AActor::DestroyUpdate(float _DeltaTime)
{
	// �θ��� �Լ��� ȣ���ϴ°� �⺻�̴�.
	UTickObject::DestroyUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->DestroyUpdate(_DeltaTime);
	}
}