#pragma once
#include "Client_Defines.h"
#include "Base.h"
#include "Food.h"

BEGIN(Client)
class CFoodList final: public CBase 
{
	DECLARE_SINGLETON(CFoodList)
private:
	explicit CFoodList();
	virtual  ~CFoodList() = default;
public:
	void	Add_FoodScore(_uint eType, _uint iNum)
	{
		m_FoodClear_Score.emplace(eType, iNum);
	};
	_uint	Get_MapSize()
	{
		return m_FoodClear_Score.size();
	}
	_uint Get_FoodType(_uint iNum);
	bool	GameClear();
	bool	GameOver();
public:
	void	Add_TrashNum();
	int 	Sub_FoodScord(CFood::FOODTYPE eType);
	void	Edit_FoodScore(CFood::FOODTYPE eType, _uint iNum);
	_uint	Get_FoodNum(CFood::FOODTYPE eType);
private:
	map<_uint, _uint>		m_FoodClear_Score;
private:
	virtual void Free() override;
};
END

