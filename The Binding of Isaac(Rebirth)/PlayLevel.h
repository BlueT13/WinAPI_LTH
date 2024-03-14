#pragma once
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>
#include "Room.h"
#include "Monster.h"

// 설명 :
class AMonster;
class UPlayLevel : public ULevel
{
public:
	// constrcuter destructer
	UPlayLevel();
	~UPlayLevel();

	// delete Function
	UPlayLevel(const UPlayLevel& _Other) = delete;
	UPlayLevel(UPlayLevel&& _Other) noexcept = delete;
	UPlayLevel& operator=(const UPlayLevel& _Other) = delete;
	UPlayLevel& operator=(UPlayLevel&& _Other) noexcept = delete;

	void SetCurRoom(int _X, int _Y);
	void SetPrevRoom(int _X, int _Y);
	ARoom* GetCurRoom();
	ARoom* GetPrevRoom();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void End() override;

private:
	// 방을 관리하는 건 레벨마다 해야하니까
	ARoom* CreateRoom(int _X, int _Y, std::string_view _Img, ERoomType _RoomType);
	std::map<__int64, ARoom*> Rooms;
	ARoom* CurRoom = nullptr;
	ARoom* PrevRoom = nullptr;
	bool IsFreeCamera = false;
	float RoomMoveCameraTime = 0.0f;
	bool IsEnd = false;
	bool IsEscape = false;
};

