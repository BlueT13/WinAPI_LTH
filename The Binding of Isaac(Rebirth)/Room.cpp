#include "Room.h"
#include "ContentsHelper.h"
#include "Player.h"
//#include <EngineCore\EngineResourcesManager.h>

FRoomIndex FRoomIndex::Left = { -1, 0 };
FRoomIndex FRoomIndex::Right = { 1, 0 };
FRoomIndex FRoomIndex::Up = { 0, -1 };
FRoomIndex FRoomIndex::Down = { 0, 1 };
FRoomIndex FRoomIndex::ArrDir[4] = { FRoomIndex::Left , FRoomIndex::Right , FRoomIndex::Up , FRoomIndex::Down };

ARoom::ARoom()
{
}

ARoom::~ARoom()
{
}

void ARoom::Link(ARoom* _Room)
{
	ERoomDir OtherRoomDir = GetOtherRoomDir(_Room);

	CreateDoor(OtherRoomDir);
}

ERoomDir ARoom::GetOtherRoomDir(ARoom* _Room)
{
	int OtherX = _Room->RoomIndex.X - RoomIndex.X;
	int OtherY = _Room->RoomIndex.Y - RoomIndex.Y;

	if (-1 == OtherX && 0 == OtherY)
	{
		return ERoomDir::Left;
	}
	else if (1 == OtherX && 0 == OtherY)
	{
		return ERoomDir::Right;
	}
	else if (0 == OtherX && -1 == OtherY)
	{
		return ERoomDir::Up;
	}
	else if (0 == OtherX && 1 == OtherY)
	{
		return ERoomDir::Down;
	}

	MsgBoxAssert("�밢�� ���⿡ �����ϴ� ���� ��ũ�Ϸ��� �߽��ϴ�.");
}

void ARoom::CreateDoor(ERoomDir _Dir)
{
	int DirIndex = static_cast<int>(_Dir);

	DoorRenderer[DirIndex] = CreateImageRenderer(IsaacRenderOrder::Door);

	switch (_Dir)
	{
	case ERoomDir::Left:
		DoorRenderer[DirIndex]->SetImage("Door.png", 0);
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ -370, 0 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 50, 50 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ -370, 0 });
		break;
	case ERoomDir::Right:
		DoorRenderer[DirIndex]->SetImage("Door.png", 1);
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 370, 0 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 50, 50 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 370, 0 });
		break;
	case ERoomDir::Up:
		DoorRenderer[DirIndex]->SetImage("Door.png", 2);
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, -215 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 50, 50 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 0, -215 });
		break;
	case ERoomDir::Down:
		DoorRenderer[DirIndex]->SetImage("Door.png", 3);
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, 215 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 50, 50 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 0, 215 });
		break;
	case ERoomDir::Max:
		break;
	default:
		break;
	}

	// DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
}

void ARoom::BeginPlay()
{
	AActor::BeginPlay();

	RoomRenderer = CreateImageRenderer(IsaacRenderOrder::Room);
	RoomRenderer->SetImage("Room_01.png");
	UWindowImage* Image = RoomRenderer->GetImage();
	FVector ImageScale = Image->GetScale();
	RoomRenderer->SetScale(ImageScale);
}

void ARoom::RoomCameraFocus()
{
	if (false == APlayer::IsFreeCamera)
	{
		FVector Scale = GEngine->MainWindow.GetWindowScale();
		GetWorld()->SetCameraPos(GetActorLocation() - Scale.Half2D());
	}
}

void ARoom::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	APlayer* Player = APlayer::GetMainPlayer();

	for (UCollision* DCollision : DoorCollision)
	{
		if (DCollision == nullptr)
		{
			continue;
		}

		std::vector<UCollision*> Result;
		if (true == DCollision->CollisionCheck(IsaacCollisionOrder::Player, Result))
		{
			Player->SetActorLocation({ 0,0 });
		}
	}

}
