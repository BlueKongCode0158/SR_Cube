#include "stdafx.h"
#include "..\public\SkyBox.h"
#include "GameInstance.h"

CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CSkyBox::CSkyBox(const CSkyBox & rhs)
	:CGameObject(rhs)
{
}

HRESULT CSkyBox::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSkyBox::NativeConstruct(void * pArg)
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

_int CSkyBox::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	return _int();
}

_int CSkyBox::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_matrix camViewMatrix, camInverseMatrix;
	camViewMatrix = pGameInstance->Get_Transform(D3DTS_VIEW);
	D3DXMatrixInverse(&camInverseMatrix, nullptr, &camViewMatrix);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, *reinterpret_cast<_float3*>(&camInverseMatrix.m[3][0]));

	RELEASE_INSTANCE(CGameInstance);


	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_PRIORITY, this);
	return _int();
}

HRESULT CSkyBox::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &pGameInstance->Get_Transform(D3DTS_VIEW));
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &pGameInstance->Get_Transform(D3DTS_PROJECTION));


	m_pTextureCom->SetUp_OnGraphic_Device(0,0);

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZWRITEENABLE, FALSE);

	m_pVIBufferCom->Render_VIBuffer();
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphic_Device->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZWRITEENABLE, TRUE);

	
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CSkyBox::Add_Component()
{
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
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_VIBuffer_Cube"), TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
	{
		return E_FAIL;
	}
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_SkyBox"), TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
	{
		return E_FAIL;
	}

	return S_OK;
}

CSkyBox * CSkyBox::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSkyBox* pInstance = new CSkyBox(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed To Creating SkyBox_Prototpye");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CSkyBox::Clone(void * pArg)
{
	CGameObject* pInstance = new CSkyBox(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed To Creating SkyBox_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSkyBox::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
