#pragma once

namespace Engine
{
	typedef struct tagVertexTexture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR2		vTexUV;		
	}VTXTEX;

	typedef struct tagVertexCubeTexture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vTexUV;		
	}VTXCUBETEX;

	typedef struct tagVertexNormalTexture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNormal;
		D3DXVECTOR2		vTexUV;		
	}VTXNORTEX;

	
	
}


