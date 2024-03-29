#include "PlayLevel.h"
#include "Player.h"
#include "Room.h"
#include "UIManager.h"
#include "MiniMap.h"
#include "HpUI.h"
#include "Fly.h"
#include "DukeOfFlies.h"
#include "ContentsHelper.h"
#include <EngineCore/EngineResourcesManager.h>
#include <EngineBase/EngineDirectory.h>

bool UPlayLevel::IsEnd = false;

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == UEngineResourcesManager::GetInst().IsImage("Head.png"))
	{
		UEngineDirectory FilePath;
		FilePath.MoveToSearchChild("Res");
		FilePath.Move("PlayLevel");
		AllFileList = FilePath.AllFile({ ".png", ".bmp" }, true);
		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath();
			UEngineResourcesManager::GetInst().LoadImg(FullPath);
		}

		SoundFileList = FilePath.AllFile({ ".wav" }, true);
		for (UEngineFile& File : SoundFileList)
		{
			UEngineSound::Load(File.GetFullPath());
		}

		UEngineResourcesManager::GetInst().CuttingImage("Head.png", 5, 2);
		UEngineResourcesManager::GetInst().CuttingImage("Body.png", 5, 6);
		UEngineResourcesManager::GetInst().CuttingImage("PlayerState.png", 5, 3);

		UEngineResourcesManager::GetInst().CuttingImage("Tears.png", 5, 6);
		UEngineResourcesManager::GetInst().CuttingImage("DestroyTear.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Bomb.png", 5, 1);
		UEngineResourcesManager::GetInst().CuttingImage("Explosion.png", 5, 3);

		UEngineResourcesManager::GetInst().CuttingImage("NormalRoomDoor.png", 4, 2);
		UEngineResourcesManager::GetInst().CuttingImage("GoldRoomDoor.png", 4, 3);
		UEngineResourcesManager::GetInst().CuttingImage("BossRoomDoor.png", 4, 2);

		UEngineResourcesManager::GetInst().CuttingImage("MonsterTear.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("SpawnEffect_Small.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("SpawnEffect_Medium.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("SpawnEffect_Large.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("LargeBloodExplosion.png", 5, 2);

		UEngineResourcesManager::GetInst().CuttingImage("Fly.png", 5, 3);
		UEngineResourcesManager::GetInst().CuttingImage("Pooter.png", 5, 4);
		UEngineResourcesManager::GetInst().CuttingImage("Boomfly.png", 2, 1);
		UEngineResourcesManager::GetInst().CuttingImage("RedBoomfly.png", 2, 1);

		UEngineResourcesManager::GetInst().CuttingImage("DukeOfFlies_SpawnFly.png", 3, 1);
		UEngineResourcesManager::GetInst().CuttingImage("DukeOfFlies_SendFly.png", 3, 1);
	}

	SpawnActor<APlayer>(IsaacUpdateOrder::Player);
	SpawnActor<UIManager>(IsaacUpdateOrder::UI);
	SpawnActor<AMiniMap>(IsaacUpdateOrder::UI);
	SpawnActor<AHpUI>(IsaacUpdateOrder::UI);

	ARoom* Room_0 = CreateRoom(0, 0, "Room_01.png", ERoomType::Normal);
	//ARoom* Room_1 = CreateRoom(0, 1, "Room_01.png", ERoomType::GoldRoom);
	ARoom* Room_2 = CreateRoom(-1, 0, "Room_02.png", ERoomType::Normal);
	ARoom* Room_3 = CreateRoom(-2, 0, "Room_01.png", ERoomType::Normal);
	ARoom* Room_4 = CreateRoom(1, 0, "Room_02.png", ERoomType::Normal);
	ARoom* Room_5 = CreateRoom(2, 0, "Room_01.png", ERoomType::Normal);
	ARoom* Room_6 = CreateRoom(0, -1, "Room_02.png", ERoomType::Normal);
	ARoom* Room_7 = CreateRoom(0, -2, "Room_01.png", ERoomType::Normal);
	ARoom* Room_8 = CreateRoom(-1, -2, "Room_02.png", ERoomType::Normal);
	ARoom* Room_9 = CreateRoom(-2, -2, "Room_03.png", ERoomType::BossRoom);

	//Room_1->CreateItem(EItemType::Passive, {0, 0});
	Room_2->CreateMonsters(EMonsterType::Boomfly, { -200, 0 });
	Room_3->CreateMonsters(EMonsterType::RedBoomfly, { -100, 0 });
	Room_4->CreateMonsters(EMonsterType::Fly, { 200, 0 });
	Room_5->CreateMonsters(EMonsterType::Pooter, { 200, 0 });

	Room_6->CreateMonsters(EMonsterType::Fly, { -200, 0 });
	Room_6->CreateMonsters(EMonsterType::Fly, { 200, 0 });
	Room_6->CreateMonsters(EMonsterType::Pooter, { -200, -100 });
	Room_6->CreateMonsters(EMonsterType::Pooter, { 200, -100 });

	Room_7->CreateMonsters(EMonsterType::Boomfly, { -200, 0 });
	Room_7->CreateMonsters(EMonsterType::RedBoomfly, { 200, 0 });

	Room_8->CreateMonsters(EMonsterType::Fly, { -200, 100 });
	Room_8->CreateMonsters(EMonsterType::Pooter, { 200, 100 });
	Room_8->CreateMonsters(EMonsterType::Boomfly, { -50, 0 });
	Room_8->CreateMonsters(EMonsterType::RedBoomfly, { 50, 0 });

	Room_9->CreateMonsters(EMonsterType::DukeOfFlies, { 0, 0 });

	SetPrevRoom(0, 0);
	SetCurRoom(0, 0);
}

// 플레이어가 존재하는 룸 지정
void UPlayLevel::SetCurRoom(int _X, int _Y)
{
	FRoomIndex Index = { _X , _Y };

	if (false == Rooms.contains(Index.Key))
	{
		MsgBoxAssert("존재하지 않는 룸을 CurRoom으로 설정할 수 없습니다.");
		return;
	}

	for (std::pair<const __int64, ARoom*>& _Pair : Rooms)
	{
		ARoom* Room = _Pair.second;
		Room->SetActive(false);
		Room->ActiveMonsters(false);
	}

	CurRoom = Rooms[Index.Key];
	CurRoom->RoomCameraFocus();
	CurRoom->SetActive(true);
	PrevRoom->SetActive(true);

	CurRoom->ActiveMonsters(true);
}

void UPlayLevel::SetPrevRoom(int _X, int _Y)
{
	FRoomIndex Index = { _X , _Y };

	if (false == Rooms.contains(Index.Key))
	{
		MsgBoxAssert("존재하지 않는 룸을 PrevRoom으로 설정할 수 없습니다.");
		return;
	}

	PrevRoom = Rooms[Index.Key];
}

ARoom* UPlayLevel::GetCurRoom()
{
	return CurRoom;
}

ARoom* UPlayLevel::GetPrevRoom()
{
	return PrevRoom;
}

ARoom* UPlayLevel::CreateRoom(int _X, int _Y, std::string_view _Img, ERoomType _RoomType)
{
	FRoomIndex Index = { _X , _Y };

	if (true == Rooms.contains(Index.Key))
	{
		MsgBoxAssert("이미 방이 존재하는 곳에 또 방을 만들려고 했습니다.");
	}

	FVector WindowScale = GEngine->MainWindow.GetWindowScale();

	ARoom* NewRoom = SpawnActor<ARoom>(IsaacUpdateOrder::Room);
	NewRoom->SetPlayLevel(this);
	NewRoom->SetRoomImg(_Img);
	NewRoom->SetRoomType(_RoomType);
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

	return NewRoom;
}


void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (CurRoom != PrevRoom)
	{
		RoomMoveCameraTime += _DeltaTime * 5;

		// 
		// PrevRoom => 시작위치
		// CurRoom => 도착 위치
		// 카메라가 PrevRoom을 바라보고 있다가
		// CurRoom룸을 바라볼때까지 이동한다.

		FVector WindowScale = GEngine->MainWindow.GetWindowScale();

		FVector StartCameraPos = PrevRoom->GetActorLocation() - WindowScale.Half2D();
		FVector TargetCameraPos = CurRoom->GetActorLocation() - WindowScale.Half2D();

		FVector CurCameraPos = FVector::LerpClamp(StartCameraPos, TargetCameraPos, RoomMoveCameraTime);

		SetCameraPos(CurCameraPos);

		if (1.0f <= RoomMoveCameraTime)
		{
			RoomMoveCameraTime = 0.0f;
			PrevRoom = CurRoom;
			CurRoom->RoomCameraFocus();
		}
	}

	// 미니맵 확대 축소
	if (UEngineInput::IsDown(VK_TAB))
	{
		if (AMiniMap::MiniMapS->IsActive())
		{
			AMiniMap::MiniMapS->SetActive(false);
			AMiniMap::MiniMapL->SetActive(true);
		}
		else
		{
			AMiniMap::MiniMapS->SetActive(true);
			AMiniMap::MiniMapL->SetActive(false);
		}
	}

	// esc 버튼이 눌리고 퍼즈창이 꺼져있다면
	if (UEngineInput::IsDown(VK_ESCAPE) && !UIManager::PauseScreen->IsActive())
	{
		// 퍼즈창을 띄운다.
		UIManager::PauseScreen->SetActive(true);
		SetAllTimeScale(0.0f);
		return;
	}

	// 퍼즈창이 켜져있을 때
	if (UIManager::PauseScreen->IsActive())
	{
		if (UEngineInput::IsDown(VK_SPACE))
		{
			UIManager::PauseScreen->SetActive(false);
			SetAllTimeScale(1.0f);
		}
		else if (UEngineInput::IsDown(VK_ESCAPE))
		{
			GEngine->ChangeLevel("TitleLevel");
			IsEnd = true;
			GEngine->DestroyLevel("PlayLevel");
		}
	}


	if (UEngineInput::IsPress('R'))
	{
		IsEnd = false;
		ADukeOfFlies::IsBossDeath = false;
		GEngine->DestroyLevel("PlayLevel");
	}
}

void UPlayLevel::End()
{
	APlayer::PlayerHp = 6;
	GEngine->CreateLevel<UPlayLevel>("PlayLevel");
	if (IsEnd == false)
	{
		GEngine->ChangeLevel("PlayLevel");
	}
}
