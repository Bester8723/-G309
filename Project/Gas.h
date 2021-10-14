/*************************************************************************//*!

					@file	Gas.h
					@brief	·èãCÅB

															@author	írè„Å@àªçÅ
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"DebugManager.h"
#include	"GameEndManager.h"
#include	"Item.h"

#define				SPEEDX			1.0f
#define				SPEEDY			0.5f
#define				STARTPOS		10

class CGas {
private:
	CTexture		m_Tex;
	CVector2		m_Move;
	CVector2		m_Scroll;
public:
	CGas();
	~CGas();
	bool Load();
	void Initialize(Vector2 world);
	void Update();
	void UpdateDebug();
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
	bool CollisionItem(CItem& itm);
	Vector2 GetScroll() { return m_Scroll; }
};