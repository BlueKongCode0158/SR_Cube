#include "stdafx.h"
#include "..\public\Level_End.h"
#include "GameInstance.h"
#include "UI.h"
#include "Level_Loading.h"
#include "Level_PlayStage.h"
#include "SoundMgr.h"

CLevel_End::CLevel_End(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_End::NativeConstruct()
{
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"GameOver_Background.wav");

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

_int CLevel_End::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		if (FAILED(Ready_GameStage()))
		{
			return -1;
		}

		if (SUCCEEDED(pGameInstance->SetUp_Level(CLevel_PlayStage::Create(m_pGraphic_Device))))
		{
			pGameInstance->Clear(LEVEL_GAMEOVER);
			goto succeeded;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
	return -1;
succeeded:
	RELEASE_INSTANCE(CGameInstance);
	return _int();

	return _int();
}

HRESULT CLevel_End::Render()
{
	if (FAILED(__super::Render()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLevel_End::Ready_BackGround_Layer(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CUI::UIDESC UIDesc;
	UIDesc.m_fSizeX = g_nWinCX;
	UIDesc.m_fSizeY = g_nWinCY;
	UIDesc.m_fX = (g_nWinCX >> 1);
	UIDesc.m_fY = (g_nWinCY >> 1);

	if (FAILED(pGameInstance->Add_GameObject(LEVEL_GAMEOVER, TEXT("Prototype_GameOver_BackGround"), pLayerTag, &UIDesc)))
	{
		return E_FAIL;
	}


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;
}

HRESULT CLevel_End::Ready_GameStage()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_FoodBox"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../bin/resources/food/cube_%d.dds"), 5))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_SkyBox"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../bin/resources/skybox/SkyColor.dds")))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_VIBuffer_Cube"), CVIBuffer_Cube::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	//if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_Trash"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../bin/resources/ObjectTexture/trash.dds")))))
	//{
	//	goto failed;
	//}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_Rail"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../bin/resources/ObjectTexture/Rail.dds")))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_ResponeBox"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../bin/resources/ObjectTexture/ResponseBox2.dds")))))
	{
		goto failed;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_FoodIcon"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/resources/UI/Food/Food_0%d.png"), 5))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_Trash"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/resources/UI/Food/Trash.png")))))
	{
		goto failed;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_FoodICon_BackGround"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/resources/UI/Food/FoodNum.png")))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_ITemCount"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/resources/UI/Num/Num_%d.png"), 10))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/resources/Effect/Smoke/Explosion%d.png"), 90))))
	{
		goto failed;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;

}

CLevel_End * CLevel_End::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_End* pInstance = new CLevel_End(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX("Failed to Creating CLevel_End");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_End::Free()
{
	__super::Free();
}
