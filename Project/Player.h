/*************************************************************************//*!

					@file	Player.h
					@brief	プレイヤー。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"

#define		PLAYER_SPEED			0.3f			//移動速度
#define		PLAYER_MAXSPEED			10.0f			//移動最大速度
#define		PLAYER_JUMP				-10.0f			//ジャンプ初速
#define		MAXJUMPCOUNT			2				//最大ジャンプ回数
#define		GRAVITY					0.3f			//重力
#define		MAXGRAVITY				20.0f			//最大重力加速

class CPlayer {
private:
	CTexture					m_Tex;
	CRectangle					m_SrcRect;
	bool						m_bReverse;
	CSpriteMotionController		m_Motion;
	CVector2					m_Pos;
	CVector2					m_Move;
	bool						m_bMove;
	int							m_JumpCount;
	bool						m_bJumping;
	bool						m_bDead;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void Update();
	void UpdateKey();
	void UpdateMove();
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
};