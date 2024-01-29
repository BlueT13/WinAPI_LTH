#pragma once
#include <string>
#include <filesystem> 
// C++ǥ�� ���� ��� ������ ���Խ��ϴ�.
// �Լ��� ȣ���ص� �׳� ��ΰ� Ƣ�� ������ 
// ���� ����� ��� �����ϰ� �Ǿ����ϴ�.

// ���� : ���� ����� ������ �̵� ����� ó���Ѵ�.
class UEnginePath
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	//// delete Function
	//UEnginePath(const UEnginePath& _Other) = delete;
	//UEnginePath(UEnginePath&& _Other) noexcept = delete;
	//UEnginePath& operator=(const UEnginePath& _Other) = delete;
	//UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	// �̰� ���ϰ������.
	bool IsFile();
	bool IsDirectory();

	bool IsExists();

	void MoveParent();
	void Move(std::string_view _Path);

protected:
	// ���ڿ��� �� ����ǥ���Ҽ� �־�� �ߴ�.
	// Path = C:\GM\WIn\ContentsResources\Texture\CherryBomb_0.png
	// Path = C:\GM\WIn\ContentsResources\Texture\
	// ���ڿ��� �⺻
	// std::string StringPath;
	std::filesystem::path Path;

private:
};

