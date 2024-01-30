#include "WindowImage.h"
#include <EngineBase\EngineString.h>
#include <Windows.h>
#include <EngineBase\EngineDebug.h>

// �����쿡�� �̹����� ����ϱ� ���ؼ� �����ϴ� ���̺귯��.
// ����� �ٸ��� ���̺귯���� #pragma comment ���ؼ� �߰� �ؾ� �Ѵ�.
#pragma comment(lib, "Msimg32.lib")

#include <objidl.h>
#include <gdiplus.h>

// Png�� �ε��ϴ� ����� ������ �⺻ ���̺귯�������� ���������� �ʱ� ������
// GDIPlus�� ����ؾ� �Ѵ�.
// GIDPlus�� �����찡 �ʱ� �������� �׷��� �ý����� �����ؼ� �߰��� ���̺귯���Դϴ�.

#pragma comment(lib, "Gdiplus.lib")

UWindowImage::UWindowImage()
{
}

UWindowImage::~UWindowImage()
{
	// �����찡 �Ҵ����ذ�����
	// ������ �츮�� ���ִ°� �����ϴ�.
	DeleteObject(hBitMap);
	DeleteDC(ImageDC);

}

FVector UWindowImage::GetScale()
{
	return FVector(BitMapInfo.bmWidth, BitMapInfo.bmHeight);
}

bool UWindowImage::Create(HDC _MainDC)
{
	ImageDC = _MainDC;

	if (nullptr == ImageDC)
	{
		return false;
	}

	return true;
}

bool UWindowImage::Load(UWindowImage* _Image)
{
	UEnginePath Path = GetEnginePath();

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	if (".BMP" == UpperExt)
	{
		//HINSTANCE hInst,  �� �̹����� ����� ���α׷��� �˷��޶�°ǵ�. nullptr�־ ������.
		//LPCSTR name, // ���
		//UINT type, // �̹��� Ÿ��
		//int cx, // �̹����� �ε��� ũ�� X 0�� ������ ��ü ũ��� �ε�
		//int cy, // �̹����� �ε��� ũ�� Y 0�� ������ ��ü ũ��� �ε�
		//UINT fuLoad �ε� �ɼ�
		
		// ��Ʈ���� �����Ҽ� �ִ� �ڵ��Դϴ�.
		// ��Ʈ���� �׸��� �ִ� �ڵ��� �ƴմϴ�.
		// �׸��ٴ� ������ ���� �ڵ��
		// ��Ʈ���� �ε��Ѵٴ� ������ �ڵ��� �ٸ��ٴ� ���Դϴ�.
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
		ImageType = EWIndowImageType::IMG_BMP;
	}
	else if (".PNG" == UpperExt)
	{
		ULONG_PTR gdiplusToken = 0;
		// Gdiplus����� �Լ����� ���δ� Gdiplus ���ӽ����̽� �ȿ� ����־��.
		// GDi�� ����ϰڴٴ� ���� 
		// GDIPlus�� ����غ����� ���� ���µ� �̹��� Png�� �ε尡 �ȵǸ� �����е��� ������ �ҰͰ��Ƽ�
		// �ε��ϴ°� �˾ƺôµ�.
		// Png�� �״�� ����ϴ� �Լ��� �־��µ�. 
		// �̳��� ���Ƚ��ϴ�.
		// ������ ��������������.
		// �װ� ����
		// �ε�� �����ѵ�. png�� ����ϸ� �ȵǱ� ������
		// Png�� �ε��� �༮�� Bmp�� �ٲٸ� �������� �Ǽ� �� ������� �ϱ�� �߽��ϴ�.
		Gdiplus::GdiplusStartupInput gdistartupinput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);

		// �����ڵ�� �Ǿ����ϴ�.
		// �׷��� ��Ƽ����Ʈ ��θ� �����ڵ� ��η� �����ϴ� �Լ��� �ʿ��ѵ�.
		std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());

		// � ���ڿ��� ����ؼ� ����������� �˼� ����?
		// �׳� ��� ���ڿ��� ����� ����� ã�ƾ� �մϴ�.
		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);

		if (Gdiplus::Status::Ok != stat)
		{
			MsgBoxAssert("Png ���� ���ҽ� �ε忡 �����߽��ϴ�.");
		}

		ImageType = EWIndowImageType::IMG_PNG;
	}

	// �׸����ְ� �̹����� �����Ҽ� �ִ� �����̴�.
	// ��� �׸��ų�.
	// �����ؼ� ��� �׷��� DC�ĸ� �־���� �մϴ�.
	// �翬�� �ϳ����� mainwindow�� DC�� �־��ָ� �˴ϴ�.
	// �׸��� �ִ� ������ �ڽ��� �� �׷����ϴ����� �˷���� �մϴ�.
	// ImageDC�� �ʴ� BitMap�׷��� ��.
	ImageDC = CreateCompatibleDC(_Image->ImageDC);
	HBITMAP OldBitMap = (HBITMAP)SelectObject(ImageDC, hBitMap);
	DeleteObject(OldBitMap);

	// hBitMap���� �����ڴ�.
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	// ImageDC�� ����� ���ο��� 1,1ũ���� HBITMAP�� �����.



	// �ΰ����� ����Ұǵ�.
	// Png���� bmp�ϴ� �ε��ϴ� ����� �޶��.

	return true;
}

void UWindowImage::BitCopy(UWindowImage* _CopyImage, FTransform _Trans)
{
	// ���ʱ��� �ƴϰ�
	// �̹����� �׷����մϴ�

	// HDC hdc, // => � �̹�����
	// int x,   // => �� ũ���
	// int y,   // 
	// int cx,  // => 
	// int cy,  
	// HDC hdcSrc,  
	// int x1,  
	// int y1, 
	// DWORD rop

	// ������
	HDC hdc = ImageDC;
	// �̹���
	HDC hdcSrc = _CopyImage->ImageDC;
	BitBlt(
		hdc, 							  // HDC hdc, // 
		_Trans.iLeft(), 				  // int x,   // 
		_Trans.iTop(), 				  // int y,   // 
		_Trans.GetScale().iX(), 		  // int cx,  // 
		_Trans.GetScale().iY(),		  // int cy,  
		hdcSrc,							// HDC hdcSrc, 
		0,								// int x1,  
		0,								// int y1, 
		SRCCOPY							// DWORD rop => �̹��� �״�� ��� ���縦 �ض�.
	);
}