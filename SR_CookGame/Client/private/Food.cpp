#include "stdafx.h"
#include "..\public\Food.h"
#include "GameInstance.h"
#include "FoodList.h"
#include "Effect.h"

CFood::CFood(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{

}

CFood::CFood(const CFood & rhs)
	:CGameObject(rhs)
{

}

HRESULT CFood::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFood::NativeConstruct(void * pArg)
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
		memcpy(&m_tFoodInfo, pArg, sizeof(FOOD));

		m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, m_tFoodInfo.vPosition);
	}
	else
	{
		MSGBOX("Food Information is NullSpace");
	}
	m_pTransformCom->Set_Scale(1.f, 0.5f, 1.f);

	_float3 vPostion = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	vPostion.y -= 0.25f;
	m_fScale = 1.f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPostion);

	return S_OK;
}

_int CFood::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	if (true == m_pTransformCom->Get_DeadState())
	{
		 CFoodList::Get_Instance()->Sub_FoodScord(m_tFoodInfo.eType);

		 CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		 CEffect::EFFECTDESC EffectDesc;
		 EffectDesc.m_fFrame = 0.f;
		 EffectDesc.m_fPosition = m_pTransformCom->Get_State(CTransform::STATE::STATE_POSITION);
		 if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_Effect"), TEXT("Layer_Effect"), &EffectDesc)))
		 {
			 RELEASE_INSTANCE(CGameInstance)
			 return CGameObject::STATE::OBJ_DEAD;
		 }

		 RELEASE_INSTANCE(CGameInstance)
		return CGameObject::STATE::OBJ_DEAD;
	}

	_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE::STATE_POSITION);

	if (vPosition.z < -2.3f)
	{
		m_pTransformCom->Rotation_Axis(_float3(-1.f, 0.f, 0.f), TimeDelta);

		m_fScale -= 0.015f;

		_float3 fScale = m_pTransformCom->Get_Scale();

		m_pTransformCom->Set_Scale(m_fScale, m_fScale, m_fScale);

		if (fScale.x < 0.15f)
		{
			return CGameObject::STATE::OBJ_DEAD;
		}
	}

	m_pTransformCom->Back_Straight(TimeDelta);




	return CGameObject::STATE::OBJ_NOEVENT;
}

_int CFood::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDERGROUP::RENDER_NONALPHA, this);
	return _int();
}

HRESULT CFood::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_pGraphic_Device->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &pGameInstance->Get_Transform(D3DTS_VIEW));
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &pGameInstance->Get_Transform(D3DTS_PROJECTION));

	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pTextureCom->SetUp_OnGraphic_Device(0, m_tFoodInfo.eType);
	m_pVIBufferCom->Render_VIBuffer();
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CFood::Add_Component()
{
	CTransform::TRANSFORMDESC TrasformDesc;
	TrasformDesc.fRotationPerSec = D3DXToRadian(148.f);
	TrasformDesc.fSpeedPerSec = 3.1f;

	if (__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Transform"), TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom),&TrasformDesc))
	{
		return E_FAIL;
	}
	if (__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Renderer"), TEXT("Com_Renderer"), reinterpret_cast<CComponent**>(&m_pRendererCom)))
	{
		return E_FAIL;
	}
	if (__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_FoodBox"), TEXT("Com_Textrue"), reinterpret_cast<CComponent**>(&m_pTextureCom)))
	{
		return E_FAIL;
	}
	if (__super::Add_Component(LEVEL_GAMEPLAY0, TEXT("Prototype_VIBuffer_Cube"), TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom)))
	{
		return E_FAIL;
	}

	return S_OK;
}

CFood * CFood::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CFood* pInstance = new CFood(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating Food_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFood::Clone(void * pArg)
{
	CGameObject* pInstance = new CFood(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating Food_Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFood::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
}
