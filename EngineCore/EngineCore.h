#pragma once
#include <EngineBase\EngineDebug.h>
#include <EnginePlatform\EngineWindow.h>
#include <map>

class ULevel;
// ���� :
class EngineCore
{
public:
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// �ϳ��� ������ ��������� ��������� �������̹Ǥ�.
	// �ھ �����츦 ������
	EngineWindow MainWindow;

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore);

	void CoreInit(HINSTANCE _Init);

	virtual void Start();
	virtual void Update();
	virtual void End();

	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		if (true == AllLevel.contains(_Name.data()))
		{
			MsgBoxAssert(std::string(_Name) + "�̶�� �̸��� Level�� �� ������� �߽��ϴ�");
		}

		LevelType* NewLevel = new LevelType();
		AllLevel.insert(std::pair<std::string, ULevel*>(_Name, NewLevel));
	}

protected:
	EngineCore();

private:
	bool EngineInit = false;
	std::map<std::string, ULevel*> AllLevel;

	static void EngineUpdate();
	static void EngineEnd();
};

extern EngineCore* GEngine;


#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
    LeakCheck; \
	USERCORE NewUserCore = USERCORE(); \
	EngineCore::EngineStart(hInstance, &NewUserCore); \
}