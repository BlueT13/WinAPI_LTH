#pragma once

// Ό³Έν :
class UImage
{
public:
	// constrcuter destructer
	UImage();
	~UImage();

	// delete Function
	UImage(const UImage& _Other) = delete;
	UImage(UImage&& _Other) noexcept = delete;
	UImage& operator=(const UImage& _Other) = delete;
	UImage& operator=(UImage&& _Other) noexcept = delete;

protected:

private:

};

