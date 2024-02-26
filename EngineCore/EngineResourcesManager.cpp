#include "EngineResourcesManager.h"
#include <EnginePlatform\WindowImage.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>
#include "EngineCore.h"
#include "EngineBase\EngineDebug.h"

//UEngineResourcesManager UEngineResourcesManager::Inst;
//UEngineResourcesManager* UEngineResourcesManager::pInst = nullptr;

UEngineResourcesManager::UEngineResourcesManager() 
{
}

UEngineResourcesManager::~UEngineResourcesManager() 
{
	for (std::pair<const std::string, UWindowImage*>& Pair : Images)
	{
		delete Pair.second;
		Pair.second = nullptr;
	}

	Images.clear();
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();
	return LoadImg(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path, std::string_view _Name)
{
	// ��� �̸��� �빮�ڷ�
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == Images.contains(UpperName))
	{
		// ������ ��峪 ����׿����� �ӷ��� �����ʿ䰡 ����.
		// ���ӿ��� ���� ������� ���� ���뿡 ���ؼ��� �ӷ��� ������ �ʴ´�.
		MsgBoxAssert(std::string("��� : ") + std::string(_Path) + "���ϸ� : " + std::string(_Name) + "�̹� �ε��� ������ �� �ε��Ϸ��� �߽��ϴ�");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->Load(GEngine->MainWindow.GetWindowImage());

	// .Png .bmp => Ȯ���ڸ� �ٲٸ� png�� bmp�� �ȴٰ� �����ߴ� �л��� �־��µ� �ƴմϴ�.
	// ����� �̹��� ���� ���α׷����� ������ �����ϰ� �����ϼž� �մϴ�.
	// �ϴ� winapi�� �⺻������ png�� ����ϴ� �Լ��� �������� �ʽ��ϴ�.
	// ������ bmp�� �˴ϴ�.
	// .Png�� �ε��ؼ� bmp�� �����ؼ� ����� �̴ϴ�. => ó���մϴ�.
	// �׷��� Png�� ����ϴ°͵� �ƴϰ� �κ� ������
	Images[UpperName] = NewImage;

	return nullptr;

}

void UEngineResourcesManager::UnloadImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == Images.contains(UpperName))
	{
		MsgBoxAssert("�̹����� : " + std::string(_Name) + "�������� �ʴ� �̹����� ��ε��Ϸ��� �߽��ϴ�");
		return;
	}

	UWindowImage* Image = Images[UpperName];
	Images.erase(UpperName);
	delete Image;
}

UWindowImage* UEngineResourcesManager::FindImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == Images.contains(UpperName))
	{
		MsgBoxAssert("���ϸ� : " + std::string(_Name) + "�� �������� �ʴ� �̹����Դϴ�");
		return nullptr;
	}

	return Images[UpperName];
}

void UEngineResourcesManager::CuttingImage(std::string_view _Name, int _X, int _Y)
{
	UWindowImage* FindImage = FindImg(_Name);

	if (nullptr == FindImage)
	{
		MsgBoxAssert("���ϸ� : " + std::string(_Name) + "�������� �ʴ� �̹����� Ŀ���Ϸ��� �߽��ϴ�");
	}

	FindImage->Cutting(_X, _Y);
}

UWindowImage* UEngineResourcesManager::LoadFolder(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();
	return LoadFolder(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadFolder(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == Images.contains(UpperName))
	{
		MsgBoxAssert(std::string("��� : ") + std::string(_Path) + "���ϸ� : " + std::string(_Name) + "�̹� �ε��� ������ �� �ε��Ϸ��� �߽��ϴ�");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->LoadFolder(GEngine->MainWindow.GetWindowImage());

	// .Png .bmp => Ȯ���ڸ� �ٲٸ� png�� bmp�� �ȴٰ� �����ߴ� �л��� �־��µ� �ƴմϴ�.
	// ����� �̹��� ���� ���α׷����� ������ �����ϰ� �����ϼž� �մϴ�.
	// �ϴ� winapi�� �⺻������ png�� ����ϴ� �Լ��� �������� �ʽ��ϴ�.
	// ������ bmp�� �˴ϴ�.
	// .Png�� �ε��ؼ� bmp�� �����ؼ� ����� �̴ϴ�. => ó���մϴ�.
	// �׷��� Png�� ����ϴ°͵� �ƴϰ� �κ� ������
	Images[UpperName] = NewImage;

	return NewImage;
}