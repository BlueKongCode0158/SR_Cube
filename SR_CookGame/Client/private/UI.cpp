#include "stdafx.h"
#include "..\public\UI.h"
#include "GameInstance.h"

CUI::CUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{

}

CUI::CUI(const CUI & rhs)
	:CGameObject(rhs)
{

}

HRESULT CUI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
	{
		return E_FAIL;
	}

	if (nullptr != pArg)
	{
		memcpy(&m_tUIDesc, pArg, sizeof(UIDESC));
	}
	else
	{
		MSGBOX("Failed Copy UI");
		return E_FAIL;
	}

	if (FAILED(Add_Component()))
	{
		return E_FAIL;
	}
	D3DXMatrixIdentity(&m_ProjMatrix);
	D3DXMatrixOrthoLH(&m_ProjMatrix, g_nWinCX, g_nWinCY, 0.f, 1.f);

	return S_OK;
}

HRESULT CUI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

_int CUI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	return _int();
}

_int CUI::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	return _int();
}

HRESULT CUI::Render()
{
	_matrix TransformMatrix, ViewMatrix;
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	
	D3DXMatrixIdentity(&TransformMatrix);
	D3DXMatrixIdentity(&ViewMatrix);
	TransformMatrix._11 = m_tUIDesc.m_fSizeX;
	TransformMatrix._22 = m_tUIDesc.m_fSizeY;

	TransformMatrix._41 =  m_tUIDesc.m_fX	- (g_nWinCX >> 1);
	TransformMatrix._42 = -m_tUIDesc.m_fY	+ (g_nWinCY >> 1);

	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &TransformMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, /*0 ~ 255*/1);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pVIBufferCom->Render_VIBuffer();
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	return S_OK;
}

HRESULT CUI::Add_Component()
{
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Renderer"), TEXT("Com_Renderer"), reinterpret_cast<CComponent**>(&m_pRendererCom))))
	{
		return E_FAIL;
	}
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_VIBuffer_Rect"), TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CUI::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);
}
