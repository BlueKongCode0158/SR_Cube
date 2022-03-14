#include "..\public\Renderer.h"
#include "GameObject.h"


CRenderer::CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{

}

HRESULT CRenderer::NativeConstruct_Prototype()
{
	return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject ||
		RENDER_END <= eGroup)
		return E_FAIL;

	m_RenderObjects[eGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRenderer::Render_GameObject()
{
	if (FAILED(Render_Priority()))
	{
		return E_FAIL;
	}
	if (FAILED(Render_NonAlpha()))
	{
		return E_FAIL;
	}
	if (FAILED(Render_Alpha()))
	{
		return E_FAIL;
	}
	if (FAILED(Render_UI()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CRenderer::Render_Priority()
{
	for (auto& pGameObject : m_RenderObjects[RENDER_PRIORITY])
	{
		if (FAILED(pGameObject->Render()))
		{
			return E_FAIL;
		}
		Safe_Release(pGameObject);
	}
	m_RenderObjects[RENDER_PRIORITY].clear();

	return S_OK;
}

HRESULT CRenderer::Render_NonAlpha()
{
	for (auto& pGameObject : m_RenderObjects[RENDER_NONALPHA])
	{
		if (FAILED(pGameObject->Render()))
		{
			return E_FAIL;
		}
		Safe_Release(pGameObject);
	}
	m_RenderObjects[RENDER_NONALPHA].clear();

	return S_OK;
}

bool Compare(CGameObject * pDest, CGameObject * pSour)
{
	return pDest->Get_Distance() > pSour->Get_Distance();
}


HRESULT CRenderer::Render_Alpha()
{
	m_RenderObjects[RENDER_ALPHA].sort(Compare);

	for (auto& pGameObject : m_RenderObjects[RENDER_ALPHA])
	{
		if (FAILED(pGameObject->Render()))
		{
			return E_FAIL;
		}
		Safe_Release(pGameObject);
	}
	m_RenderObjects[RENDER_ALPHA].clear();

	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	for (auto& pGameObject : m_RenderObjects[RENDER_UI])
	{
		if (FAILED(pGameObject->Render()))
		{
			return E_FAIL;
		}
		Safe_Release(pGameObject);
	}
	m_RenderObjects[RENDER_UI].clear();

	return S_OK;
}


CRenderer * CRenderer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRenderer*	pInstance = new CRenderer(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CRenderer");
		Safe_Release(pInstance);
	}


	return pInstance;
}

CComponent * CRenderer::Clone(void * pArg)
{
	AddRef();

	return this;
}

void CRenderer::Free()
{
	__super::Free();
}
