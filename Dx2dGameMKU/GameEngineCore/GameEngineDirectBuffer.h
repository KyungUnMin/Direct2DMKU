#pragma once

//GPU�� ����� �� ���������� ���̴� ���ۿ� ���� ������ ��Ƴ��� Ŭ����
class GameEngineDirectBuffer
{
public:
	GameEngineDirectBuffer();
	~GameEngineDirectBuffer();

	GameEngineDirectBuffer(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&& _Other) noexcept = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer&& _Other) noexcept = delete;

	inline UINT GetBufferSize() const
	{
		return BufferInfo.ByteWidth;
	}

protected:
	D3D11_BUFFER_DESC BufferInfo = { 0, };
	ID3D11Buffer* Buffer = nullptr;

private:

};

