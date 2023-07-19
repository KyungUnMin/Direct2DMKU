#pragma once

//enum class ItemType
//{
//	Empty,
//
//};

class DataMgr
{
public:
	static const int PlayerFullPoint;

	DataMgr();
	~DataMgr();

	DataMgr(const DataMgr& _Other) = delete;
	DataMgr(DataMgr&& _Other) noexcept = delete;
	DataMgr& operator=(const DataMgr& _Other) = delete;
	DataMgr& operator=(const DataMgr&& _Other) noexcept = delete;

	//------------------HP---------------------------------

	static inline int GetPlayerHP()
	{
		return PlayerHp;
	}

	static inline void PlusPlayerHP(int _Value)
	{
		_Value = abs(_Value);
		PlayerHp += _Value;
		if (100 < PlayerHp)
		{
			PlayerHp = 100;
		}
	}

	static inline void MinusPlayerHP(int _Value)
	{
		_Value = abs(_Value);
		PlayerHp -= _Value;
		if (PlayerHp < 0)
		{
			PlayerHp = 0;
		}
	}

	static inline void SetPlayerHP(int _Value)
	{
		_Value = abs(_Value);
		PlayerHp = _Value;
		PlayerHp = std::clamp(PlayerHp, 0, 100);
	}

	//------------------MP---------------------------------

	static inline int GetPlayerMP()
	{
		return PlayerMp;
	}

	static inline void PlusPlayerMP(int _Value)
	{
		PlayerMp += _Value;
		if (100 < PlayerMp)
		{
			PlayerMp = 100;
		}
	}

	static inline void MinusPlayerMP(int _Value)
	{
		_Value = abs(_Value);
		PlayerMp -= _Value;
		if (PlayerMp < 0)
		{
			PlayerMp = 0;
		}
	}

	static inline void SetPlayerMP(int _Value)
	{
		PlayerMp = _Value;
		PlayerMp = std::clamp(PlayerMp, 0, 100);
	}

	//------------------Money---------------------------------

	static inline int GetPlayerMoney()
	{
		return PlayerMoney;
	}

	static inline void PlusPlayerMoney(int _Value)
	{
		_Value = abs(_Value);
		PlayerMoney += _Value;
		if (999999 < PlayerMoney)
		{
			PlayerMoney = 999999;
		}
	}

	static inline bool MinusPlayerMoney(int _Value)
	{
		_Value = abs(_Value);
		if ((PlayerMoney - _Value) < 0)
			return false;

		PlayerMoney -= _Value;
		return true;
	}

	static inline void SetPlayerMoney(int _Value)
	{
		_Value = abs(_Value);
		PlayerMoney = _Value;
		PlayerMoney = std::clamp(PlayerMoney, 0, 999999);
	}

	//------------------ATT---------------------------------

	static inline int GetPlayerAtt()
	{
		return PlayerAtt;
	}

	static inline void PlusPlayerAtt(int _Value)
	{
		_Value = abs(_Value);
		PlayerAtt += _Value;
	}

	static inline void MinusPlayerAtt(int _Value)
	{
		_Value = abs(_Value);
		PlayerAtt -= _Value;
		if (PlayerAtt < 0)
		{
			PlayerAtt = 0;
		}
	}

	//------------------Unbeatable(무적 여부)---------------------------------

	static bool IsUnbeatable;

	//------------------Speed---------------------------------

	static inline float GetPlayerSpeedPer()
	{
		return PlayerSpeedPer;
	}

	static inline void SetPlayerSpeedPer(float _Per)
	{
		if (_Per <= 0.f)
		{
			MsgAssert("플레이어 속력퍼센트를 음수로 설정할 수는 없습니다");
			return;
		}

		PlayerSpeedPer = _Per;
	}

	//------------------Level & EXP---------------------------------

private:
	static void PlayerLevelUp();

public:
	static void AddPlayerExp(int _Exp)
	{
		PlayerExp += _Exp;
		if (PlayerExp < PlayerFullPoint)
			return;

		PlayerLevelUp();
		PlayerExp %= PlayerFullPoint;
	}

	static inline int GetPlayerLevel()
	{
		return PlayerLevel;
	}

	static inline int GetPlayerExp()
	{
		return PlayerExp;
	}

	//콜백의 return값은 레벨업 이벤트 에서 삭제할 지에 대한 유무(true를 리턴하면 이벤트가 한번만 실행)
	static inline void PushLevelUpCallBack(std::function<bool(void)> _CallBack)
	{
		LevelUpCallBacks.emplace_back() = _CallBack;
	}



protected:

private:
	static int PlayerHp;
	static int PlayerMp;
	static int PlayerMoney;

	static float PlayerSpeedPer;
	static int PlayerAtt;

	static int PlayerLevel;
	static int PlayerExp;
	static std::list<std::function<bool(void)>> LevelUpCallBacks;

	//static std::vector<ItemType> Inventory;


};

