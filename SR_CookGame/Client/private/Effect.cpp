#include "stdafx.h"
#include "..\public\Effect.h"
#include "GameInstance.h"

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CEffect::CEffect(const CEffect & rhs)
	:CGameObject(rhs)
{
}

HRESULT CEffect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEffect::NativeConstruct(void * pArg)
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
		memcpy(&m_tEffectDesc, pArg, sizeof(EFFECTDESC));
		m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, m_tEffectDesc.m_fPosition);
	}
	return S_OK;
}

_int CEffect::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_tEffectDesc.m_fFrame += 90.f*TimeDelta;

	if (m_tEffectDesc.m_fFrame > 90.f)
	{
		return OBJ_DEAD;
	}

	return _int();
}

_int CEffect::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	_matrix ViewMatrix, ViewMatrixInverse;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	ViewMatrix = pGameInstance->Get_Transform(D3DTS_VIEW);
	D3DXMatrixInverse(&ViewMatrixInverse, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_RIGHT, *reinterpret_cast<_float3*>(&ViewMatrixInverse.m[0][0]));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_UP, *reinterpret_cast<_float3*>(&ViewMatrixInverse.m[1][0]));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_LOOK, *reinterpret_cast<_float3*>(&ViewMatrixInverse.m[2][0]));

	Compute_CameraDistance(m_pTransformCom);

	RELEASE_INSTANCE(CGameInstance);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_ALPHA, this);

	return _int();
}

HRESULT CEffect::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_pGraphic_Device->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &pGameInstance->Get_Transform(D3DTS_VIEW));
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &pGameInstance->Get_Transform(D3DTS_PROJECTION));

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pTextureCom->SetUp_OnGraphic_Device(0, static_cast<_uint>(m_tEffectDesc.m_fFrame));
	m_pVIBufferCom->Render_VIBuffer();

	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CEffect::Add_Component()
{
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_Effect"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	{
		return E_FAIL;
	}

	CTransform::TRANSFORMDESC TransformDesc;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.f);
	TransformDesc.fSpeedPerSec = 5.f;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom),&TransformDesc)))
	{
		return E_FAIL;
	}
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

CEffect * CEffect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CEffect* pInstance = new CEffect(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating Effect_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CEffect::Clone(void * pArg)
{
	CGameObject* pInstance = new CEffect(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating Effect_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEffect::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);
}
