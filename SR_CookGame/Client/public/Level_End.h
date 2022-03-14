#pragma once
#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)
class CLevel_End final : public CLevel
{
private:
	explicit CLevel_End(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_End() = default;
public:
	virtual HRESULT NativeConstruct()		override;
	virtual _int	Tick(_double TimeDelta) override;
	virtual HRESULT Render()				override;
private:
	HRESULT Ready_BackGround_Layer(const _tchar* pLayerTag);
	HRESULT Ready_GameStage();
public:
	static CLevel_End*  Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void		Free()			 override;
};
END
