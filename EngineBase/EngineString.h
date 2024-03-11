#pragma once
// 전부다 std의 헤더뿐이다.
#include <string>
#include <string_view>

// 설명 :
class UEngineString
{
public:
	static std::string ToUpper(std::string_view View);
	// 내가 사용하려는 함수가 멀티바이트를 지원하지 않을 때 사용.
	// MultyByte는 곧 Ansi

	// std::string => std::wstring으로 바꿀 수 있는 함수
	// C++은 다른 라이브러리나 함수를 추가하기 전까지는 
	// wstring과 string 구분을 하고 인코딩을 해가면서 사용해야 한다.
	static std::wstring AnsiToUniCode(std::string_view View);

protected:

private:
	// constrcuter destructer
	UEngineString();
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;
};

