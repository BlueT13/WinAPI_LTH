#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/EngineCore.h>
#include "ContentsHelper.h"

enum class ERoomDir
{
	Left,
	Right,
	Up,
	Down,
	Max,
};

enum class ERoomType
{
	None,
	Normal,
	GoldRoom,
	BossRoom,
};

class AMonster;
class FRoomIndex
{
public:
	static FRoomIndex Left;
	static FRoomIndex Right;
	static FRoomIndex Up;
	static FRoomIndex Down;
	static FRoomIndex ArrDir[static_cast<int>(ERoomDir::Max)];

	union
	{
		struct
		{
			int X;
			int Y;
		};

		__int64 Key = 0;
	};
};

class UPlayLevel;
class ARoom : public AActor
{
public:
	// constrcuter destructer
	ARoom();
	~ARoom();

	// delete Function
	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

	void Link(ARoom* _Room);
	ERoomDir GetOtherRoomDir(ARoom* _Room);
	ERoomType GetOtherRoomType(ARoom* _Room);

	void SetRoomIndex(FRoomIndex _RoomIndex)
	{
		RoomIndex = _RoomIndex;
	}

	void SetRoomImg(std::string_view _Img)
	{
		RoomRenderer->SetImage(_Img);
	}

	void RoomCameraFocus();

	void SetPlayLevel(UPlayLevel* _Level)
	{
		PlayLevel = _Level;
	}

	void CreateMonsters(EMonsterType _Type, FVector _Pos);

	void ActiveMonsters(bool _Active);

	std::vector<AMonster*> GetAllMonsters()
	{
		return Monsters;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CreateDoor(ERoomDir _Dir, ERoomType _RoomType);

private:
	UPlayLevel* PlayLevel = nullptr;

	UImageRenderer* RoomRenderer = nullptr;

	FRoomIndex RoomIndex = { 0, 0 };

	// 한방은 최대 4의 방과 연결될 수 있기 때문에
	ARoom* LinkRoom[static_cast<int>(ERoomDir::Max)];

	UImageRenderer* DoorRenderer[4] = { nullptr, };
	UCollision* DoorCollision[4] = { nullptr, };

	FVector WindowScale = GEngine->MainWindow.GetWindowScale();

	std::vector<AMonster*> Monsters;

	float ChangeRoomTime = 0.0f;

	ERoomType RoomType = ERoomType::None;
};

