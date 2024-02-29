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
	//       0               0
	int OtherX = _Room->RoomIndex.X - RoomIndex.X;
	//       0               1
	int OtherY = _Room->RoomIndex.Y - RoomIndex.Y;

	// 왼쪽
	if (-1 == OtherX && 0 == OtherY)
	{

		return ERoomDir::Left;
	}
	// 오른쪽
	else if (1 == OtherX && 0 == OtherY)
	{
		return ERoomDir::Right;
	}
	// 위
	else if (0 == OtherX && -1 == OtherY)
	{
		return ERoomDir::Up;
	}
	// 아래
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
	DoorRenderer[DirIndex]->SetImage("Door.png",0);

	switch (_Dir)
	{
	case ERoomDir::Left:
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ -400, 0 });
		break;
	case ERoomDir::Right:
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 400, 0 });
		break;
	case ERoomDir::Up:
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, -300 });
		break;
	case ERoomDir::Down:
		DoorRenderer[DirIndex]->AutoImageScale();
		DoorRenderer[DirIndex]->SetPosition({ 0, 300 });
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
}
