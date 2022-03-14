#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)
class CEffect final : public CGameObject
{
public:
	typedef struct tagEffect
	{
		_float	m_fFrame;
		_float3 m_fPosition;
	}EFFECTDESC;
private:
	explicit CEffect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CEffect(const CEffect& rhs);
	virtual  ~CEffect() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg)	override;
	virtual _int Tick(_double TimeDelta)		override;
	virtual _int Late_Tick(_double TimeDelta)	override;
	virtual HRESULT Render()					override;
private:
	CTexture*		m_pTextureCom	= nullptr;
	CRenderer*		m_pRendererCom	= nullptr;
	CTransform*		m_pTransformCom = nullptr;
	CVIBuffer_Rect*	m_pVIBufferCom	= nullptr;
private:
	EFFECTDESC m_tEffectDesc;
private:
	HRESULT Add_Component();
public:
	static	CEffect*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg)		override;
	virtual void			Free()					override;
};
END
