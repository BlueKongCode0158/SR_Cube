#pragma once
#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)
class CLevel_PlayStage final : public CLevel
{
private:
	explicit CLevel_PlayStage(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual  ~CLevel_PlayStage() = default;
public:
	virtual HRESULT NativeConstruct() override;
	virtual _int	Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;
private:
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_ResponeseBox(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_UI(const _tchar* pLayerTag);
public:
	static CLevel_PlayStage*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void				Free() override;
};
END
