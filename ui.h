/**
* @file ui.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once


// マクロ定義
//UI
#define UI_GOUKEI						(2)

//ストライクゾーン
#define TEXTURE_GAME_STRIKE	_T("data/TEXTURE/item/strike.png")	// サンプル用画像  

#define TEXTURE_STRIKE_SIZE_X	(150/2) // テクスチャサイズ 
#define TEXTURE_STRIKE_SIZE_Y	(180/2) // 同上  

#define TEXTURE_STRIKE_COLLISION_BB_SIZE_X	(150/2) // テクスチャサイズ 
#define TEXTURE_STRIKE_COLLISION_BB_SIZE_Y	(180/2) // 同上  

#define TEXTURE_STRIKE_COLLISION_BC_SIZE		((TEXTURE_STRIKE_SIZE_X+TEXTURE_STRIKE_SIZE_Y)/2) // バレット当たり判定BCテクスチャサイズ 


#define STRIKE_TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)  
#define STRIKE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)  
#define STRIKE_ANIM_PATTERN_NUM			(STRIKE_TEXTURE_PATTERN_DIVIDE_X*STRIKE_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数  
#define STRIKE_TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント  

#define STRIKE_GOUKEI						(1) //ボールの合計

#define STRIKE_NO						(0)

//ミートカーソル
#define TEXTURE_GAME_CURSOR	_T("data/TEXTURE/item/batcursor.png")	// サンプル用画像  

#define TEXTURE_CURSOR_BIG_SIZE_X	(75/2) // テクスチャサイズ 
#define TEXTURE_CURSOR_BIG_SIZE_Y	(75/2) // 同上  
#define TEXTURE_CURSOR_BIG_COLLISION_BC_SIZE		((TEXTURE_CURSOR_BIG_SIZE_X+TEXTURE_CURSOR_BIG_SIZE_Y)/2) // バレット当たり判定BCテクスチャサイズ 


#define TEXTURE_CURSOR_SMALL_SIZE_X	(30/2) // テクスチャサイズ 
#define TEXTURE_CURSOR_SMALL_SIZE_Y	(30/2) // 同上  
#define TEXTURE_CURSOR_SMALL_COLLISION_BC_SIZE		((TEXTURE_CURSOR_SMALL_SIZE_X+TEXTURE_CURSOR_SMALL_SIZE_Y)/2) // バレット当たり判定BCテクスチャサイズ 


#define CURSOR_TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)  
#define CURSOR_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)  
#define CURSOR_ANIM_PATTERN_NUM			(CURSOR_TEXTURE_PATTERN_DIVIDE_X*CURSOR_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数  
#define CURSOR_TIME_ANIMATION				(4)	// アニメーションの切り替わるカウント  

#define CURSOR_GOUKEI						(1) //ボールの合計

#define CURSOR_NO						(1)


//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
/**
*　@struct TITLE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct // バレット構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポリゴン 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	D3DXVECTOR3				pos;						// ポリゴンの移動量
	D3DXVECTOR3				rot;						// ポリゴンの回転量
	int						nCountAnim;					// アニメーションカウント 
	int						nPatternAnim;				// アニメーションパターンナンバー 
	int						direction;					// ポリゴンの移動方向
	int						meet;
	bool					use;
} Ui;

/**
*　@struct TITLE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct // バレット構造体
{
	Ui s;
}STRIKE;

/**
*　@struct TITLE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct // バレット構造体
{
	Ui c;
}CURSOR;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief R18初期化関数 InitR18select
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitUi(int type);
/**
* @brief R18再初期化関数 ReInitR18select
*/
void ReInitUi(void);
/**
* @brief R18開放関数 UninitR18select
*/
void UninitUi(void);
/**
* @brief R18更新関数 UpdateR18select
*/
void UpdateUi(void);
/**
* @brief R18描画関数 DrawR18select
*/
void DrawUi(void);

/**
* @brief R18取得関数 GetR18select
*/
STRIKE *GetStrike(void);
/**
* @brief R18取得関数 GetR18select
*/
CURSOR *Get_Cursor(void);

HRESULT MakeVertexUi(int i);
void SetTextureUi(int cntPattern, int i);	// 
void SetVertexUi(int i);					// 

