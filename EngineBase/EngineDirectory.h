#pragma once
#include "EnginePath.h"
#include <list>

class UEngineFile;
// Ό³Έν :
class UEngineDirectory : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineDirectory();
	UEngineDirectory(const UEnginePath& _Path);
	~UEngineDirectory();

	// delete Function
	//UEngineDirectory(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	//UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	std::list<UEngineFile> AllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
	std::list<UEngineDirectory> AllDirectory(bool _Recursive = false);
	void MoveToSearchChild(std::string_view _Path);

	UEngineFile NewFile(std::string_view FileName);

protected:

private:
	void AllDirectoryRecursive(const std::string_view _Path, std::list<UEngineDirectory>& _Result, bool _Recursive = false);
	void AllFileRecursive(const std::string_view _Path, std::list<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};

