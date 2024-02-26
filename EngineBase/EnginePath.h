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

	std::string GetFileName() const ;
	std::string GetExtension() const;

	bool IsRoot();

	void MoveParent();
	void Move(std::string_view _Path);

	std::string AppendPath(std::string_view _Path);

	std::string GetFullPath() const
	{
		// ���ڿ��� std������ char* char[100]
		// std::string�� �������ش�.
		// std::filesystem::path�� ������ �ľ��ϰ� ��ο� ���õ� ���� ��ɵ��� �����Ѵ�.
		// ��ζ�°��� �ٺ������� ���ڸ� "C:\\aaaa\bbb\\ccc" => ���ڿ��� ������.
		// �� ��θ� ����ϴ� Ŭ������ �и��� ���ο� std::string�� �������ִ� �Լ��� �־�� �Ѵ�.
		// ������ ���Ѵ�. �׷��� �������� ���ٰ� �����ϰ�
		// ��ã���� ���� �˻��ɷ��� �����ų� ���� ������ ������ ��찡 ���Ƽ� �߸� �����ϰ� �ִ� ��찡 ����.
		// => Ŀ�´����̼� ȥ�� �����˾ƺ��� ����ɰ� �����.
		// �׸��� ȸ�翡 ������ ������ ����� ��κ� ���մϴ�.
		// ��Ȥ���� �����ڰ� ������ ���� 
		return Path.string();
	}

protected:
	// ���ڿ��� �� ����ǥ���Ҽ� �־�� �ߴ�.
	// Path = C:\GM\WIn\ContentsResources\Texture\CherryBomb_0.png
	// Path = C:\GM\WIn\ContentsResources\Texture\
	// ���ڿ��� �⺻
	// std::string StringPath;
	std::filesystem::path Path;

private:
};

