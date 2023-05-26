#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"



//-----------------AnimationInfo-----------------


const SpriteInfo& AnimationInfo::CurSpriteInfo()
{
	const SpriteInfo& Info = Sprite->GetSpriteInfo(FrameIndex[CurFrame]);
	return Info;
}


bool AnimationInfo::IsEnd()
{
	return IsEndValue;
}


void AnimationInfo::Reset()
{
	CurFrame = 0;
	CurTime = FrameTime[0];
	IsEndValue = false;
	IsPauseValue = false;
}


void AnimationInfo::Update(float _DeltaTime)
{
	if (true == Loop)
	{
		IsEndValue = false;
	}

	//정지중이면 return
	if (true == IsPauseValue)
	{
		return;
	}


	//스프라이트 상의 현재 프레임
	size_t CurFrameIndex = FrameIndex[CurFrame];

	//Update콜백이 있으면 호출
	if (UpdateEventFunction.end() != UpdateEventFunction.find(CurFrameIndex))
	{
		UpdateEventFunction[CurFrameIndex]();
	}

	CurTime -= _DeltaTime;


	if (CurTime < 0.0f)
	{
		//다음 프레임으로 전환
		++CurFrame;


		//방금전이 마지막 프레임이였다면
		if (FrameIndex.size() <= CurFrame)
		{
			IsEndValue = true;

			//반복재생인 경우
			if (true == Loop)
			{
				CurFrame = 0;
			}
			//반복재생이 아닌 경우
			else
			{
				//마지막 프레임을 유지
				IsEndValue = true;
				--CurFrame;
			}
		}


		else
		{
			CurFrameIndex = FrameIndex[CurFrame];

			//Start콜백이 있으면 호출
			if (StartEventFunction.end() != StartEventFunction.find(CurFrameIndex))
			{
				StartEventFunction[CurFrameIndex]();
			}
		}

		

		CurTime += FrameTime[CurFrame];
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
	SpriteRenderInit();
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

void GameEngineSpriteRenderer::SetSprite(const std::string_view& _SpriteName, size_t _Frame/* = 0*/)
{
	Sprite = GameEngineSprite::Find(_SpriteName);
	Frame = _Frame;

	const SpriteInfo& Info = Sprite->GetSpriteInfo(Frame);
	GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
	AtlasData = Info.CutData;
}

void GameEngineSpriteRenderer::SetFrame(size_t _Frame)
{
	Frame = _Frame;

	const SpriteInfo& Info = Sprite->GetSpriteInfo(Frame);
	GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
	AtlasData = Info.CutData;
}


std::shared_ptr<AnimationInfo> GameEngineSpriteRenderer::FindAnimation(const std::string_view& _Name)
{
	std::map<std::string, std::shared_ptr<AnimationInfo>>::iterator FindIter = Animations.find(_Name.data());

	if (FindIter == Animations.end())
		return nullptr;

	return FindIter->second;
}

std::shared_ptr<AnimationInfo> GameEngineSpriteRenderer::CreateAnimation(const AnimationParameter& _Paramter)
{
	if (nullptr != FindAnimation(_Paramter.AnimationName))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션을 또 만들려고 했습니다." + std::string(_Paramter.AnimationName));
		return nullptr;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(_Paramter.SpriteName);
	if (nullptr == Sprite)
	{
		MsgAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다." + std::string(_Paramter.AnimationName));
		return nullptr;
	}


	//애니메이션 생성 및 자료구조에 저장
	std::shared_ptr<AnimationInfo> NewAnimation = std::make_shared<AnimationInfo>();
	Animations[_Paramter.AnimationName.data()] = NewAnimation;


	// 프레임 인덱스 입력시
	if (0 != _Paramter.FrameIndex.size())
	{
		NewAnimation->FrameIndex = _Paramter.FrameIndex;
	}

	// 프레임 인덱스 미 입력시
	else
	{
		//디폴트 인자인 경우엔 폴더의 0번 스프라이트 부터 시작
		if (-1 != _Paramter.Start)
		{
			if (_Paramter.Start < 0)
			{
				MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Paramter.AnimationName));
				return nullptr;
			}

			NewAnimation->StartFrame = _Paramter.Start;
		}
		//애니메이션 시작 위치를 직접 지정한 경우
		else
		{
			NewAnimation->StartFrame = 0;
		}


		//디폴트 인자인 경우엔 폴더의 마지막 스프라이트까지 애니메이션 재생
		if (-1 != _Paramter.End)
		{
			if (_Paramter.End >= Sprite->GetSpriteCount())
			{
				MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Paramter.AnimationName));
				return nullptr;
			}

			NewAnimation->EndFrame = _Paramter.End;
		}
		//애니메이션 마지막 위치를 직접 지정한 경우
		else
		{
			NewAnimation->EndFrame = Sprite->GetSpriteCount() - 1;
		}

		//예외처리
		if (NewAnimation->EndFrame < NewAnimation->StartFrame)
		{
			MsgAssert("애니메이션을 생성할때 End가 Start보다 클 수 없습니다");
			return nullptr;
		}


		NewAnimation->FrameIndex.reserve(NewAnimation->EndFrame - NewAnimation->StartFrame + 1);

		// StartFrame 부터 EndFrame까지 순서대로 FrameIndex에 푸시
		for (size_t i = NewAnimation->StartFrame; i <= NewAnimation->EndFrame; ++i)
		{
			NewAnimation->FrameIndex.push_back(i);
		}
	}



	// 타임 데이터가 있다면
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation->FrameTime = _Paramter.FrameTime;
	}

	// 타임 데이터가 없다면
	else
	{
		for (size_t i = 0; i < NewAnimation->FrameIndex.size(); ++i)
		{
			NewAnimation->FrameTime.push_back(_Paramter.FrameInter);
		}
	}



	NewAnimation->Sprite = Sprite;
	NewAnimation->Parent = this;
	NewAnimation->Loop = _Paramter.Loop;
	NewAnimation->ScaleToImage = _Paramter.ScaleToImage;

	return NewAnimation;
}



void GameEngineSpriteRenderer::ChangeAnimation(const std::string_view& _Name, size_t _Frame, bool _Force)
{
	//이미 재생중인 애니메이션이면서, 처음부터 재생이 아닌 경우엔 return
	std::shared_ptr<AnimationInfo> Find = FindAnimation(_Name);

	if (nullptr == Find)
	{
		MsgAssert("이러한 이름의 애니메이션은 존재하지 않습니다" + std::string(_Name));
		return;
	}


	if (CurAnimation.get() == Find.get() && false == _Force)
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


void GameEngineSpriteRenderer::Update(float _Delta)
{
	//애니메이션 용 Sprite인 경우
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_Delta);

		const SpriteInfo& Info = CurAnimation->CurSpriteInfo();

		GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
		AtlasData = Info.CutData;


		//애니메이션마다 크기를 설정해준 경우
		if (true == CurAnimation->ScaleToImage)
		{
			std::shared_ptr<GameEngineTexture> Texture = Info.Texture;
			float4 Scale = Texture->GetScale();

			Scale.x *= Info.CutData.SizeX;
			Scale.y *= Info.CutData.SizeY;
			Scale.z = 1.0f;

			Scale *= ScaleRatio;

			GetTransform()->SetLocalScale(Scale);
		}
	}
}


void GameEngineSpriteRenderer::Render(float _DeltaTime)
{
	//일반 이미지 Sprite인 경우
	GameEngineRenderer::Render(_DeltaTime);
}




void GameEngineSpriteRenderer::SetAnimationUpdateEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event)
{
	std::shared_ptr<AnimationInfo>  Info = FindAnimation(_AnimationName);

	if (nullptr == Info)
	{
		MsgAssert("존재하지 않는 애니메이션에 이벤트 세팅을 하려고 했습니다.");
	}

	Info->UpdateEventFunction[_Frame] = _Event;
}



void GameEngineSpriteRenderer::SetAnimationStartEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event)
{
	std::shared_ptr<AnimationInfo>  Info = FindAnimation(_AnimationName);

	if (nullptr == Info)
	{
		MsgAssert("존재하지 않는 애니메이션에 이벤트 세팅을 하려고 했습니다.");
	}

	Info->StartEventFunction[_Frame] = _Event;
}

std::string GameEngineSpriteRenderer::GetTexName()
{
	GameEngineTextureSetter* Tex = GetShaderResHelper().GetTextureSetter("DiffuseTex");
	std::string Name = Tex->Res->GetNameToString();
	return Name;
}

void GameEngineSpriteRenderer::SpriteRenderInit()
{
	SetPipeLine("2DTexture");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue);
}
