#pragma once
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CClear_BackGround final : public CUI
{
private:
	explicit CClear_BackGround(LPDIRECT3DDEVICE9 pGaraphic_Device);
	explicit CClear_BackGround(const CClear_BackGround& rhs);
	virtual ~CClear_BackGround() = default;
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
	static	CClear_BackGround*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg) override;
	virtual void			Free() override;
};
END
