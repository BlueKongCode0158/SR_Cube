#include "stdafx.h"
#include "..\public\Level_Loading.h"
#include "Loader.h"
#include "GameInstance.h"
#include "Level_PlayStage.h"
#include "UI.h"
#include "Loading_BackGround.h"
#include "Level_Clear.h"
#include "Level_End.h"

CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{

}

HRESULT CLevel_Loading::NativeConstruct(LEVEL eNextLevel)
{
	if (eNextLevel == m_eNextLevel)
	{
		return E_FAIL;
	}
	m_eNextLevel = eNextLevel;

	m_pLoader = CLoader::Create(m_pGraphic_Device, eNextLevel);

	if (nullptr == m_pLoader)
	{
		return E_FAIL;
	}

	if(Ready_Layer_BackGround(TEXT("Layer_Background")))

	return S_OK;
}

_int CLevel_Loading::Tick(_double TimeDelta)
{

	if (true == m_pLoader->Get_Finish())
	{
		CLoading_BackGround::Set_Num(1);

		if (GetAsyncKeyState(VK_RETURN) & 0x0001)
		{
			CGameInstance*	pGameInstance	= GET_INSTANCE(CGameInstance);
			CLevel*			pLevel			= nullptr;

			switch (m_eNextLevel)
			{
			case LEVEL_GAMEPLAY0:
				pLevel = CLevel_PlayStage::Create(m_pGraphic_Device);
				break;
			case LEVEL_CLEAR:
				pLevel = CLevel_Clear::Create(m_pGraphic_Device);
				break;
			case LEVEL_GAMEOVER:
				pLevel = CLevel_End::Create(m_pGraphic_Device);
				break;
			default:
				break;
			}
			pGameInstance->Clear(LEVEL_LOADING);
			pGameInstance->SetUp_Level(pLevel);
			
			RELEASE_INSTANCE(CGameInstance);
		}
	}
	else
	{
		CLoading_BackGround::Set_Num(0);
	}
	return _int();
}

HRESULT CLevel_Loading::Render()
{
	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_UserInterface(const _tchar * pLayerTag)
{
	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CUI::UIDESC UIDesc;
	UIDesc.m_fSizeX = g_nWinCX;
	UIDesc.m_fSizeY = g_nWinCY;
	UIDesc.m_fX = (g_nWinCX >> 1);
	UIDesc.m_fY = (g_nWinCY >> 1);

	if (FAILED(pGameInstance->Add_GameObject(LEVEL_LOADING, TEXT("Prototype_Loading_Background"), pLayerTag,&UIDesc)))
	{
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}


CLevel_Loading * CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLevel_Loading* pInstance = new CLevel_Loading(pGraphic_Device);

	if (FAILED(HRESULT(pInstance->NativeConstruct(eNextLevel))))
	{
		MSGBOX("Failed to Creating CLevel_Loading_Object");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);
}
