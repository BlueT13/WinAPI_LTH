#include "Room.h"
#include "ContentsHelper.h"
#include "Player.h"
#include "PlayLevel.h"
#include <EngineBase/EngineMath.h>

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

	MsgBoxAssert("대각선 방향에 존재하는 방을 링크하려고 했습니다.");
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
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ -340, 0 });
		break;
	case ERoomDir::Right:
		DoorRenderer[DirIndex]->SetImage("Door.png", 1);
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 370, 0 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 340, 0 });
		break;
	case ERoomDir::Up:
		DoorRenderer[DirIndex]->SetImage("Door.png", 2);
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, -215 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 0, -190 });
		break;
	case ERoomDir::Down:
		DoorRenderer[DirIndex]->SetImage("Door.png", 3);
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, 215 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 0, 190 });
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
	RoomRenderer->AutoImageScale();
}

void ARoom::RoomCameraFocus()
{
	if (false == APlayer::IsFreeCamera)
	{
		GetWorld()->SetCameraPos(GetActorLocation() - WindowScale.Half2D());
	}
}

void ARoom::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	APlayer* Player = APlayer::GetMainPlayer();

	for (int i = 0; i < 4; i++)
	{
		if (DoorCollision[i] == nullptr)
		{
			continue;
		}

		ERoomDir Dir = static_cast<ERoomDir>(i);

		std::vector<UCollision*> Result;
		if (true == DoorCollision[i]->CollisionCheck(IsaacCollisionOrder::Player, Result))
		{
			FVector CurPos = GetTransform().GetPosition();
			PlayLevel->SetPrevRoom(RoomIndex.X, RoomIndex.Y);

			switch (Dir)
			{
			case ERoomDir::Left:
				Player->SetActorLocation({ CurPos.X - (WindowScale.X - 300), CurPos.Y });
				//GetWorld()->AddCameraPos({ CurPos.X - WindowScale.X, CurPos.Y });
				PlayLevel->SetCurRoom(RoomIndex.X - 1, RoomIndex.Y);
				break;
			case ERoomDir::Right:
				Player->SetActorLocation({ CurPos.X + (WindowScale.X - 300), CurPos.Y });
				//GetWorld()->AddCameraPos({ CurPos.X + WindowScale.X, CurPos.Y });
				PlayLevel->SetCurRoom(RoomIndex.X + 1, RoomIndex.Y);
				break;
			case ERoomDir::Up:
				Player->SetActorLocation({ CurPos.X, CurPos.Y - (WindowScale.Y - 150) });
				//GetWorld()->AddCameraPos({ CurPos.X, CurPos.Y - WindowScale.Y });
				PlayLevel->SetCurRoom(RoomIndex.X, RoomIndex.Y - 1);
				break;
			case ERoomDir::Down:
				Player->SetActorLocation({ CurPos.X, CurPos.Y + (WindowScale.Y - 150) });
				//GetWorld()->AddCameraPos({ CurPos.X, CurPos.Y + WindowScale.Y });
				PlayLevel->SetCurRoom(RoomIndex.X, RoomIndex.Y + 1);
				break;
			case ERoomDir::Max:
				break;
			default:
				break;
			}
		}
	}

}
