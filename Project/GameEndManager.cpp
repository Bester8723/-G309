/*************************************************************************//*!

					@file	GameEndManager.cpp
					@brief	�Q�[���I���Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#include "GameEndManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CGameEndManager::CGameEndManager() :
m_bGameEnd(false),
m_GameEndNo(0) {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CGameEndManager::~CGameEndManager() {
}

/// <summary>
/// �Q�[���I��������ݒ�
/// </summary>
/// <param name="endNo">�I���ԍ�</param>
void CGameEndManager::SetGameEndCondition(int endNo) {
	m_GameEndNo = endNo;
	if (endNo == GAMEENDNO_CONTINUE)
	{
		m_bGameEnd = false;
	}
	else
	{
		m_bGameEnd = true;
	}
}