/**
* @file score.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once


// マクロ定義
#define TEXTURE_GAME_DOT	_T("data/TEXTURE/BG/dot.png")	
#define TEXTURE_SCORE_SIZE_X	(50) // テクスチャサイズ 
#define TEXTURE_SCORE_SIZE_Y	(50) // 同上  
#define SCORE_TEXTURE_PATTERN_DIVIDE_X	(10)	// アニメパターンのテクスチャ内分割数（X)  
#define SCORE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)  
#define SCORE_ANIM_PATTERN_NUM			(SCORE_TEXTURE_PATTERN_DIVIDE_X*SCORE_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数  
#define SCORE_TIME_ANIMATION			(4)	// アニメーションの切り替わるカウント  
#define TEXTURE_DOT_SIZE_X	(7) // テクスチャサイズ 
#define TEXTURE_DOT_SIZE_Y	(7) // 同上  


#define DOT_GOUKEI					(2)
#define TIME_DIGIT					(3)
#define SCORE_DIGIT					(4)
#define SCORE_GOUKEI				(60) //スコアの合計
#define FPS_TIME_COUNT				(4200) //毎フレームカウントしてタイム計測


#define TEXTURE_GAME_SCORELOGO	_T("data/TEXTURE/sozai/SCORE.png") 
#define TEXTURE_GAME_TIMELOGO	_T("data/TEXTURE/sozai/TIME.png") 
#define TEXTURE_SCORELOGO_SIZE_X	(100) // テクスチャサイズ
#define TEXTURE_SCORELOGO_SIZE_Y	(75) // 同上  
#define TEXTURE_TIMELOGO_SIZE_X	(100) // テクスチャサイズ 
#define TEXTURE_TIMELOGO_SIZE_Y	(75) // 同上  

#define TEXTURE_SCORE_POS_X	(SCREEN_CENTER_X-430.0f) // テクスチャサイズ
#define TEXTURE_SCORE_POS_Y	(SCREEN_CENTER_Y+400.0f) // 同上  
#define TEXTURE_TIME_POS_X	(SCREEN_CENTER_X+570.0f) // テクスチャサイズ 
#define TEXTURE_TIME_POS_Y	(TEXTURE_SCORE_POS_Y) // 同上  


#define TEXTURE_SCORELOGO_POS_X	(SCREEN_CENTER_X-520.0f) // テクスチャサイズ
#define TEXTURE_SCORELOGO_POS_Y	(TEXTURE_SCORE_POS_Y-120.0f) // 同上  
#define TEXTURE_TIMELOGO_POS_X	(SCREEN_CENTER_X+520.0f) // テクスチャサイズ 
#define TEXTURE_TIMELOGO_POS_Y	(TEXTURE_TIME_POS_Y-100.0f) // 同上  

#define NUM_INTERVAL_X	(60.0f) // 同上  

//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
typedef struct // エネミー構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		

	VERTEX_2D				texture[NUM_VERTEX];

	D3DXVECTOR3				pos;					
	D3DXVECTOR3				rot;					
	int						nCountAnim;				
	int						nPatternAnim;
	bool					use;
} TIME;

typedef struct // エネミー構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		

	VERTEX_2D				texture[NUM_VERTEX];

	D3DXVECTOR3				pos;					
	D3DXVECTOR3				rot;					
	int						nCountAnim;				
	int						nPatternAnim;
	int						level;
} SCORE;

typedef struct // エネミー構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		

	VERTEX_2D				texture[NUM_VERTEX];

	D3DXVECTOR3				pos;					
	int						nCountAnim;				
	int						nPatternAnim;			
} DOT;

typedef struct // エネミー構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;
	VERTEX_2D				texture[NUM_VERTEX];
	D3DXVECTOR3				pos;
} TIMELOGO;

typedef struct // エネミー構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;
	VERTEX_2D				texture[NUM_VERTEX];
	D3DXVECTOR3				pos;
} SCORELOGO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int type);
void ReInitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
SCORE *GetScore(void);
int *GetTimemaneger(void);
int *GetScoremaneger(void);
void AddScore(int val,int type);

