#pragma once
#include <EngineCore/Level.h>
#include "Room.h"

// ���� :
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// ���� �����ϴ� �� �������� �ؾ��ϴϱ�
	std::map<__int64, ARoom*> Rooms;
	ARoom* CurRoom = nullptr;

};

