#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <EngineBase\EngineDebug.h>
#include <Windows.h>
#include <string>
#include <string_view>

#include <objidl.h>
#include <gdiplus.h>

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
	UImageInfo* RotationMaskImage = nullptr;
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

	// ���Ķ� ���ÿ� �ȵɰ��̴�.
	void PlgCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, float _RadAngle);

	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/);

	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _OutLineColor, Color8Bit _FillColor);

	void TextCopyBold(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/);

	void TextCopyFormat(const std::string& _Text, const std::string& _Font, const Gdiplus::StringFormat& stringFormat, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/);

	bool Create(UWindowImage* _Image, const FVector& _Scale);

	void Cutting(int _X, int _Y);

	void SetCuttingTransform(const FTransform& _CuttingTrans, int _Index = 0);

	void DrawRectangle(const FTransform& _Trans);
	void DrawEllipse(const FTransform& _Trans);

	Color8Bit GetColor(int _X, int _Y, Color8Bit _DefaultColor);

	EWIndowImageType GetImageType()
	{
		return ImageType;
	}

	// �̰� ����� ȸ���� �����մϴ�.
	void SetRotationMaskImage(int _Index, UWindowImage* _RotationMaskImage, int _MaskIndex)
	{
		UImageInfo& Ref = _RotationMaskImage->Infos[_MaskIndex];
		Infos[_Index].RotationMaskImage = &Ref;
	}

	void SetRotationMaskImageFolder(UWindowImage* _RotationMaskImage)
	{
		if (Infos.size() != _RotationMaskImage->Infos.size())
		{
			MsgBoxAssert("�̹��������� ũ�Ⱑ �ٸ� �̹��� ���� ��Ī�� �Ҽ��� �����ϴ�.");
			return;
		}

		for (int i = 0; i < static_cast<int>(Infos.size()); i++)
		{
			SetRotationMaskImage(i, _RotationMaskImage, i);
		}
	}

	void TextPrint(std::string_view _Text, FVector _Pos);
	const UImageInfo& ImageInfo(int _Index)
	{
		return Infos[_Index];
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

