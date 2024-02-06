#pragma once
#include <Windows.h>
#include <string>
#include <EngineBase\EngineMath.h>

class UWindowImage;
// ���� :
class UEngineWindow
{
public:
	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Open(std::string_view _Title = "Title");

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

	UWindowImage* GetWindowImage()
	{
		return WindowImage;
	}

	UWindowImage* GetBackBufferImage()
	{
		return BackBufferImage;
	}

	void SetWindowPosition(const FVector& _Pos);
	void SetWindowScale(const FVector& _Scale);

	void ScreenClear();
	void ScreenUpdate();

	FVector GetWindowScale()
	{
		return Scale;
	}

	FVector GetMousePosition();

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HWND hWnd = nullptr;
	// HDC hDC = nullptr;
	// ������� ���������� ����� DC�� ������ �ִ� ���� �̹���
	UWindowImage* WindowImage = nullptr;
	// �����츦 ���� 1���� �����ϱ� ���� �̹���

	// �̳༮�� ������ �մϴ�.
	// �������� ũ�⸦ �츰 ���� Ư�� �Ҽ��� �����.
	// �̹����� 1�� ������. => ������ ��ü ũ�⸸�ϰ� => �ܰ踦 �Ҽ��� ����.
	UWindowImage* BackBufferImage = nullptr;
	// �̹����� 2���� �̹����� ���۶�� �������ε� �θ���. => ������۸��̶�� �̸��� �̴ϴ�.
	FVector Scale;
	FVector Position;

};

