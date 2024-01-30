#pragma once
// ���δ� std�� ������̴�.
#include <string>
#include <string_view>

// ���� :
class UEngineString
{
public:
	static std::string ToUpper(std::string_view View);
	// ���� ����Ϸ��� �Լ��� ��Ƽ����Ʈ�� �������� ������.
	// MultyByte�� �� Ansi

	// std::string => std::wstring���� �ٲܼ� �ִ� �Լ�
	// ����Ʈ���忡�� ������ �Լ�. ���� => ���ڵ��� �˾ƾ��ϴ� ���� ������.
	// 3���� ����� �ϴ� c#�̳� java�̷��ֵ��� string�� �־��
	// wstring string ������ �ȵǾ� �ִ�.
	// C++�� �������� �ٸ� ���̺귯���� �Լ��� �߰��ϱ� �������� 
	// wstring�� string ������ �ϰ� ���ڵ��� �ذ��鼭 ����ؾ� �Ѵ�.
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

