#include "stdafx.h"
#include "..\public\FoodIcon.h"
#include "GameInstance.h"
#include "FoodList.h"

CFoodIcon::CFoodIcon(LPDIRECT3DDEVICE9 pGraphic_Deviece)
	:CUI(pGraphic_Deviece)
{
}

CFoodIcon::CFoodIcon(const CFoodIcon & rhs)
	:CUI(rhs)
	,m_uiTextureNum(rhs.m_uiTextureNum)
{
}

HRESULT CFoodIcon::NativeConstruct(void * pArg)
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

HRESULT CFoodIcon::NativeConstruct_Prototype(_uint iTypeNum)
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}

	if (iTypeNum == 0)
	{
		m_uiTextureNum = (CFoodList::Get_Instance()->Get_FoodType(iTypeNum));
	}
	else if (iTypeNum == 1)
	{
		m_uiTextureNum = (CFoodList::Get_Instance()->Get_FoodType(iTypeNum));
	}
	else if (iTypeNum == 2)
	{
		m_uiTextureNum = (CFoodList::Get_Instance()->Get_FoodType(iTypeNum));
	}
	else if (iTypeNum == 3)
	{
		m_uiTextureNum = (CFoodList::Get_Instance()->Get_FoodType(iTypeNum));
	}
	else if (iTypeNum == 4)
	{
		m_uiTextureNum = (CFoodList::Get_Instance()->Get_FoodType(iTypeNum));
	}


	return S_OK;
}

_int CFoodIcon::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CFoodIcon::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_UI, this);
	return _int();
}

HRESULT CFoodIcon::Render()
{
	/* 순서 주의 */
	m_pTextureCom->SetUp_OnGraphic_Device(0, m_uiTextureNum);
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFoodIcon::Add_Component()
{
	if (CGameObject::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_FoodIcon"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom)))
	{
		return E_FAIL;
	}
	return S_OK;
}

CFoodIcon * CFoodIcon::Create(LPDIRECT3DDEVICE9 pGraphic_Device,_uint iTypeNum)
{
	CFoodIcon* pInstance = new CFoodIcon(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype(iTypeNum)))
	{
		MSGBOX("Failed to Creating FoodIcon_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFoodIcon::Clone(void * pArg)
{
	CGameObject* pInstance = new CFoodIcon(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating FoodIcon_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFoodIcon::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
}
