#pragma once
#include "Camera.h"

BEGIN(Client)
class CTPSCamera final : public CCamera
{
private:
	explicit CTPSCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTPSCamera(const CTPSCamera& rhs);
	virtual  ~CTPSCamera() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual _int	Tick(_double TimeDelta) override;
	virtual _int	Late_Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;
private:
	HRESULT Add_Component();
public:
	static	CTPSCamera*	Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CCamera*	Clone(void* pArg) override;
	virtual void		Free() override;

};
END

