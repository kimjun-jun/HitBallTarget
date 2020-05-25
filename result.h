/**
* @file result.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULT_OK		_T("data/TEXTURE/result/result_gameclear.png")			//!< 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_NO		_T("data/TEXTURE/result/result_gameover.png")			//!< 読み込むテクスチャファイル名
#define	RESULT_POS_X			(0)														//!< ポリゴンの表示位置X
#define	RESULT_POS_Y			(0)														//!< ポリゴンの表示位置Y
#define	RESULT_SIZE_X			(SCREEN_W)												//!< ポリゴンの幅
#define	RESULT_SIZE_Y			(SCREEN_H)												//!< ポリゴンの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Result初期化関数 InitResult
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitResult(int type);

/**
* @brief Result開放関数 UninitResult
*/
void UninitResult(void);

/**
* @brief Result更新関数 UpdateResult
*/
void UpdateResult(void);

/**
* @brief Result描画関数 DrawResult
* @param[in] type 描画タイプ
*/
void DrawResult(int type);

