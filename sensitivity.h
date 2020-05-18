/**
* @file sensitivity.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_L1R1				_T("data/TEXTURE/sozai/select/digital.png")		
#define	TEXTURE_SENSITIVITYNUM		_T("data/TEXTURE/BG/0-9.png")		

#define TEXTURE_SENSITIVITYBROAD_SIZE_X		(200)										// タイトルロゴの幅
#define TEXTURE_SENSITIVITYBROAD_SIZE_Y		(100)										// タイトルロゴの高さ


#define SENSITIVITY_TEXTURE_PATTERN_DIVIDE_X	(10)	// アニメパターンのテクスチャ内分割数（X)  
#define SENSITIVITY_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)  
#define SENSITIVITY_ANIM_PATTERN_NUM			(SENSITIVITY_TEXTURE_PATTERN_DIVIDE_X*SENSITIVITY_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数  


#define	SENSITIVITYMAX		(2)						//ポーズ画面の選択肢数

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
}SENSITIVITY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSensitivity(int type);
void ReInitSensitivity(void);
void UninitSensitivity(void);
void UpdateSensitivity(void);
void UpdateTUTOSensitivity(void);
void DrawSensitivity(void);
void SetTextureSensitivity(void);
void SetVertexSensitivity(void);
int GetSSENSIkey(void);
