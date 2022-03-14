#include "..\public\VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{

}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer & rhs)
	: CVIBuffer(rhs)
{

}

HRESULT CVIBuffer_Cube::NativeConstruct_Prototype()
{

#pragma region VERTICES
	m_iNumVertices = 8;
	m_iStride = sizeof(VTXCUBETEX);
	m_dwVBUsage = 0;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
#pragma endregion

#pragma region INDICES
	m_iNumPrimitive = 12;
	m_iNumVerticesPerPrimitive = 3;
	m_dwIBUsage = 0;

	/* 2 or 4 */
	m_iOneIndexSize = 2;
#pragma endregion

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	VTXCUBETEX*		pVertices = nullptr;

	/* 정점메모리공간에 접근할 수 있는 포인터를 얻어온다. */
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);


	/* 앞면 */
	pVertices[0].vPosition = m_pVerticesPos[0] =_float3(-0.5f, 0.5f, -0.5f);
	pVertices[0].vTexUV = pVertices[0].vPosition;
	pVertices[1].vPosition = m_pVerticesPos[1] = _float3(0.5f, 0.5f, -0.5f);
	pVertices[1].vTexUV = pVertices[1].vPosition;
	pVertices[2].vPosition = m_pVerticesPos[2] = _float3(0.5f, -0.5f, -0.5f);
	pVertices[2].vTexUV = pVertices[2].vPosition;
	pVertices[3].vPosition = m_pVerticesPos[3] = _float3(-0.5f, -0.5f, -0.5f);
	pVertices[3].vTexUV = pVertices[3].vPosition;

	/* 뒷면 */
	pVertices[4].vPosition = m_pVerticesPos[4] = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[4].vTexUV = pVertices[4].vPosition;
	pVertices[5].vPosition = m_pVerticesPos[5] = _float3(0.5f, 0.5f, 0.5f);
	pVertices[5].vTexUV = pVertices[5].vPosition;
	pVertices[6].vPosition = m_pVerticesPos[6] = _float3(0.5f, -0.5f, 0.5f);
	pVertices[6].vTexUV = pVertices[6].vPosition;
	pVertices[7].vPosition = m_pVerticesPos[7] = _float3(-0.5f, -0.5f, 0.5f);
	pVertices[7].vTexUV = pVertices[7].vPosition;

	m_pVB->Unlock();


	_ushort*	pIndices = 0;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	/* +x */
	reinterpret_cast<_ushort*>(m_pIndices)[0] = pIndices[0] = 1;
	reinterpret_cast<_ushort*>(m_pIndices)[1] = pIndices[1] = 5;
	reinterpret_cast<_ushort*>(m_pIndices)[2] = pIndices[2] = 6;

	reinterpret_cast<_ushort*>(m_pIndices)[3] = pIndices[3] = 1;
	reinterpret_cast<_ushort*>(m_pIndices)[4] = pIndices[4] = 6;
	reinterpret_cast<_ushort*>(m_pIndices)[5] = pIndices[5] = 2;

	/* -x */
	reinterpret_cast<_ushort*>(m_pIndices)[6] = pIndices[6] = 4;
	reinterpret_cast<_ushort*>(m_pIndices)[7] = pIndices[7] = 0;
	reinterpret_cast<_ushort*>(m_pIndices)[8] = pIndices[8] = 3;

	reinterpret_cast<_ushort*>(m_pIndices)[9]  = pIndices[9] = 4;
	reinterpret_cast<_ushort*>(m_pIndices)[10] = pIndices[10] = 3;
	reinterpret_cast<_ushort*>(m_pIndices)[11] = pIndices[11] = 7;

	/* +y */
	reinterpret_cast<_ushort*>(m_pIndices)[12] = pIndices[12] = 4;
	reinterpret_cast<_ushort*>(m_pIndices)[13] = pIndices[13] = 5;
	reinterpret_cast<_ushort*>(m_pIndices)[14] = pIndices[14] = 1;

	reinterpret_cast<_ushort*>(m_pIndices)[15] = pIndices[15] = 4;
	reinterpret_cast<_ushort*>(m_pIndices)[16] = pIndices[16] = 1;
	reinterpret_cast<_ushort*>(m_pIndices)[17] = pIndices[17] = 0;

	/* -y */
	reinterpret_cast<_ushort*>(m_pIndices)[18] = pIndices[18] = 3;
	reinterpret_cast<_ushort*>(m_pIndices)[19] = pIndices[19] = 2;
	reinterpret_cast<_ushort*>(m_pIndices)[20] = pIndices[20] = 6;

	reinterpret_cast<_ushort*>(m_pIndices)[21] = pIndices[21] = 3;
	reinterpret_cast<_ushort*>(m_pIndices)[22] = pIndices[22] = 6;
	reinterpret_cast<_ushort*>(m_pIndices)[23] = pIndices[23] = 7;

	/* +z */
	reinterpret_cast<_ushort*>(m_pIndices)[24] = pIndices[24] = 5;
	reinterpret_cast<_ushort*>(m_pIndices)[25] = pIndices[25] = 4;
	reinterpret_cast<_ushort*>(m_pIndices)[26] = pIndices[26] = 7;

	reinterpret_cast<_ushort*>(m_pIndices)[27] = pIndices[27] = 5;
	reinterpret_cast<_ushort*>(m_pIndices)[28] = pIndices[28] = 7;
	reinterpret_cast<_ushort*>(m_pIndices)[29] = pIndices[29] = 6;

	/* -z */
	reinterpret_cast<_ushort*>(m_pIndices)[30] = pIndices[30] = 0;
	reinterpret_cast<_ushort*>(m_pIndices)[31] = pIndices[31] = 1;
	reinterpret_cast<_ushort*>(m_pIndices)[32] = pIndices[32] = 2;

	reinterpret_cast<_ushort*>(m_pIndices)[33] = pIndices[33] = 0;
	reinterpret_cast<_ushort*>(m_pIndices)[34] = pIndices[34] = 2;
	reinterpret_cast<_ushort*>(m_pIndices)[35] = pIndices[35] = 3;


	m_pIB->Unlock();
	return S_OK;
}

HRESULT CVIBuffer_Cube::NativeConstruct(void * pArg)
{
	return S_OK;
}

CVIBuffer_Cube * CVIBuffer_Cube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX("Failed to Creating CVIBuffer_Cube");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CVIBuffer_Cube::Clone(void * pArg)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX("Failed to Creating CVIBuffer_Cube");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIBuffer_Cube::Free()
{
	__super::Free();


}
