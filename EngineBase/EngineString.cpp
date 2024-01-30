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
	// ������ �����մϴ�.
	// �����ڵ�� �����Ͻ��� ���ڿ��� ������ �˰� �ִ°��� window�̱� ����
	// ��ȯ�Լ��� �ִٸ� window�� ������ ��� �մϴ�.
	// MultiByteToWideChar�� ��Ƽ����Ʈ�� �����ڵ�� �����Ҽ� �ִ�.
	// ���Լ��� ������ 2������ �ֽ��ϴ�.
	// ù��° 
	// ���ڿ��� ��ȯ�ϸ� ũ�Ⱑ ����˴ϴ�.

	// 1����Ʈ�̰ų� 2����Ʈ�� ���ڿ� => ��Ƽ����Ʈ
	// ������ 2����Ʈ �ϴ� => �����ڵ�
	// ����Ʈ ����� �ٲ�̴ϴ�.

	// char Arr[5000] => ��Ƽ����Ʈ ���ڿ�
	// wchar_t wArr[] => �װ� ��ȯ�Ѱ� ���� wide����Ʈ �迭 ??????????
	// �Ϲ������� �󸶳� �ʿ��ѵ�? 
	// �� �Լ��� 2���� ������ �ִ�.
	// ��ȯ�� ���ڿ��� �־���������
	// ��ȯ�Ǿ����� ũ�⸦ �����մϴ�.
	// int Size = �ʿ��� wchar_�迭�� ũ�⸦ �����մϴ�.

	//UINT CodePage, = CP_ACP ���� window�� ������ �ʱ� ���ڿ� ���ڵ����� ó���ش޶�
	//DWORD dwFlags, = ��ȯ�Ҷ� �߰� ������ �ֳ���? �ƴϿ� 0 => ����Ʈ ���� �÷��׾ּ� �˰� ���� �ʾ� 0=> ����Ʈ�� ����
	//LPCCH lpMultiByteStr, = ��ȯ�� ���ڿ�
	//int cbMultiByte, => ��ȯ�� ���ڿ��� ����
	//LPWSTR lpWideCharStr, => wide ����Ʈ ���ڿ� => ��ȯ�� ���� nullptr �־��ָ� �̳༮�� ũ�⸦ �����Ѵ�
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

	// ��ȯ�Ǿ��� ������ �����µ�.
	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	// �ڿ������� RValue ���۷����� �Ǵϱ� �߰� ������ �̷������ �ʰ���.
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