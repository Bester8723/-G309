/*************************************************************************//*!

					@file	Effect.h
					@brief	�G�t�F�N�g�B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

//�G�t�F�N�g��ޗ�
enum tag_EFFECTTYPE {
	EFC_DAMAGE,						//�_���[�W
	EFC_EXPLOSION01,				//�G���j
	EFC_EXPLOSION02,				//�v���C���[���j

	EFC_TYPECOUNT,
};

class CEffect {
private:
	CTexture* m_pTexture;
	CSpriteMotionController	m_Motion;
	CVector2				m_Pos;
	bool					m_bShow;
	CRectangle				m_SrcRect;

public:
	CEffect();
	~CEffect();
	void Initialize(int type);
	void Start(Vector2 pos);
	void Update(void);
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release(void);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
};