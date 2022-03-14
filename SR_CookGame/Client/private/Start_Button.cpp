#include "stdafx.h"
#include "..\public\Start_Button.h"
#include "GameInstance.h"


bool CStart_Button::m_bisStart = false;
CStart_Button::CStart_Button(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{

}

CStart_Button::CStart_Button(const CStart_Button & rhs)
	:CUI(rhs)
{

}

HRESULT CStart_Button::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CStart_Button::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
	{
		return E_FAIL;
	}
	if (FAILED(Add_Component()))
	{
		return E_FAIL;
	}
	return S_OK;
}

_int CStart_Button::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	POINT pt{};
	
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rc = {
		m_tUIDesc.m_fX - (m_tUIDesc.m_fSizeX *0.5f),
		m_tUIDesc.m_fY - (m_tUIDesc.m_fSizeY*0.5f),
		m_tUIDesc.m_fX + (m_tUIDesc.m_fSizeX *0.5f),
		m_tUIDesc.m_fY + (m_tUIDesc.m_fSizeY*0.5f) };

	if (PtInRect(&rc, pt))
	{
		m_uiTextureNum = 1; 
		m_bisStart = true;
	}
	else
	{
		m_uiTextureNum = 0;
		m_bisStart = false;
	}

	return _int();
}

_int CStart_Button::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);
	
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_UI, this);
	return _int();
}

HRESULT CStart_Button::Render()
{
	m_pTextureCom->SetUp_OnGraphic_Device(0,m_uiTextureNum);

	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStart_Button::Add_Component()
{
	if (FAILED(CGameObject::Add_Component(LEVEL_LOGO, TEXT("Prototype_Start_Button_Texture"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	{
		return E_FAIL;
	}
	return S_OK;
}

CStart_Button * CStart_Button::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CStart_Button* pInstance = new CStart_Button(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating Start_Button_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CStart_Button::Clone(void * pArg)
{
	CStart_Button* pInstance = new CStart_Button(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating Start_Button_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStart_Button::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
}
