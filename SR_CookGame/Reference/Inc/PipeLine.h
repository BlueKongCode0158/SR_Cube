#pragma once

#include "Base.h"

/* ��, ����������� �����Ѵ�. */
/* ��? �̱���? ��ü���� �ʿ��Ҷ����� ���� ���� �����ٷ���. */

BEGIN(Engine)

class CPipeLine final : public CBase
{
	DECLARE_SINGLETON(CPipeLine)

private:
	CPipeLine();
	virtual ~CPipeLine() = default;

public:
	_matrix Get_Transform(D3DTRANSFORMSTATETYPE eStateType) {
		return eStateType == D3DTS_VIEW ? m_ViewMatrix : m_ProjMatrix;
	}

public:
	void Set_Transform(D3DTRANSFORMSTATETYPE eStateType, const _matrix& TransformMatrix);
private:
	_matrix			m_ViewMatrix;
	_matrix			m_ProjMatrix;

public:
	virtual void Free() override;
};

END