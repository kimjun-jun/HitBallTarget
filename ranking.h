/**
* @file ranking.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NUM							_T("data/TEXTURE/BG/0-9.png")				//!< 読み込むテクスチャファイル名
#define	TEXTURE_ALPHA						_T("data/TEXTURE/sozai/keyborad.png")		//!< 読み込むテクスチャファイル名
#define	TEXTURE_RANKINGLOGO					_T("data/TEXTURE/sozai/ranklogo.png")		//!< 読み込むテクスチャファイル名
#define TEXTURE_RANKING_LOGO_SIZE_X			(200)										//!< ポリゴンの幅
#define TEXTURE_RANKING_LOGO_SIZE_Y			(100)										//!< ポリゴンの高さ
#define	TEXTURE_RANKING_RANK_SIZE_X			(200)										//!< ポリゴンの幅
#define	TEXTURE_RANKING_RANK_SIZE_Y			(100)										//!< ポリゴンの高さ
#define	TEXTURE_RANKING_SCORE_SIZE_X		(20)										//!< ポリゴンの幅
#define	TEXTURE_RANKING_SCORE_SIZE_Y		(20)										//!< ポリゴンの高さ
#define	TEXTURE_RANKING_NAME_SIZE_X			(200)										//!< ポリゴンの幅
#define	TEXTURE_RANKING_NAME_SIZE_Y			(100)										//!< ポリゴンの高さ
#define TEXTURE_RANKING_LOGO_POS_X			(SCREEN_CENTER_X)							//!< ポリゴンの座標X
#define TEXTURE_RANKING_LOGO_POS_Y			(SCREEN_CENTER_Y-300.0f)					//!< ポリゴンの座標Y
#define	RANKINGSOCRED						(4)											//!< 登録されるスコアの桁数
#define	RANKINGMAX							(9)											//!< 登録できる合計数
#define	RANKINGLOGO_MAX						(1)											//!< ロゴの合計
#define	TEXTURE_RANKING_SCORE_OFFSET_POS_X	(10.0f)										//!< 順位の表示間隔オフセット値

/**
*　@struct RANKING
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		namepD3DTexture = NULL;										//!< テクスチャへのポリゴン 
	LPDIRECT3DTEXTURE9		numpD3DTexture = NULL;										//!< テクスチャへのポリゴン 
	LPDIRECT3DTEXTURE9		scorepD3DTexture = NULL;									//!< テクスチャへのポリゴン 
	VERTEX_2D				namevertexWk[NUM_VERTEX];									//!< 頂点情報格納ワーク
	VERTEX_2D				numvertexWk[NUM_VERTEX];									//!< 頂点情報格納ワーク
	VERTEX_2D				scorevertexWk[RANKINGSOCRED][NUM_VERTEX];					//!< 頂点情報格納ワーク[桁][頂点]
	D3DXVECTOR3				namepos;													//!< ポリゴンの座標
	D3DXVECTOR3				numpos;														//!< ポリゴンの座標
	D3DXVECTOR3				scorepos[RANKINGSOCRED];									//!< ポリゴンの座標[桁数]
	bool					use;														//!< 使用しているかどうか
}RANKING;


/**
*　@struct RANKINGLOGO
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;											//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];										//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;														//!< ポリゴンの座標
	bool					use;														//!< 使用しているかどうか
}RANKINGLOGO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Ranking初期化関数 InitRanking
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitRanking(int type);

/**
* @brief Ranking再初期化関数 ReInitRanking
*/
void ReInitRanking(int type);

/**
* @brief Ranking開放関数 UninitRanking
*/
void UninitRanking(void);

/**
* @brief Ranking更新関数 UpdateRanking
*/
void UpdateRanking(void);

/**
* @brief Ranking描画関数 DrawRanking
*/
void DrawRanking(void);

/**
* @brief Ranking取得関数 GetRanking
* @return RANKING
*/
RANKING *GetRanking(void);
