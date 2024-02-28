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


	// 100���������� ����Ǵ� ��ǻ�Ͱ� �ִٸ�
	// 0.01�� ���;� �Ѵ�.
	// float Time;
	// Time += 0.01f;
	// 
	// �츮�� 50���������� �����ϰ� �ʹ�.
	// 0.02�� ���;� �Ѵ�.
	// FrameTime = 1 / 50.0; =>
	// FrameTime = 0.02;
	// CurFrameTime += 0.01;
	// 0.01             0.02
	// CurFrameTime <= FrameTime
	// CurFrameTime += 0.01;
	// 0.0203000        0.02
	// CurFrameTime <= FrameTime
	// ���ƾ��Ѵ�.
	// 0.0003000
	// CurFrameTime -= FrameTime;

	if (1 <= Frame)
	{
		//               5.0f
		CurFrameTime += DeltaTime;

		//  0.00001        0.016666675
		if (CurFrameTime <= FrameTime)
		{
			return;
		} 

		//  0.0167         0.016666675
		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	}

	// �̰͵� �ɼ�
	if (1.0f / 60.0f <= DeltaTime)
	{
		DeltaTime = 1.0f / 60.0f;
	}

	UEngineSound::Update();
	UEngineInput::KeyCheckTick(DeltaTime);


	// �������ӵ��� ������ ����� ������ �ʰ�
	// �������� �����Ҷ� ������ ��ȭ�Ѵ�.
	// ��Ű�� ���ؼ� release �������� ����Ǵ� ���ȿ��� �����
	// ������ �ٲ��� �ʴ´�.
	if (nullptr != NextLevel)
	{
		// ���ʿ��� ���� ������ �������� ���� ���̴�.
		// �ٲ� ������ �ִٴ� �̾߱��Դϴ�.
		if (nullptr != CurLevel)
		{
			// ������ �������� �˸��ϴ�.
			CurLevel->LevelEnd(NextLevel);
		}

		NextLevel->LevelStart(CurLevel);
		CurLevel = NextLevel;
		NextLevel = nullptr;
		MainTimer.TimeCheckStart();
		DeltaTime = MainTimer.TimeCheck();
		CurFrameTime = 0.0f;
	}

	for (size_t i = 0; i < DestroyLevelName.size(); i++)
	{
		std::string UpperName = UEngineString::ToUpper(DestroyLevelName[i]);

		ULevel* Level = AllLevel[UpperName];
		if (nullptr != Level)
		{
			delete Level;
			Level = nullptr;
		}

		AllLevel.erase(DestroyLevelName[i]);
	}
	DestroyLevelName.clear();

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
	// �����Ѵ�.(�׾���� ������Ʈ���� �� �ı��Ѵ�)
	CurLevel->LevelRelease(DeltaTime);


	//HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	//Rectangle(WindowDC, -200, -200, 3000, 3000);
}

void UEngineCore::EngineTick()
{

	// ���̶�� ������ �����ӻ��̿� �ѹ��� ���� �ð��� �Ҹ��ϴ� �Լ��� ȣ���ϸ�
	// ��ŸŸ���� �����ϴ� ������ ���Ѵ�.
	// EX) for�� 1000���� �����µ� 5�ʰ� �ɷȴ�.
	//    5.0
	//    => �ѹ��� 5.0�� ���� ������ ���� �������Ӹ��� �̵��ع����ϱ� �����̵��ϵ��� ���̰� �ȴ�.

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

void Exit()
{

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

	// ���� �������� ��������?
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
