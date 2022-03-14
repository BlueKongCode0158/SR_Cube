#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)
class CStart_Button final : public CUI
{
private:
	explicit CStart_Button(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CStart_Button(const CStart_Button& rhs);
	virtual  ~CStart_Button() = default;
public:
	virtual HRESULT NativeConstruct_Prototype()		override;
	virtual HRESULT NativeConstruct(void* pArg)		override;
	virtual _int	Tick(_double TimeDelta)			override;
	virtual _int	Late_Tick(_double TimeDelta)	override;
	virtual HRESULT Render()						override;
public:
	static bool Start()
	{
		return m_bisStart;
	}
private:
	CTexture*		m_pTextureCom = nullptr;
	static bool		m_bisStart;
	_uint			m_uiTextureNum;
private:
	HRESULT	Add_Component();
public:
	static CStart_Button*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg) override;
	virtual void			Free() override;
};
END
