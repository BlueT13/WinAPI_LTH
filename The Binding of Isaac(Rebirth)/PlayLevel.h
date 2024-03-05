#pragma once
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>
#include "Room.h"

// 설명 :
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

	void CreateRoom(int _X, int _Y, std::string_view _Img);
	void SetCurRoom(int _X, int _Y);
	void SetPrevRoom(int _X, int _Y);
	ARoom* GetCurRoom();
	ARoom* GetPrevRoom();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 방을 관리하는 건 레벨마다 해야하니까
	std::map<__int64, ARoom*> Rooms;
	ARoom* CurRoom = nullptr;
	ARoom* PrevRoom = nullptr;
	bool IsFreeCamera = false;
};

