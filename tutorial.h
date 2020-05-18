/**
* @file tutorial.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TUTORIALF1		_T("data/TEXTURE/tutorial/tutorialF1.png")			
#define	TEXTURE_TUTORIALF2		_T("data/TEXTURE/tutorial/tutorialF2.png")			
#define	TEXTURE_TUTORIALF3		_T("data/TEXTURE/tutorial/tutorialF3.png")
#define	TUTORIAL_POS_X			(0)													// チュートリアルの表示位置
#define	TUTORIAL_POS_Y			(0)													// チュートリアルの表示位置
#define	TUTORIAL_SIZE_X			(SCREEN_W)												// チュートリアルの幅
#define	TUTORIAL_SIZE_Y			(SCREEN_H)												// チュートリアルの高さ

#define TUTORIAL_GOUKEI			(3)

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
}TUTO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorial(int type);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

