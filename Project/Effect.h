/*************************************************************************//*!

					@file	Effect.h
					@brief	エフェクト。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

//エフェクト種類列挙
enum tag_EFFECTTYPE {
	EFC_DAMAGE,						//ダメージ
	EFC_EXPLOSION01,				//敵爆破
	EFC_EXPLOSION02,				//プレイヤー爆破

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