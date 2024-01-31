#include "ImageRenderer.h"
#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"
#include <EngineCore\EngineResourcesManager.h>

UImageRenderer::UImageRenderer() 
{
}

UImageRenderer::~UImageRenderer() 
{
}

void UImageRenderer::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UImageRenderer*>>& Renderers = Level->Renderers;
	// ���� ������ �ٲ������ Ȥ�ó� ���� � �׷쿡 �����ִٸ�
	// �� �׷쿡�� ���� ���´�.
	Renderers[GetOrder()].remove(this);

	// ���� ������ �ٲ��.
	UTickObject::SetOrder(_Order);

	Renderers[GetOrder()].push_back(this);
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (nullptr == Image)
	{
		MsgBoxAssert("�̹����� �������� �ʴ� ������ �Դϴ�");
	}

	// ���������� �о�� �մϴ�.
	FTransform ThisTrans = GetTransform();

	// �����ε� ���� �ǹ̰� �����ϴ�.
	FTransform OwnerTrans = GetOwner()->GetTransform();

	// ������Ʈ�� ��ġ�� �θ𿡰Լ� ������̱� ������.
	// �θ��� ��ġ�� ������� �Ѵ�.
	ThisTrans.AddPosition(OwnerTrans.GetPosition());


	// �̷��� ������ �̹����� �׸��� ȭ���� ������ ��������� �Ͼ�Ƿ�
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans);

	// 
	// GEngine->MainWindow.GetBackBufferImage()->BitCopy(Image, ThisTrans);
	// Rectangle(WindowDC, ThisTrans.iLeft(), ThisTrans.iTop(), ThisTrans.iRight(), ThisTrans.iBottom());

	// 1, 0, 0, 255

	// �����Դϴ�.

	GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform);

}

void UImageRenderer::BeginPlay()
{
	// �θ���� ��������ִ� ������ ������.
	USceneComponent::BeginPlay();
}

void UImageRenderer::SetImage(std::string_view _Name)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (nullptr == Image)
	{
		// ���ܸ� ����ϰ� �ϴ°͵� �߿��ϴ�.
		MsgBoxAssert(std::string(_Name) + "�̹����� �������� �ʽ��ϴ�.");
		return;
	}
}