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

	//�Ǽ� ������ �����ϱ� ���� _Tolerance���ϴ� 0���� ����� �Լ�
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

	//������ ������ 0�� ���� �� ������ŭ ȸ���� ���Ͱ� ���´�.
	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}


	//GetAngleVectorToVectorDeg�Լ��� ġ���� 0.f ~ 180.f ������ ġ���� 360.f�� Ȯ���ؼ� ������ �Լ�
	static float GetAngleVectorToVectorDeg360(const float4& _Pivot, const float4& _Other)
	{
		return GetAngleVectorToVectorRad360(_Pivot, _Other) * GameEngineMath::RadToDeg;
	}

	//GetAngleVectorToVectorDeg�Լ��� ġ���� 0.f ~ 180.f ������ ġ���� 360.f�� Ȯ���ؼ� ������ �Լ�
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



	//�� ���� ���� ���� ���ϴ� �Լ�
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
		
		//��α׿� ������
		float Angle = acosf(CosSeta);
		return Angle;
	}



	//����
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

	//����
	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		//float Value = (_Left.x * _Right.x) + (_Left.y * _Right.y) + (_Left.z * _Right.z);

		//SIMD���� ��� ������ __m128�� �޴´�
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

	//ȸ�����͸� ���ʹϾ����� ��ȯ
	float4 EulerDegToQuaternion();

	//���ʹϾ��� ȸ�� ��ķ� ��ȯ
	class float4x4 QuaternionToRotationMatrix();

	//���ʹϾ��� ȸ�����ͷ� ��ȯ(Degree)
	float4 QuaternionToEulerDeg();
	//���ʹϾ��� ȸ�����ͷ� ��ȯ(Radian)
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

	//xyz�� ���� ū ���� ��ȯ���ش�
	float MaxFloat() const
	{
		return (x < y) ? (y < z ? z : y) : (x < z ? z : x);
	}


	//������ ���� ���ϱ�(Radian)
	float GetAngleRadZ()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();

		//cos(����)�� x���� ���´�
		//�׷� ���Լ��� acos�� x���� ������ ������ ���´�
		float Result = acosf(AngleCheck.x);

		//������ ���ﰢ�Լ��� ���ܻ��Լ�(�ϴ��� ����)�� �ƴϴ�
			//ex) sin(PIE * 1/2) == sin(PIE * 3/2) == 1
			//ex) asin(1) => (PIE * 1/2 ) or (PIE * 3/2) ???
		//�׷��� ���ﰢ�Լ��� ġ���� 0 ~ PIE�� ���ѵȴ�

		//(���� ������ PIE�� �Ѱ��� �ϴ� �������� 
			//���򼱰� ��Ī�Ǵ� ������ ���Ծ��ٸ�)
		if (0.f < AngleCheck.y)
		{
			//������ ���� �������� ��Ī�̵� ��Ų��
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
		//���͸� �ﰢ������ �����غ��� �� ���� �� �����ϴ��� �� �� �ִ�,(�ﰢ���� ������)
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




	//���� ���� string���� ��ȯ�Ͽ� return
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
	
	//�׵���� �����
	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();
	}


	//���� ������� �����(�����þ߰�, ȭ�� ��Ⱦ��(����/����), �����, �����)
	void PersperctiveFovLH(float _FovAngle, float _AspectRatio, float _NearZ = 0.1f, float _FarZ = 10000.f)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle * GameEngineMath::DegToRad, _AspectRatio, _NearZ, _FarZ);

		{
			////��׸� -> ����
			//float FOV = _FovAngle * GameEngineMath::DegToRad;

			////Z���� ���� ���ܵα� ���� (2,3)�� ���� 1�� �д�
			//// [0] [] [] []
			//// [] [0] [] []
			//// [] [] [0][1]
			//// [] [] [] [0]
			//Arr2D[2][3] = 1.f;
			//Arr2D[3][3] = 0.f;

			////���� ����� ȭ�鿡 �׸� ��ü���� ���� (-1.f ~ 1.f)�� ������, ���� (0.f ~ 1.f)�� ��ȯ�Ѵ�.
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

		//������ȯ�� -1 ~ 1������ ������ �ٲ�� ������ �ػ��� ���ݸ�ŭ ���Ѵ�

		//�ػ󵵸�ŭ �ø���, ��������ǥ�踦 ������Ű�� ���� y���� -��
		Arr2D[0][0] = _Width * 0.5f;
		Arr2D[1][1] = -_Height * 0.5f;
		Arr2D[2][2] = (_ZMax == 0.f) ? 1.f : (_ZMin / _ZMax);

		//������ ��ǥ��� ���� ����� (0,0)�̱� ������
		//(0,0)�� ȭ�� ���߾����� ���߱� ���� �ػ� ���ݸ�ŭ �̵�
		//_Right�� _Left�� ������
		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = (_Height * 0.5f) + _Right;
		Arr2D[3][2] = (_ZMax == 0.0f) ? 0.0f : (_ZMin / _ZMax);
		Arr2D[3][3] = 1.f;
	}

	//ũ���̷� ����� ����� �Լ�(ȸ���� ���ʹϾ��� ����)
	void Compose(const float4& _Scale, const float4& _RotQuaternion, const float4& _Pos)
	{
		float4 _Rot = _RotQuaternion;
		_Rot.QuaternionToEulerDeg();
		*this = DirectX::XMMatrixAffineTransformation(_Scale.DirectVector, _Rot.DirectVector, _RotQuaternion.DirectVector, _Pos.DirectVector);
	}


	//��Ŀ��� ũ���̸� ����, ��� ȸ���� ���ʹϾ����� ���´�
	void Decompose(float4& _Scale, float4& _RotQuaternion, float4& _Pos) const
	{
		DirectX::XMMatrixDecompose(
			&_Scale.DirectVector, 
			&_RotQuaternion.DirectVector, 
			&_Pos.DirectVector, 
			DirectMatrix);
	}

	//��Ŀ��� ȸ�����͸� ����, ��� ���ʹϾ����� ����
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

	//��Ŀ��� �̵����� ����
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

	//��Ŀ��� ũ�⺤�� ����
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


	



	//�� ��� �����
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
			//ī�޶� ȸ���� �� �ߴٸ� �ܼ���,
			//D0�� -ī�޶��� X��ġ
			//D1�� -ī�޶��� y��ġ
			//D2�� -ī�޶��� z��ġ�� �� ���̴�.

			//������ ī�޶� ȸ���ߴٸ� ȸ���� �� ���� ���翵�� ��ġ�� ��ȯ�Ǳ� ������
			//�Ʒ��� ���� �����Ͽ� ��ġ���� ���Ѵ�.
			//*/

			////�̵� ��ġ(�Ʒ��� ȸ������� ��ġ�� �����Ű�� ���� ���� ���д�)
			//float D0Value = float4::DotProduct3D(Right, NegEyePos);			//x
			//float D1Value = float4::DotProduct3D(UpVector, NegEyePos);	//y
			//float D2Value = float4::DotProduct3D(EyeDir, NegEyePos);			//z

			////ī�޶��� ȸ�����
			//ArrVector[0] = Right;
			//ArrVector[1] = UpVector;
			//ArrVector[2] = EyeDir;

			////ȸ������� ��ġ��Ű�� ȸ���ϱ� ������ ������ �ִ�
			////ȸ������� ����� �ִ�.
			//Transpose();

			////ȸ���� �̵� ����
			//ArrVector[3] = { D0Value, D1Value, D2Value, 0 };
		}
	}

	//��� ��ġ��Ű��
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

	//����ķ� �����
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


	//ũ�� ��� �����
	void Scale(const float4& _Value)
	{
		Identity();
		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value);

		/*Arr2D[0][0] = _Value.x;
		Arr2D[1][1] = _Value.y;
		Arr2D[2][2] = _Value.z;*/
	}

	//�̵� ��� �����
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


	//ȸ�� ��� �����
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


	//w�� 0�� ���ϱ�
	float4 TransformNormal(const float4& _Value)
	{
		return DirectX::XMVector3TransformNormal(_Value, *this);
	}

	//w�� 1�� ���ϱ�
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