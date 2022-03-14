#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CPicking;
class CRenderer;
END

BEGIN(Client)
class CPlayer final : public CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual _int	Tick(_double TimeDelta) override;
	virtual _int	Late_Tick(_double TimeDelta) override;
	virtual HRESULT	Render() override;
private:
	CPicking*		m_pPickingCom	= nullptr;
	CRenderer*		m_pRendererCom	= nullptr;
private:
	HRESULT	Add_Component();
public:
	static	CPlayer*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg) override;
	virtual void			Free() override;
};
END

