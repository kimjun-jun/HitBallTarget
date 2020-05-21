/**
* @file title.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/title/title_logo.png")			// 読み込むテクスチャファイル名
#define	TITLELOGO_POS_X		(SCREEN_CENTER_X)								// タイトルロゴの表示位置
#define	TITLELOGO_POS_Y		(SCREEN_CENTER_Y)								// タイトルロゴの表示位置
#define	TITLELOGO_SIZE_X	(SCREEN_CENTER_X/2)								// タイトルロゴの幅
#define	TITLELOGO_SIZE_Y	(SCREEN_CENTER_Y/2)								// タイトルロゴの高さ

#define	TITLE_GOUKEI	(1)													// 

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク
}TITLE;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(int type);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

