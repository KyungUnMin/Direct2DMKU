#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"



//-----------------AnimationInfo-----------------


std::shared_ptr<GameEngineTexture> AnimationInfo::CurFrameTexture()
{
	const SpriteInfo& Info = Sprite->GetSpriteInfo(CurFrame);
	return Info.Texture;
}


bool AnimationInfo::IsEnd()
{
	return IsEndValue;
}


void AnimationInfo::Reset()
{
	CurFrame = StartFrame;
	CurTime = 0.0f;
	IsEndValue = false;
}


void AnimationInfo::Update(float _DeltaTime)
{
	IsEndValue = false;
	CurTime -= _DeltaTime;


	if (CurTime < 0.0f)
	{
		//���� ���������� ��ȯ
		++CurFrame;
		CurTime += Inter;

		//������� ������ �������̿��ٸ�
		if (EndFrame < CurFrame)
		{
			IsEndValue = true;

			//�ݺ������ ���
			if (true == Loop)
			{
				CurFrame = StartFrame;
			}
			//�ݺ������ �ƴ� ���
			else
			{
				//������ �������� ����
				--CurFrame;
			}
		}
	}

}


//-----------------GameEngineSpriteRenderer-----------------


GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{

}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{

}


void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();
	SetPipeLine("2DTexture");
}




void GameEngineSpriteRenderer::SetTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
}

void GameEngineSpriteRenderer::SetFlipX()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.x = -LocalScale.x;
	GetTransform()->SetLocalScale(LocalScale);
}

void GameEngineSpriteRenderer::SetFlipY()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.y = -LocalScale.y;
	GetTransform()->SetLocalScale(LocalScale);
}


void GameEngineSpriteRenderer::SetScaleToTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);

	if (nullptr == FindTex)
	{
		MsgAssert("�������� �ʴ� �̹��� �Դϴ�.");
		return;
	}

	float4 Scale = float4(static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1);
	GetTransform()->SetLocalScale(Scale);
}


std::shared_ptr<AnimationInfo> GameEngineSpriteRenderer::FindAnimation(const std::string_view& _Name)
{
	std::map<std::string, std::shared_ptr<AnimationInfo>>::iterator FindIter = Animations.find(_Name.data());

	if (FindIter == Animations.end())
		return nullptr;

	return FindIter->second;
}

std::shared_ptr<AnimationInfo> GameEngineSpriteRenderer::CreateAnimation(
	const std::string_view& _Name, 
	const std::string_view& _SpriteName, 
	float _FrameInter, 
	int _Start, int _End, bool _Loop)
{
	if (nullptr != FindAnimation(_Name))
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼��� �� ������� �߽��ϴ�." + std::string(_Name));
		return nullptr;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(_SpriteName);
	if (nullptr == Sprite)
	{
		MsgAssert("�������� �ʴ� ��������Ʈ�� �ִϸ��̼��� ������� �߽��ϴ�." + std::string(_Name));
		return nullptr;
	}


	//�ִϸ��̼� ���� �� �ڷᱸ���� ����
	std::shared_ptr<AnimationInfo> NewAnimation = std::make_shared<AnimationInfo>();
	Animations[_Name.data()] = NewAnimation;

	//����Ʈ ������ ��쿣 ������ 0�� ��������Ʈ ���� ����
	if (-1 != _Start)
	{
		if (_Start < 0)
		{
			MsgAssert("��������Ʈ ������ �ʰ��ϴ� �ε����� �ִϸ��̼��� ������� �߽��ϴ�." + std::string(_Name));
			return nullptr;
		}

		NewAnimation->StartFrame = _Start;
	}
	//�ִϸ��̼� ���� ��ġ�� ���� ������ ���
	else
	{
		NewAnimation->StartFrame = 0;
	}


	//����Ʈ ������ ��쿣 ������ ������ ��������Ʈ���� �ִϸ��̼� ���
	if (-1 != _End)
	{
		if (_End >= Sprite->GetSpriteCount())
		{
			MsgAssert("��������Ʈ ������ �ʰ��ϴ� �ε����� �ִϸ��̼��� ������� �߽��ϴ�." + std::string(_Name));
			return nullptr;
		}

		NewAnimation->EndFrame = _End;
	}
	//�ִϸ��̼� ������ ��ġ�� ���� ������ ���
	else
	{
		NewAnimation->EndFrame = Sprite->GetSpriteCount() - 1;
	}


	NewAnimation->Sprite = Sprite;
	NewAnimation->Parent = this;
	NewAnimation->Loop = _Loop;
	NewAnimation->Inter = _FrameInter;
	return NewAnimation;
}

void GameEngineSpriteRenderer::ChangeAnimation(const std::string_view& _Name, size_t _Frame, bool _Force)
{
	//�̹� ������� �ִϸ��̼��̸鼭, ó������ ����� �ƴ� ��쿣 return
	std::shared_ptr<AnimationInfo> Find = FindAnimation(_Name);
	if (CurAnimation == Find && false == _Force)
		return;


	//�ִϸ��̼� ���� 
	CurAnimation = Find;
	CurAnimation->Reset();

	//�ִϸ��̼� �������� ���� ������ ���
	if (_Frame != -1)
	{
		CurAnimation->CurFrame = _Frame;
	}
}



void GameEngineSpriteRenderer::Render(float _DeltaTime)
{
	//�ִϸ��̼� �� Sprite�� ���
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_DeltaTime);
		GetShaderResHelper().SetTexture("DiffuseTex", CurAnimation->CurFrameTexture());
	}

	//�Ϲ� �̹��� Sprite�� ���
	GameEngineRenderer::Render(_DeltaTime);
}
