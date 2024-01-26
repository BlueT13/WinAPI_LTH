#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"


EngineCore* GEngine = nullptr;

EngineCore::EngineCore() 
	: MainWindow()
{
}

EngineCore::~EngineCore() 
{
}

void EngineCore::CoreTick()
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

	EngineInput::KeyCheckTick(DeltaTime);

	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ ������ ������ �������� �ʾҽ��ϴ� ġ������ �����Դϴ�");
	}

	// ������ ���� ƽ�� ������
	CurLevel->Tick(DeltaTime);
	// ���Ϳ� �ΰ����� ������Ʈ���� ƽ�� ������ => �ൿ�ϰ�
	CurLevel->LevelTick(DeltaTime);
	// ���������� ������ ���ؼ� ȭ�鿡 �׸��� �׸��� => �׸���
	CurLevel->LevelRender(DeltaTime);
	// �����Ѵ�.(�׾���� ������Ʈ���� �� �ı��Ѵ�)
	CurLevel->LevelRelease(DeltaTime);


	//HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	//Rectangle(WindowDC, -200, -200, 3000, 3000);
}

void EngineCore::EngineTick()
{

	// ���̶�� ������ �����ӻ��̿� �ѹ��� ���� �ð��� �Ҹ��ϴ� �Լ��� ȣ���ϸ�
	// ��ŸŸ���� �����ϴ� ������ ���Ѵ�.
	// EX) for�� 1000���� �����µ� 5�ʰ� �ɷȴ�.
	//    5.0
	//    => �ѹ��� 5.0�� ���� ������ ���� �������Ӹ��� �̵��ع����ϱ� �����̵��ϵ��� ���̰� �ȴ�.

	GEngine->CoreTick();

}

void EngineCore::EngineEnd()
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

void EngineCore::EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore)
{
	EngineCore* Ptr = _UserCore;
	GEngine = Ptr;
	Ptr->MainTimer.TimeCheckStart();
	Ptr->CoreInit(_hInstance); 
	Ptr->BeginPlay();
	EngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void EngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	EngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	this->AllLevel;

	EngineInit = true;
}

void EngineCore::BeginPlay()
{

}

void EngineCore::Tick(float _DeltaTime)
{

}

void EngineCore::End()
{

}

void EngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "��� �������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�");
	}

	// ���� �������� ��������?
	CurLevel = AllLevel[UpperName];
}

void EngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}