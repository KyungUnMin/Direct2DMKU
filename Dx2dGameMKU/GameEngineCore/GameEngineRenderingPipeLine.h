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

	inline  std::shared_ptr<class GameEngineVertexShader> GetVertexShader() const
	{
		return VertexShaderPtr;
	}

	inline  std::shared_ptr<class GameEnginePixelShader> GetPixelShader() const
	{
		return PixelShaderPtr;
	}

	void SetVertexBuffer(const std::string_view& _Value);
	void SetVertexShader(const std::string_view& _Value);
	void SetIndexBuffer(const std::string_view& _Value);
	void SetRasterizer(const std::string_view& _Value);
	void SetPixelShader(const std::string_view& _Value);

	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		FILL_MODE = _Value;
	}

	void Render();



protected:

private:
	//������ ������ �ܰ迡�� �ȼ����� ��� �׸����� ���� ��
	D3D11_FILL_MODE FILL_MODE = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	//��ǲ �����2 �ܰ迡�� � ����� ������ �׸� �������� ���� ��
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineInputLayOut> InputLayOutPtr;
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;



	//-------------REDERING PIPELiNE---------

	//���� ���� ������ GPU�� �Էµȴ�
	void InputAssembler1();


	//���ؽ� ���̴����� ����� ��������
	//�̶� ����, ��, ��������(�������) ������ ��������,
	//��������� w������� ���� ����
	//	w������� ������ ������ �ܰ迡�� ��������
	//
	//�̶� �� ���ؽ��� ��ȸ�ϴ� ���̴��� �ۼ��ϰ� �Ǵµ�,
	//�ܺ� ���Ͽ� ���̴� �ڵ带 ¥�� �� ��θ� ���� �ε��Ѵ�
	void VertexShader();

	//�ε��� ���۰� ���ǰ�
	//	���ؽ��� ������ �����ȴ�
	//	(���� ��� �׷��� �� ���ϴ� �ܰ�)
	//	�츮�� �� 4���� �̿���
	//�ﰢ�� �ΰ��� �簢�� �������
	void InputAssembler2();


	//�Ÿ��� ���� �޽��� �ɰ�
	//�ٵ� ������ ���� Actor��
	//	������ ������ �ٸ� �޽��� �̿��ؼ� ǥ����
	//	�̸� LOD��� ��(���� ���� ������)
	void HullShader();
	void Tesselator();

	//(��ƼŬ�� ����� �ܰ�)
	//	������ : ���� Ư���� ������ �ο�
	//	������Ʈ�� : ���� �޽��� ����
	void DomainShader();
	void GeometryShader();

	//���� ����� w�γ�����(������ Z��) + ����Ʈ + ȭ�� �ø�(ȭ�鿡 ���� �κ� �ڸ���)
	// +�ȼ� ������(���͸� ������ȭ, �Ƹ��� ��Ī�� �����Ͷ������̼��̿����� ����)
	void Rasterizer();


	//�����Ͷ������ؼ� ���� �ȼ����� ��ȸ�ؼ� ������ ����
	//��, �޽��� ������ ����Ϳ�  ��ĥ�ϰ� ���� ������ �����ϴ� ���̰�
	//�ȼ����̴����� �� ��ü�� ������ ������
	//
	//�Ƹ� �̶��� ���̴��� �ۼ����� ������ �����
	void PixelShader();

	//��� ����Ÿ�Ͽ��� ����������� �����ϴ� �ܰ�
	void OutputMerger();


	/*
	�ٷ� 11 ������ ���������� �ܰ��� �з�
	���α׷��� ���� �ܰ�
		���ؽ� ���̴�
		�ȼ� ���̴� ��� ���̴� �ܰ�
			Ư�� ��Ģ�� ��Ų ���� ���� �ڵ� ��ü�� �ѱ��

	���� ��� �ܰ�
		������ �ֵ�, ���� �ɼ� ������ �ִ� �ܰ�
		���� ���� ��� �ܰ�� �� ������Ʈ�� �ѱ��
	*/
};

