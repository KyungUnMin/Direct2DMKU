#pragma once
#include "GameEngineResource.h"

class GameEngineRenderingPipeLine : public GameEngineResource<GameEngineRenderingPipeLine>
{
public:
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine() override;

	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRenderingPipeLine> Create(const std::string_view& _Name)
	{
		std::shared_ptr<class GameEngineRenderingPipeLine> NewRes = GameEngineResource<GameEngineRenderingPipeLine>::Create(_Name);
		return NewRes;
	}

	inline  std::shared_ptr<class GameEngineVertexShader> GetVertexShader() const
	{
		return VertexShaderPtr;
	}

	inline  std::shared_ptr<class GameEnginePixelShader> GetPixelShader() const
	{
		return PixelShaderPtr;
	}

	//void SetVertexBuffer(const std::string_view& _Value);
	void SetVertexShader(const std::string_view& _Value);
	//void SetIndexBuffer(const std::string_view& _Value);
	void SetRasterizer(const std::string_view& _Value);
	void SetPixelShader(const std::string_view& _Value);
	void SetBlendState(const std::string_view& _Value);
	void SetDepthState(const std::string_view& _Value);

	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		FILL_MODE = _Value;
	}

	//GPU에 랜더링 파이프 라인을 세팅하는 단계들
	void RenderingPipeLineSetting();
	//실질적으로 그리는 단계
	void Render();

	std::shared_ptr<GameEngineRenderingPipeLine> Clone();

	bool IsClone()
	{
		return IsCloneValue;
	}

protected:

private:
	//클론된 파이프라인인지 여부
	bool IsCloneValue = false;

	//래스터 라이저 단계에서 픽셀들을 어떻게 그릴지에 대한 값
	D3D11_FILL_MODE FILL_MODE = D3D11_FILL_MODE::D3D11_FILL_SOLID;

	//인풋 어셈블러2 단계에서 어떤 모양의 도형을 그릴 것인지에 대한 값(코드를 메시로 이사시킴)
	//D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	//std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;	(코드를 메시로 이사시킴)
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;
	std::shared_ptr<class GameEngineBlend> BlendStatePtr;
	std::shared_ptr<class GameEngineDepthState> DepthStatePtr;



	//-------------REDERING PIPELiNE---------

	//점에 대한 정보가 GPU에 입력된다
	//void InputAssembler1(); (코드를 메시로 이사시킴)


	//버텍스 쉐이더에서 행렬이 곱해진다
	//이때 월드, 뷰, 프로젝션(투영행렬) 까지만 곱해지고,
	//투영행렬의 w나누기는 하지 않음
	//	w나누기는 레스터 라이저 단계에서 나눠진다
	//
	//이때 각 버텍스를 순회하는 쉐이더를 작성하게 되는데,
	//외부 파일에 쉐이더 코드를 짜고 그 경로를 통해 로드한다
	void VertexShader();

	//인덱스 버퍼가 사용되고
	//	버텍스의 순서가 결정된다
	//	(점이 어떻게 그려질 지 정하는 단계)
	//	우리는 점 4개를 이용해
	//삼각형 두개로 사각형 만들것임
	//void InputAssembler2();	(코드를 메시로 이사시킴)


	//거리에 따라 메쉬를 쪼갬
	//근데 보통은 같은 Actor를
	//	정점의 갯수가 다른 메쉬로 이용해서 표현함
	//	이를 LOD라고 함(레벨 오브 디테일)
	void HullShader();
	void Tesselator();

	//(파티클을 만드는 단계)
	//	도메인 : 점에 특정한 정보를 부여
	//	지오메트리 : 없던 메쉬를 만듬
	void DomainShader();
	void GeometryShader();

	//투영 행렬의 w로나누기(기존의 Z값) + 뷰포트 + 화면 컬링(화면에 나간 부분 자르기)
	// +픽셀 던지기(벡터를 레스터화, 아마도 명칭이 래스터라이제이션이였던거 같음)
	void Rasterizer();


	//레스터라이저해서 나온 픽셀들을 순회해서 색상을 결정
	//즉, 메쉬의 역할은 모니터에  색칠하고 싶은 범위를 지정하는 것이고
	//픽셀쉐이더에서 그 물체의 색상을 결정함
	//
	//아마 이때도 쉐이더를 작성하지 않을까 예상됨
	void PixelShader();

	//어느 렌더타켓에서 만들어지는지 결정하는 단계
	void OutputMerger();


	/*
	다렉 11 렌더링 파이프라인 단계의 분류
	프로그래밍 가능 단계
		버텍스 쉐이더
		픽셀 쉐이더 등등 쉐이더 단계
			특정 규칙만 지킨 내가 만든 코드 자체를 넘긴다

	고정 기능 단계
		나머지 애들, 내가 옵션 정도만 넣는 단계
		보통 고정 기능 단계는 다 스테이트를 넘긴다
	*/
};

