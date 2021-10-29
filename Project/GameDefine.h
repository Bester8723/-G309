/*************************************************************************//*!

					@file	GameDefine.h
					@brief	�񋓂̂܂Ƃ߁B

															@author	�r��@����
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"Mof.h"

#define			GRAVITY					0.3f			//�d��
#define			MAXGRAVITY				20.0f			//�ő�d�͉���

//�V�[���̗�
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_MODESELECT,
	SCENENO_GAME,
	SCENENO_RESULT,

	SCENENO_COUNT,
};

//���[�h�̗�
enum tag_MODENO {
	MODENO_STORY,
	MODENO_ENDLESS,

	MODENO_COUNT,
};

//�Q�[���I�������̗�
enum tag_GAMEENDNO {
	GAMEENDNO_CONTINUE,
	GAMEENDNO_CLEAR,
	GAMEENDNO_HP,
	GAMEENDNO_JEWEL,
	GAMEENDNO_GAS,

	GAMEENDNO_COUNT,
};