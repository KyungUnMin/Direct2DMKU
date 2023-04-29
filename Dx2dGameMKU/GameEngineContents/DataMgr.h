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

	static inline int GetPlayerHP()
	{
		return PlayerHp;
	}

	static inline void PlusPlayerHP(int _Value)
	{
		PlayerHp += _Value;
		if (100 < PlayerHp)
		{
			PlayerHp = 100;
		}
	}

	static inline void MinusPlayerHP(int _Value)
	{
		PlayerHp -= _Value;
		if (PlayerHp < 0)
		{
			PlayerHp = 0;
		}
	}

	static inline void SetPlayerHP(int _Value)
	{
		PlayerHp = _Value;
		PlayerHp = std::clamp(PlayerHp, 0, 100);
	}

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

protected:

private:
	static int PlayerHp;
	static int PlayerMp;

	//static std::vector<ItemType> Inventory;


};

