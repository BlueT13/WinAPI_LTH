#pragma once
#include <string>
#include <string_view>
#include <map>


// class Monster �̱����̶�� �޸������� 
// class Monster�� �� 1���� ��������� �־�� �Ѵ�.

// class UEngineResourcesManager �̱����̶�� �޸������� 
// class UEngineResourcesManager�� �� 1���� ��������� �־�� �Ѵ�.

class UImage;
// ���� : �̹��� ���� ����� ���� �����Ұ̴ϴ�.
//       ���ӿ��� ���ҽ���� �Ҹ��� ��ü���� ���δ� �̳༮�� ������ ����.
class UEngineResourcesManager
{
public:
	// delete Function
	UEngineResourcesManager(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager(UEngineResourcesManager&& _Other) noexcept = delete;
	UEngineResourcesManager& operator=(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager& operator=(UEngineResourcesManager&& _Other) noexcept = delete;

	// �̱����̶�� �Ѵ�.
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
	//  // 1. ���� �����ϰ� ������ �����Ҽ� �ִ�.
	//  // 2. new�� �����Ҵ�����?
	//  //    new�� ���� �������� �������� �ؾ��Ѵٴ� �ݾ��� �ִ�.
	//  //    ?????? 100����Ʈ �Ʋ��� ���ϰ�?
	//	if (nullptr == pInst)
	//	{
	//		pInst = new UEngineResourcesManager();
	//	}
	//	
	//	return pInst;
	//}

	// �������� �̱��� ��ü�� �ı��Ҽ� �ִٴ� ������ �ִ�.
	// �׷� �� �ı��ϴµ�?
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
	// ������ ���󰡽� ���α׷���.
	// �ϵ��ũ�� �ִ� �̹����� �ε��Ѵ�.
	UImage* LoadImg(std::string_view _Path);

	UImage* FindImg(std::string_view _Name);



protected:

private: 
	// constrcuter destructer
	UEngineResourcesManager();
	~UEngineResourcesManager();

	std::map<std::string, UImage*> Images;

	// C++������ �̷��� static���� �ڱ��ڽ��� �ڱⰡ ���ο��� ����ϴ�.
	// �ڱ��ڽ��� ���ο��� ������ ����� ����� ����.
	// �װ� �� 1���� ����°� �̱����� ����
	// static UEngineResourcesManager Inst;
	// static UEngineResourcesManager* pInst;
};
