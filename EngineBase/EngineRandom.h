#pragma once
#include <random>
#include <time.h>

// Ό³Έν :
class UEngineRandom
{
public:
	static UEngineRandom MainRandom;

	// constrcuter destructer
	UEngineRandom();
	~UEngineRandom();

	// delete Function
	UEngineRandom(const UEngineRandom& _Other) = delete;
	UEngineRandom(UEngineRandom&& _Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& _Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> RandomCreate(_Min, _Max);
		return RandomCreate(MtGen);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution<float> RandomCreate(_Min, _Max);
		return RandomCreate(MtGen);
	}

protected:

private:
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));
};

