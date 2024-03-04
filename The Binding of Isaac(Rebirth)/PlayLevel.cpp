#include "PlayLevel.h"
#include "Player.h"
#include "Room.h"
#include "Fly.h"
#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory FilePath;
	FilePath.MoveToSearchChild("Res");
	FilePath.Move("PlayLevel");
	std::list<UEngineFile> AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}
	UEngineResourcesManager::GetInst().CuttingImage("Head.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Body.png", 5, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Tears.png", 5, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Fly.png", 5, 3);
	UEngineResourcesManager::GetInst().CuttingImage("Door.png", 4, 5);

	SpawnActor<APlayer>();
	SpawnActor<AFly>();

	CreateRoom(0, 0, "Room_01.png");
	CreateRoom(-1, 0, "Room_02.png");
	CreateRoom(1, 0, "Room_02.png");
	CreateRoom(0, -1, "Room_02.png");
	CreateRoom(0, 1, "Room_02.png");

	SetCurRoom(0, 0);
}

// 플레이어가 존재하는 룸 지정
void UPlayLevel::SetCurRoom(int _X, int _Y)
{
	FRoomIndex Index = { _X , _Y };

	if (false == Rooms.contains(Index.Key))
	{
		MsgBoxAssert("존재하지 않는 룸을 포커스 룸으로 설정할 수 없습니다.");
		return;
	}

	for (std::pair<const __int64, ARoom*>& _Pair : Rooms)
	{
		ARoom* Room = _Pair.second;
		//Room->SetActive(false);
	}

	CurRoom = Rooms[Index.Key];
	CurRoom->RoomCameraFocus();
	//CurRoom->SetActive(true);
}

ARoom* UPlayLevel::GetCurRoom()
{
	return CurRoom;
}

void UPlayLevel::CreateRoom(int _X, int _Y, std::string_view _Img)
{
	FRoomIndex Index = { _X , _Y };

	if (true == Rooms.contains(Index.Key))
	{
		MsgBoxAssert("이미 방이 존재하는 곳에 또 방을 만들려고 했습니다.");
	}

	FVector WindowScale = GEngine->MainWindow.GetWindowScale();

	ARoom* NewRoom = SpawnActor<ARoom>();
	NewRoom->SetPlayLevel(this);
	NewRoom->SetRoomImg(_Img);
	NewRoom->SetRoomIndex(Index);
	NewRoom->SetActorLocation({ WindowScale.X * _X, WindowScale.Y * _Y });

	for (size_t i = 0; i < static_cast<int>(ERoomDir::Max); i++)
	{
		FRoomIndex LinkCheckDir;
		LinkCheckDir.X = _X + FRoomIndex::ArrDir[i].X;
		LinkCheckDir.Y = _Y + FRoomIndex::ArrDir[i].Y;

		// 연결할 룸이 없다면 continue
		if (false == Rooms.contains(LinkCheckDir.Key))
		{
			continue;
		}

		ARoom* OtherRoom = Rooms[LinkCheckDir.Key];

		NewRoom->Link(OtherRoom);
		OtherRoom->Link(NewRoom);
	}

	Rooms[Index.Key] = NewRoom;

}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->ChangeLevel("TitleLevel");
	}
}
