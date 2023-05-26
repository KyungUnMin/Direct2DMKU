#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

//렌더링을 1번 수행하는 단위
class GameEngineRenderUnit
	:std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe;

	/*
		유니티나 언리얼 같은 엔진에서는 여러 엑터들이
		공통된 파이프라인을 공유한다.
		그래서 그 파이프라인의 상수버퍼 하나만 바꿔도
		해당 파이프라인을 사용하고 있던 엑터들이 전부 바뀐다.

		이 엔진 구조에서는 그것과는 다르게
		렌더러마다 별도의 상수버퍼, 텍스처들을 같게 했다.
		때문에 각 쉐이더 파일을 리플렉션을 통해 조사해서
		어떤 리소스들이 사용되었는지 알아내고,
		그에 대한 정보를 랜더링 파이프라인이 세팅될때
		GameEngineShaderResHelper::Copy함수를 통해 복사해온다
		그렇게 복사된 세터에 렌더러 별도의 상수버퍼, 텍스처 등을 채워넣으면 된다
	*/
	GameEngineShaderResHelper ShaderResHelper;

public:
	//파이프라인 세팅 밎 쉐이더 정보 세팅
	void SetPipeLine(const std::string_view& _Name);
	//렌더링
	void Render(float _DeltaTime);
};

class GameEngineCamera;

class GameEngineRenderer : public GameEngineComponent
{
	friend GameEngineCamera;

public:
	GameEngineRenderer();
	~GameEngineRenderer() override;

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _Other) noexcept = delete;

	//(드로우(그리기) 하기 직전에 쉐이더 파일에 값을 넣어주는 것 같다)
	//파이프라인을 세팅하면서, 쉐이더 과정들의 헬터들을 한곳에 모은다
	void SetPipeLine(const std::string_view& _Name, int _index = 0);

	// 여기서 리턴된 파이프라인을 수정하면 이 파이프라인을 사용하는 모든 애들이 바뀌게 된다.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLine(int _index = 0);

	// 이걸 사용하게되면 이 랜더러의 유니트는 자신만의 클론 파이프라인을 가지게 된다.
	std::shared_ptr<GameEngineRenderingPipeLine> GetPipeLineClone(int _index = 0);

	inline GameEngineShaderResHelper& GetShaderResHelper(int _index = 0)
	{
		return Units[_index]->ShaderResHelper;
	}

	inline void CameraCullingOn()
	{
		IsCameraCulling = true;
	}

	//카메라을 기준으로 Z값을 계산한다
	void CalSortZ(GameEngineCamera* _Camera);

protected:
	void Start() override;

	void Render(float _DeltaTime) override;

	//레벨의 _CameraOrder번째 카메라에 이 렌더러를 등록
	void PushCameraRender(int _CameraOrder);

private:
	bool IsCameraCulling = false;

	float CalZ = 0.0f;

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

	//등록된 카메라를 바탕으로 행렬을 계산한다
	void RenderTransformUpdate(GameEngineCamera* _Camera);
};

