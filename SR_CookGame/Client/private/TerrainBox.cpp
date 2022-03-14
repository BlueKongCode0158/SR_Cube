#include "stdafx.h"
#include "..\public\TerrainBox.h"
#include "GameInstance.h"


CTerrainBox::CTerrainBox(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{

}

CTerrainBox::CTerrainBox(const CTerrainBox & rhs)
	:CGameObject(rhs)
{

}

HRESULT CTerrainBox::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTerrainBox::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
	{
		return E_FAIL;
	}
	if (FAILED(Add_Component()))
	{
		return E_FAIL;
	}

	m_pTransformCom->Set_Scale(1.f, 1.f, 8.f);

	if (nullptr != pArg)
	{
		memcpy(&m_WorldPosition, pArg, sizeof(POSITION));
		m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, *(reinterpret_cast<_float3*>(&m_WorldPosition)));
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 0.f, 0.f));
	}


	return S_OK;
}

_int CTerrainBox::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CTerrainBox::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_NONALPHA, this);

	return _int();
}

HRESULT CTerrainBox::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	CGameInstance* pGameinstance = GET_INSTANCE(CGameInstance);

	m_pGraphic_Device->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &pGameinstance->Get_Transform(D3DTS_VIEW));
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &pGameinstance->Get_Transform(D3DTS_PROJECTION));

	m_pTextureCom->SetUp_OnGraphic_Device(0, 0);

	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pVIBufferRailCom->Render_VIBuffer();
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CTerrainBox::Add_Component()
{
	if (__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Renderer"), TEXT("Com_Renderer"), reinterpret_cast<CComponent**>(&m_pRendererCom)))
	{
		return E_FAIL;
	}
	if (__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom)))
	{
		return E_FAIL;
	}
	if (__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_VIBuffer_Cube"), TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferRailCom)))
	{
		return E_FAIL;
	}
	if (__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_Rail"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom)))
	{
		return E_FAIL;
	}

	return S_OK;
}

CTerrainBox * CTerrainBox::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTerrainBox* pInstance = new CTerrainBox(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating TerrainBox_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTerrainBox::Clone(void * pArg)
{
	CGameObject* pInstance = new CTerrainBox(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating TerrainBox_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTerrainBox::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferRailCom);
}
