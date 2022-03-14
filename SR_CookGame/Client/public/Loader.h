#pragma once
#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)
class CLoader final : public CBase
{
private:
	explicit CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual  ~CLoader() = default;
public:
	_bool Get_Finish() const
	{ 
		return m_isFinish;
	}
	_tchar*	Get_SystemMessage() const
	{
		return m_szSystemMessage;
	}
public:
	HRESULT	NativeConstruct(LEVEL eNextLevel);
public:
	static unsigned __stdcall Thread_Main(void* pArg);
private:
	HANDLE					m_hThread;
	CRITICAL_SECTION		m_CS;
	LEVEL					m_eNextLevel		= LEVEL_END;
	_tchar*					m_szSystemMessage = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphic_Device	= nullptr;
	_bool					m_isFinish			= false;
private:
	HRESULT	GamePlay_Stage0();
	HRESULT Clear();
	HRESULT GameOver();
public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void	Free() override;
};
END

