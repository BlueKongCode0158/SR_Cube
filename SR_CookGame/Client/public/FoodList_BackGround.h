#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CFoodList_BackGround final : public CUI
{
private:
	explicit CFoodList_BackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CFoodList_BackGround(const CFoodList_BackGround& rhs);
	virtual  ~CFoodList_BackGround() = default;
public:
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual _int	Tick(_double TimeDelta)		override;
	virtual _int	Late_Tick(_double TimeDelta)override;
	virtual HRESULT Render()					override;
private:
	CTexture*		m_pTextureCom				= nullptr;
private:
	HRESULT Add_Component();
public:
	static CFoodList_BackGround*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*			Clone(void* pArg = nullptr) override;
	virtual void					Free()						override;

};
END
