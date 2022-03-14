#include "..\public\PipeLine.h"

IMPLEMENT_SINGLETON(CPipeLine)

CPipeLine::CPipeLine()
{
	D3DXMatrixIdentity(&m_ViewMatrix);
	D3DXMatrixIdentity(&m_ProjMatrix);
}

void CPipeLine::Set_Transform(D3DTRANSFORMSTATETYPE eStateType, const _matrix & TransformMatrix)
{
	if (eStateType == D3DTS_VIEW)
		m_ViewMatrix = TransformMatrix;
	else 
		m_ProjMatrix = TransformMatrix;
}

void CPipeLine::Free()
{
	
}
