#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CPicking;
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
END

BEGIN(Client)
class CFood final : public CGameObject
{
public:
	enum FOODTYPE { HAMBURGER, BIBIMBAP, PIZZA, DRINKING, SOURCE, FOODEND };
public:
	typedef struct tagFOOD
	{
		FOODTYPE eType;
		_float3	 vPosition;
	}FOOD;
private:
	explicit CFood(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CFood(const CFood& rhs);
	virtual  ~CFood() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual _int	Tick(_double TimeDelta)		override;
	virtual _int Late_Tick(_double TimeDelta)	override;
	virtual HRESULT Render()					override;
private:
	CTexture*		m_pTextureCom	= nullptr;
	CRenderer*		m_pRendererCom	= nullptr;
	CTransform*		m_pTransformCom = nullptr;
	CVIBuffer_Cube*	m_pVIBufferCom	= nullptr;
private:
	FOOD			m_tFoodInfo;
	_float			m_fScale;
private:
	HRESULT Add_Component();
public:
	static CFood*			Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*	Clone(void* pArg)	override;
	virtual void			Free()				override;

};
END
