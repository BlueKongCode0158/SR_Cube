#include "stdafx.h"
#include "..\public\End_BackGround.h"
#include "GameInstance.h"

CEnd_BackGround::CEnd_BackGround(LPDIRECT3DDEVICE9 pGaraphic_Device)
	:CUI(pGaraphic_Device)
{

}

CEnd_BackGround::CEnd_BackGround(const CEnd_BackGround & rhs)
	:CUI(rhs)
{

}

HRESULT CEnd_BackGround::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEnd_BackGround::NativeConstruct(void * pArg)
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

_int CEnd_BackGround::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CEnd_BackGround::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_UI, this);

	return _int();
}

HRESULT CEnd_BackGround::Render()
{
	m_pTextureCom->SetUp_OnGraphic_Device(0, 0);
	
	/* 순서 중요 */
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEnd_BackGround::Add_Component()
{
	if (FAILED(CGameObject::Add_Component(LEVEL_STATIC, TEXT("Prototype_GameOver_Texture"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	{
		return E_FAIL;
	}
	return S_OK;
}

CEnd_BackGround * CEnd_BackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CEnd_BackGround* pInstance = new CEnd_BackGround(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating BackGround_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CEnd_BackGround::Clone(void * pArg)
{
	CGameObject* pInstance = new CEnd_BackGround(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating BackGround_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEnd_BackGround::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
}
