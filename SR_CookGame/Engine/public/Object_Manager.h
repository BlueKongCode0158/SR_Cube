#pragma once

/* ��ü���� �������� ���ؿ� ���� �����Ͽ� �����ϳ�. */
/* �����������������Ѵ�. (����) */
#include "Base.h"

BEGIN(Engine)

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;
public:
	class CComponent* Get_ComponentPtr(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex);
	_uint	Get_GameObjectMapSize(_uint iLevelIndex, const _tchar* pLayerTag);
public:
	HRESULT Reserve_Container(_uint iNumLevel);
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject(_uint iLevelIndex, const _tchar* pPrototypeTag, const _tchar* pLayerTag, void* pArg = nullptr);
	_int Tick(_double TimeDelta);
	_int Late_Tick(_double TimeDelta);
	void Clear(_uint iLevelIndex);

private:
	map<const _tchar*, class CGameObject*>			m_Prototypes;
	typedef map<const _tchar*, class CGameObject*>	PROTOTYPES;
private:
	map<const _tchar*, class CLayer*>*			m_pLayers = nullptr;
	typedef map<const _tchar*, class CLayer*>	LAYERS;

private:
	_uint			m_iNumLevel = 0;

private:
	CGameObject* Find_Prototype(const _tchar* pPrototypeTag);
	CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);
public:
	virtual void Free() override;
};

END