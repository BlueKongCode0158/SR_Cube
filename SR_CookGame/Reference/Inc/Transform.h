#pragma once

/* 객체의 월드공간상에서의 상태를 표현한다. */
/* 1행 : 라이트, 2행 : 업, 3행 : 룩, 4행 : 포지션 */
/* 월드공간으로의 변환, 상태를 표현 */
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };
public:
	typedef struct tagTransformDesc
	{
		_float	fSpeedPerSec;
		_float	fRotationPerSec;
	}TRANSFORMDESC;
private:
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public:
	const _matrix* Get_WorldMatrix() const {
		return &m_WorldMatrix;
	}
	_matrix Get_WorldMatrixInverse() const {
		_matrix WorldMatrixInverse;
		return *D3DXMatrixInverse(&WorldMatrixInverse, nullptr, &m_WorldMatrix);
	}

	_float3 Get_State(STATE eState) const {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}

	_float3 Get_Scale() const;
	bool	Get_DeadState() const
	{
		return m_isDead;
	}
public:
	void Set_State(STATE eState, _float3 vState);
	void Set_Scale(_float fScaleX, _float fScaleY, _float fScaleZ);
	void Set_MovingState(bool isMoving) {
		m_isMoving = isMoving;
	}
	void Set_DeadState(bool isDead)
	{
		m_isDead = isDead;
	}
public:
	virtual HRESULT NativeConstruct_Prototype()override;
	virtual HRESULT NativeConstruct(void* pArg)override;
public:	
	void Go_Straight(_float fTimeDelta);
	void Back_Straight(_float fTimeDelta);
	void Walk_Left(_float fTimeDelta);
	void Walk_Right(_float fTimeDelta);
	void Rotation_Axis(_float3 vAxis, _float fTimeDelta); /* 동적 */
	void SetUp_Rotation(_float3 vAxis, _float fRadian); /* 정적 */
	void Chase_Target(const CTransform* pTargetTransform, _float fTimeDelta);
	void Chase_Target(_float3	vTargetPos, _float fTimeDelta);
	void LookAt_Target(const CTransform* pTargetTransform);
	void LookAt_Target(_float3	vTargetPos);
	void Stand_OnTerrain(class CVIBuffer_Terrain* pVIBuffer, const _matrix* pTerrainWorldMatrix);
private:
	/* 객체의 상태를 표현한다. */
	_matrix			m_WorldMatrix;	
	TRANSFORMDESC	m_TransformState;

private:
	bool			m_isMoving	= false;
	bool			m_isDead	= false;

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg = nullptr)override;
	virtual void Free() override;
};

END