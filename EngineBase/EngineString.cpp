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
	// 윈도우 지원
	// 국가코드와 컴파일시의 문자열의 배합을 알고 있는것은 window이기 때문
	// 변환함수가 있다면 window가 지원해 줘야 함
	// MultiByteToWideChar는 멀티바이트를 유니코드로 변경할 수 있다.
	// 이 함수의 역할은 2가지
	// 첫 번째 
	// 문자열을 변환하면 크기가 변경
	// 1바이트이거나 2바이트인 문자열 => 멀티바이트
	// 무조건 2바이트 하는 => 유니코드
	// 바이트 사이즈가 바뀜
	// char Arr[5000] => 멀티바이트 문자열
	// wchar_t wArr[] => 변환한걸 받을 wide바이트 배열
	
	// 두 번째
	// 변환할 문자열만 넣어줬을 때는 변환되는 크기를 리턴
	// int Size = 필요한 wchar_배열의 크기를 리턴

	//UINT CodePage, = CP_ACP 현재 window에 설정된 초기 문자열 인코딩으로 처리 요청
	//DWORD dwFlags, = 변환할 때 추가 정보가 있나요? 0(아니요) => (0은 디폴트 설정)
	//LPCCH lpMultiByteStr, = 변환할 문자열
	//int cbMultiByte, => 변환할 문자열의 길이
	//LPWSTR lpWideCharStr, => wide 바이트 문자열 => 변환을 받을 nullptr 넣어주면 크기를 리턴
	//int cchWideChar => wide 바이트 문자열의 크기
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return L"";
	}

	// std::string이나 std::wstring 내부에 std::vector<char>
	// std::vector<char> Vector;
	// Vector[0] => char&
	// &Vector[0] => *char

	//wchar_t* Arr = new wchar_t[Size];
	//delete Arr;
	std::wstring Result;
	Result.resize(Size);

	// 변환된 개수를 리턴
	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return L"";
	}

	// RValue 레퍼런스가 되므로 추가 생성은 이루어지지 않음
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