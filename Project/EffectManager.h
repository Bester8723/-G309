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
	//�G�t�F�N�g
	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];
	//�G�t�F�N�g�摜
	CTexture	m_Texture[EFC_TYPECOUNT];
public:
	CEffectManager();
	~CEffectManager();
	bool Load(void);
	void Initialize(void);
	CEffect* Start(Vector2 pos, int type);
	void Update(void);
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release(void);
};