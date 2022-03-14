#include "stdafx.h"
#include "..\public\TPSCamera.h"
#include "GameInstance.h"


CTPSCamera::CTPSCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CCamera(pGraphic_Device)
{

}

CTPSCamera::CTPSCamera(const CTPSCamera & rhs)
	:CCamera(rhs)
{
}

HRESULT CTPSCamera::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTPSCamera::NativeConstruct(void * pArg)
{
	/* 순서 주의 */
	if (FAILED(Add_Component()))
	{
		return E_FAIL;
	}
	if (FAILED(__super::NativeConstruct(pArg)))
	{
		return E_FAIL;
	}

	return S_OK;
}

_int CTPSCamera::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CTPSCamera::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	return _int();
}

HRESULT CTPSCamera::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CTPSCamera::Add_Component()
{
	CTransform::TRANSFORMDESC TransformDesc;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.f);
	TransformDesc.fSpeedPerSec = 5.f;
	if (CGameObject::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransform), &TransformDesc))
	{
		return E_FAIL;
	}
	return S_OK;
}

CTPSCamera * CTPSCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTPSCamera* pInstance = new CTPSCamera(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed To Creating TPSCamera_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CCamera * CTPSCamera::Clone(void * pArg)
{
	CCamera* pInstance = new CTPSCamera(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed To Creating TPSCamera_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTPSCamera::Free()
{
	__super::Free();
}
