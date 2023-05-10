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
		//다음 프레임으로 전환
		++CurFrame;
		CurTime += Inter;

		//방금전이 마지막 프레임이였다면
		if (EndFrame < CurFrame)
		{
			IsEndValue = true;

			//반복재생인 경우
			if (true == Loop)
			{
				CurFrame = StartFrame;
			}
			//반복재생이 아닌 경우
			else
			{
				//마지막 프레임을 유지
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
		MsgAssert("존재하지 않는 이미지 입니다.");
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
		MsgAssert("이미 존재하는 이름의 애니메이션을 또 만들려고 했습니다." + std::string(_Name));
		return nullptr;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(_SpriteName);
	if (nullptr == Sprite)
	{
		MsgAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다." + std::string(_Name));
		return nullptr;
	}


	//애니메이션 생성 및 자료구조에 저장
	std::shared_ptr<AnimationInfo> NewAnimation = std::make_shared<AnimationInfo>();
	Animations[_Name.data()] = NewAnimation;

	//디폴트 인자인 경우엔 폴더의 0번 스프라이트 부터 시작
	if (-1 != _Start)
	{
		if (_Start < 0)
		{
			MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Name));
			return nullptr;
		}

		NewAnimation->StartFrame = _Start;
	}
	//애니메이션 시작 위치를 직접 지정한 경우
	else
	{
		NewAnimation->StartFrame = 0;
	}


	//디폴트 인자인 경우엔 폴더의 마지막 스프라이트까지 애니메이션 재생
	if (-1 != _End)
	{
		if (_End >= Sprite->GetSpriteCount())
		{
			MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Name));
			return nullptr;
		}

		NewAnimation->EndFrame = _End;
	}
	//애니메이션 마지막 위치를 직접 지정한 경우
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
	//이미 재생중인 애니메이션이면서, 처음부터 재생이 아닌 경우엔 return
	std::shared_ptr<AnimationInfo> Find = FindAnimation(_Name);
	if (CurAnimation == Find && false == _Force)
		return;


	//애니메이션 변경 
	CurAnimation = Find;
	CurAnimation->Reset();

	//애니메이션 프레임을 직접 지정한 경우
	if (_Frame != -1)
	{
		CurAnimation->CurFrame = _Frame;
	}
}



void GameEngineSpriteRenderer::Render(float _DeltaTime)
{
	//애니메이션 용 Sprite인 경우
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_DeltaTime);
		GetShaderResHelper().SetTexture("DiffuseTex", CurAnimation->CurFrameTexture());
	}

	//일반 이미지 Sprite인 경우
	GameEngineRenderer::Render(_DeltaTime);
}
