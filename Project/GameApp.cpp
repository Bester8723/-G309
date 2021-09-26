/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"GameDefine.h"
#include	"SceneBase.h"
#include	"SceneTitle.h"
#include	"SceneStageSelect.h"
#include	"SceneGame.h"

//デバッグ用フラグ
bool m_bDebug = false;
//シーンクラス
CSceneBase* gpScene = NULL;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//最初に実行されるシーンの初期化
	gpScene = new CSceneTitle();
	gpScene->Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

	//シーンの更新
	gpScene->Update();
	//シーンが終了したか
	if (gpScene->IsEnd())
	{
		//次のシーンを取得
		int change = gpScene->GetNextScene();
		//古いシーンを消去する
		gpScene->Release();
		delete gpScene;
		//次のシーン番号に応じてシーンを作って初期化する
		switch (change)
		{
		case SCENENO_TITLE:
			gpScene = new CSceneTitle();
			break;
		case SCENENO_STAGESELECT:
			gpScene = new CSceneStageSelect();
			break;
		case SCENENO_GAME:
			gpScene = new CSceneGame();
			break;
		case SCENENO_RESULT:
			gpScene = new CSceneGameClear();
			break;
		default:
			gpScene = new CSceneTitle();
			break;
		}
		gpScene->Initialize();
	}

#ifdef _DEBUG
	//F1キーでデバッグ表示の切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_bDebug = !m_bDebug;
	}
#endif // _DEBUG


	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	//シーンの描画
	gpScene->Render();
	//シーンのデバッグ描画
	if (m_bDebug)
	{
		gpScene->RenderDebug();
	}

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	//シーンの解放
	if (gpScene)
	{
		delete gpScene;
		gpScene = NULL;
	}
	return TRUE;
}