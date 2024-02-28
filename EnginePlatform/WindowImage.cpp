#include "WindowImage.h"
#include <EngineBase\EngineString.h>
#include <Windows.h>
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>

// �����쿡�� �̹����� ����ϱ� ���ؼ� �����ϴ� ���̺귯��.
// ����� �ٸ��� ���̺귯���� #pragma comment ���ؼ� �߰� �ؾ� �Ѵ�.
#pragma comment(lib, "Msimg32.lib")



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

	switch (LoadType)
	{
	case EImageLoadType::IMG_Folder:
	{
		for (size_t i = 0; i < Infos.size(); i++)
		{
			DeleteObject(Infos[i].hBitMap);
			DeleteDC(Infos[i].ImageDC);
		}
		break;
	}
	case EImageLoadType::IMG_Cutting:
		DeleteObject(hBitMap);
		DeleteDC(ImageDC);
		break;
	default:
		break;
	}
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
	LoadType = EImageLoadType::IMG_Cutting;

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

		delete pBitMap;
		delete pImage;

		ImageType = EWIndowImageType::IMG_PNG;
	}

	// �׸����ְ� �̹����� �����Ҽ� �ִ� �����̴�.
	// ��� �׸��ų�.
	// �����ؼ� ��� �׷��� DC�ĸ� �־���� �մϴ�.
	// �翬�� �ϳ����� mainwindow�� DC�� �־��ָ� �˴ϴ�.
	// �׸��� �ִ� ������ �ڽ��� �� �׷����ϴ����� �˷���� �մϴ�.
	// ImageDC�� �ʴ� BitMap�׷��� ��.
	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// hBitMap���� �����ڴ�.
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	// ImageDC�� ����� ���ο��� 1,1ũ���� HBITMAP�� �����.

	UImageInfo Info;
	Info.hBitMap = hBitMap;
	Info.ImageDC = ImageDC;
	Info.CuttingTrans.SetPosition({0,0});
	Info.CuttingTrans.SetScale(GetScale());
	Info.ImageType = ImageType;
	Infos.push_back(Info);

	return true;
}


bool UWindowImage::LoadFolder(UWindowImage* _Image)
{
	LoadType = EImageLoadType::IMG_Folder;

	UEnginePath EnginePath = GetEnginePath();

	if (false == EnginePath.IsDirectory())
	{
		MsgBoxAssert("���丮�� �ƴ� ��η� �����ε带 �Ϸ��� �߽��ϴ�");
	}

	UEngineDirectory Dir = EnginePath;

	std::list<UEngineFile> NewList = Dir.AllFile({ ".png", ".bmp" }, false);
	Infos.reserve(NewList.size());

	for (UEngineFile& File : NewList)
	{
		UEnginePath Path = File;

		std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

		if (".BMP" == UpperExt)
		{
			HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
			ImageType = EWIndowImageType::IMG_BMP;
		}
		else if (".PNG" == UpperExt)
		{
			ULONG_PTR gdiplusToken = 0;
			Gdiplus::GdiplusStartupInput gdistartupinput;
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);
			std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());
			Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
			Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());
			Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);
			if (Gdiplus::Status::Ok != stat)
			{
				MsgBoxAssert("Png ���� ���ҽ� �ε忡 �����߽��ϴ�.");
			}

			delete pBitMap;
			delete pImage;

			ImageType = EWIndowImageType::IMG_PNG;
		}
		ImageDC = CreateCompatibleDC(_Image->ImageDC);

		if (nullptr == ImageDC)
		{
			MsgBoxAssert("�̹��� ������ �����߽��ϴ�");
			return false;
		}

		HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
		DeleteObject(OldBitMap);
		GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

		UImageInfo Info;
		Info.hBitMap = hBitMap;
		Info.ImageDC = ImageDC;
		Info.CuttingTrans.SetPosition({ 0,0 });
		Info.CuttingTrans.SetScale(GetScale());
		Infos.push_back(Info);
	}


	return true;
}

bool UWindowImage::Create(UWindowImage* _Image, const FVector& _Scale)
{
	// ������ ���� �̹����� �����.


	// HBITMAP ��Ʈ�� �̹����� �޸𸮱���
	HANDLE ImageHandle = CreateCompatibleBitmap(_Image->ImageDC, _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�");
		return false;
	}

	hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// hBitMap���� �����ڴ�.
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
}

void UWindowImage::BitCopy(UWindowImage* _CopyImage, const FTransform& _Trans)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr �� �̹����� ������ �� �����ϴ�");
	}
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

void UWindowImage::TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr �� �̹����� ������ �� �����ϴ�");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + "�̹��� ������ �ε����� �����Ͽ� ����߽��ϴ�");
	}

	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	// ��ġ�� �־��ش�.
	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft   = ImageTrans.GetPosition().iX();
	int ImageTop    = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();

	HDC hdc = ImageDC;
	// �̹���
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;
	TransparentBlt(
		hdc, 							  // HDC hdc, // 
		RenderLeft, 		  // int x,   // 
		RenderTop, 		  // int y,   // 
		RenderScaleX,		  // int cx,  // 
		RenderScaleY,		  // int cy,  
		hdcSrc,							// HDC hdcSrc, 
		ImageLeft,   							// int y1, 
		ImageTop,   							// int x1,  
		ImageScaleX, 							// int y1, 
		ImageScaleY, 							// int y1, 
		_Color.Color						// DWORD rop => �̹��� �״�� ��� ���縦 �ض�.
	);
	// �̹����� � ������ �׸����� �����ټ��� �ִ�.
}

void UWindowImage::TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color/* = Color8Bit::Black*/)
{
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	TextCopyFormat(_Text, _Font, stringFormat, _Size, _Trans, _Color);  //���
}

void UWindowImage::TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _OutLineColor, Color8Bit _FillColor)
{
	Gdiplus::Graphics graphics(ImageDC);
	std::wstring WFont = UEngineString::AnsiToUniCode(_Font);
	Gdiplus::Font fnt(WFont.c_str(), _Size, Gdiplus::FontStyleBold | Gdiplus::FontStyleItalic, Gdiplus::UnitPixel);

	// �׵θ��� �귯�� ����
	Gdiplus::SolidBrush OutLineBrush(Gdiplus::Color(_OutLineColor.R, _OutLineColor.G, _OutLineColor.B));

	// ���� ä���� �귯�� ����
	Gdiplus::SolidBrush fillBrush(Gdiplus::Color(_FillColor.R, _FillColor.G, _FillColor.B));

	FVector Pos = _Trans.GetPosition();
	Gdiplus::RectF rectF(Pos.X, Pos.Y, 0, 0);

	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	std::wstring WText = UEngineString::AnsiToUniCode(_Text);

	// �׵θ� ȿ���� ���� �ؽ�Ʈ�� ���� �������� �׸��ϴ�.
	float offsetsX[] = { -3.f, 3.f }; // �׵θ��� �β��� �����Ϸ��� �� ���� ����.
	float offsetsY[] = { -2.f, 2.f }; // �׵θ��� �β��� �����Ϸ��� �� ���� ����.
	for (float dx : offsetsX)
	{
		for (float dy : offsetsY)
		{
			Gdiplus::RectF borderRect = rectF;
			borderRect.X += dx;
			borderRect.Y += dy;
			graphics.DrawString(WText.c_str(), -1, &fnt, borderRect, &stringFormat, &OutLineBrush);
		}
	}
	float offsets_X[] = { -2.f, 2.f }; // ������ �β��� �����Ϸ��� �� ���� ����.
	float offsets_Y[] = { -1.f, 1.f }; // ������ �β��� �����Ϸ��� �� ���� ����.
	for (float dx : offsets_X)
	{
		for (float dy : offsets_Y)
		{
			Gdiplus::RectF borderRect = rectF;
			borderRect.X += dx;
			borderRect.Y += dy;
			graphics.DrawString(WText.c_str(), -1, &fnt, borderRect, &stringFormat, &fillBrush);
		}
	}
}

void UWindowImage::TextCopyBold(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color)
{
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	Gdiplus::Graphics graphics(ImageDC);
	std::wstring WFont = UEngineString::AnsiToUniCode(_Font);
	Gdiplus::Font fnt(WFont.c_str(), _Size, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush hB(Gdiplus::Color(_Color.R, _Color.G, _Color.B));
	FVector Pos = _Trans.GetPosition();
	Gdiplus::RectF  rectF(_Trans.GetPosition().X, _Trans.GetPosition().Y, 0, 0);

	std::wstring WText = UEngineString::AnsiToUniCode(_Text);
	graphics.DrawString(WText.c_str(), -1, &fnt, rectF, &stringFormat, &hB);  //���
}

void UWindowImage::TextCopyFormat(const std::string& _Text, const std::string& _Font, const Gdiplus::StringFormat& stringFormat, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/)
{
	Gdiplus::Graphics graphics(ImageDC);
	std::wstring WFont = UEngineString::AnsiToUniCode(_Font);
	Gdiplus::Font fnt(WFont.c_str(), _Size, /*Gdiplus::FontStyleBold | Gdiplus::FontStyleItalic*/0, Gdiplus::UnitPixel);
	// Gdiplus::HatchBrush hB(HatchStyle::HatchStyle05Percent, Gdiplus::Color(_Color.R, _Color.G, _Color.B), Gdiplus::Color::Transparent);
	Gdiplus::SolidBrush hB(Gdiplus::Color(_Color.R, _Color.G, _Color.B));
	FVector Pos = _Trans.GetPosition();
	// Gdiplus::PointF ptf(Pos.X, Pos.Y);
	Gdiplus::RectF  rectF(_Trans.GetPosition().X, _Trans.GetPosition().Y, 0, 0);

	std::wstring WText = UEngineString::AnsiToUniCode(_Text);
	graphics.DrawString(WText.c_str(), -1, &fnt, rectF, &stringFormat, &hB);  //���
}

void UWindowImage::AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color /*= Color8Bit::Black*/)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr �� �̹����� ������ �� �����ϴ�");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + "�̹��� ������ �ε����� �����Ͽ� ����߽��ϴ�");
	}


	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();


	HDC hdc = ImageDC;
	// �̹���
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	BLENDFUNCTION Function;
	Function.BlendOp = AC_SRC_OVER;
	Function.BlendFlags = 0;
	// 0~255
	Function.SourceConstantAlpha = _Color.A;
	Function.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		hdc, 							  // HDC hdc, // 
		RenderLeft, 		  // int x,   // 
		RenderTop, 		  // int y,   // 
		RenderScaleX,		  // int cx,  // 
		RenderScaleY,		  // int cy,  
		hdcSrc,							// HDC hdcSrc, 
		ImageLeft,   							// int y1, 
		ImageTop,   							// int x1,  
		ImageScaleX, 							// int y1, 
		ImageScaleY, 							// int y1, 
		Function
	);
}

void UWindowImage::PlgCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, float _RadAngle)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr �� �̹����� ������ �� �����ϴ�");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + "�̹��� ������ �ε����� �����Ͽ� ����߽��ϴ�");
	}


	UImageInfo& CurInfo = _CopyImage->Infos[_Index];

	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	POINT Arr[3];

	{
		FTransform Trans = FTransform(float4::Zero, _Trans.GetScale());

		FVector LeftTop = Trans.LeftTop();
		FVector RightTop = Trans.RightTop();
		FVector LeftBot = Trans.LeftBottom();

		LeftTop.RotationZToRad(_RadAngle);
		RightTop.RotationZToRad(_RadAngle);
		LeftBot.RotationZToRad(_RadAngle);

		LeftTop += _Trans.GetPosition();
		RightTop += _Trans.GetPosition();
		LeftBot += _Trans.GetPosition();

		Arr[0] = LeftTop.ConvertToWinApiPOINT();
		Arr[1] = RightTop.ConvertToWinApiPOINT();
		Arr[2] = LeftBot.ConvertToWinApiPOINT();
	}

	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();

	//// ������ŭ ȸ����Ų ���� ����� ���� �մϴ�.
	//// ��� �׷��� ����� ������?

	if (nullptr == CurInfo.RotationMaskImage)
	{
		MsgBoxAssert("�̹����� ȸ����Ű���� �ߴµ� �̹����� �����ϴ�.");
	}

	HDC hdc = ImageDC;
	//// �̹���
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	PlgBlt(
		hdc, 							  // HDC hdc, // 
		Arr,
		hdcSrc,							// HDC hdcSrc, 
		ImageLeft,   							// int y1, 
		ImageTop,   							// int x1,  
		ImageScaleX, 							// int y1, 
		ImageScaleY, 							// int y1, 
		CurInfo.RotationMaskImage->hBitMap, // ����ó���� �κ��� �˷��޶�� �ϴµ�
		ImageLeft,   							// int y1, 
		ImageTop   							// int x1,  
	);
}

void UWindowImage::Cutting(int _X, int _Y)
{
	Infos.clear();

	FVector CuttingScale = { GetScale().X / _X,  GetScale().Y / _Y };
	FVector CuttingPos = { 0, 0 };

	for (int i = 0; i < _Y; i++)
	{
		for (int i = 0; i < _X; i++)
		{
			UImageInfo Info;
			Info.ImageDC = ImageDC;
			Info.CuttingTrans.SetPosition(CuttingPos);
			Info.CuttingTrans.SetScale(CuttingScale);
			Infos.push_back(Info);

			CuttingPos.X += CuttingScale.X;
		}

		CuttingPos.X = 0.0f;
		CuttingPos.Y += CuttingScale.Y;
	}
}

void UWindowImage::SetCuttingTransform(const FTransform& _CuttingTrans, int _Index)
{
	Infos[_Index].CuttingTrans = _CuttingTrans;
}

Color8Bit UWindowImage::GetColor(int _X, int _Y, Color8Bit _DefaultColor)
{
	// �� �Լ��� �Ϻ����� �ʴ�.

	if (0 > _X)
	{
		return _DefaultColor;
	}

	if (0 > _Y)
	{
		return _DefaultColor;
	}

	if (GetScale().iX() <= _X)
	{
		return _DefaultColor;
	}

	if (GetScale().iY() <= _Y)
	{
		return _DefaultColor;
	}

	Color8Bit Color;

	Color.Color = ::GetPixel(ImageDC, _X, _Y);

	return Color;
}

void UWindowImage::DrawRectangle(const FTransform& _Trans)
{
	Rectangle(ImageDC, _Trans.iLeft(), _Trans.iTop(), _Trans.iRight(), _Trans.iBottom());
}

void UWindowImage::DrawEllipse(const FTransform& _Trans)
{
	Ellipse(ImageDC, _Trans.iLeft(), _Trans.iTop(), _Trans.iRight(), _Trans.iBottom());
}

void UWindowImage::TextPrint(std::string_view _Text, FVector _Pos)
{
	TextOutA(ImageDC, _Pos.iX(), _Pos.iY(), _Text.data(), static_cast<int>(_Text.size()));
}