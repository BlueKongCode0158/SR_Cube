#include "stdafx.h"
#include "..\public\Trash_Icon.h"
#include "GameInstance.h"
#include "FoodList.h"

CTrash_Icon::CTrash_Icon(LPDIRECT3DDEVICE9 pGraphic_Deviece)
	:CUI(pGraphic_Deviece)
{
}

CTrash_Icon::CTrash_Icon(const CTrash_Icon & rhs)
	:CUI(rhs)
{
}

HRESULT CTrash_Icon::NativeConstruct(void * pArg)
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

HRESULT CTrash_Icon::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}

	return S_OK;
}

_int CTrash_Icon::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CTrash_Icon::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_UI, this);
	return _int();
}

HRESULT CTrash_Icon::Render()
{
	/* 순서 주의 */
	m_pTextureCom->SetUp_OnGraphic_Device(0, 0);
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTrash_Icon::Add_Component()
{
	if (CGameObject::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_Trash"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom)))
	{
		return E_FAIL;
	}
	return S_OK;
}

CTrash_Icon * CTrash_Icon::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTrash_Icon* pInstance = new CTrash_Icon(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating FoodIcon_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTrash_Icon::Clone(void * pArg)
{
	CGameObject* pInstance = new CTrash_Icon(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating FoodIcon_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTrash_Icon::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
}
