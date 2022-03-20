#include "stdafx.h"
#include "..\public\MainApp.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "Level_Logo.h"
#include "BackGround.h"
#include "Player.h"
#include "FoodList.h"
#include "Start_Button.h"
#include "Loading_BackGround.h"
#include "End_BackGround.h"
#include "Clear_BackGround.h"
#include "SoundMgr.h"


CMainApp::CMainApp()
{
}

HRESULT CMainApp::NativeConstruct()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CSoundMgr::Get_Instance()->Initialize();

	if (FAILED(pGameInstance->Initialize_Engine(g_hInst, g_hWnd, LEVEL_END)))
		return E_FAIL;

	if (FAILED(pGameInstance->Ready_Graphic_Device(g_hWnd, CGraphic_Device::MODE_WIN, g_nWinCX, g_nWinCY, &m_pGraphic_Device)))
		return E_FAIL;
	if (FAILED(Add_Prototype_Component()))
		return E_FAIL;

	if (FAILED(Add_Prototype_GameObject()))
		return E_FAIL;

	/* 씬을 생성한다. */
	if (FAILED(pGameInstance->SetUp_Level(CLevel_Logo::Create(m_pGraphic_Device))))
		return E_FAIL;

	CFoodList::Get_Instance()->Add_FoodScore(CFood::FOODTYPE::HAMBURGER, 5);
	CFoodList::Get_Instance()->Add_FoodScore(CFood::FOODTYPE::BIBIMBAP, 4);
	CFoodList::Get_Instance()->Add_FoodScore(CFood::FOODTYPE::PIZZA, 7);
	CFoodList::Get_Instance()->Add_FoodScore(CFood::FOODTYPE::DRINKING, 4);
	CFoodList::Get_Instance()->Add_FoodScore(CFood::FOODTYPE::SOURCE, 8);
	CFoodList::Get_Instance()->Add_FoodScore(TRASH, 0);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

_int CMainApp::Tick(_double TimeDelta)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	if (FAILED(pGameInstance->Tick(TimeDelta)))
	{
		return -1;
	}
	m_pPickingCom->Compute_MouseCursorPosInWorld(g_hWnd);

	if (FAILED(pGameInstance->LateTick(TimeDelta)))
	{
		return -1;
	}
	RELEASE_INSTANCE(CGameInstance);
	return _int();
}

HRESULT CMainApp::Render()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Render_Begin();

	if (FAILED(m_pRendererCom->Render_GameObject()))
	{
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Render_Level()))
	{
		return E_FAIL;
	}

	pGameInstance->Render_End();

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CMainApp::Add_Prototype_Component()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Transform"), CTransform::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Renderer"), m_pRendererCom = CRenderer::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	Safe_AddRef(m_pRendererCom);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Picking"), m_pPickingCom = CPicking::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	Safe_AddRef(m_pPickingCom);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_VIBuffer_Rect"), CVIBuffer_Rect::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Logo_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/Resources/Logo_Image/Food_Logo.png")))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Start_Button_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/Resources/Button/StartButton_0%d.png"), 2))))
	{
		goto failed;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Loading_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/Resources/Loading/Loading_0%d.png"), 2))))
	{
		goto failed;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Clear_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/Resources/Clear/Clear.png")))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_GameOver_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/Resources/End/Game_Over.png")))))
	{
		goto failed;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;

}

HRESULT CMainApp::Add_Prototype_GameObject()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_BackGround"), CBackGround::Create(m_pGraphic_Device))))
	{
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Start_Button"), CStart_Button::Create(m_pGraphic_Device))))
	{
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Loading_Background"), CLoading_BackGround::Create(m_pGraphic_Device))))
	{
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameOver_BackGround"), CEnd_BackGround::Create(m_pGraphic_Device))))
	{
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Clear_BackGround"), CClear_BackGround::Create(m_pGraphic_Device))))
	{
		return E_FAIL;
	}


	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp();
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed To Creating MainApp_Prototype");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphic_Device);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pPickingCom);

	CSoundMgr::Destroy_Instance();
	CGameInstance::Release_Engine();
	CFoodList::Destroy_Instance();
}
