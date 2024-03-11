#pragma once
#include <string>
#include <filesystem> 

// 설명 : 파일 경로의 편집과 이동을 처리
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
		return Path.string();
	}

protected:
	std::filesystem::path Path;

private:
};

