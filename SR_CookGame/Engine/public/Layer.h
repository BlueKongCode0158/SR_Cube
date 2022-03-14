
#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CLayer final : public CBase
{
private:
	CLayer();
	virtual ~CLayer() = default;
public:
	_uint Get_listSize()
	{
		return m_Objects.size();
	}
	class CComponent* Get_ComponentPtr(const _tchar* pComponentTag, _uint iIndex);
public:
	HRESULT NativeConstruct();
	HRESULT Add_GameObject(CGameObject* pGameObject);
	_int Tick(_double TimeDelta);
	_int Late_Tick(_double TimeDelta);

private:
	list<class CGameObject*>		m_Objects;

public:
	static CLayer* Create();
	virtual void Free() override;
};

END