#include "stdafx.h"
#include "Level_PlayStage.h"
#include "GameInstance.h"
#include "Camera.h"
#include "ResponseBox.h"
#include "TerrainBox.h"
#include "SkyBox.h"
#include "UI.h"
#include "FoodList.h"
#include "Clear_BackGround.h"
#include "Level_Clear.h"
#include "Level_End.h"
#include "FoodList.h"
#include "Level_Loading.h"
#include "SoundMgr.h"

CLevel_PlayStage::CLevel_PlayStage(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{

}

HRESULT CLevel_PlayStage::NativeConstruct()
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Play_Background.mp3");

	if (FAILED(__super::NativeConstruct()))
	{
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
	{
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
	{
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_ResponeseBox(TEXT("Layer_ResponeseBox"))))
	{
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
	{
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_UI(TEXT("Layer_UI"))))
	{
		return E_FAIL;
	}

	CFoodList::Get_Instance()->Edit_FoodScore(CFood::FOODTYPE::HAMBURGER,5);
	CFoodList::Get_Instance()->Edit_FoodScore(CFood::FOODTYPE::BIBIMBAP, 5);
	CFoodList::Get_Instance()->Edit_FoodScore(CFood::FOODTYPE::PIZZA,	 5);
	CFoodList::Get_Instance()->Edit_FoodScore(CFood::FOODTYPE::DRINKING, 5);
	CFoodList::Get_Instance()->Edit_FoodScore(CFood::FOODTYPE::SOURCE,	 5);
	CFoodList::Get_Instance()->Edit_FoodScore(static_cast<CFood::FOODTYPE>(TRASH), 0);

	return S_OK;
}

_int CLevel_PlayStage::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	if (true == CFoodList::Get_Instance()->GameClear())
	{
		if (SUCCEEDED(pGameInstance->SetUp_Level(CLevel_Clear::Create(m_pGraphic_Device))))
		{
			pGameInstance->Clear(LEVEL_GAMEPLAY0);
			goto succeeded;
		}
	}
	else if (true == CFoodList::Get_Instance()->GameOver())
	{
		if (SUCCEEDED(pGameInstance->SetUp_Level(CLevel_End::Create(m_pGraphic_Device))))
		{
			pGameInstance->Clear(LEVEL_GAMEPLAY0);
			goto succeeded;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
	return -1;
succeeded:
	RELEASE_INSTANCE(CGameInstance);
	return _int();
}

HRESULT CLevel_PlayStage::Render()
{
	__super::Render();

	return S_OK;
}

HRESULT CLevel_PlayStage::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	
	CCamera::CAMERADESC CameraDesc;
	CameraDesc.fAspect	= static_cast<_float>(g_nWinCX) / g_nWinCY;
	CameraDesc.fFar		= 300.f;
	CameraDesc.fNear	= 0.12f;
	CameraDesc.fFovy	= D3DXToRadian(82.f);
	CameraDesc.vAt		= _float3(0.f, 0.f, 0.f);
	CameraDesc.vEye		= _float3(1.0f, 3.5f, -2.8f);
	CameraDesc.vAxisY	= _float3(0.f, 1.f, 0.f);
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_TPSCamera"), pLayerTag ,&CameraDesc)))
	{
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_PlayStage::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_Player"), pLayerTag)))
	{
		return E_FAIL;
	}
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_PlayStage::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	
	for (_uint i = 0; i < 5; i++)
	{
		CResponseBox::POSITION tPosition;
		tPosition.m_worldPosition = _float3{ i*1.f - 3.f,-1.f,2.f };

		if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_TerrainBox"), pLayerTag, &tPosition)))
		{
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_SkyBox"), pLayerTag)))
	{
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_PlayStage::Ready_Layer_ResponeseBox(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < 5; i++)
	{
		CResponseBox::POSITION tPosition;
		tPosition.m_worldPosition = _float3{ i*1.f - 3.f,0.f,5.f };

		if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_ResponseBox"), pLayerTag, &tPosition)))
		{
			return E_FAIL;
		}

	}
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_PlayStage::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CUI::UIDESC tUIDesc;
	tUIDesc.m_fSizeX =	256;
	tUIDesc.m_fSizeY =	612;
	tUIDesc.m_fX = 1152;
	tUIDesc.m_fY = 256;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_FoodList_BackGround"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}
#pragma region ICON
	/*---------------------------------------------------------------------------------------------------------------------------------*/
	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1080;
	tUIDesc.m_fY = 100;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_FoodICon_00"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1080;
	tUIDesc.m_fY = 180;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_FoodICon_01"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1080;
	tUIDesc.m_fY = 260;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_FoodICon_02"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1080;
	tUIDesc.m_fY = 340;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_FoodICon_03"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1080;
	tUIDesc.m_fY = 420;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_FoodICon_04"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1080;
	tUIDesc.m_fY = 500;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_Trash_Icon"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	
#pragma endregion


#pragma region Number
	/*--------------------------------------------------------------------------------------------------------------------------------------*/
	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1200;
	tUIDesc.m_fY = 100;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_ITemCount_00"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1200;
	tUIDesc.m_fY = 180;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_ITemCount_01"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1200;
	tUIDesc.m_fY = 260;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_ITemCount_02"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1200;
	tUIDesc.m_fY = 340;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_ITemCount_03"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1200;
	tUIDesc.m_fY = 420;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_ITemCount_04"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

	tUIDesc.m_fSizeX = 64;
	tUIDesc.m_fSizeY = 64;
	tUIDesc.m_fX = 1200;
	tUIDesc.m_fY = 500;
	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEPLAY0, TEXT("Prototype_ITemCount_Trash"), pLayerTag, &tUIDesc)))
	{
		goto failed;;
	}

#pragma endregion

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;

failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;;
}

CLevel_PlayStage * CLevel_PlayStage::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_PlayStage* pInstance = new CLevel_PlayStage(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed To Creating CLevel_PlayStage_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_PlayStage::Free()
{
	__super::Free();
}
