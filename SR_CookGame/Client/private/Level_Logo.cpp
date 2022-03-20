#include "stdafx.h"
#include "..\public\Level_Logo.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "UI.h"
#include "Start_Button.h"
#include "SoundMgr.h"


CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{

}

HRESULT CLevel_Logo::NativeConstruct()
{

	CSoundMgr::Get_Instance()->PlayBGM(L"Start_Background.mp3");
	if (FAILED(__super::NativeConstruct()))
	{
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_UI(TEXT("Layer_BackGround"))))
	{
		return E_FAIL;
	}
	if (FAILED(Reay_Layer_Button(TEXT("Layer_Button"))))
	{
		return E_FAIL;
	}
	return S_OK;
}

_int CLevel_Logo::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CStart_Button::Start())
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
		{
			if (SUCCEEDED(pGameInstance->SetUp_Level(CLevel_Loading::Create(m_pGraphic_Device, LEVEL_GAMEPLAY0))))
			{
				pGameInstance->Clear(LEVEL_LOGO);
				goto succeeded;
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
	return -1;
succeeded:
	RELEASE_INSTANCE(CGameInstance);
	return _int();
}

HRESULT CLevel_Logo::Render()
{
	__super::Render();
	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CUI::UIDESC UIDesc;
	UIDesc.m_fSizeX = g_nWinCX;
	UIDesc.m_fSizeY = g_nWinCY;
	UIDesc.m_fX = (g_nWinCX >> 1);
	UIDesc.m_fY = (g_nWinCY >> 1);

	if (FAILED(pGameInstance->Add_GameObject(LEVEL_LOGO, TEXT("Prototype_BackGround"), pLayerTag, &UIDesc)))
	{
		goto failed;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;
}

HRESULT CLevel_Logo::Reay_Layer_Button(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CUI::UIDESC UIDesc;
	UIDesc.m_fSizeX = 426;
	UIDesc.m_fSizeY = 142;
	UIDesc.m_fX = (g_nWinCX >> 1) + 300;
	UIDesc.m_fY = (g_nWinCY >> 1) + 100;

	if (FAILED(pGameInstance->Add_GameObject(LEVEL_LOGO, TEXT("Prototype_Start_Button"), pLayerTag, &UIDesc)))
	{
		goto failed;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;
}

CLevel_Logo * CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Logo* pInstance = new CLevel_Logo(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed To Creating Level_Logo");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();
}
