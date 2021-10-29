/*************************************************************************//*!

					@file	GameDefine.h
					@brief	列挙のまとめ。

															@author	池上　綾香
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"Mof.h"

#define			GRAVITY					0.3f			//重力
#define			MAXGRAVITY				20.0f			//最大重力加速

//シーンの列挙
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_MODESELECT,
	SCENENO_GAME,
	SCENENO_RESULT,

	SCENENO_COUNT,
};

//モードの列挙
enum tag_MODENO {
	MODENO_STORY,
	MODENO_ENDLESS,

	MODENO_COUNT,
};

//ゲーム終了条件の列挙
enum tag_GAMEENDNO {
	GAMEENDNO_CONTINUE,
	GAMEENDNO_CLEAR,
	GAMEENDNO_HP,
	GAMEENDNO_JEWEL,
	GAMEENDNO_GAS,

	GAMEENDNO_COUNT,
};