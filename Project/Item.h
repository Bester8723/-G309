/*************************************************************************//*!

					@file	Item.h
					@brief	アイテム。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"

//アイテム種類列挙
enum tag_ITEMTYPE {
	ITEMTYPE_CHARM,				//札
	ITEMTYPE_JEWEL,				//宝玉

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