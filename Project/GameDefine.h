/*************************************************************************//*!

					@file	GameDefine.h
					@brief	�񋓂̂܂Ƃ߁B

															@author	�r��@����
*//**************************************************************************/

#pragma once
//INCLUDE
#include	"Mof.h"

//���݂���V�[���̗�
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_STAGESELECT,
	SCENENO_GAME,
	SCENENO_RESULT,

	COUNT_SCENENO,
};

#define			GRAVITY					0.3f			//�d��
#define			MAXGRAVITY				20.0f			//�ő�d�͉���