#include "Chest.h"
#include "Player.h"
#include "ContentsHelper.h"
#include "DukeOfFlies.h"

AChest::AChest()
{
}

AChest::~AChest()
{
}

void AChest::BeginPlay()
{
	AActor::BeginPlay();

	ChestRenderer = CreateImageRenderer(IsaacRenderOrder::Item);
	ChestRenderer->SetImage("Chest.png");
	ChestRenderer->AutoImageScale();

	ChestCollision = CreateCollision(IsaacCollisionOrder::Item);
	ChestCollision->SetScale({ 30, 30 });
	ChestCollision->SetColType(ECollisionType::Rect);
}

void AChest::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Results;
	if (true == ChestCollision->CollisionCheck(IsaacCollisionOrder::Player, Results))
	{
		GEngine->ChangeLevel("TitleLevel");
		UPlayLevel::IsEnd = true;
		ADukeOfFlies::IsBossDeath = false;
		GEngine->DestroyLevel("PlayLevel");
	}
}

