#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

// �츮 ���� WinAPi�ܰ迡�� �������̶�°���
// �̹����� �ٸ� �̹����� �ڽų��ο� �׸��� �̴ϴ�.
// DC��°� �ܺη� �巯���� �ȵ˴ϴ�.
// DC�� ���ؼ� �׸��� ��� å���� ������ => UWindowImage�� ��� ����Ѵ�.

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class UEngineWindow;
// ���� :
class UWindowImage : public UPathObject
{
	friend UEngineWindow;

public:
	// constrcuter destructer
	UWindowImage();
	~UWindowImage();

	// delete Function
	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	// bool�� �����ؼ� false�� ���� true�� ����
	bool Load(UWindowImage* _Image);

	FVector GetScale();

	// ������ �������� �ٽ� �������̽��� �ϳ��� HDC�� �ܺο� ������ �ʿ�� ���� ����.
	//HDC GetImageDC()
	//{
	//	return ImageDC;
	//}

	// UWindowImage* _Copy �� �̹�����
	// FTransform _Trans �� ��ġ�� ũ���
	// ������ ī���ض�.
	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans);

protected:

private:
	// �����쿡�� �������ִ� H���� �ֵ��� �� struct HBITMAP__{int unused;}; typedef struct HBITMAP__ *HBITMAP
	// �������̸鼭 8����Ʈ �����Դϴ�.
	HBITMAP hBitMap = 0;
	HDC ImageDC = 0;
	BITMAP BitMapInfo = BITMAP(); // ��Ʈ�ʸ� ��� ����ü�ε� �̰� ���;� �մϴ�.

	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	bool Create(HDC _MainDC);
};

