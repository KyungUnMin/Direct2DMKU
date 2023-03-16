#pragma once
#include <Windows.h>
#include <string_view>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>


struct ImageCutData
{
	float StartX = 0.0f;
	float StartY = 0.0f;
	float SizeX = 0.0f;
	float SizeY = 0.0f;

	float4 GetStartPos()
	{
		return { StartX, StartY };
	}

	float4 GetScale()
	{
		return { SizeX, SizeY };
	}
};


class GameEnginePath;

class GameEngineImage
{
public:
	GameEngineImage();
	~GameEngineImage();

	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;



	//인자 HDC와 연결 및 사이즈 정보 초기화
	bool ImageCreate(HDC _Hdc);

	//크기를 입력받아서 BitMap을 만들고 ImageDC에 연결 및 정보 초기화
	bool ImageCreate(const float4& _Scale);

	//ImageLoad(const std::string_view& _Path)를 래핑
	bool ImageLoad(const GameEnginePath& _Path);

	//string을 이용한 이미지 로드
	bool ImageLoad(const std::string_view& _Path);

	//이미지를 흰색으로 칠해버리기
	void ImageClear();



	HDC GetImageDC() const
	{
		return ImageDC;
	}

	float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}



	//잘린 이미지인지 확인
	bool IsImageCutting()
	{
		return IsCut;
	}

	size_t GetImageCuttingCount()
	{
		return ImageCutDatas.size();
	}

	//벡터안에 유효한 범위인지 확인
	bool IsCutIndexValid(int _Index) const
	{
		if (0 > _Index)
		{
			return false;
		}

		if (ImageCutDatas.size() <= _Index)
		{
			return false;
		}

		return true;
	}

	//원하는 인덱스의 이미지 정보 가져오기
	ImageCutData GetCutData(int _Index) const
	{
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("유효하지 않은 컷 인덱스 입니다.");
		}

		return ImageCutDatas[_Index];
	}


	//이미지를 자를 시작점, 끝점, 자를 갯수(가로 세로)
	void Cut(float4 _Start, float4 _End, int _X, int _Y);

	//X(가로 이미지 갯수), Y(세로 이미지 갯수)로 자른 이미지 정보를 벡터에 저장
	void Cut(int _X, int _Y);


	//인자로 받은 이미지 전체를 이 객체의 HDC에 bitblt
	void BitCopy(
		const GameEngineImage* _OtherImage,
		float4 _CenterPos, float4 _Scale);


	//인자로 받은 이미지를 현재 객체에 TransParentBlt
	void TransCopy(
		const GameEngineImage* _OtherImage,
		float4 _CopyCenterPos, float4 _CopySize,
		float4 _OtherImagePos, float4 _OtherImageSize,
		int _Color = RGB(147, 187, 236));


	//컷팅된 이미지 TransParentBlt
	void TransCopy(
		const GameEngineImage* _OtherImage, int _CutIndex, 
		float4 _CopyCenterPos, float4 _CopySize, 
		int _Color = RGB(147, 187, 236));


	void AlphaCopy(
		const GameEngineImage* _OtherImage,
		float4 _CopyCenterPos, float4 _CopySize,
		float4 _OtherImagePos, float4 _OtherImageSize,
		int _Alpha);


	void AlphaCopy(
		const GameEngineImage* _OtherImage, int _CutIndex,
		float4 _CopyCenterPos, float4 _CopySize,
		int _Alpha);


	void PlgCopy(
		const GameEngineImage* _OtherImage,
		float4 _CopyCenterPos, float4 _CopySize,
		float4 _OtherImagePos, float4 _OtherImageSize,
		float _Angle, GameEngineImage* _FilterImage);


	void PlgCopy(
		const GameEngineImage* _OtherImage, int _CutIndex,
		float4 _CopyCenterPos, float4 _CopySize,
		float _Angle, GameEngineImage* _FilterImage);



	//내가 가지고 있는 이미지에서 해당 좌표의 색상을 받아옴
	DWORD GetPixelColor(float4 _Pos, DWORD _OutColor);

	//내가 가지고 있는 이미지에서 해당 좌표의 색상을 받아옴
	DWORD GetPixelColor(int _X, int _Y, DWORD _OutColor);

protected:

private:
	HDC				ImageDC = nullptr;
	HBITMAP		BitMap = nullptr;
	HBITMAP		OldBitMap = nullptr;
	BITMAP		Info = BITMAP();
	bool				IsCut = false;

	//커팅한 이미지 정보들을 관리
	std::vector<ImageCutData> ImageCutDatas;

	//현재 BITMAP의 정보를 Info로 기록하는 함수 
	void ImageScaleCheck();
};

