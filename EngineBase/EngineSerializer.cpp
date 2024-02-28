#include "EngineSerializer.h"

UEngineSerializer::UEngineSerializer() 
{
}

UEngineSerializer::~UEngineSerializer() 
{
}

void UEngineSerializer::BufferResize(int _Size)
{
	Data.resize(_Size);
}

void UEngineSerializer::Write(void* _Data, unsigned int _Size)
{
	if (WriteOffset + _Size >= Data.size())
	{
		Data.resize(Data.capacity() * 2 + _Size);
	}

	// &Data[WriteOffset] �ּӰ���
	// _Size ũ�⸸ŭ
	// _Data �ּҰ��� �ִ� �����͸� 
	// _Size ũ�⸸ŭ �����ض�.
	// &Data[WriteOffset]<= _Data
	memcpy_s(&Data[WriteOffset], _Size, _Data, _Size);
	WriteOffset += _Size;
}


void UEngineSerializer::Read(void* _Data, unsigned int _Size)
{
	memcpy_s(_Data, _Size, &Data[ReadOffset], _Size);
	ReadOffset += _Size;
}