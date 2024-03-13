#pragma once
#include <string>
#include <cmath>
#include <Windows.h>


// 설명 :
class UEngineMath
{
public:
	// constrcuter destructer
	UEngineMath();
	~UEngineMath();

	// delete Function
	UEngineMath(const UEngineMath& _Other) = delete;
	UEngineMath(UEngineMath&& _Other) noexcept = delete;
	UEngineMath& operator=(const UEngineMath& _Other) = delete;
	UEngineMath& operator=(UEngineMath&& _Other) noexcept = delete;

	static const float PI;
	static const float PI2;

	// 디그리 To 라디안
	static const float DToR;
	// 라디안 To 디그리
	static const float RToD;

protected:

private:

};



struct float4
{
public:
	static const float4 Zero;
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		struct
		{
			float R;
			float G;
			float B;
			float A;
		};
	};

	float4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	float4(long _X, long _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	float4(int _X, int _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	float4(float _X, float _Y)
		: X(_X), Y(_Y), Z(0.0f), W(1.0f)
	{

	}

	float4(int _X, int _Y, int _Z, int _W)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(static_cast<float>(_Z)), W(static_cast<float>(_W))
	{

	}

	float4(float _X, float _Y, float _Z, float _W)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}

public:
	static float4 VectorRotationZToDeg(float4 _OriginVector, float _Angle)
	{
		return VectorRotationZToRad(_OriginVector, _Angle * UEngineMath::DToR);
	}

	static float4 VectorRotationZToRad(float4 _OriginVector, float _Angle)
	{
		float4 Result;
		Result.X = (_OriginVector.X * cosf(_Angle)) - (_OriginVector.Y * sinf(_Angle));
		Result.Y = (_OriginVector.X * sinf(_Angle)) + (_OriginVector.Y * cosf(_Angle));
		return Result;
	}

	static float4 DegToDir(float _Angle)
	{
		return RadToDir(_Angle * UEngineMath::DToR);
	}
	static float4 RadToDir(float _Angle)
	{
		return float4(cosf(_Angle), sinf(_Angle));
	}

	static float4 LerpClamp(float4 p1, float4 p2, float d1)
	{
		if (0.0f >= d1)
		{
			d1 = 0.0f;
		}

		if (1.0f <= d1)
		{
			d1 = 1.0f;
		}

		return Lerp(p1, p2, d1);
	}

	static float4 Lerp(float4 p1, float4 p2, float d1) 
	{
		return (p1 * (1.0f - d1)) + (p2 * d1);
	}

	float Size2D()
	{
		return std::sqrtf((X * X) + (Y * Y));
	}

	void RotationZToDeg(float _Angle)
	{
		RotationZToRad(_Angle * UEngineMath::DToR);
	}

	void RotationZToRad(float _Angle)
	{
		*this = VectorRotationZToRad(*this, _Angle);
		return;
	}

	void Normalize2D()
	{
		float Size = Size2D();
		if (0.0f < Size && false == isnan(Size))
		{
			X /= Size;
			Y /= Size;
			Z = 0.0f;
			W = 0.0f;
		}
	}

	float4 Normalize2DReturn()
	{
		float4 Result = *this;
		Result.Normalize2D();
		return Result;
	}

	std::string ToString()
	{
		return "[X : " + std::to_string(X) + " Y : " + std::to_string(Y) + " Z : " + std::to_string(Z) + " W : " + std::to_string(W) + "]";
	}

	float4 Half2D()
	{
		return { hX(), hY() };
	}

	bool IsZeroVector2D() const
	{
		return X == 0.0f && Y == 0.0f;
	}


	int iX() const
	{
		return std::lround(X);
	}

	int iY() const
	{
		return std::lround(Y);
	}


	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}


	int ihY() const
	{
		return std::lround(hY());
	}

	int ihX() const
	{
		return std::lround(hX());
	}

	float4& operator=(const float4& _Other)
	{
		X = _Other.X;
		Y = _Other.Y;
		Z = _Other.Z;
		W = _Other.W;
		return *this;
	}


	float4 operator+(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X += _Other.X;
		Result.Y += _Other.Y;
		Result.Z += _Other.Z;
		return Result;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

	float4 operator*(float _Value) const
	{
		float4 Result = *this;
		Result.X *= _Value;
		Result.Y *= _Value;
		Result.Z *= _Value;
		return Result;
	}

	float4& operator*=(float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X *= _Other.X;
		Result.Y *= _Other.Y;
		Result.Z *= _Other.Z;
		return Result;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4 operator-() 
	{
		float4 Result;
		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		return Result;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X -= _Other.X;
		Result.Y -= _Other.Y;
		Result.Z -= _Other.Z;
		return Result;
	}

	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	POINT ConvertToWinApiPOINT()
	{
		return { iX(),iY() };
	}
};

using FVector = float4;
using FColor = float4;

class Color8Bit
{
public:
	static const Color8Bit Black;
	static const Color8Bit Red;
	static const Color8Bit Green;
	static const Color8Bit Blue;
	static const Color8Bit Yellow;
	static const Color8Bit White;
	static const Color8Bit Magenta;
	static const Color8Bit Orange;

	static const Color8Bit BlackA;
	static const Color8Bit RedA;
	static const Color8Bit GreenA;
	static const Color8Bit BlueA;
	static const Color8Bit YellowA;
	static const Color8Bit WhiteA;
	static const Color8Bit MagentaA;
	static const Color8Bit OrangeA;
	static const Color8Bit CyanA;

	union
	{
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};

		unsigned char Arr1D[4] = { 0,0,0,255 };
		unsigned int Color;
	};

	Color8Bit()
	{

	}

	Color8Bit(
		unsigned char _R,
		unsigned char _G,
		unsigned char _B,
		unsigned char _A
	)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}

	bool operator==(Color8Bit _Color)
	{
		return Color == _Color.Color;
	}

	Color8Bit ZeroAlphaColor() const
	{
		return Color8Bit{ R,G,B,0 };
	}
};
