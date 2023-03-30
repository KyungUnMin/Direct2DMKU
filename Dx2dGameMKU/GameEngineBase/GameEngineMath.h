#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>


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
	static const float4 One;
	static const float4 Zero;
	static const float4 Null;



	//각도를 넣으면 0도 부터 그 각도만큼 회전한 벡터가 나온다.
	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}


	//두 벡터 사이 각을 구하는 함수
	static float GetAngleVectorToVectorDeg(const float4& _Left, const float4& _Right)
	{
		return GetAngleVectorToVectorRad(_Left, _Right) * GameEngineMath::RadToDeg;
	}

	static float GetAngleVectorToVectorRad(const float4& _Left, const float4& _Right)
	{
		float4 Left = _Left;
		float4 Right = _Right;

		Left.Normalize();
		Right.Normalize();

		float CosSeta = DotProduct3D(Left, Right);
		
		//블로그에 정리함
		float Angle = acosf(CosSeta);
		return Angle;
	}



	//외적
	static float4 Cross3DReturnNormal(const float4& _Left, const float4& _Right)
	{
		return Cross3DReturn(_Left.NormalizeReturn(), _Right.NormalizeReturn());
	}

	static float4 Cross3DReturn(const float4& _Left, const float4& _Right)
	{
		float4 ReturnValue;
		ReturnValue.x = (_Left.y * _Right.z) - (_Left.z * _Right.y);
		ReturnValue.y = (_Left.z * _Right.x) - (_Left.x * _Right.z);
		ReturnValue.z = (_Left.x * _Right.y) - (_Left.y * _Right.x);
		return ReturnValue;
	}

	//내적
	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		float Value = (_Left.x * _Right.x) + (_Left.y * _Right.y) + (_Left.z * _Right.z);
		return Value;
	}



public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float Arr1D[4];
	};

	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}








	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
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



	float GetAngleDegZ()
	{
		return GetAngleRadZ() * GameEngineMath::RadToDeg;
	}

	//벡터의 각도 구하기(Radian)
	float GetAngleRadZ()
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





	

	float4 RotationXDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotationXRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	float4 RotationYDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotationYRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	float4 RotationZDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotationZRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	void RotationXDeg(float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationYDeg(float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationZDeg(float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationXRad(float _Rad);
	void RotationYRad(float _Rad);
	void RotationZRad(float _Rad);






	





	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	float Size() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;
	}

	float4 NormalizeReturn() const
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


	static float4 LerpClamp(const float4& Start, const float4& End, float Ratio)
	{
		if (0 >= Ratio)
		{
			Ratio = 0.0f;
		}

		if (1.0f <= Ratio)
		{
			Ratio = 1.0f;
		}

		return Lerp(Start, End, Ratio);
	}






	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}


	bool operator == (const float4& _Value) const
	{
		return (_Value.x == x) && (_Value.y == y) && (_Value.z == z);
	}


	float4 operator +(const float4& _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4& _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator *(const float4& _Value) const
	{
		float4 Return;
		Return.x = x * _Value.x;
		Return.y = y * _Value.y;
		Return.z = z * _Value.z;
		return Return;
	}
	
	float4 operator /(const float4& _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}

	float4 operator -() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4& operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator *=(const float _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		return *this;
	}


	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}

	float4 operator*(const class float4x4& _Other);
	float4& operator*=(const class float4x4& _Other);




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

	float4 LeftTop() const
	{
		return float4{ Left(), Top() };
	}
	float4 RightTop() const
	{
		return float4{ Right(), Top() };
	}
	float4 LeftBot() const
	{
		return float4{ Left(), Bot() };
	}
	float4 RightBot() const
	{
		return float4{ Right(), Bot() };
	}
};















class float4x4
{
public:
	static const float4x4 Zero;

	static const int YCount = 4;
	static const int XCount = 4;

public:
	union
	{
		float Arr1D[16];
		float Arr2D[4][4];
		float4 ArrVector[4];

		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;
			float _10;
			float _11;
			float _12;
			float _13;
			float _20;
			float _21;
			float _22;
			float _23;
			float _30;
			float _31;
			float _32;
			float _33;
		};
	};
	
	//항등행렬 만들기
	void Identity()
	{
		memset(Arr1D, 0, sizeof(float) * 16);
		Arr2D[0][0] = 1.0f;
		Arr2D[1][1] = 1.0f;
		Arr2D[2][2] = 1.0f;
		Arr2D[3][3] = 1.0f;
	}

	//뷰 행렬 만들기
	void LookAtLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		Identity();

		float4 EyePos = _EyePos;

		float4 EyeDir = _EyeDir.NormalizeReturn();
		float4 EyeUp = _EyeUp;
		float4 Right = float4::Cross3DReturn(EyeUp, EyeDir);
		Right.Normalize();

		float4 UpVector = float4::Cross3DReturn(_EyeDir, Right);
		Right.Normalize();

		float4 NegEyePos = -_EyePos;


		/*
		카메라가 회전을 안 했다면 단순히,
		D0는 -카메라의 X위치
		D1는 -카메라의 y위치
		D2는 -카메라의 z위치가 될 것이다.

		하지만 카메라를 회전했다면 회전한 각 축의 정사영된 위치로 변환되기 때문에
		아래와 같이 내적하여 위치값을 구한다.
		*/

		//이동 위치
		float D0Value = float4::DotProduct3D(Right, NegEyePos);			//x
		float D1Value = float4::DotProduct3D(UpVector, NegEyePos);	//y
		float D2Value = float4::DotProduct3D(EyeDir, NegEyePos);			//z

		ArrVector[0] = { 1, 0, 0, 0 };
		ArrVector[1] = { 0, 1, 0, 0 };
		ArrVector[2] = { 0, 0, 1, 0 };
		ArrVector[3] = { D0Value, D1Value, D2Value, 0 };
	}


	//크기 행렬 만들기
	void Scale(const float4& _Value)
	{
		Identity();
		Arr2D[0][0] = _Value.x;
		Arr2D[1][1] = _Value.y;
		Arr2D[2][2] = _Value.z;
	}

	//이동 행렬 만들기
	void Pos(const float4& _Value)
	{
		Identity();
		Arr2D[3][0] = _Value.x;
		Arr2D[3][1] = _Value.y;
		Arr2D[3][2] = _Value.z;
	}

	//회전 행렬 만들기
	void RotationDeg(const float4& _Deg)
	{
		float4x4 RotX = float4x4::Zero;
		float4x4 RotY = float4x4::Zero;
		float4x4 RotZ = float4x4::Zero;

		RotX.RotationXDeg(_Deg.x);
		RotY.RotationYDeg(_Deg.y);
		RotZ.RotationZDeg(_Deg.z);

		*this = RotX * RotY * RotZ;
	}

	void RotationXDeg(const float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationXRad(const float _Rad)
	{
		Identity();
		Arr2D[1][1] = cosf(_Rad);
		Arr2D[1][2] = sinf(_Rad);
		Arr2D[2][1] = -sinf(_Rad);
		Arr2D[2][2] = cosf(_Rad);
	}


	void RotationYDeg(const float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}


	void RotationYRad(const float _Rad)
	{
		Identity();
		Arr2D[0][0] = cosf(_Rad);
		Arr2D[0][2] = -sinf(_Rad);
		Arr2D[2][0] = sinf(_Rad);
		Arr2D[2][2] = cosf(_Rad);
	}

	void RotationZDeg(const float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	

	void RotationZRad(const float _Rad)
	{
		Identity();
		Arr2D[0][0] = cosf(_Rad);
		Arr2D[0][1] = sinf(_Rad);
		Arr2D[1][0] = -sinf(_Rad);
		Arr2D[1][1] = cosf(_Rad);
	}








	float4x4 operator*(const float4x4& _Other)
	{
		float4x4 Return = Zero;
		for (size_t y = 0; y < YCount; ++y)
		{
			for (size_t x = 0; x < XCount; ++x)
			{
				for (size_t j = 0; j < 4; ++j)
				{
					Return.Arr2D[y][x] += (Arr2D[y][j] * _Other.Arr2D[j][x]);
				}
			}
		}

		return Return;
	}

	float4x4()
	{
		Identity();
	}


	float4x4(const float4& _X, const float4&  _Y, const float4& _Z, const float4& _W)
	{
		ArrVector[0] = _X;
		ArrVector[1] = _Y;
		ArrVector[2] = _Z;
		ArrVector[3] = _W;
	}
};