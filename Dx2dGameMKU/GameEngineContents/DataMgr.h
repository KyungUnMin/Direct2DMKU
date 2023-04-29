#pragma once

enum class ItemType
{
	Empty,

};

class DataMgr
{
public:
	static const int PlayerFullHp;

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

protected:

private:
	static int PlayerHp;
	static std::vector<ItemType> Inventory;


};

