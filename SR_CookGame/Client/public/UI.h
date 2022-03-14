#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)
class CUI : public CGameObject 
{
public:
	typedef struct tagUIDESC
	{
		_float m_fX;
		_float m_fY;
		_float m_fSizeX;
		_float m_fSizeY;
	}UIDESC;
protected:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CUI(const CUI& rhs);
	virtual ~CUI() = default;
public:
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual _int	Tick(_double TimeDelta)		override;
	virtual _int	Late_Tick(_double TimeDelta)override;
	virtual HRESULT Render()					override;
protected:
	UIDESC			m_tUIDesc;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;
	CRenderer*		m_pRendererCom = nullptr;
	_matrix			m_ProjMatrix;
protected:
	HRESULT Add_Component();
public:
	virtual CGameObject*	Clone(void* pArg = nullptr)PURE;
	virtual void			Free();
};
END

