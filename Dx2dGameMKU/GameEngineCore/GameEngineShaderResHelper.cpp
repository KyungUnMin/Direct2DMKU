#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"


//이 ResHelper(주로 렌더러에 있는 헬퍼)에 있는 세터들에 인자로 받은 ResHelper의 세터를 옮긴다
void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBufferSetters)
	{
		ConstantBufferSetters.insert(Setter);
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& Setter : _ResHelper.TextureSetters)
	{
		TextureSetters.insert(Setter);
	}

	for (const std::pair<std::string, GameEngineSamplerSetter>& Setter : _ResHelper.SamplerSetters)
	{
		SamplerSetters.insert(Setter);
	}
}


//상수 버퍼 세터의 함수
void GameEngineConstantBufferSetter::Setting()
{
	//이번 프레임의 상수버퍼값 재갱신
	Res->ChangeData(CPUData, CPUDataSize);

	//이 세터의 주인인 쉐이더가 어떤 타입의 쉐이더인지 가져오기
	ShaderType Type = ParentShader->GetType();
	//쉐이더 타입에 따라 상수버퍼 BindPoint(슬롯)에 세팅
	switch (Type)
	{
	case ShaderType::None:
	{
		MsgAssert("어떤 쉐이더에 세팅될 지 알 수 없는 상수버퍼입니다");
		break;
	}
	case ShaderType::Vertex:
		Res->VSSetting(BindPoint);
		break;
	case ShaderType::Pixel:
		Res->PSSetting(BindPoint);
		break;
	default:
		break;
	}
}





void GameEngineTextureSetter::Setting()
{
	ShaderType Type = ParentShader->GetType();

	switch (Type)
	{
	case ShaderType::None:
	{
		MsgAssert("어떤 쉐이더에 세팅될지 알수 없는 텍스처 입니다.");
		break;
	}
	case ShaderType::Vertex:
	{
		Res->VSSetting(BindPoint);
		break;
	}
	case ShaderType::Pixel:
	{
		Res->PSSetting(BindPoint);
		break;
	}
	default:
		break;
	}

}


void GameEngineTextureSetter::Reset()
{
	ShaderType Type = ParentShader->GetType();

	switch (Type)
	{
	case ShaderType::None:
	{
		MsgAssert("어떤 쉐이더에 세팅될지 알수없는 상수버퍼 입니다.");
		break;
	}
	case ShaderType::Vertex:
	{
		Res->VSReset(BindPoint);
		break;
	}
	case ShaderType::Pixel:
	{
		Res->PSReset(BindPoint);
		break;
	}
	default:
		break;
	}
}




void GameEngineSamplerSetter::Setting()
{
	ShaderType Type = ParentShader->GetType();

	switch (Type)
	{
	case ShaderType::None:
	{
		MsgAssert("어떤 쉐이더에 세팅될지 알수없는 상수버퍼 입니다.");
		break;
	}
	case ShaderType::Vertex:
	{
		Res->VSSetting(BindPoint);
		break;
	}
	case ShaderType::Pixel:
	{
		Res->PSSetting(BindPoint);
		break;
	}
	default:
		break;
	}
}


//리소스 헬퍼의 함수
void GameEngineShaderResHelper::Setting()
{
	//상수버퍼세터 Setting 호출
	{
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator StartIter = ConstantBufferSetters.begin();
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator EndIter = ConstantBufferSetters.end();
		for (; (StartIter != EndIter); ++StartIter)
		{
			GameEngineConstantBufferSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}

	//텍스처 세터 Setting 호출
	{
		std::multimap<std::string, GameEngineTextureSetter>::iterator StartIter = TextureSetters.begin();
		std::multimap<std::string, GameEngineTextureSetter>::iterator EndIter = TextureSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineTextureSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}

	//샘플러 세터 Setting호출
	{
		std::multimap<std::string, GameEngineSamplerSetter>::iterator StartIter = SamplerSetters.begin();
		std::multimap<std::string, GameEngineSamplerSetter>::iterator EndIter = SamplerSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineSamplerSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}
}







void GameEngineShaderResHelper::SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSetters.find(UpperName);

	if (ConstantBufferSetters.end() == FindIter)
	{
		MsgAssert("존재하지 않는 상수버퍼를 세팅하려고 했습니다 : " + UpperName);
		return;
	}

	//찾은 값중 가장 앞쪽의 값
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter = ConstantBufferSetters.lower_bound(UpperName);

	//찾은 값중 가장 뒤쪽의 값
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter = ConstantBufferSetters.upper_bound(UpperName);

	//쉐이더 과정 중에서 해당 상수버퍼를 사용한 만큼 진행하게 될 것이다.
	//(해당 상수버퍼를 사용한 모든 쉐이더들에 상수버퍼 값이 변경된다는 말)
	for (; (NameStartIter != NameEndIter); ++NameStartIter)
	{
		GameEngineConstantBufferSetter& Setter = NameStartIter->second;

		if (Setter.Res->GetBufferSize() != _Size)
		{
			MsgAssert("상수버퍼와 세팅하려는 데이터의 크기가 다릅니다. 상수버퍼 : " + std::to_string(Setter.Res->GetBufferSize()) + "유저가 세팅한 데이터" + std::to_string(_Size) + UpperName);
			return;
		}

		Setter.CPUData = _Data;
		Setter.CPUDataSize = _Size;
	}

}




void GameEngineShaderResHelper::SetTexture(const std::string_view& _SettingName, std::shared_ptr<GameEngineTexture> _Texture)
{
	if (nullptr == _Texture)
	{
		MsgAssert("nullptr인 텍스처를 세팅하려고 했습니다." + std::string(_SettingName));
		return;
	}

	

	//해당 이름의 텍스처 버퍼를 쉐이더 파일에서 사용하는지 검사
	std::string UpperName = GameEngineString::ToUpper(_SettingName);
	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);
	if (TextureSetters.end() == FindIter)
	{
		MsgAssert("쉐이더에서 이런 이름의 텍스처 세팅를 사용하지 않았습니다." + UpperName);
		return;
	}

	//모든 쉐이더 텍스처 버퍼에 값 넣는다
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStartIter = TextureSetters.lower_bound(UpperName);
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEndIter = TextureSetters.upper_bound(UpperName);
	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineTextureSetter& Setter = NameStartIter->second;
		Setter.Res = _Texture;
	}
}



void GameEngineShaderResHelper::SetTexture(const std::string_view& _SettingName, const std::string_view& _ImageName)
{
	std::string UpperName = GameEngineString::ToUpper(_SettingName);
	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);

	if (TextureSetters.end() == FindIter)
	{
		MsgAssert("쉐이더에서 이런 이름의 텍스처 세팅을 사용하지 않았습니다: " + UpperName);
		return;
	}

	//찾은 값중 가장 앞쪽의 값
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStartIter = TextureSetters.lower_bound(UpperName);

	//찾은 값중 가장 뒤쪽의 값
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEndIter = TextureSetters.upper_bound(UpperName);


	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_ImageName);
	
	

	if (nullptr == FindTex)
	{
		std::string TexName = _ImageName.data();
		MsgAssert("이런 이름의 텍스처는 로드한 적이 없습니다: " + TexName);
		return;
	}

	//모두 변경
	for (; (NameStartIter != NameEndIter); ++NameStartIter)
	{
		GameEngineTextureSetter& Setter = NameStartIter->second;
		Setter.Res = FindTex;
	}

}




GameEngineTextureSetter* GameEngineShaderResHelper::GetTextureSetter(const std::string_view& _View)
{
	std::string UpperName = GameEngineString::ToUpper(_View);
	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);

	if (FindIter == TextureSetters.end())
		return nullptr;

	return &(FindIter->second);
}

std::vector<GameEngineTextureSetter*> GameEngineShaderResHelper::GetTextureSetters(const std::string_view& _View)
{
	std::string UpperName = GameEngineString::ToUpper(_View);
	std::multimap<std::string, GameEngineTextureSetter>::iterator FindIter = TextureSetters.find(UpperName);

	std::vector<GameEngineTextureSetter*> Result;
	if (FindIter == TextureSetters.end())
	{
		return Result;
	}

	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStartIter = TextureSetters.lower_bound(UpperName);
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEndIter = TextureSetters.upper_bound(UpperName);
	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		Result.push_back(&NameStartIter->second);
	}

	return Result;
}



void GameEngineShaderResHelper::AllResourcesReset()
{
	std::multimap<std::string, GameEngineTextureSetter>::iterator StartIter = TextureSetters.begin();
	std::multimap<std::string, GameEngineTextureSetter>::iterator EndIter = TextureSetters.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		GameEngineTextureSetter& Setter = StartIter->second;
		Setter.Reset();
	}
}
