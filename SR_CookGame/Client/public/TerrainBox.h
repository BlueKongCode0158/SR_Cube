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
class CTerrainBox final : public CGameObject
{
public:
	typedef struct tagPOSITION
	{
		_float3	m_worldPosition;
	}POSITION;
private:
	explicit CTerrainBox(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTerrainBox(const CTerrainBox& rhs);
	virtual ~CTerrainBox() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual _int	Tick(_double TimeDelta) override;
	virtual _int	Late_Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;
private:
	CTexture*		m_pTextureCom		= nullptr;
	CRenderer*		m_pRendererCom		= nullptr;
	CTransform*		m_pTransformCom		= nullptr;
	CVIBuffer_Rect*	m_pVIBufferRailCom	= nullptr;
private:
	POSITION		m_WorldPosition;
public:
	HRESULT Add_Component();
public:
	static	CTerrainBox*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg) override;
	virtual void			Free() override;
};
END

