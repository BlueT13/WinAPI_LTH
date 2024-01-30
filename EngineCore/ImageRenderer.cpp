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

	FTransform ThisTrans = GetTransform();
	FTransform OwnerTrans = GetOwner()->GetTransform();

	// ������Ʈ�� ��ġ�� �θ𿡰Լ� ������̱� ������.
	// �θ��� ��ġ�� ������� �Ѵ�.
	ThisTrans.AddPosition(OwnerTrans.GetPosition());


	GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans);

	// Rectangle(WindowDC, ThisTrans.iLeft(), ThisTrans.iTop(), ThisTrans.iRight(), ThisTrans.iBottom());
}

void UImageRenderer::BeginPlay()
{
	// �θ���� ��������ִ� ������ ������.
	USceneComponent::BeginPlay();
}

void UImageRenderer::SetImageToScale(std::string_view _Name)
{
	SetImage(_Name, true);
}

void UImageRenderer::SetImage(std::string_view _Name, bool _IsImageScale /*= false*/)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (nullptr == Image)
	{
		// ���ܸ� ����ϰ� �ϴ°͵� �߿��ϴ�.
		MsgBoxAssert(std::string(_Name) + "�̹����� �������� �ʽ��ϴ�.");
		return;
	}

	if (true == _IsImageScale)
	{
		FVector Scale = Image->GetScale();
		SetScale(Scale);
	}
}