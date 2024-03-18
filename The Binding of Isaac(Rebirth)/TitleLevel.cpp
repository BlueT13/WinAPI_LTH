#include "TitleLevel.h"
#include "StartImage.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineResourcesManager.h>
#include "IntroBackground.h"


UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory FilePath;
	FilePath.MoveToSearchChild("Res");
	FilePath.Move("TitleLevel");
	UEngineResourcesManager::GetInst().LoadFolder(FilePath.AppendPath("Start"));
	AStartImage* StartImg = SpawnActor<AStartImage>();

	SoundFileList = FilePath.AllFile({ ".wav" }, true);
	for (UEngineFile& File : SoundFileList)
	{
		UEngineSound::Load(File.GetFullPath());
	}
	TitleSound = UEngineSound::SoundPlay("title screen.wav");
	TitleSound.SetVolume(0.3f);
	TitleSound.Off();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == AIntroBackground::IntroEnd)
	{
		TitleSound.On();
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		TitleSound.Off();
		GEngine->ChangeLevel("PlayLevel");
	}
	if (UEngineInput::IsDown(VK_ESCAPE))
	{
		TitleSound.Off();
		GEngine->MainWindow.Off();
	}
}
