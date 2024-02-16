#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

// �츮 ���� WinAPi�ܰ迡�� �������̶�°���
// �̹����� �ٸ� �̹����� �ڽų��ο� �׸��� �̴ϴ�.
// DC��°� �ܺη� �巯���� �ȵ˴ϴ�.
// DC�� ���ؼ� �׸��� ��� å���� ������ => UWindowImage�� ��� ����Ѵ�.

enum class EImageLoadType
{
	IMG_Folder,
	IMG_Cutting,
};

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class UImageInfo 
{
public:
	HBITMAP hBitMap;
	HDC ImageDC = nullptr;
	FTransform CuttingTrans;
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
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

	bool LoadFolder(UWindowImage* _Image);

	FVector GetScale();

	// ������ �������� �ٽ� �������̽��� �ϳ��� HDC�� �ܺο� ������ �ʿ�� ���� ����.
	//HDC GetImageDC()
	//{
	//	return ImageDC;
	//}

	// UWindowImage* _Copy �� �̹�����
	// FTransform _Trans �� ��ġ�� ũ���
	// ������ ī���ض�.
	// �̹����� �̹��� ũ���θ� �׸��� �ִ�.
	void BitCopy(UWindowImage* _CopyImage, const FTransform& _Trans);

	// �̳༮�� �̹����� Ű����� �ְ� Ư�� ������ �ȱ׸����� �ִ�.
	// EX) ������ ȭ�鿡�� ����
	void TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);

	void AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);

	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/);

	bool Create(UWindowImage* _Image, const FVector& _Scale);

	void Cutting(int _X, int _Y);

	void DrawRectangle(const FTransform& _Trans);
	void DrawEllipse(const FTransform& _Trans);

	Color8Bit GetColor(int _X, int _Y, Color8Bit _DefaultColor);

	EWIndowImageType GetImageType()
	{
		return ImageType;
	}

protected:

private:
	EImageLoadType LoadType = EImageLoadType::IMG_Cutting;

	// �����쿡�� �������ִ� H���� �ֵ��� �� struct HBITMAP__{int unused;}; typedef struct HBITMAP__ *HBITMAP
	// �������̸鼭 8����Ʈ �����Դϴ�.
	HBITMAP hBitMap = 0;
	HDC ImageDC = 0;
	BITMAP BitMapInfo = BITMAP(); // ��Ʈ�ʸ� ��� ����ü�ε� �̰� ���;� �մϴ�.
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	std::vector<UImageInfo> Infos;

	bool Create(HDC _MainDC);
};

