#include "GameEngineMath.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

const float			GameEngineMath::PIE	= 3.141592653589793238462643383279502884197169399375105820974944f;
const float			GameEngineMath::PIE2	= PIE * 2.0f;

//(180도는 파이 라디안), (1도는 파이 / 180 라디안)
const float			GameEngineMath::DegToRad = GameEngineMath::PIE / 180;
//(파이 라디안은 180), (1라디안은 180 / 파이)
const float			GameEngineMath::RadToDeg = 180 / GameEngineMath::PIE;


const float4		float4::Left						= { -1.0f, 0.0f, 0.0f, 1.0f };
const float4		float4::Right					= { 1.0f, 0.0f, 0.0f, 1.0f };
const float4		float4::Up						= { 0.0f, 1.0f, 0.0f, 1.0f };
const float4		float4::Down					= { 0.0f, -1.0f, 0.0f, 1.0f };

const float4		float4::Forward				= { 0.0f, 0.0f, 1.0f, 1.0f };
const float4		float4::Back					= { 0.0f, 0.0f, -1.0f, 1.0f };
const float4		float4::One						= { 1.0f, 1.0f, 1.0f, 1.0f };

const float4		float4::Zero					= { 0.0f, 0.0f, 0.0f, 1.0f };
const float4		float4::Null						= { 0.0f, 0.0f, 0.0f, 0.0f };


void float4::RotationXRad(float _Rad)
{
	float4x4 Rot;
	Rot.RotationXRad(_Rad);
	*this *= Rot;
}

void float4::RotationYRad(float _Rad)
{
	float4x4 Rot;
	Rot.RotationYRad(_Rad);
	*this *= Rot;
}

void float4::RotationZRad(float _Rad)
{
	float4x4 Rot;
	Rot.RotationZRad(_Rad);
	*this *= Rot;
}




std::vector<unsigned int> GameEngineMath::GetDigits(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(_Value);

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')
	{
		StartIndex = 1;
	}

	ResultValue.reserve(StringValue.size());

	for (size_t i = StartIndex; i < StringValue.size(); i++)
	{
		ResultValue.push_back(StringValue[i] - '0');
	}

	return ResultValue;
}

unsigned int GameEngineMath::GetLenth(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(_Value);

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')
	{
		StartIndex = 1;
	}

	return static_cast<unsigned int>(StringValue.size()) - StartIndex;
}


float4 float4::operator*(const class float4x4& _Other)
{
	/*ReturnValue.x = (_Other.Arr2D[0][0] * Arr1D[0]) + (_Other.Arr2D[1][0] * Arr1D[1]) + (_Other.Arr2D[2][0] * Arr1D[2]) + (_Other.Arr2D[3][0] * Arr1D[3]);
	ReturnValue.y = (_Other.Arr2D[0][1] * Arr1D[0]) + (_Other.Arr2D[1][1] * Arr1D[1]) + (_Other.Arr2D[2][1] * Arr1D[2]) + (_Other.Arr2D[3][1] * Arr1D[3]);
	ReturnValue.z = (_Other.Arr2D[0][2] * Arr1D[0]) + (_Other.Arr2D[1][2] * Arr1D[1]) + (_Other.Arr2D[2][2] * Arr1D[2]) + (_Other.Arr2D[3][2] * Arr1D[3]);
	ReturnValue.w = (_Other.Arr2D[0][3] * Arr1D[0]) + (_Other.Arr2D[1][3] * Arr1D[1]) + (_Other.Arr2D[2][3] * Arr1D[2]) + (_Other.Arr2D[3][3] * Arr1D[3]);*/

	float4 ReturnValue = DirectX::XMVector4Transform(*this, _Other);
	return ReturnValue;
}

float4& float4::operator*=(const class float4x4& _Other)
{
	float4 ReturnValue;
	ReturnValue.x = (_Other.Arr2D[0][0] * Arr1D[0]) + (_Other.Arr2D[1][0] * Arr1D[1]) + (_Other.Arr2D[2][0] * Arr1D[2]) + (_Other.Arr2D[3][0] * Arr1D[3]);
	ReturnValue.y = (_Other.Arr2D[0][1] * Arr1D[0]) + (_Other.Arr2D[1][1] * Arr1D[1]) + (_Other.Arr2D[2][1] * Arr1D[2]) + (_Other.Arr2D[3][1] * Arr1D[3]);
	ReturnValue.z = (_Other.Arr2D[0][2] * Arr1D[0]) + (_Other.Arr2D[1][2] * Arr1D[1]) + (_Other.Arr2D[2][2] * Arr1D[2]) + (_Other.Arr2D[3][2] * Arr1D[3]);
	ReturnValue.w = (_Other.Arr2D[0][3] * Arr1D[0]) + (_Other.Arr2D[1][3] * Arr1D[1]) + (_Other.Arr2D[2][3] * Arr1D[2]) + (_Other.Arr2D[3][3] * Arr1D[3]);
	*this = ReturnValue;

	return *this;
}



const float4x4 float4x4::Zero = float4x4(float4::Null, float4::Null, float4::Null, float4::Null);

