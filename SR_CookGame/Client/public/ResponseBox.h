#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
END

BEGIN(Client)
class CResponseBox final : public CGameObject
{
public:
	typedef struct tagPOSITION
	{
		_float3	m_worldPosition;
	}POSITION;
private:
	explicit CResponseBox(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CResponseBox(const CResponseBox& rhs);
	virtual  ~CResponseBox() = default;
public:
	virtual HRESULT NativeConstruct_Prototype()		override;
	virtual HRESULT NativeConstruct(void* pArg)		override;
	virtual _int	Tick(_double TimeDelta)			override;
	virtual _int	Late_Tick(_double TimeDelta)	override;
	virtual HRESULT Render()						override;
private:
	HRESULT Create_Food();
private:
	/* Member_º¯¼ö */
	CTexture*			m_pTextureCom	= nullptr;
	CRenderer*			m_pRendererCom	= nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CVIBuffer_Cube*		m_pVIBufferCom	= nullptr;
private:
	POSITION			m_WorldPosition;
	_float				m_fTime;
	_uint				m_dwCount;
private:
	HRESULT Add_Component();
public:
	static	CResponseBox*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg)	override;
	virtual void			Free()				override;
};
END
