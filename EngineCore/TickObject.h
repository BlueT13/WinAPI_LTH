#pragma once

// ���� :
class UTickObject
{
public:
	// constrcuter destructer
	UTickObject();
	virtual ~UTickObject();

	// delete Function
	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	void On()
	{
		IsUpdateValue = true;
	}

	void Off()
	{
		IsUpdateValue = false;
	}

	bool IsOn()
	{
		// ���� �����ְ�         ������ �ʾҴٸ�
		return IsUpdateValue && IsDeathValue == false;
	}


	void Death()
	{
		IsDeathValue = true;
	}

	bool IsDeath()
	{
		return IsDeathValue;
	}

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

protected:

private:
	bool IsUpdateValue = true;
	bool IsDeathValue = false;

};

