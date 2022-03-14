#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Food.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CItemCount final : public CUI
{
private:
	explicit CItemCount(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CItemCount(const CItemCount& rhs);
	virtual	 ~CItemCount() = default;
public:
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual HRESULT NativeConstruct_Prototype(CFood::FOODTYPE eType);
	virtual _int	Tick(_double TimeDelta)		override;
	virtual _int	Late_Tick(_double TimeDelta)override;
	virtual HRESULT Render()					override;
private:
	CTexture*		m_pTextureCom	= nullptr;
private:
	CFood::FOODTYPE m_eType;
	_uint			m_uiCountNum;
private:
	HRESULT Add_Component();
public:
	static CItemCount*				Create(LPDIRECT3DDEVICE9 pGraphic_Device, CFood::FOODTYPE eType);
	virtual CGameObject*			Clone(void* pArg = nullptr) override;
	virtual void					Free()						override;

};
END
