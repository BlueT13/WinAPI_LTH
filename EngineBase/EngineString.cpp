#include "EngineString.h"
#include <Windows.h>
#include "EngineDebug.h"

UEngineString::UEngineString() 
{
}

UEngineString::~UEngineString() 
{
}

std::wstring UEngineString::AnsiToUniCode(std::string_view _View)
{
	// ������ ����
	// �����ڵ�� �����Ͻ��� ���ڿ��� ������ �˰� �ִ°��� window�̱� ����
	// ��ȯ�Լ��� �ִٸ� window�� ������ ��� ��
	// MultiByteToWideChar�� ��Ƽ����Ʈ�� �����ڵ�� ������ �� �ִ�.
	// �� �Լ��� ������ 2����
	// ù ��° 
	// ���ڿ��� ��ȯ�ϸ� ũ�Ⱑ ����
	// 1����Ʈ�̰ų� 2����Ʈ�� ���ڿ� => ��Ƽ����Ʈ
	// ������ 2����Ʈ �ϴ� => �����ڵ�
	// ����Ʈ ����� �ٲ�
	// char Arr[5000] => ��Ƽ����Ʈ ���ڿ�
	// wchar_t wArr[] => ��ȯ�Ѱ� ���� wide����Ʈ �迭
	
	// �� ��°
	// ��ȯ�� ���ڿ��� �־����� ���� ��ȯ�Ǵ� ũ�⸦ ����
	// int Size = �ʿ��� wchar_�迭�� ũ�⸦ ����

	//UINT CodePage, = CP_ACP ���� window�� ������ �ʱ� ���ڿ� ���ڵ����� ó�� ��û
	//DWORD dwFlags, = ��ȯ�� �� �߰� ������ �ֳ���? 0(�ƴϿ�) => (0�� ����Ʈ ����)
	//LPCCH lpMultiByteStr, = ��ȯ�� ���ڿ�
	//int cbMultiByte, => ��ȯ�� ���ڿ��� ����
	//LPWSTR lpWideCharStr, => wide ����Ʈ ���ڿ� => ��ȯ�� ���� nullptr �־��ָ� ũ�⸦ ����
	//int cchWideChar => wide ����Ʈ ���ڿ��� ũ��
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	// std::string�̳� std::wstring ���ο� std::vector<char>
	// std::vector<char> Vector;
	// Vector[0] => char&
	// &Vector[0] => *char

	//wchar_t* Arr = new wchar_t[Size];
	//delete Arr;
	std::wstring Result;
	Result.resize(Size);

	// ��ȯ�� ������ ����
	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	// RValue ���۷����� �ǹǷ� �߰� ������ �̷������ ����
	return Result;
}

std::string UEngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}