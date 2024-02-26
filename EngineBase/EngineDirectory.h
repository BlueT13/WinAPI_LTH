#pragma once
#include "EnginePath.h"
#include <list>

class UEngineFile;
// ���� :
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

	void MoveToSearchChild(std::string_view _Path);

	// AAA.Png;
	// AAA.pNg;

	/// <summary>
	/// ������ ���δ� ã���ִ� �Լ�
	/// </summary>
	/// <param name="_Ext">Ȯ���ڵ� �ҹ��� �빮�� ������ ����.</param>
	/// <param name="_Rescursive">���� �������� �� ��������.</param>
	/// <returns></returns>
	std::list<UEngineFile> AllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

	// std::list<UEnginePath> AllPath(bool _Recursive = false);

	// �̷��� �������� �ʴ� �밡�� ���
	std::list<UEngineDirectory> AllDirectory(bool _Recursive = false);

protected:

private:
	void AllDirectoryRecursive(const std::string_view _Path, std::list<UEngineDirectory>& _Result, bool _Recursive = false);
	void AllFileRecursive(const std::string_view _Path, std::list<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};

