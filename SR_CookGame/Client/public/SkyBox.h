#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CVIBuffer_Cube;
class CTransform;
END

BEGIN(Client)
class CSkyBox final : public CGameObject
{
private:
	explicit CSkyBox(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CSkyBox(const CSkyBox& rhs);
	virtual  ~CSkyBox() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual _int Tick(_double TimeDelta)		override;
	virtual _int Late_Tick(_double TimeDelta)	override;
	virtual HRESULT Render()					override;
private:
	CTexture*		m_pTextureCom	= nullptr;
	CRenderer*		m_pRendererCom	= nullptr;
	CTransform*		m_pTransformCom = nullptr;
	CVIBuffer_Cube*	m_pVIBufferCom	= nullptr;
private:
	HRESULT Add_Component();
public:
	static	CSkyBox*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg) override;
	virtual void			Free() override;

};
END
