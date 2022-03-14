#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CTrash_Icon final : public CUI
{
private:
	explicit CTrash_Icon(LPDIRECT3DDEVICE9 pGraphic_Deviece);
	explicit CTrash_Icon(const CTrash_Icon& rhs);
	virtual  ~CTrash_Icon() = default;
public:
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual HRESULT NativeConstruct_Prototype();
	virtual _int	Tick(_double TimeDelta)		override;
	virtual _int	Late_Tick(_double TimeDelta)override;
	virtual HRESULT Render()					override;
private:
	CTexture*				m_pTextureCom = nullptr;
private:
	HRESULT	Add_Component();
public:
	static	CTrash_Icon*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg = nullptr) override;
	virtual void			Free()						override;
};
END
