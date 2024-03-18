#include "Trophy.h"
#include "Player.h"
#include "ContentsHelper.h"

ATrophy::ATrophy()
{
}

ATrophy::~ATrophy()
{
}

void ATrophy::BeginPlay()
{
	AActor::BeginPlay();

	TrophyRenderer = CreateImageRenderer(IsaacRenderOrder::Item);
	TrophyRenderer->SetImage("trophy.png");
	TrophyRenderer->AutoImageScale();

	TrophyCollision = CreateCollision(IsaacCollisionOrder::Item);
	TrophyCollision->SetScale({ 30, 30 });
	TrophyCollision->SetColType(ECollisionType::Rect);
}

void ATrophy::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Results;
	if (true == TrophyCollision->CollisionCheck(IsaacCollisionOrder::Player, Results))
	{
		GEngine->ChangeLevel("TitleLevel");
		UPlayLevel::IsEnd = true;
		GEngine->DestroyLevel("PlayLevel");
	}
}

