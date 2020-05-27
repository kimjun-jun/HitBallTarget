/**
* @file enemy.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
/**
*　@struct CAT
*　@brief 2Dポリゴンを定義する構造体(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< テクスチャへのポインタ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;						//!< 座標
	D3DXVECTOR3				rot;						//!< 回転角
	D3DXVECTOR3				move;						//!< 移動量
	D3DXVECTOR3				oldmove;					//!< 古い移動量
	D3DXVECTOR3				oldpos;						//!< 古い座標
	D3DXVECTOR3				ppos[4];					//!< 4分割ポリゴンの各ポリゴン中心座標
	int						colori;						//!< 変色値(int)
	int						nCountAnim;					//!< アニメカウント 
	int						nPatternAnim;				//!< アニメパターン 
	int						direction;					//!< 移動方向
	int						movecount;					//!< 移動カウント
	int						point;						//!< 得点
	float					chengeval;					//!< 変化量
	float					oldchengeval;				//!< 古い変化量
	bool					motion;						//!< モーションしているかどうか
	bool					use;						//!< 使用しているかどうか
	bool					color;						//!< 変色判定
	bool					effect;						//!< エフェクト判定
} CAT;

/**
*　@struct SURAIMU
*　@brief 2Dポリゴンを定義する構造体(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< テクスチャへのポインタ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;						//!< 座標
	D3DXVECTOR3				rot;						//!< 回転角
	D3DXVECTOR3				move;						//!< 移動量
	D3DXVECTOR3				oldmove;					//!< 古い移動量
	D3DXVECTOR3				oldpos;						//!< 古い座標
	D3DXVECTOR3				ppos[4];					//!< 4分割ポリゴンの各ポリゴン中心座標
	int						colori;						//!< 変色値(int)
	int						nCountAnim;					//!< アニメカウント 
	int						nPatternAnim;				//!< アニメパターン 
	int						direction;					//!< 移動方向
	int						movecount;					//!< 移動カウント
	int						point;						//!< 得点
	float					chengeval;					//!< 変化量
	float					oldchengeval;				//!< 古い変化量
	bool					motion;						//!< モーションしているかどうか
	bool					use;						//!< 使用しているかどうか
	bool					color;						//!< 変色判定
	bool					effect;						//!< エフェクト判定
} SURAIMU;

/**
*　@struct HINOTAMA
*　@brief 2Dポリゴンを定義する構造体(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< テクスチャへのポインタ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;						//!< 座標
	D3DXVECTOR3				rot;						//!< 回転角
	D3DXVECTOR3				move;						//!< 移動量
	D3DXVECTOR3				oldmove;					//!< 古い移動量
	D3DXVECTOR3				oldpos;						//!< 古い座標
	D3DXVECTOR3				ppos[4];					//!< 4分割ポリゴンの各ポリゴン中心座標
	int						colori;						//!< 変色値(int)
	int						nCountAnim;					//!< アニメカウント 
	int						nPatternAnim;				//!< アニメパターン 
	int						direction;					//!< 移動方向
	int						movecount;					//!< 移動カウント
	int						point;						//!< 得点
	float					chengeval;					//!< 変化量
	float					oldchengeval;				//!< 古い変化量
	bool					motion;						//!< モーションしているかどうか
	bool					use;						//!< 使用しているかどうか
	bool					color;						//!< 変色判定
	bool					effect;						//!< エフェクト判定
} HINOTAMA;

/**
*　@struct UFO
*　@brief 2Dポリゴンを定義する構造体(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< テクスチャへのポインタ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;						//!< 座標
	D3DXVECTOR3				rot;						//!< 回転角
	D3DXVECTOR3				move;						//!< 移動量
	D3DXVECTOR3				oldmove;					//!< 古い移動量
	D3DXVECTOR3				ppos[4];					//!< 古い座標
	D3DXVECTOR3				oldpos;						//!< 4分割ポリゴンの各ポリゴン中心座標
	int						nCountAnim;					//!< 変色値(int)
	int						nPatternAnim;				//!< アニメカウント 
	int						direction;					//!< アニメパターン 
	int						colori;						//!< 移動方向
	int						point;						//!< 移動カウント
	float					movecount;					//!< 得点
	float					rad;						//!< 変化量
	float					angle;						//!< 古い変化量
	bool					motion;						//!< モーションしているかどうか
	bool					use;						//!< 使用しているかどうか
	bool					color;						//!< 変色判定
	bool					effect;						//!< エフェクト判定
} UFO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Enemy初期化関数 InitEnemy
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitEnemy(int type);

/**
* @brief Enemy再初期化関数 ReInitEnemy
*/
void ReInitEnemy(void);

/**
* @brief Enemy開放関数 UninitEnemy
*/
void UninitEnemy(void);

/**
* @brief Enemy更新関数 UpdateEnemy
*/
void UpdateEnemy(void);

/**
* @brief Enemy描画関数 DrawEnemy
*/
void DrawEnemy(void);

/**
* @brief Enemy取得関数 GetCat
* @param[in] int i アドレス番地指定
* @return CAT
*/
CAT *GetCat(int i);

/**
* @brief Enemy取得関数 GetSuraimu
* @param[in] int i アドレス番地指定
* @return SURAIMU
*/
SURAIMU *GetSuraimu(int i);

/**
* @brief Enemy取得関数 GetHinotama
* @param[in] int i アドレス番地指定
* @return HINOTAMA
*/
HINOTAMA *GetHinotama(int i);

/**
* @brief Enemy取得関数 GetUfo
* @param[in] int i アドレス番地指定
* @return UFO
*/
UFO *GetUfo(int i);
