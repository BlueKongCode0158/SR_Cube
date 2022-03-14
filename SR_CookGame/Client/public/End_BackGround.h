#pragma once
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CEnd_BackGround final : public CUI
{
private:
	explicit CEnd_BackGround(LPDIRECT3DDEVICE9 pGaraphic_Device);
	explicit CEnd_BackGround(const CEnd_BackGround& rhs);
	virtual ~CEnd_BackGround() = default;
public:
	virtual HRESULT NativeConstruct_Prototype()		override;
	virtual HRESULT NativeConstruct(void* pArg)		override;
	virtual _int	Tick(_double TimeDelta)			override;
	virtual _int	Late_Tick(_double TimeDelta)	override;
	virtual HRESULT Render()						override;
private:
	CTexture*		m_pTextureCom	= nullptr;
private:
	HRESULT Add_Component();
public:
	static	CEnd_BackGround*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg) override;
	virtual void			Free() override;
};
END
