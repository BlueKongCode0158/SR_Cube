#include "stdafx.h"
#include "..\public\ResponseBox.h"
#include "GameInstance.h"
#include "Food.h"

CResponseBox::CResponseBox(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{

}

CResponseBox::CResponseBox(const CResponseBox & rhs)
	:CGameObject(rhs)
{

}

HRESULT CResponseBox::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CResponseBox::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
	{
		return E_FAIL;
	}
	if (FAILED(Add_Component()))
	{
		return E_FAIL;
	}
	if (nullptr != pArg)
	{
		memcpy(&m_WorldPosition, pArg, sizeof(POSITION));
		m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, *(reinterpret_cast<_float3*>(&m_WorldPosition)));
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 0.f, 10.f));
	}
	m_dwCount = ((rand() % 5) + 2);
	m_fTime = 0.f;
	return S_OK;
}

_int CResponseBox::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	
	m_fTime += TimeDelta;

	if (m_fTime > m_dwCount)
	{
		if (FAILED(Create_Food()))
		{
			return E_FAIL;
		}
	}
	
	//m_pTransformCom->Rotation_Axis(_float3(1.f, 0.f, 0.f), TimeDelta);
	
	return _int();
}

_int CResponseBox::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_NONALPHA, this);
	return _int();
}

HRESULT CResponseBox::Render()
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


	//m_pGraphic_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//m_pGraphic_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pVIBufferCom->Render_VIBuffer();
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//m_pGraphic_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	//m_pGraphic_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CResponseBox::Create_Food()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CFood::FOOD tFood;
	int iRand = (rand() % CFood::FOODTYPE::FOODEND);

	switch (iRand)
	{
	case CFood::FOODTYPE::HAMBURGER:
		tFood.eType = CFood::FOODTYPE::HAMBURGER;
		break;
	case CFood::FOODTYPE::BIBIMBAP:
		tFood.eType = CFood::FOODTYPE::BIBIMBAP;
		break;
	case CFood::FOODTYPE::PIZZA:
		tFood.eType = CFood::FOODTYPE::PIZZA;
		break;
	case CFood::FOODTYPE::DRINKING:
		tFood.eType = CFood::FOODTYPE::DRINKING;
		break;
	case CFood::FOODTYPE::SOURCE:
		tFood.eType = CFood::FOODTYPE::SOURCE;
		break;
	default:
		break;
	}

	tFood.vPosition = m_pTransformCom->Get_State(CTransform::STATE::STATE_POSITION);

	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_Food"), TEXT("Layer_Food"), &tFood)))
	{
		return E_FAIL;
	}

	m_dwCount = ((rand() % 5) + 2);
	m_fTime = 0.f;

	RELEASE_INSTANCE(CGameInstance);
	
	return E_NOTIMPL;
}

HRESULT CResponseBox::Add_Component()
{
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_ResponeBox"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	{
		return E_FAIL;
	}
	
	CTransform::TRANSFORMDESC TrasformDesc;
	TrasformDesc.fRotationPerSec = D3DXToRadian(90.f);
	TrasformDesc.fSpeedPerSec = 5.f;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TrasformDesc)))
	{
		return E_FAIL;
	}
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_VIBuffer_Cube"), TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
	{
		return E_FAIL;
	}
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Renderer"), TEXT("Com_Renderer"), reinterpret_cast<CComponent**>(&m_pRendererCom))))
	{
		return E_FAIL;
	}

	return S_OK;
}

CResponseBox * CResponseBox::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CResponseBox* pInstance = new CResponseBox(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CResponseBox_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CResponseBox::Clone(void * pArg)
{
	CGameObject* pInstance = new CResponseBox(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating CResponseBox_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CResponseBox::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}	
