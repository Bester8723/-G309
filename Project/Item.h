/*************************************************************************//*!

					@file	Item.h
					@brief	�A�C�e���B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"

//�A�C�e����ޗ�
enum tag_ITEMTYPE {
	ITEMTYPE_CHARM,				//�D
	ITEMTYPE_JEWEL,				//���

	ITEMTYPE_COUNT,
};

class CItem {
private:
	CTexture*					m_pTexture;
	CSpriteMotionController		m_Motion;
	int							m_Type;
	CVector2					m_Pos;
	CVector2					m_Move;
	bool						m_bShow;
	CRectangle					m_SrcRect;
public:
	CItem();
	~CItem();
	void Initialize(Vector2 pos, int type);
	void Update();
	void CollisionStage(Vector2 buried);
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
	CRectangle GetRect() {
		return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight());
	}
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow() { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	int GetType() { return m_Type; }
};