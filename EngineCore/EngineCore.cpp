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
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다 치명적인 오류입니다");
	}

	GEngine->Tick(DeltaTime);
	// 레벨이 먼저 틱을 돌리고
	CurLevel->Tick(DeltaTime);
	// 액터와 부가적인 오브젝트들의 틱도 돌리고 => 행동하고
	CurLevel->LevelTick(DeltaTime);
	// 랜더러들의 랜더를 통해서 화면에 그림도 그린다 => 그리고
	MainWindow.ScreenClear();
	CurLevel->LevelRender(DeltaTime);
	MainWindow.ScreenUpdate();
	// 정리한다 (죽어야할 오브젝트들은 다 파괴한다)
	CurLevel->LevelRelease(DeltaTime);
}

void UEngineCore::EngineTick()
{

	// 렉이라는 현상은 프레임사이에 한번에 많은 시간을 소모하는 함수를 호출하면
	// 델타타임이 증가하는 현상을 말한다.
	// EX) for문 1000만번 돌리는데 5초가 걸렸다.
	// 한 번에 5.0초 동안 가야 할 거리를 한 프레임 만에 이동해서 순간이동을 하듯이 보이게 된다.

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
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 체인지 하려고 했습니다");
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
		MsgBoxAssert(std::string(_Name) + "존재하지 않는 레벨을 파괴할수는 없습니다");
	}

	DestroyLevelName.push_back(UpperName);
}
