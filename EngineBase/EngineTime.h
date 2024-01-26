#pragma once
// #include <chrono> �ֽ� �ð� ��� ��� std.
#include <Windows.h>

// ���� :
class EngineTime
{
public:
	// constrcuter destructer
	EngineTime();
	~EngineTime();

	// delete Function
	EngineTime(const EngineTime& _Other) = delete;
	EngineTime(EngineTime&& _Other) noexcept = delete;
	EngineTime& operator=(const EngineTime& _Other) = delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept = delete;

	// �ð������� �����ϰڴ�.
	void TimeCheckStart();

	// ���ݱ��� �� ������?
	float TimeCheck();

	double GetDeltaTime()
	{
		return DeltaTime;
	}

protected:

private:
	__int64 Count64;
	LARGE_INTEGER Count;
	LARGE_INTEGER PrevTime;
	LARGE_INTEGER CurTime;
	double dCount;
	double DeltaTime;

	// �⺻������ CPU�ϵ� ���� ������ ���ο� Count�� �ϴ� �κ��� �����մϴ�.
	// ���� �������ڸ� ��ǻ�ʹ� �Ѵ� ���� CPU�� �����ϸ鼭 0 1 2 3 4 5 6
	// �ʰ� �ƴմϴ� �׷��� �̳༮�� ���� �ʴ� ������ ���� ���� ������ �����ϰ� ���ϴ�.
	// ex) ��ǻ�� �״� 0 
	// ex) 1�� 10000000
	// ex) 2�� 20000000
	// ex) 3�� 29999990
	// ex) 4�� 40000000
	// ex) 5�� 50000001

	// ������� �̷� �Լ��� �����մϴ�.
	// ���ݱ��� �󸶳� ����?
	// ex) �󸶳����� 150
	
	// �� �ʴ� �󸶸� ���� �־�?
	// ex) 100

	// ����
	// �� �ʴ� �󸶸� ���� �־�?
	// int Count = 100;
	// 
	// �󸶳� ����?
	// int CurTime = 100;
	// int PrevTime = CurTime;
	// ~~~~~~~~~~~~~~~~~~~~ ���������� ������.
	// �󸶳� ����?
	// CurTime = 120;
	//                    120         100     / 100
	// float DeltaTime = (CurTime - PrevTime) / Count;
	// PrevTime = CurTime;
	// ~~~~~~~~~~~~~~~~~~~~ ���������� ������.
	// �󸶳� ����?
	// CurTime = 320;
	//                    320         120     / 100
	// float DeltaTime = (CurTime - PrevTime) / Count;
	// PrevTime = CurTime;
};

