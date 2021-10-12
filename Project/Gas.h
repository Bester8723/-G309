/*************************************************************************//*!

					@file	Gas.h
					@brief	ᏋC�B

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"

class CGas {
private:
	CTexture		m_Tex;
	CVector2		m_Pos;
	CVector2		m_Move;
public:
	CGas();
	~CGas();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();
};