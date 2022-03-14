#pragma once
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CLoading_BackGround final : public CUI
{
private:
	explicit CLoading_BackGround(LPDIRECT3DDEVICE9 pGaraphic_Device);
	explicit CLoading_BackGround(const CLoading_BackGround& rhs);
	virtual ~CLoading_BackGround() = default;
public:
	virtual HRESULT NativeConstruct_Prototype()		override;
	virtual HRESULT NativeConstruct(void* pArg)		override;
	virtual _int	Tick(_double TimeDelta)			override;
	virtual _int	Late_Tick(_double TimeDelta)	override;
	virtual HRESULT Render()						override;
public:
	static void Set_Num(int iNum)
	{
		m_iTexNum = iNum;
	}
private:
	CTexture*		m_pTextureCom		= nullptr;
	static int		m_iTexNum;
private:
	HRESULT Add_Component();
public:
	static	CLoading_BackGround*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg) override;
	virtual void			Free() override;
};
END
