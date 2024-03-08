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
	int DirIndex = static_cast<int>(_Dir);

	DoorRenderer[DirIndex] = CreateImageRenderer(IsaacRenderOrder::Door);

	int RoomImageIndex = 0;

	switch (_Dir)
	{
	case ERoomDir::Left:
		RoomImageIndex = 4;
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ -370, 0 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ -340, 0 });
		break;
	case ERoomDir::Right:
		RoomImageIndex = 5;
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 370, 0 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 340, 0 });
		break;
	case ERoomDir::Up:
		RoomImageIndex = 6;
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, -215 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 0, -205 });
		break;
	case ERoomDir::Down:
		RoomImageIndex = 7;
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, 215 });

		DoorCollision[DirIndex] = CreateCollision(IsaacCollisionOrder::Door);
		DoorCollision[DirIndex]->SetScale({ 30, 30 });
		DoorCollision[DirIndex]->SetColType(ECollisionType::Rect);
		DoorCollision[DirIndex]->SetPosition({ 0, 185 });
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
			DoorRenderer[DirIndex]->SetImage("NormalRoomDoor.png", RoomImageIndex);
			break;

		case ERoomType::GoldRoom:
			DoorName[DirIndex] = "GoldRoomDoor.png";
			DoorRenderer[DirIndex]->SetImage("GoldRoomDoor.png", RoomImageIndex);

			break;
		case ERoomType::BossRoom:
			DoorName[DirIndex] = "BossRoomDoor.png";
			DoorRenderer[DirIndex]->SetImage("BossRoomDoor.png", RoomImageIndex);

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
			if (DoorRenderer[i] == nullptr)
			{
				continue;
			}

			DoorRenderer[i]->SetImage(DoorName[i], i);
			DoorCollision[i]->SetActive(true);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (DoorRenderer[i] == nullptr)
			{
				continue;
			}
			DoorCollision[i]->SetActive(false);
		}
	}

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
