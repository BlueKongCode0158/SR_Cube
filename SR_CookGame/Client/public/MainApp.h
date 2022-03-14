#pragma once
#include "Base.h"

BEGIN(Engine)
class CRenderer;
class CPicking;
END

BEGIN(Client)
class CMainApp final : public CBase
{
private:
	explicit CMainApp();
	virtual  ~CMainApp() = default;
public:
	HRESULT NativeConstruct();
	_int	Tick(_double TimeDelta);
	HRESULT	Render();
private:
	HRESULT Add_Prototype_Component();
	HRESULT Add_Prototype_GameObject();
private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device	= nullptr;
	CRenderer*			m_pRendererCom		= nullptr;
	CPicking*			m_pPickingCom		= nullptr;
public:
	static CMainApp*	Create();
	virtual void		Free() override;
};
END

