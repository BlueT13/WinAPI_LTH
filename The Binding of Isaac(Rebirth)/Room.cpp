#include "ContentsHelper.h"
#include "PlayLevel.h"
#include "Room.h"
#include "Player.h"
#include "Fly.h"
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
	ERoomType OtherRoomType = GetOtherRoomType(_Room);
	CreateDoor(OtherRoomDir, OtherRoomType);
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



ERoomType ARoom::GetOtherRoomType(ARoom* _Room)
{
	return _Room->RoomType;
}

void ARoom::CreateDoor(ERoomDir _Dir, ERoomType _OtherRoomType)
{
	// 내 방에서 다른 방으로 가는 문 생성
	{
		int DirIndex = static_cast<int>(_Dir);

		OtherRoomDoorRenderer[DirIndex] = CreateImageRenderer(IsaacRenderOrder::Door);

		switch (_Dir)
		{
		case ERoomDir::Left:
			MyRoomImageIndex = 4;
			OtherRoomDoorRenderer[DirIndex]->AutoImageScale();
			OtherRoomDoorRenderer[DirIndex]->SetPosition({ -370, 0 });

			OtherRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			OtherRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			OtherRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			OtherRoomDoorCollision[DirIndex]->SetPosition({ -340, 0 });
			break;
		case ERoomDir::Right:
			MyRoomImageIndex = 5;
			OtherRoomDoorRenderer[DirIndex]->AutoImageScale();
			OtherRoomDoorRenderer[DirIndex]->SetPosition({ 370, 0 });

			OtherRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			OtherRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			OtherRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			OtherRoomDoorCollision[DirIndex]->SetPosition({ 340, 0 });
			break;
		case ERoomDir::Up:
			MyRoomImageIndex = 6;
			OtherRoomDoorRenderer[DirIndex]->AutoImageScale();
			OtherRoomDoorRenderer[DirIndex]->SetPosition({ 0, -215 });

			OtherRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			OtherRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			OtherRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			OtherRoomDoorCollision[DirIndex]->SetPosition({ 0, -205 });
			break;
		case ERoomDir::Down:
			MyRoomImageIndex = 7;
			OtherRoomDoorRenderer[DirIndex]->AutoImageScale();
			OtherRoomDoorRenderer[DirIndex]->SetPosition({ 0, 215 });

			OtherRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			OtherRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			OtherRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			OtherRoomDoorCollision[DirIndex]->SetPosition({ 0, 185 });
			break;
		case ERoomDir::Max:
			break;
		default:
			break;
		}

		if (DirIndex < 4)
		{
			switch (_OtherRoomType)
			{
			case ERoomType::Normal:
				DoorName[DirIndex] = "NormalRoomDoor.png";
				OtherRoomDoorRenderer[DirIndex]->SetImage(DoorName[DirIndex], MyRoomImageIndex);
				break;

			case ERoomType::GoldRoom:
				DoorName[DirIndex] = "GoldRoomDoor.png";
				OtherRoomDoorRenderer[DirIndex]->SetImage(DoorName[DirIndex], MyRoomImageIndex);
				break;
			case ERoomType::BossRoom:
				DoorName[DirIndex] = "BossRoomDoor.png";
				OtherRoomDoorRenderer[DirIndex]->SetImage(DoorName[DirIndex], MyRoomImageIndex);
				break;
			default:
				break;
			}
		}
		else
		{
			MsgBoxAssert("잘못된 방향으로 문을 생성하려 했습니다");
		}
	}


	// 다른 방에서 내 방으로 가는 문 생성
	{
		// 다른 방의 방향
		int DirIndex = static_cast<int>(_Dir);

		MyRoomDoorRenderer[DirIndex] = CreateImageRenderer(IsaacRenderOrder::Door);

		switch (_Dir)
		{
			//다른 방의 방향이 왼쪽이면 내 방은 오른쪽 문을 만들어야 한다.
		case ERoomDir::Left:
			OtherRoomImageIndex = 5;
			MyRoomDoorRenderer[DirIndex]->AutoImageScale();
			MyRoomDoorRenderer[DirIndex]->SetPosition({ -590, 0 });

			MyRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			MyRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			MyRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			MyRoomDoorCollision[DirIndex]->SetPosition({ -620, 0 });
			break;
		case ERoomDir::Right:
			OtherRoomImageIndex = 4;
			MyRoomDoorRenderer[DirIndex]->AutoImageScale();
			MyRoomDoorRenderer[DirIndex]->SetPosition({ 590, 0 });

			MyRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			MyRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			MyRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			MyRoomDoorCollision[DirIndex]->SetPosition({ 620, 0 });
			break;
		case ERoomDir::Up:
			OtherRoomImageIndex = 7;
			MyRoomDoorRenderer[DirIndex]->AutoImageScale();
			MyRoomDoorRenderer[DirIndex]->SetPosition({ 0, -330 });

			MyRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			MyRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			MyRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			MyRoomDoorCollision[DirIndex]->SetPosition({ 0, -335 });
			break;
		case ERoomDir::Down:
			OtherRoomImageIndex = 6;
			MyRoomDoorRenderer[DirIndex]->AutoImageScale();
			MyRoomDoorRenderer[DirIndex]->SetPosition({ 0, 330 });

			MyRoomDoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
			MyRoomDoorCollision[DirIndex]->SetScale({ 30, 30 });
			MyRoomDoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
			MyRoomDoorCollision[DirIndex]->SetPosition({ 0, 345 });
			break;
		case ERoomDir::Max:
			break;
		default:
			break;
		}

		if (DirIndex < 4)
		{
			switch (_OtherRoomType)
			{
			case ERoomType::Normal:
				DoorName[DirIndex] = "NormalRoomDoor.png";
				MyRoomDoorRenderer[DirIndex]->SetImage(DoorName[DirIndex], OtherRoomImageIndex);
				break;
			case ERoomType::GoldRoom:
				DoorName[DirIndex] = "GoldRoomDoor.png";
				MyRoomDoorRenderer[DirIndex]->SetImage(DoorName[DirIndex], OtherRoomImageIndex);
				break;
			case ERoomType::BossRoom:
				DoorName[DirIndex] = "BossRoomDoor.png";
				MyRoomDoorRenderer[DirIndex]->SetImage(DoorName[DirIndex], OtherRoomImageIndex);
				break;
			default:
				break;
			}
		}
		else
		{
			MsgBoxAssert("잘못된 방향으로 문을 생성하려 했습니다");
		}
	}
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

	// 몬스터 배열 확인
	for (int i = 0; i < Monsters.size(); i++)
	{
		AMonster* Monster = Monsters[i];

		if (Monster->IsDestroy())
		{
			Monsters.erase(Monsters.begin() + i);
		}
	}

	if (0 == Monsters.size())
	{
		for (int i = 0; i < 4; i++)
		{
			if (OtherRoomDoorRenderer[i] == nullptr)
			{
				continue;
			}

			OtherRoomDoorRenderer[i]->SetImage(DoorName[i], MyRoomImageIndex - 4);
			OtherRoomDoorCollision[i]->SetActive(true);
			MyRoomDoorRenderer[i]->SetImage(DoorName[i], OtherRoomImageIndex - 4);
			MyRoomDoorCollision[i]->SetActive(true);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (OtherRoomDoorRenderer[i] == nullptr)
			{
				continue;
			}
			OtherRoomDoorCollision[i]->SetActive(false);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (OtherRoomDoorCollision[i] == nullptr)
		{
			continue;
		}

		ERoomDir Dir = static_cast<ERoomDir>(i);

		std::vector<UCollision*> Result;
		if (true == OtherRoomDoorCollision[i]->CollisionCheck(IsaacCollisionOrder::Player, Result))
		{
			Player->BodyStateChange(EPlayerBodyState::Wait);

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

void ARoom::CreateMonsters(EMonsterType _Type, FVector _Pos)
{
	AMonster* Monster = nullptr;
	switch (_Type)
	{
	case EMonsterType::Fly:
		Monster = GetWorld()->SpawnActor<AFly>(IsaacUpdateOrder::Monster);
		break;
	default:
		break;
	}

	FVector CurRoomPos = GetActorLocation();
	FVector SetMonsterLocation = _Pos;
	Monster->SetActorLocation(CurRoomPos + SetMonsterLocation);
	Monster->SetMonsterRoom(this);
	Monsters.push_back(Monster);
}

void ARoom::ActiveMonsters(bool _Active)
{
	for (int i = 0; i < Monsters.size(); i++)
	{
		AMonster* Monster = Monsters[i];

		Monster->SetActive(_Active);
	}
}
