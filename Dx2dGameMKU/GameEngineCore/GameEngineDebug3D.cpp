#include "PrecompileHeader.h"
#include "GameEngineDebug3D.h"

#include "GameEngineRenderer.h"

namespace GameEngineDebug
{
	enum class DebugDrawType
	{
		Box,
		Sphere,
		Point
	};

	class DebugData
	{
	public:
		DebugDrawType Type;
		class GameEngineTransform* Trans;
		float4 Color;
	};

	GameEngineRenderUnit DebugRenderUnit;

	//<카메라, 그려야 할 데이터>
	std::map<GameEngineCamera*, std::vector<DebugData>> DebugDrawDatas;

	void DrawBox(class GameEngineCamera* _Cam, class GameEngineTransform* _Trans, float4 Color)
	{
		//이 카메라가 처음으로 디버깅 충돌체를 그리는 경우
		if (DebugDrawDatas.end() == DebugDrawDatas.find(_Cam))
		{
			DebugDrawDatas[_Cam].reserve(1000);
		}

		DebugDrawDatas[_Cam].push_back({ DebugDrawType::Box, _Trans, Color });
	}

	void DrawSphere(class GameEngineCamera* _Cam, class GameEngineTransform* _Trans, float4 Color)
	{
		//이 카메라가 처음으로 디버깅 충돌체를 그리는 경우
		if (DebugDrawDatas.end() == DebugDrawDatas.find(_Cam))
		{
			DebugDrawDatas[_Cam].reserve(1000);
		}

		DebugDrawDatas[_Cam].push_back({ DebugDrawType::Sphere, _Trans, Color });
	}




	void DebugRender(GameEngineCamera* _Camera, float _Delta)
	{
		// 맨 처음엔 유닛에 파이프라인이 세팅되어 있지 않을텐데 그때 세팅
		if (nullptr == DebugRenderUnit.Pipe)
		{
			DebugRenderUnit.SetPipeLine("DebugMeshRender");
		}
		
		//이 카메라(_Camera)가 그려야 할 콜리전 데이터들
		std::vector<DebugData>& Data = DebugDrawDatas[_Camera];
		for (size_t i = 0; i < Data.size(); i++)
		{
			//현재 그릴 콜리전 데이터
			DebugData& CurData = Data[i];
			DebugDrawType Type = CurData.Type;

			//콜리전 타입에 따라 메시 설정
			switch (Type)
			{
			case GameEngineDebug::DebugDrawType::Box:
				DebugRenderUnit.SetMesh("DebugBox");
				break;
			case GameEngineDebug::DebugDrawType::Sphere:
				DebugRenderUnit.SetMesh("DebugSphere");
				break;
			case GameEngineDebug::DebugDrawType::Point:
				break;
			default:
				break;
			}

			//콜리전 데이터의 윈도우 화면위치를 알기 위해 카메라의 뷰행렬과 투영행렬을 곱한다
			CurData.Trans->SetCameraMatrix(_Camera->GetView(), _Camera->GetProjection());



			//그리려는 콜리전의 TransData 받아오기
			static TransformData DrawData;
			DrawData = CurData.Trans->GetTransDataRef();

			switch (Type)
			{
			case GameEngineDebug::DebugDrawType::Box:
				//DebugRenderUnit.SetMesh("DebugBox");
				break;

				//구의 경우에는 X값 만이 반지름이 되어야 한다
			case GameEngineDebug::DebugDrawType::Sphere:
				//DebugRenderUnit.SetMesh("DebugSphere");
				
				//TransData의 Scale.x에 맞춰 행렬 재 계산
				DrawData.Scale = { DrawData.Scale.x, DrawData.Scale.x, DrawData.Scale.x };

				//로컬행렬 계산
				DrawData.LocalCalculation();
				//월드행렬 = 로컬행렬
				DrawData.WorldMatrix = DrawData.LocalWorldMatrix;

				//부모가 있는 경우 월드행렬 재계산
				if (nullptr != CurData.Trans->GetParent())
				{
					DrawData.WorldCalculation(CurData.Trans->GetParent()->GetWorldMatrixRef(), CurData.Trans->IsAbsoluteScale(), CurData.Trans->IsAbsoluteRotation(), CurData.Trans->IsAbsolutePosition());
				}

				//뷰행렬과 투영행렬 계산
				DrawData.SetViewAndProjection(_Camera->GetView(), _Camera->GetProjection());
				break;
			case GameEngineDebug::DebugDrawType::Point:
				break;
			default:
				break;
			}


			//상수버퍼 연결
			DebugRenderUnit.ShaderResHelper.SetConstantBufferLink("TransformData", DrawData);
			DebugRenderUnit.ShaderResHelper.SetConstantBufferLink("DebugColor", CurData.Color);

			//그리기
			DebugRenderUnit.Render(_Delta);
		}

		Data.clear();
	}
}