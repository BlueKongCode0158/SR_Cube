#pragma once

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Timer_Manager.h"
#include "PipeLine.h"
#include "Input_Device.h"


BEGIN(Engine)


class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public:
	HRESULT Initialize_Engine(HINSTANCE hInst, HWND hWnd, _uint iNumLevel);
	_int Tick(_double TimeDelta);
	_int LateTick(_double TimeDelta);
	void Clear(_uint iLevelIndex);





#pragma region GRAPHIC_DEVICE
public:
	HRESULT Ready_Graphic_Device(HWND hWnd, CGraphic_Device::WINMODE eMode, _uint iWinCX, _uint iWinCY, LPDIRECT3DDEVICE9* ppGraphic_Device = nullptr);
	void Render_Begin();
	void Render_End(HWND hWND = nullptr);
#pragma endregion


#pragma region LEVEL_MANAGER
public:
	HRESULT SetUp_Level(class CLevel* pLevel);
	HRESULT Render_Level();
#pragma endregion

#pragma region OBJECT_MANAGER
	HRESULT		Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT		Add_GameObject(_uint iLevelIndex, const _tchar* pPrototypeTag, const _tchar* pLayerTag, void* pArg = nullptr);
	CComponent* Get_ComponentPtr(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
	_uint		Get_GameObjectMapSize(_uint iLevelIndex, const _tchar* pLayerTag);
#pragma endregion

#pragma region COMPONENT_MANAGER
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);
#pragma endregion


#pragma region TIMER_MANAGER
	HRESULT Add_Timers(const _tchar* pTimerTag);
	_float Compute_TimeDelta(const _tchar* pTimerTag);
#pragma endregion

#pragma region PIPELINE
	_matrix Get_Transform(D3DTRANSFORMSTATETYPE eStateType);
#pragma endregion

#pragma region INPUT_DEVICE
	_byte Get_DIKeyState(_byte byKey);
	_byte Get_DIMouseKeyState(CInput_Device::DIM eMouseKey);
	_long Get_DIMouseMoveState(CInput_Device::DIMM eMouseMove);
#pragma endregion
public:
	static void Release_Engine();

private:
	CGraphic_Device*		m_pGraphic_Device = nullptr;
	CLevel_Manager*			m_pLevel_Manager = nullptr;
	CObject_Manager*		m_pObject_Manager = nullptr;
	CComponent_Manager*		m_pComponent_Manager = nullptr;
	CTimer_Manager*			m_pTimer_Manager = nullptr;
	CPipeLine*				m_pPipeLine = nullptr;
	CInput_Device*			m_pInput_Device = nullptr;

public:
	virtual void Free() override;
};

END