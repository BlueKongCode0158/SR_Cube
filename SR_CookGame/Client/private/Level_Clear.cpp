#include "stdafx.h"
#include "..\public\Level_Clear.h"
#include "GameInstance.h"
#include "SoundMgr.h"
#include "UI.h"

CLevel_Clear::CLevel_Clear(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Clear::NativeConstruct()
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Clear_Background.wav");
	if (FAILED(__super::NativeConstruct()))
	{
		return E_FAIL;
	}
	if (FAILED(Ready_BackGround_Layer(TEXT("Layer_BackGround"))))
	{
		return E_FAIL;
	}
	return S_OK;
}

_int CLevel_Clear::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	return _int();
}

HRESULT CLevel_Clear::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_Clear::Ready_BackGround_Layer(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CUI::UIDESC UIDesc;
	UIDesc.m_fSizeX = g_nWinCX;
	UIDesc.m_fSizeY = g_nWinCY;
	UIDesc.m_fX = (g_nWinCX >> 1);
	UIDesc.m_fY = (g_nWinCY >> 1);

	if (FAILED(pGameInstance->Add_GameObject(LEVEL_CLEAR, TEXT("Prototype_Clear_BackGround"), pLayerTag, &UIDesc)))
	{
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CLevel_Clear * CLevel_Clear::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Clear* pInstance = new CLevel_Clear(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating Level_Clear");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Clear::Free()
{
	__super::Free();
}
