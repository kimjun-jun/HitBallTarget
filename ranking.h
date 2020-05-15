///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	select.h
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NUM					_T("data/TEXTURE/BG/0-9.png")		
#define	TEXTURE_ALPHA				_T("data/TEXTURE/sozai/keyborad.png")		
#define	TEXTURE_RANKINGLOGO			_T("data/TEXTURE/sozai/ranklogo.png")		

#define TEXTURE_RANKING_LOGO_SIZE_X			(200)										// タイトルロゴの幅
#define TEXTURE_RANKING_LOGO_SIZE_Y			(100)										// タイトルロゴの高さ
#define	TEXTURE_RANKING_RANK_SIZE_X			(200)					
#define	TEXTURE_RANKING_RANK_SIZE_Y			(100)					
#define	TEXTURE_RANKING_SCORE_SIZE_X		(20)					
#define	TEXTURE_RANKING_SCORE_SIZE_Y		(20)					
#define	TEXTURE_RANKING_NAME_SIZE_X			(200)					
#define	TEXTURE_RANKING_NAME_SIZE_Y			(100)					
					   

#define TEXTURE_RANKING_LOGO_POS_X			(SCREEN_CENTER_X)							// タイトルロゴの幅
#define TEXTURE_RANKING_LOGO_POS_Y			(SCREEN_CENTER_Y-300.0f)					// タイトルロゴの高さ

#define	TEXTURE_RANKING_RANK147_POS_X			(SCREEN_CENTER_X-300.0f)
#define	TEXTURE_RANKING_RANK258_POS_X			(SCREEN_CENTER_X)					
#define	TEXTURE_RANKING_RANK369_POS_X			(SCREEN_CENTER_X+300.0f)	
#define	TEXTURE_RANKING_RANK123_POS_Y			(SCREEN_CENTER_Y-300.0f)
#define	TEXTURE_RANKING_RANK456_POS_Y			(SCREEN_CENTER_Y)					
#define	TEXTURE_RANKING_RANK789_POS_Y			(SCREEN_CENTER_Y+300.0f)					

#define	TEXTURE_RANKING_SCORE147_POS_X			(SCREEN_CENTER_X-200.0f)
#define	TEXTURE_RANKING_SCORE258_POS_X			(SCREEN_CENTER_X)
#define	TEXTURE_RANKING_SCORE369_POS_X			(SCREEN_CENTER_X+200.0f)
#define	TEXTURE_RANKING_SCORE123_POS_Y			(SCREEN_CENTER_Y-300.0f)
#define	TEXTURE_RANKING_SCORE456_POS_Y			(SCREEN_CENTER_Y)
#define	TEXTURE_RANKING_SCORE789_POS_Y			(SCREEN_CENTER_Y+300.0f)

#define	TEXTURE_RANKING_NAME147_POS_X			(SCREEN_CENTER_X-100.0f)
#define	TEXTURE_RANKING_NAME258_POS_X			(SCREEN_CENTER_X)					
#define	TEXTURE_RANKING_NAME369_POS_X			(SCREEN_CENTER_X+100.0f)	
#define	TEXTURE_RANKING_NAME123_POS_Y			(SCREEN_CENTER_Y-300.0f)
#define	TEXTURE_RANKING_NAME456_POS_Y			(SCREEN_CENTER_Y)					
#define	TEXTURE_RANKING_NAME789_POS_Y			(SCREEN_CENTER_Y+300.0f)					


#define	RANKINGSOCRED		(4)						//ポーズ画面の選択肢数
#define	RANKINGMAX			(9)						//ポーズ画面の選択肢数
#define	RANKINGLOGO_MAX		(1)						//ポーズ画面の選択肢数

#define	TEXTURE_RANKING_SCORE_OFFSET_POS_X			(10.0f)

typedef struct
{
	LPDIRECT3DTEXTURE9		namepD3DTexture = NULL;			// テクス?ャへの?リゴン 
	LPDIRECT3DTEXTURE9		numpD3DTexture = NULL;			// テクス?ャへの?リゴン 
	LPDIRECT3DTEXTURE9		scorepD3DTexture = NULL;			// テクス?ャへの?リゴン 

	VERTEX_2D				namevertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク
	VERTEX_2D				numvertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク
	VERTEX_2D				scorevertexWk[RANKINGSOCRED][NUM_VERTEX];		// [桁][頂点]

	D3DXVECTOR3				namepos;						// ?リゴンの移動量
	D3DXVECTOR3				numpos;						// ?リゴンの移動量
	D3DXVECTOR3				scorepos[RANKINGSOCRED];						// ?リゴンの移動量

	bool					use;
}RANKING;


typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク
	D3DXVECTOR3				pos;						// ?リゴンの移動量
	bool					use;
}RANKINGLOGO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRanking(int type);
void ReInitRanking(int type);
void UninitRanking(void);
void UpdateRanking(void);
void UpdateinRanking(void);
void DrawRanking(void);
void SetTextureRanking(void);
void SetVertexRanking(void);
RANKING *GetRanking(void);
