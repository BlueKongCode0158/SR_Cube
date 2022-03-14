#include "stdafx.h"
#include "..\public\ItemCount.h"
#include "GameInstance.h"
#include "FoodList.h"

CItemCount::CItemCount(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CItemCount::CItemCount(const CItemCount & rhs)
	:CUI(rhs)
	,m_eType(rhs.m_eType)
{
}

HRESULT CItemCount::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
	{
		return E_FAIL;
	}
	if (FAILED(Add_Component()))
	{
		return E_FAIL;
	}

	m_uiCountNum = CFoodList::Get_Instance()->Get_FoodNum(m_eType);

	return S_OK;
}

HRESULT CItemCount::NativeConstruct_Prototype(CFood::FOODTYPE eType)
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	m_eType = eType;
	return S_OK;
}

_int CItemCount::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CItemCount::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	m_uiCountNum = CFoodList::Get_Instance()->Get_FoodNum(m_eType);
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_UI, this);
	return _int();
}

HRESULT CItemCount::Render()
{
	/* 여기 수정하기 */
	m_pTextureCom->SetUp_OnGraphic_Device(0,m_uiCountNum);

	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CItemCount::Add_Component()
{
	if (FAILED(CGameObject::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_ITemCount"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	{
		return E_FAIL;
	}

	return S_OK;
}

CItemCount * CItemCount::Create(LPDIRECT3DDEVICE9 pGraphic_Device, CFood::FOODTYPE eType)
{
	CItemCount* pInstance = new CItemCount(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype(eType)))
	{
		MSGBOX("Failed to Creating CItemCount_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CItemCount::Clone(void * pArg)
{
	CGameObject* pInstance = new CItemCount(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating CItemCount_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CItemCount::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
}
