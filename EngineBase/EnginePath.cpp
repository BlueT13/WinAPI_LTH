#include "EnginePath.h"
#include "EngineDebug.h"
#include <Windows.h>

UEnginePath::UEnginePath() 
	: Path(std::filesystem::current_path())
{
	// ������ ���
	//char Arr[100];
	//GetCurrentDirectoryA(100, Arr);
	//StringPath = Arr;

	// ���ο����� �������� �Լ��� ����ϰ� �ִ�
	// ���ο��� 
}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

UEnginePath::~UEnginePath() 
{
}

void UEnginePath::Move(std::string_view _Path)
{
	std::filesystem::path NextPath = Path;
	NextPath.append(_Path);

	bool Check = std::filesystem::exists(NextPath);
	if (false == Check)
	{
		MsgBoxAssert(NextPath.string() + "��� ��δ� �������� �ʽ��ϴ�");
	}

	Path = NextPath;
}

bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

bool UEnginePath::IsFile()
{
	return !std::filesystem::is_directory(Path);
}
bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}