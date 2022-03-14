#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
public:
	enum STATE { OBJ_NOEVENT, OBJ_ATTACK, OBJ_RUN, OBJ_WALK, OBJ_DEAD, OBJ_END };

protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;

public:
	HRESULT Add_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, const _tchar * pComponentTag, class CComponent** ppOut, void* pArg = nullptr);
	class CComponent* Get_ComponentPtr(const _tchar* pComponentTag);
public:
	_float Get_Distance()
	{
		return m_fCamDistance;
	}
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual _int Tick(_double TimeDelta);
	virtual _int Late_Tick(_double TimeDelta);
	virtual HRESULT Render();
public:
	void Compute_CameraDistance(class CTransform* pTransform);
protected:
	LPDIRECT3DDEVICE9			m_pGraphic_Device	= nullptr;
	_float						m_fCamDistance		= 0.f;
protected:
	map<const _tchar*, class CComponent*>			m_Components;
	typedef map<const _tchar*, class CComponent*>	COMPONENTS;

private:
	CComponent* Find_Component(const _tchar* pComponentTag);
public:
	virtual CGameObject* Clone(void* pArg = nullptr) = 0;
	virtual void Free();
};

END