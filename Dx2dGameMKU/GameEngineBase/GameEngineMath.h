#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>


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


	static const float4 Red;
	static const float4 Green;
	static const float4 Blue;
	static const float4 White;
	static const float4 Black;

	//실수 오차를 방지하기 위해 _Tolerance이하는 0으로 만드는 함수
	static float4 GetSafeScaleReciprocal(const float4& _InScale, float _Tolerance)
	{
		float4 SafeReciprocalScale;

		if (std::fabsf(_InScale.x) <= _Tolerance)
		{
			SafeReciprocalScale.x = 0.f;
		}
		else
		{
			SafeReciprocalScale.x = 1 / _InScale.x;
		}

		if (std::fabsf(_InScale.y) <= _Tolerance)
		{
			SafeReciprocalScale.y = 0.f;
		}
		else
		{
			SafeReciprocalScale.y = 1 / _InScale.y;
		}

		if (std::fabsf(_InScale.z) <= _Tolerance)
		{
			SafeReciprocalScale.z = 0.f;
		}
		else
		{
			SafeReciprocalScale.z = 1 / _InScale.z;
		}

		return SafeReciprocalScale;
	}

	//각도를 넣으면 0도 부터 그 각도만큼 회전한 벡터가 나온다.
	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}


	//GetAngleVectorToVectorDeg함수는 치역이 0.f ~ 180.f 였으나 치역을 360.f로 확장해서 보안한 함수
	static float GetAngleVectorToVectorDeg360(const float4& _Pivot, const float4& _Other)
	{
		return GetAngleVectorToVectorRad360(_Pivot, _Other) * GameEngineMath::RadToDeg;
	}

	//GetAngleVectorToVectorDeg함수는 치역이 0.f ~ 180.f 였으나 치역을 360.f로 확장해서 보안한 함수
	static float GetAngleVectorToVectorRad360(const float4& _Pivot, const float4& _Other)
	{
		float4 Pivot = _Pivot;
		float4 Other = _Other;

		Pivot.Normalize();
		Other.Normalize();

		float CosSeta = DotProduct3D(Pivot, Other);

		float Angle = 0.f;
		(Pivot.x * Other.y) - (Pivot.y * Other.x) > 0.0f ? Angle = acosf(CosSeta) : Angle = -acosf(CosSeta);

		return Angle;
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
		//float4 ReturnValue;
		/*ReturnValue.x = (_Left.y * _Right.z) - (_Left.z * _Right.y);
		ReturnValue.y = (_Left.z * _Right.x) - (_Left.x * _Right.z);
		ReturnValue.z = (_Left.x * _Right.y) - (_Left.y * _Right.x);*/

		float4 ReturnValue = DirectX::XMVector3Cross(_Left, _Right);
		return ReturnValue;
	}

	//내적
	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		//float Value = (_Left.x * _Right.x) + (_Left.y * _Right.y) + (_Left.z * _Right.z);

		//SIMD연산 방식 때문에 __m128로 받는다
		float4 ReturnValue = DirectX::XMVector3Dot(_Left, _Right);
		return ReturnValue.x;
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

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		float Arr1D[4];

		DirectX::XMFLOAT3 DirectFloat3;
		DirectX::XMFLOAT4 DirectFloat4;
		DirectX::XMVECTOR DirectVector;

		struct 
		{
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
		};
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

	float4(DirectX::FXMVECTOR _Vector)
		:DirectVector(_Vector)
	{

	}


	void RotationXRad(float _Rad);
	void RotationYRad(float _Rad);
	void RotationZRad(float _Rad);

	//회전벡터를 쿼터니언으로 변환
	float4 EulerDegToQuaternion();

	//쿼터니언을 회전 행렬로 변환
	class float4x4 QuaternionToRotationMatrix();

	//쿼터니언을 회전벡터로 변환(Degree)
	float4 QuaternionToEulerDeg();
	//쿼터니언을 회전벡터로 변환(Radian)
	float4 QuaternionToEulerRad();


	float XYDistance(float4 _Value);
	float XYZDistance(float4 _Value);


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

	int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}

	int uiz() const
	{
		return static_cast<unsigned int>(z);
	}

	int uiw() const
	{
		return static_cast<unsigned int>(w);
	}

	int uhix() const
	{
		return static_cast<unsigned int>(x * 0.5f);
	}

	int uhiy() const
	{
		return static_cast<unsigned int>(y * 0.5f);
	}

	int uhiz() const
	{
		return static_cast<unsigned int>(z * 0.5f);
	}

	int uhiw() const
	{
		return static_cast<unsigned int>(w * 0.5f);
	}




	float GetAngleDegZ()
	{
		return GetAngleRadZ() * GameEngineMath::RadToDeg;
	}

	//xyz중 가장 큰 값을 반환해준다
	float MaxFloat() const
	{
		return (x < y) ? (y < z ? z : y) : (x < z ? z : x);
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



	UINT ColorToUint() const
	{
		UINT Return;

		char* Ptr = reinterpret_cast<char*>(&Return);

		// 0~1
		Ptr[0] = static_cast<int>(r * 255.0f);
		Ptr[1] = static_cast<int>(g * 255.0f);
		Ptr[2] = static_cast<int>(b * 255.0f);
		Ptr[3] = static_cast<int>(a * 255.0f);

		return Return;
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
		/*float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;*/

		DirectVector = DirectX::XMVector3Normalize(*this);
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
		//return _Start * (1.0f - _Ratio) + (_End * _Ratio);

		return DirectX::XMVectorLerp(_Start, _End, _Ratio);
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

	operator DirectX::FXMVECTOR() const
	{
		return DirectVector;
	}




	float4 operator *(const float _Value) const
	{
		return DirectX::XMVectorMultiply(*this, float4{ _Value, _Value ,_Value ,_Value });
	}


	bool operator == (const float4& _Value) const
	{
		return (_Value.x == x) && (_Value.y == y) && (_Value.z == z);
	}


	float4 operator +(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, _Value);
		Return.w = PrevW;

		return Return;
	}

	float4 operator -(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorAdd(*this, -_Value);
		Return.w = PrevW;
		
		return Return;
	}

	float4 operator *(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorMultiply(*this, _Value);
		Return.w = PrevW;

		return Return;
	}
	
	float4 operator /(const float4& _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, _Value);
		Return.w = PrevW;

		return Return;
	}

	float4 operator /(const float _Value) const
	{
		float PrevW = w;
		float4 Return = DirectX::XMVectorDivide(*this, { _Value ,_Value ,_Value ,_Value });
		Return.w = PrevW;

		return Return;
	}

	float4 operator -() const
	{
		return { -x, -y, -z, w };
	}

	float4& operator +=(const float4& _Other)
	{
		*this = *this + _Other;
		return *this;
	}

	float4& operator *=(const float _Value)
	{
		*this = *this * _Value;
		return *this;
	}

	float4& operator /=(const float _Value)
	{
		*this = *this / _Value;
		return *this;
	}


	float4& operator *=(const float4& _Other)
	{
		*this = *this * _Other;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		*this = *this - _Other;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		*this = *this / _Other;
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







class CollisionDataAPI
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













typedef float4 Quaternion;

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
		DirectX::XMMATRIX DirectMatrix;

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
		DirectMatrix = DirectX::XMMatrixIdentity();
	}


	//원근 투영행렬 만들기(수직시야각, 화면 종횡비(가로/세로), 근평면, 원평면)
	void PersperctiveFovLH(float _FovAngle, float _AspectRatio, float _NearZ = 0.1f, float _FarZ = 10000.f)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle * GameEngineMath::DegToRad, _AspectRatio, _NearZ, _FarZ);

		{
			////디그리 -> 라디안
			//float FOV = _FovAngle * GameEngineMath::DegToRad;

			////Z축의 값을 남겨두기 위해 (2,3)의 값을 1로 둔다
			//// [0] [] [] []
			//// [] [0] [] []
			//// [] [] [0][1]
			//// [] [] [] [0]
			//Arr2D[2][3] = 1.f;
			//Arr2D[3][3] = 0.f;

			////투상 행렬은 화면에 그릴 물체들을 가로 (-1.f ~ 1.f)로 모으고, 깊이 (0.f ~ 1.f)로 변환한다.
			////
			//Arr2D[0][0] = 1 / (tanf(FOV / 2.f) * _AspectRatio);
			//Arr2D[1][1] = 1 / tanf(FOV / 2.f);
			//Arr2D[2][2] = _FarZ / (_FarZ - _NearZ);
			//Arr2D[3][2] = -(_NearZ * _FarZ) / (_FarZ - _NearZ);
		}
	}

	void OrthographicLH(float _ScreenWidth, float _ScreenHeight, float _NearZ = 0.1f, float _FarZ = 10000.0f)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixOrthographicLH(_ScreenWidth, _ScreenHeight, _NearZ, _FarZ);
	}


	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin = 0.f, float _ZMax = 1.f)
	{
		Identity();

		//투영변환시 -1 ~ 1까지의 범위로 바뀌였기 때문에 해상도의 절반만큼 곱한다

		//해상도만큼 늘리기, 윈도우좌표계를 반전시키기 위해 y쪽은 -값
		Arr2D[0][0] = _Width * 0.5f;
		Arr2D[1][1] = -_Height * 0.5f;
		Arr2D[2][2] = (_ZMax == 0.f) ? 1.f : (_ZMin / _ZMax);

		//윈도우 좌표계는 좌측 상단이 (0,0)이기 때문에
		//(0,0)을 화면 정중앙으로 맞추기 위해 해상도 절반만큼 이동
		//_Right와 _Left는 오프셋
		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = (_Height * 0.5f) + _Right;
		Arr2D[3][2] = (_ZMax == 0.0f) ? 0.0f : (_ZMin / _ZMax);
		Arr2D[3][3] = 1.f;
	}

	//크자이로 행렬을 만드는 함수(회전은 쿼터니언이 들어간다)
	void Compose(const float4& _Scale, const float4& _RotQuaternion, const float4& _Pos)
	{
		float4 _Rot = _RotQuaternion;
		_Rot.QuaternionToEulerDeg();
		*this = DirectX::XMMatrixAffineTransformation(_Scale.DirectVector, _Rot.DirectVector, _RotQuaternion.DirectVector, _Pos.DirectVector);
	}


	//행렬에서 크자이를 추출, 대신 회전은 쿼터니언으로 나온다
	void Decompose(float4& _Scale, float4& _RotQuaternion, float4& _Pos) const
	{
		DirectX::XMMatrixDecompose(
			&_Scale.DirectVector, 
			&_RotQuaternion.DirectVector, 
			&_Pos.DirectVector, 
			DirectMatrix);
	}

	//행렬에서 회전벡터를 추출, 대신 쿼터니언으로 나옴
	void DecomposeRotQuaternion(float4& _RotQuaternion)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(
			&Temp0.DirectVector, 
			&_RotQuaternion.DirectVector, 
			&Temp1.DirectVector, 
			DirectMatrix);
	}

	//행렬에서 이동벡터 추출
	void DecomposePos(float4& _Pos)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(
			&Temp0.DirectVector, 
			&Temp1.DirectVector, 
			&_Pos.DirectVector, 
			DirectMatrix);
	}

	//행렬에서 크기벡터 추출
	void DecomposeScale(float4& _Scale)
	{
		float4 Temp0;
		float4 Temp1;

		DirectX::XMMatrixDecompose(
			&_Scale.DirectVector,
			&Temp0.DirectVector,
			&Temp1.DirectVector,
			DirectMatrix);
	}


	



	//뷰 행렬 만들기
	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp);

		{
			//float4 EyePos = _EyePos;

			//float4 EyeDir = _EyeDir.NormalizeReturn();
			//float4 EyeUp = _EyeUp;
			//float4 Right = float4::Cross3DReturn(EyeUp, EyeDir);
			//Right.Normalize();

			//float4 UpVector = float4::Cross3DReturn(_EyeDir, Right);
			//Right.Normalize();

			//float4 NegEyePos = -_EyePos;


			///*
			//카메라가 회전을 안 했다면 단순히,
			//D0는 -카메라의 X위치
			//D1는 -카메라의 y위치
			//D2는 -카메라의 z위치가 될 것이다.

			//하지만 카메라를 회전했다면 회전한 각 축의 정사영된 위치로 변환되기 때문에
			//아래와 같이 내적하여 위치값을 구한다.
			//*/

			////이동 위치(아래의 회전행렬의 전치를 적용시키기 위해 따로 빼둔다)
			//float D0Value = float4::DotProduct3D(Right, NegEyePos);			//x
			//float D1Value = float4::DotProduct3D(UpVector, NegEyePos);	//y
			//float D2Value = float4::DotProduct3D(EyeDir, NegEyePos);			//z

			////카메라의 회전행렬
			//ArrVector[0] = Right;
			//ArrVector[1] = UpVector;
			//ArrVector[2] = EyeDir;

			////회전행렬을 전치시키면 회전하기 전으로 돌릴수 있는
			////회전행렬을 만들수 있다.
			//Transpose();

			////회전과 이동 적용
			//ArrVector[3] = { D0Value, D1Value, D2Value, 0 };
		}
	}

	//행렬 전치시키기
	void Transpose()
	{
		DirectMatrix = DirectX::XMMatrixTranspose(*this);

		/*float4x4 This = *this;
		Identity();
		for (size_t y = 0; y < YCount; ++y)
		{
			for (size_t x = 0; x < XCount; ++x)
			{
				Arr2D[x][y] = This.Arr2D[y][x];
			}
		}*/
	}

	//역행렬로 만들기
	void Inverse()
	{
		DirectMatrix = DirectX::XMMatrixInverse(nullptr, *this);
	}

	float4x4 InverseReturn() const
	{
		float4x4 Return = *this;
		Return.Inverse();
		return Return;
	}


	//크기 행렬 만들기
	void Scale(const float4& _Value)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value);

		/*Arr2D[0][0] = _Value.x;
		Arr2D[1][1] = _Value.y;
		Arr2D[2][2] = _Value.z;*/
	}

	//이동 행렬 만들기
	void Pos(const float4& _Value)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value);

		/*Arr2D[3][0] = _Value.x;
		Arr2D[3][1] = _Value.y;
		Arr2D[3][2] = _Value.z;*/
	}


	void RotationDegToXYZ(const float4& _Deg)
	{
		float4 Rot = _Deg * GameEngineMath::DegToRad;

		float4x4 RotX = DirectX::XMMatrixRotationX(Rot.x);
		float4x4 RotY = DirectX::XMMatrixRotationY(Rot.y);
		float4x4 RotZ = DirectX::XMMatrixRotationZ(Rot.z);

		*this = RotX * RotY * RotZ;

		//DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Deg * GameEngineMath::DegToRad);
	}


	//회전 행렬 만들기
	void RotationDeg(const float4& _Deg)
	{
		/*float4x4 RotX = float4x4::Zero;
		float4x4 RotY = float4x4::Zero;
		float4x4 RotZ = float4x4::Zero;

		RotX.RotationXDeg(_Deg.x);
		RotY.RotationYDeg(_Deg.y);
		RotZ.RotationZDeg(_Deg.z);

		*this = RotX * RotY * RotZ;*/

		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Deg * GameEngineMath::DegToRad);
	}

	void RotationXDeg(const float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationXRad(const float _Rad)
	{
		Identity();
		/*Arr2D[1][1] = cosf(_Rad);
		Arr2D[1][2] = sinf(_Rad);
		Arr2D[2][1] = -sinf(_Rad);
		Arr2D[2][2] = cosf(_Rad);*/

		DirectMatrix = DirectX::XMMatrixRotationX(_Rad);
	}


	void RotationYDeg(const float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}


	void RotationYRad(const float _Rad)
	{
		Identity();
		/*Arr2D[0][0] = cosf(_Rad);
		Arr2D[0][2] = -sinf(_Rad);
		Arr2D[2][0] = sinf(_Rad);
		Arr2D[2][2] = cosf(_Rad);*/

		DirectMatrix = DirectX::XMMatrixRotationY(_Rad);
	}

	void RotationZDeg(const float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	

	void RotationZRad(const float _Rad)
	{
		Identity();
		/*Arr2D[0][0] = cosf(_Rad);
		Arr2D[0][1] = sinf(_Rad);
		Arr2D[1][0] = -sinf(_Rad);
		Arr2D[1][1] = cosf(_Rad);*/

		DirectMatrix = DirectX::XMMatrixRotationZ(_Rad);
	}








	float4x4 operator*(const float4x4& _Other)
	{
		float4x4 Return = DirectX::XMMatrixMultiply(*this, _Other);
		return Return;
	}

	float4x4& operator*=(const float4x4& _Other)
	{
		DirectMatrix = DirectX::XMMatrixMultiply(*this, _Other);
		return *this;
	}


	//w가 0인 곱하기
	float4 TransformNormal(const float4& _Value)
	{
		return DirectX::XMVector3TransformNormal(_Value, *this);
	}

	//w가 1인 곱하기
	float4 TransformCoord(const float4& _Value)
	{
		return DirectX::XMVector3TransformCoord(_Value, *this);
	}



	operator DirectX::FXMMATRIX() const
	{
		return DirectMatrix;
	}

	float4x4()
	{
		Identity();
	}

	float4x4(DirectX::FXMMATRIX _DirectMatrix)
		:DirectMatrix(_DirectMatrix)
	{

	}


	float4x4(const float4& _X, const float4&  _Y, const float4& _Z, const float4& _W)
	{
		ArrVector[0] = _X;
		ArrVector[1] = _Y;
		ArrVector[2] = _Z;
		ArrVector[3] = _W;
	}
};