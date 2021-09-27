/*************************************************************************//*!

					@file	GameDefine.h
					@brief	列挙のまとめ。

															@author	池上　綾香
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"Mof.h"

//存在するシーンの列挙
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_STAGESELECT,
	SCENENO_GAME,
	SCENENO_RESULT,

	COUNT_SCENENO,
};

#define			GRAVITY					0.3f			//重力
#define			MAXGRAVITY				20.0f			//最大重力加速