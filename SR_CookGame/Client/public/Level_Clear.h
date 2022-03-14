#pragma once
#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)
class CLevel_Clear final: public CLevel
{
private:
	explicit CLevel_Clear(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual  ~CLevel_Clear() = default;
public:
	virtual HRESULT NativeConstruct()		override;
	virtual _int	Tick(_double TimeDelta) override;
	virtual HRESULT Render()				override;
private:
	HRESULT Ready_BackGround_Layer(const _tchar* pLayerTag);
public:
	static CLevel_Clear* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void		 Free()			 override;

};
END
