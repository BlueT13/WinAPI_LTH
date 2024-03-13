#pragma once
#include <string>
#include <string_view>
#include <map>

// class Monster �̱����̶�� �޸������� 
// class Monster�� �� 1���� ��������� �־�� �Ѵ�.

// class UEngineResourcesManager �̱����̶�� �޸������� 
// class UEngineResourcesManager�� �� 1���� ��������� �־�� �Ѵ�.

class UWindowImage;
// ���� : �̹��� ���� ���� ���� ����
//       ���ӿ��� ���ҽ���� �Ҹ��� ��ü���� ���� �� �̰��� ����
class UEngineResourcesManager
{
public:
	// delete Function
	UEngineResourcesManager(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager(UEngineResourcesManager&& _Other) noexcept = delete;
	UEngineResourcesManager& operator=(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager& operator=(UEngineResourcesManager&& _Other) noexcept = delete;

	// �̱���
	static UEngineResourcesManager& GetInst()
	{
		// ����static �̱���
		static UEngineResourcesManager Inst = UEngineResourcesManager();
		return Inst;
	}

	// �������� �̱���
	//static UEngineResourcesManager* GetPInst()
	//{
	//  // ���������� ����
	//  // 1. ���� �����ϰ� ������ ������ �� �ִ�.
	//  // 2. new�� �����Ҵ�
	//	if (nullptr == pInst)
	//	{
	//		pInst = new UEngineResourcesManager();
	//	}
	//	
	//	return pInst;
	//}

	// �������� �̱��� ��ü�� �ı��Ҽ� �ִٴ� ������ �ִ�.
	//static void Destroy()
	//{
	//	if (nullptr != pInst)
	//	{
	//		delete pInst;
	//		pInst = nullptr;
	//	}
	//	return;
	//}



	// �������̽��� ������ �ʹ� �߻����� �����̴�.
	// �ϵ��ũ�� �ִ� �̹����� �ε��Ѵ�.
	UWindowImage* LoadImg(std::string_view _Path);

	UWindowImage* LoadImg(std::string_view _Path, std::string_view _Name);

	void UnloadImg(std::string_view _Name);

	bool IsImage(std::string_view _Name);

	UWindowImage* FindImg(std::string_view _Name);

	// �� �̹����� �����µ� ���Ӱ� ����� ���.
	UWindowImage* LoadFolder(std::string_view _Path);

	// �� �̹����� �����µ� ���Ӱ� ����� ���.
	UWindowImage* LoadFolder(std::string_view _Path, std::string_view _Name);

	// ������ �̹� �ε��� �̹����� Ŀ���ϴ� ���
	void CuttingImage(std::string_view _Name, int _X, int _Y);

protected:

private: 
	// constrcuter destructer
	UEngineResourcesManager();
	~UEngineResourcesManager();

	std::map<std::string, UWindowImage*> Images;

	// C++������ �̷��� static���� �ڱ� �ڽ��� �ڱⰡ ���ο��� ����ϴ�.
	// �ڱ��ڽ��� ���ο��� ������ ����� ���� �� �ִ�.
	// �װ� �� 1���� ����°� �̱����� ����
	// static UEngineResourcesManager Inst;
	// static UEngineResourcesManager* pInst;
};

