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
#define	TEXTURE_RESULT_OK		_T("data/TEXTURE/result/result_gameclear.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_NO		_T("data/TEXTURE/result/result_gameover.png")		// 読み込むテクスチャファイル名
#define	RESULT_OK_POS_X			(0)							// タイトルの表示位置
#define	RESULT_OK_POS_Y			(0)							// タイトルの表示位置
#define	RESULT_OK_SIZE_X		(SCREEN_W)						// タイトルの幅
#define	RESULT_OK_SIZE_Y		(SCREEN_H)						// タイトルの高さ
#define	RESULT_NO_POS_X			(0)						
#define	RESULT_NO_POS_Y			(0)						
#define	RESULT_NO_SIZE_X		(SCREEN_W)					
#define	RESULT_NO_SIZE_Y		(SCREEN_H)					

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(int type);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(int type);

