#include "stdafx.h"
#include "..\public\Player.h"
#include "GameInstance.h"
#include "FoodList.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{

}

CPlayer::CPlayer(const CPlayer& rhs)
	:CGameObject(rhs)
{

}

HRESULT CPlayer::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayer::NativeConstruct(void * pArg)
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

_int CPlayer::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	// TEST
	//if (GetAsyncKeyState('H') & 0x0001)
	//{
	//	CFoodList::Get_Instance()->Edit_FoodScore(CFood::FOODTYPE::SOURCE, 2);
	//}

	return _int();
}

_int CPlayer::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		_uint ilistSize = pGameInstance->Get_GameObjectMapSize(LEVEL_GAMEPLAY0, TEXT("Layer_Food"));

		for (_uint iSize = 0; iSize < ilistSize; iSize++)
		{
			CTransform* pTransform = reinterpret_cast<CTransform*>(pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY0, TEXT("Layer_Food"), TEXT("Com_Transform"), iSize));
			CVIBuffer_Cube* pVIBuffer = reinterpret_cast<CVIBuffer_Cube*>(pGameInstance->Get_ComponentPtr(LEVEL_GAMEPLAY0, TEXT("Layer_Food"), TEXT("Com_VIBuffer"), iSize));
			if (nullptr != m_pPickingCom->Compute_PickingPoint(pVIBuffer, *pTransform->Get_WorldMatrix()))
			{
				pTransform->Set_DeadState(true);
				//MSGBOX("Ãæµ¹");
			}
		}

		RELEASE_INSTANCE(CGameInstance);
	}
	return _int();
}

HRESULT CPlayer::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayer::Add_Component()
{
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Picking"), TEXT("Com_Picking"), reinterpret_cast<CComponent**>(&m_pPickingCom))))
	{
		return E_FAIL;
	}
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Renderer"), TEXT("Com_Renderer"), reinterpret_cast<CComponent**>(&m_pRendererCom))))
	{
		return E_FAIL;
	}
	return S_OK;
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer* pInstance = new CPlayer(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CPlayer_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CPlayer::Clone(void * pArg)
{
	CGameObject* pInstance = new CPlayer(*this);
	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating CPlayer_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pPickingCom);
	Safe_Release(m_pRendererCom);
}
