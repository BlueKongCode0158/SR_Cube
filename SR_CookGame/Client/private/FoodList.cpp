#include "stdafx.h"
#include "..\public\FoodList.h"


IMPLEMENT_SINGLETON(CFoodList)

CFoodList::CFoodList()
{
}

void CFoodList::Add_TrashNum()
{
	map<_uint, _uint>::iterator iter = m_FoodClear_Score.find(CFood::FOODTYPE::FOODEND);

	if (iter == m_FoodClear_Score.end())
	{
		return;
	}

	if (iter->second < 5)
	{
		iter->second += 1;
	}
}

int CFoodList::Sub_FoodScord(CFood::FOODTYPE eType)
{
	map<_uint, _uint>::iterator iter = m_FoodClear_Score.find(eType);

	if (m_FoodClear_Score.end() == iter)
	{
		return 0;
	}

	if (iter->second <= 0)
	{
		iter->second = 0;

		iter = m_FoodClear_Score.find(CFood::FOODTYPE::FOODEND);

		if (iter->second >= 5)
		{
			iter->second = 5;
		}
		else
		{
			iter->second += 1;
		}
	}
	else
	{
		iter->second -= 1;
	}
	return iter->second;
}

void CFoodList::Edit_FoodScore(CFood::FOODTYPE eType, _uint iNum)
{
	map<_uint, _uint>::iterator iter = m_FoodClear_Score.find(eType);

	if (m_FoodClear_Score.end() == iter)
	{
		return;
	}

	iter->second = iNum;
	return;

}

_uint CFoodList::Get_FoodNum(CFood::FOODTYPE eType)
{
	map<_uint, _uint>::iterator iter = m_FoodClear_Score.find(eType);

	if (m_FoodClear_Score.end() == iter)
	{
		return CFood::FOODEND;
	}
	return iter->second;
}

_uint CFoodList::Get_FoodType(_uint iNum)
{
	if (iNum >= CFood::FOODTYPE::FOODEND)
	{
		return CFood::FOODTYPE::FOODEND;
	}
	map<_uint, _uint>::iterator iter = m_FoodClear_Score.find(iNum);

	if (m_FoodClear_Score.end() == iter)
	{
		return CFood::FOODTYPE::FOODEND;
	}
	return iter->first;
}

bool CFoodList::GameClear()
{
	for (int i = 0; i < CFood::FOODTYPE::FOODEND; i++)
	{
		if (m_FoodClear_Score[i] != 0)
		{
			return false;
		}
	}
	return true;
}

bool CFoodList::GameOver()
{

	if (m_FoodClear_Score[CFood::FOODTYPE::FOODEND] >= 5)
	{
		return true;
	}
	return false;
}

void CFoodList::Free()
{
}
