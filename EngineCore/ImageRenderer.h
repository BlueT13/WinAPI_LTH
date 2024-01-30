#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>

class UWindowImage;
// ���� :
class UImageRenderer : public USceneComponent
{
public:
	// constrcuter destructer
	UImageRenderer();
	~UImageRenderer();

	// delete Function
	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;
	void Render(float _DeltaTime);
	// �̹����� �����ϴ� ���Ҹ� �ϰ�
	void SetImage(std::string_view _Name, bool _IsImageScale = false);

	// �̹����� �����ϸ鼭 �̹����� ũ��� �������� �������� �����ϴ°͵� �Բ��ϴ� �Լ�
	void SetImageToScale(std::string_view _Name);

protected:
	void BeginPlay() override;

private:
	UWindowImage* Image;
};

