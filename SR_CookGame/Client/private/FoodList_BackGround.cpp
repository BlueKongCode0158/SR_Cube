#include "stdafx.h"
#include "..\public\FoodList_BackGround.h"
#include "GameInstance.h"

CFoodList_BackGround::CFoodList_BackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CFoodList_BackGround::CFoodList_BackGround(const CFoodList_BackGround & rhs)
	: CUI(rhs)
{
}

HRESULT CFoodList_BackGround::NativeConstruct(void * pArg)
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

HRESULT CFoodList_BackGround::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

_int CFoodList_BackGround::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CFoodList_BackGround::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_UI, this);
	return _int();
}

HRESULT CFoodList_BackGround::Render()
{
	m_pTextureCom->SetUp_OnGraphic_Device(0, 0);

	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFoodList_BackGround::Add_Component()
{
	if (CGameObject::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_FoodICon_BackGround"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom)))
	{
		return E_FAIL;
	}
	return S_OK;
}

CFoodList_BackGround * CFoodList_BackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CFoodList_BackGround* pInstance = new CFoodList_BackGround(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating FoodList_BackGround_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFoodList_BackGround::Clone(void * pArg)
{
	CGameObject* pInstance = new CFoodList_BackGround(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating FoodList_BackGround_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFoodList_BackGround::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
}
