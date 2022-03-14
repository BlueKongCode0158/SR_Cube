#include "stdafx.h"
#include "..\public\Loader.h"
#include "GameInstance.h"
#include "TPSCamera.h"
#include "ResponseBox.h"
#include "Player.h"
#include "TerrainBox.h"
#include "Food.h"
#include "SkyBox.h"
#include "FoodIcon.h"
#include "FoodList_BackGround.h"
#include "ItemCount.h"
#include "Trash_Icon.h"
#include "Clear_BackGround.h"
#include "End_BackGround.h"
#include "Effect.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGrephic_Device)
	:m_pGraphic_Device(pGrephic_Device)
{
	Safe_AddRef(pGrephic_Device);
}

HRESULT CLoader::NativeConstruct(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;

	InitializeCriticalSection(&m_CS);
	m_hThread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr));
	m_isFinish = false;

	if (0 == m_hThread)
	{
		return E_FAIL;
	}

	return S_OK;
}

unsigned CLoader::Thread_Main(void * pArg)
{
	CLoader* pLoader = reinterpret_cast<CLoader*>(pArg);

	EnterCriticalSection(&pLoader->m_CS);

	HRESULT hr = 0;

	switch (pLoader->m_eNextLevel)
	{
	case LEVEL_GAMEPLAY0:
		hr = pLoader->GamePlay_Stage0();
		break;
	case LEVEL_CLEAR:
		hr = pLoader->Clear();
		break;
	case LEVEL_GAMEOVER:
		hr = pLoader->GameOver();
		break;
	default:
		break;
	}

	if (FAILED(hr))
	{
		return 0;
	}


	LeaveCriticalSection(&pLoader->m_CS);

	return 0;
}

HRESULT CLoader::GamePlay_Stage0()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

#pragma region GAMEOBJECT


	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_TPSCamera"), CTPSCamera::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_ResponseBox"), CResponseBox::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Player"), CPlayer::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_TerrainBox"), CTerrainBox::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Food"), CFood::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_SkyBox"), CSkyBox::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Effect"), CEffect::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
#pragma endregion

#pragma region UI
	//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_FoodICon"), CFoodIcon::Create(m_pGraphic_Device,0))))
	//{
	//	goto failed;
	//}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_FoodICon_00"), CFoodIcon::Create(m_pGraphic_Device, 0))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_FoodICon_01"), CFoodIcon::Create(m_pGraphic_Device, 1))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_FoodICon_02"), CFoodIcon::Create(m_pGraphic_Device, 2))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_FoodICon_03"), CFoodIcon::Create(m_pGraphic_Device, 3))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_FoodICon_04"), CFoodIcon::Create(m_pGraphic_Device, 4))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Trash_Icon"), CTrash_Icon::Create(m_pGraphic_Device))))
	{
		goto failed;
	}

/*-------------------------------------------------------------------------------------------------------------------------------------*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_FoodList_BackGround"), CFoodList_BackGround::Create(m_pGraphic_Device))))
	{
		goto failed;
	}
/*-------------------------------------------------------------------------------------------------------------------------------------*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_ITemCount_00"), CItemCount::Create(m_pGraphic_Device,CFood::FOODTYPE::HAMBURGER))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_ITemCount_01"), CItemCount::Create(m_pGraphic_Device, CFood::FOODTYPE::BIBIMBAP))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_ITemCount_02"), CItemCount::Create(m_pGraphic_Device, CFood::FOODTYPE::PIZZA))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_ITemCount_03"), CItemCount::Create(m_pGraphic_Device, CFood::FOODTYPE::DRINKING))))
	{
		goto failed;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_ITemCount_04"), CItemCount::Create(m_pGraphic_Device, CFood::FOODTYPE::SOURCE))))
	{
		goto failed;
	}

	/*Prototype_ITemCount_Trash*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_ITemCount_Trash"), CItemCount::Create(m_pGraphic_Device, CFood::FOODTYPE::FOODEND))))
	{
		goto failed;
	}


/*-------------------------------------------------------------------------------------------------------------------------------------*/

#pragma endregion


#pragma region COMPONENT

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY0, TEXT("Prototype_Texture_FoodBox"), CTexture::Create(m_pGraphic_Device,CTexture::TYPE_CUBE, TEXT("../bin/resources/food/cube_%d.dds"),5))))
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
#pragma endregion

	m_isFinish = true;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;

failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;
}

HRESULT CLoader::Clear()
{

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_CLEAR, TEXT("Prototype_Clear_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/Resources/Clear/Clear.png")))))
	{
		goto failed;
	}
	//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_Clear_BackGround"), CClear_BackGround::Create(m_pGraphic_Device))))
	//{
	//	goto failed;
	//}

	m_isFinish = true;

	return S_OK;
failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;
}

HRESULT CLoader::GameOver()
{

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEOVER, TEXT("Prototype_GameOver_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE::TYPE_GENERAL, TEXT("../bin/Resources/End/Game_Over.png")))))
	{
		goto failed;
	}
	/*Prototype_GameOver_BackGround*/
	//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameOver_BackGround"), CEnd_BackGround::Create(m_pGraphic_Device))))
	//{
	//	goto failed;
	//}

	m_isFinish = true;

	return S_OK;
failed:
	RELEASE_INSTANCE(CGameInstance);
	return E_FAIL;

}

CLoader * CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader* pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct(eNextLevel)))
	{
		MSGBOX("Failed to Creating Loader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&m_CS);
	Safe_Release(m_pGraphic_Device);
	CloseHandle(m_hThread);
}
