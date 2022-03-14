#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CFoodIcon final : public CUI
{
private:
	explicit CFoodIcon(LPDIRECT3DDEVICE9 pGraphic_Deviece);
	explicit CFoodIcon(const CFoodIcon& rhs);
	virtual  ~CFoodIcon() = default;
public:
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual HRESULT NativeConstruct_Prototype(_uint iTypeNum) ;
	virtual _int	Tick(_double TimeDelta)		override;
	virtual _int	Late_Tick(_double TimeDelta)override;
	virtual HRESULT Render()					override;
private:
	CTexture*				m_pTextureCom = nullptr;
private:
	_uint	m_uiTextureNum;
private:
	HRESULT	Add_Component();
public:
	static	CFoodIcon*		Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iTypeNum);
	virtual CGameObject*	Clone(void* pArg = nullptr) override;
	virtual void			Free()						override;
};
END
