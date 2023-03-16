#pragma once
#include <math.h>
#include <cmath>
#include <string>
#include <vector>
#include <Windows.h>

class GameEngineMath final
{
public:
	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);

	static const float PIE;
	static const float PIE2;
	static const float DegToRad;
	static const float RadToDeg;

private:
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;
	static const float4 Zero;
	static const float4 Null;

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4{ cosf(_Rad), sinf(_Rad), 0.f, 1.f };
	}

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	inline int ix() const
	{
		return static_cast<int>(x);
	}

	inline int iy() const
	{
		return static_cast<int>(y);
	}

	inline int iz() const
	{
		return static_cast<int>(z);
	}

	inline int iw() const
	{
		return static_cast<int>(w);
	}

	inline int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	inline int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	inline int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	inline int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}


	void RotationZDeg(float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationZRad(float _Rad)
	{
		float4 Copy = *this;
		x = Copy.x * cosf(_Rad) - Copy.y * sinf(_Rad);
		y = Copy.x * sinf(_Rad) + Copy.y * cosf(_Rad);
	}

	float4 RotationZDegReturn(float _Deg)
	{
		float4 Copy = *this;
		Copy.RotationZDeg(_Deg);
		return Copy;
	}


	//벡터의 각도 구하기(Degree)
	float GetAngleDeg()
	{
		return GetAngleRad() * GameEngineMath::RadToDeg;
	}

	//벡터의 각도 구하기(Radian)
	float GetAngleRad()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();

		//cos(각도)는 x값이 나온다
		//그럼 역함수인 acos에 x값을 넣으면 각도가 나온다
		float Result = acosf(AngleCheck.x);

		//하지만 역삼각함수는 전단사함수(일대일 대응)가 아니다
			//ex) sin(PIE * 1/2) == sin(PIE * 3/2) == 1
			//ex) asin(1) => (PIE * 1/2 ) or (PIE * 3/2) ???
		//그래서 역삼각함수의 치역은 0 ~ PIE로 제한된다

		//(구한 각도가 PIE를 넘겼어야 하는 각도지만 
			//수평선과 대칭되는 각도가 나왔었다면)
		if (0.f < AngleCheck.y)
		{
			//각도를 수평선 기준으로 대칭이동 시킨다
			Result = GameEngineMath::PIE2 - Result;
		}

		return Result;
	}

	POINT ToWindowPOINT()
	{
		return POINT{ ix(), iy() };
	}

	float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	float Size()
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;
	}

	float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}


	static float4 Lerp(const float4& _Start, const float4& _End, float _Ratio)
	{
		//벡터를 삼각형으로 생각해보면 이 식이 왜 성립하는지 알 수 있다,(삼각형의 닮음비)
		return _Start * (1.0f - _Ratio) + (_End * _Ratio);
	}

	static float4 LerpClamp(const float4& _Start, const float4& _End, float _Ratio)
	{
		if (_Ratio <= 0.f)
		{
			_Ratio = 0.f;
		}

		if (1.f <= _Ratio)
		{
			_Ratio = 1.f;
		}

		return Lerp(_Start, _End, _Ratio);
	}


	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	float4 operator +(const float4 _Value) const
	{
		float4 Return = float4::Zero;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4 _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator -() const
	{
		return {-x, -y, -z, 1.0f};
	}


	float4& operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}


	float4 operator*(const float4& _Other) const
	{
		float4 Return;
		Return.x = x * _Other.x;
		Return.y = y * _Other.y;
		Return.z = z * _Other.z;
		return Return;
	}

	bool operator == (const float4& _Other) const
	{
		return (x == _Other.x) && (y == _Other.y) && (z == _Other.z);
	}
	
	bool operator<(const float4& _Other) const
	{
		return (x < _Other.x) && (y < _Other.y) /*&& (z < _Other.z)*/;
	}

	//현재 값을 string으로 변환하여 return
	std::string ToString()
	{
		char ArrReturn[256];
		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);
		return std::string(ArrReturn);
	}
};

class CollisionData
{
public:
	float4 Position;
	float4 Scale;

	float Left() const
	{
		return Position.x - Scale.hx();
	}
	float Right() const
	{
		return Position.x + Scale.hx();
	}
	float Top() const
	{
		return Position.y - Scale.hy();
	}
	float Bot() const
	{
		return Position.y + Scale.hy();
	}

	float4 LeftTop()
	{
		return float4{ Left(), Top() };
	}

	float4 RightTop()
	{
		return float4{ Right(), Top() };
	}

	float4 LeftBot()
	{
		return float4{ Left(), Bot() };
	}

	float4 RightBot()
	{
		return float4{ Right(), Bot() };
	}
};
