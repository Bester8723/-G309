/*************************************************************************//*!

					@file	SceneBase.cpp
					@brief	シーン基礎。

															@author	池上　綾香
*//**************************************************************************/
#include "SceneBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
CSceneBase::CSceneBase() :
m_bEnd(false),
m_bChange(false),
m_NextScene(0) {
}

/// <summary>
/// デストラクタ
/// </summary>
CSceneBase::~CSceneBase() {
}