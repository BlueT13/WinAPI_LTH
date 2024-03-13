#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include <EnginePlatform\EngineSound.h>
#include "EnginePlatform\EngineInput.h"

bool UEngineCore::IsDebugValue = false;
UEngineCore* GEngine = nullptr;

UEngineCore::UEngineCore() 
	: MainWindow()
{
}

UEngineCore::~UEngineCore() 
{
}

void UEngineCore::CoreTick()
{
	float DeltaTime = MainTimer.TimeCheck();
	double dDeltaTime = MainTimer.GetDeltaTime();

	if (1 <= Frame)
	{
		CurFrameTime += DeltaTime;

		if (CurFrameTime <= FrameTime)
		{
			return;
		} 

		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	}

	if (1.0f / 60.0f <= DeltaTime)
	{
		DeltaTime = 1.0f / 60.0f;
	}

	UEngineSound::Update();
	UEngineInput::KeyCheckTick(DeltaTime);

	for (size_t i = 0; i < DestroyLevelName.size(); i++)
	{
		std::string UpperName = UEngineString::ToUpper(DestroyLevelName[i]);

		ULevel* Level = AllLevel[UpperName];

		AllLevel.erase(DestroyLevelName[i]);

		Level->End();

		if (nullptr != Level)
		{
			delete Level;
			Level = nullptr;
		}
	}
	DestroyLevelName.clear();

	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel);
		}

		NextLevel->LevelStart(CurLevel);
		CurLevel = NextLevel;
		NextLevel = nullptr;
		MainTimer.TimeCheckStart();
		DeltaTime = MainTimer.TimeCheck();
		CurFrameTime = 0.0f;
	}

	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ ������ ������ �������� �ʾҽ��ϴ� ġ������ �����Դϴ�");
	}

	GEngine->Tick(DeltaTime);
	// ������ ���� ƽ�� ������
	CurLevel->Tick(DeltaTime);
	// ���Ϳ� �ΰ����� ������Ʈ���� ƽ�� ������ => �ൿ�ϰ�
	CurLevel->LevelTick(DeltaTime);
	// ���������� ������ ���ؼ� ȭ�鿡 �׸��� �׸��� => �׸���
	MainWindow.ScreenClear();
	CurLevel->LevelRender(DeltaTime);
	MainWindow.ScreenUpdate();
	// �����Ѵ� (�׾���� ������Ʈ���� �� �ı��Ѵ�)
	CurLevel->LevelRelease(DeltaTime);
}

void UEngineCore::EngineTick()
{

	// ���̶�� ������ �����ӻ��̿� �ѹ��� ���� �ð��� �Ҹ��ϴ� �Լ��� ȣ���ϸ�
	// ��ŸŸ���� �����ϴ� ������ ���Ѵ�.
	// EX) for�� 1000���� �����µ� 5�ʰ� �ɷȴ�.
	// �� ���� 5.0�� ���� ���� �� �Ÿ��� �� ������ ���� �̵��ؼ� �����̵��� �ϵ��� ���̰� �ȴ�.

	GEngine->CoreTick();

}

void UEngineCore::EngineEnd()
{
	// std::map<std::string, ULevel*>::iterator StartI

	for (std::pair<const std::string, ULevel*>& _Pair : GEngine->AllLevel)
	{
		if (nullptr == _Pair.second)
		{
			continue;
		}

		delete _Pair.second;
		_Pair.second = nullptr;
	}

	GEngine->AllLevel.clear();
}

void UEngineCore::EngineStart(HINSTANCE _hInstance)
{
	GEngine = this;
	MainTimer.TimeCheckStart();
	CoreInit(_hInstance); 
	BeginPlay();
	UEngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void UEngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	UEngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	this->AllLevel;

	EngineInit = true;
}

void UEngineCore::BeginPlay()
{

}

void UEngineCore::Tick(float _DeltaTime)
{

}

void UEngineCore::End()
{

}

void UEngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "��� �������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�");
	}

	NextLevel = AllLevel[UpperName];
}

void UEngineCore::LevelInit(ULevel* _Level, std::string_view _Name)
{
	_Level->SetName(_Name);
	_Level->BeginPlay();
}

void UEngineCore::DestroyLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "�������� �ʴ� ������ �ı��Ҽ��� �����ϴ�");
	}

	DestroyLevelName.push_back(UpperName);
}
