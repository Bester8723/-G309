/*************************************************************************//*!

					@file	GameEndManager.cpp
					@brief	�Q�[���I���Ǘ��B

															@author	�r��@����
*//**************************************************************************/
#include "GmeEndManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CGmeEndManager::CGmeEndManager() :
m_bGameEnd(false),
m_GameEndNo(0) {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CGmeEndManager::~CGmeEndManager() {
}

/// <summary>
/// �Q�[���I��������ݒ�
/// </summary>
/// <param name="endNo">�I���ԍ�</param>
void CGmeEndManager::SetGameEndCondition(int endNo) {
	m_GameEndNo = endNo;
	m_bGameEnd = true;
}