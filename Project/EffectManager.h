/*************************************************************************//*!

					@file	EffectManager.h
					@brief	�G�t�F�N�g�Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"Effect.h"

//�Ǘ��G�t�F�N�g�̐�
#define				EFFECTCOUNT					5

class CEffectManager {
private:
	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];			//�G�t�F�N�g
	CTexture	m_Texture[EFC_TYPECOUNT];						//�G�t�F�N�g�摜
public:
	CEffectManager();
	~CEffectManager();
	bool Load();
	void Initialize();
	CEffect* Start(Vector2 pos, int type);
	void Update();
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
};