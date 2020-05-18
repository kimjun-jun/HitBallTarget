/**
* @file main.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン 
* @date 2019/09/01
*/
#pragma once

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <string.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

/**
* @def _TEST
* @brief 簡単な説明
* @details 詳細な説明
*/
#define SCREEN_W							(1280)						// ウインドウの幅
#define SCREEN_H							(960)						// ウインドウの高さ
#define SCREEN_CENTER_X						(SCREEN_W / 2)					// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y						(SCREEN_H / 2)					// ウインドウの中心Ｙ座標


#define BG_SIZE_H_TTOP						(240)						// BG奥行制限座標上部
#define BG_SIZE_H_TOP						(300)						// BG奥行制限座標上部
#define BG_SIZE_H_MID						(400)						// 　　　　　　　中部
#define BG_SIZE_H_UNDER						(480)						// 　　　　　　　下部
#define BG_SIZE_H_UUNDER					(600)						// 　　　　　　　下部
#define BG_SIZE_W_TOP						(120)						// BG左右制限座標
#define BG_SIZE_W_MID						(250)						// 　　　　　　　
#define BG_SIZE_W_UNDER						(450)						// 　　　　　　　


#define PY1_POS_Y							(SCREEN_CENTER_Y-150)		// ポリゴンの初期位置X
#define PY2_POS_Y							(SCREEN_CENTER_Y+100)		// ポリゴンの初期位置X
#define PX1_POS_X							(SCREEN_CENTER_X-250)		// 同上
#define PX2_POS_X							(SCREEN_CENTER_X+250)		// 同上




// 画面遷移定数
enum E_STAGE//列挙型。defineの番号を自動で割り当ててくれる。
{
	SCENE_TITLE,					//0。1つめだから0。列挙型の列挙定数名。定義した名前をシンボルっていうのが一般らしい。
	SCENE_TUTORIAL,					//1チュートリアル
	SCENE_TUTORIALMENU,				//2チュートリアル
	SCENE_SELECT,					//3難易度選択
	SCENE_GAMECOUNTDOWN,			//4ゲーム開始前のカウントダウン
	SCENE_GAME,						//5ゲーム
	SCENE_PAUSE,					//6ポーズ
	SCENE_OPTION,					//7オプション
	SCENE_R18SELECT,				//8R18画像選択
	SCENE_SENSITIVITY,				//9オプション
	SCENE_TUTOSENSITIVITY,			//10オプション
	SCENE_CONTYPE,					//11オプション
	SCENE_TUTOCONTYPE,				//12チュートリアル中A/D設定
	SCENE_RESULT_CLEAR,				//13クリアスコア
	SCENE_RESULT_FIELD,				//14失敗スコア
	SCENE_REGISTER,					//15ランキング登録
	SCENE_RANKING,					//16ランキング表示
	SCENE_MAX						//17個
};

//ゲームクリアの種類
enum GAMEEND
{
	CLEAR,
	FIELD,
};

//ゲームクリアの種類
enum MASTERVOLUMEOLCHENGE
{
	VOLUP,
	VOLDOWN,
};

//ランダムの種類
enum RAND
{
	X,
	Y,
};

//ミートカーソル大きさの種類
enum MEET
{
	BIG,
	SMALL,
};

//スコアの種類
enum SCORETYPE
{
	TIMEV,
	E,
	SCOREVAL,
};

//難易度の種類
enum GAMETYPE
{
	L,
	M,
	H,
};

//ポーズの種類
enum PAUSETYPE
{
	PAUSEHAJIMEKARA,
	PAUSECANCEL,
	PAUSEMODESELECT,
	PAUSEOPTION,
	PAUSEEND,
};

//テキストの種類
enum TEXT
{
	TEXT_STRIKE,
	TEXT_BALL,
	TEXT_DEADBALL,
};

//背景の種類
enum BGTYPE
{
	OBG,				//投打背景
	DBG					//守足背景
};

//ボールエフェクトの種類
enum BETYPE
{
	BE1,				//投打背景
	BE2					//守足背景
};

//プレイヤー種類
enum PLAYER_TYPE
{
	TYPE_PIT,
	TYPE_BAT,
};

//エネミー種類
enum ENEMY_TYPE
{
	TYPE_CAT,
	TYPE_SURAIMU,
	TYPE_HINOTAMA,
	TYPE_UFO
};

//バッターの描画種類
enum BATTERPATTERN
{
	BAT_PATTERN0,	// 通常
	BAT_PATTERN1,	// スイング1
	BAT_PATTERN2,	// スイング2
	BAT_PATTERN3,	// スイング3
	BAT_PATTERN4,	// アイドリング
};

//エネミーの描画種類
enum ENEMYRPATTERN
{
	ENEMY_PATTERN0,		// 下向き
	ENEMY_PATTERN1,		// 
	ENEMY_PATTERN2,		// 
	ENEMY_PATTERN3,		// 左向き
	ENEMY_PATTERN4,		// 
	ENEMY_PATTERN5,		// 
	ENEMY_PATTERN6,		// 右向き
	ENEMY_PATTERN7,		// 
	ENEMY_PATTERN8,		// 
	ENEMY_PATTERN9,		// 上向き
	ENEMY_PATTERN10,	// 
	ENEMY_PATTERN11,	// 
};

//移動方向
enum DIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFTUP,
	DIRECTION_RIGHTUP,
	DIRECTION_LEFTDOWN,
	DIRECTION_RIGHTDOWN,
};

enum BALLDERECTION
{
	BALL_DIRECTION_PULL_BUFF,			//打球方向
	BALL_DIRECTION_PULL_KARABURI,
	BALL_DIRECTION_PULL_FOUL,
	BALL_DIRECTION_PULL_MAX,
	BALL_DIRECTION_PULL_MID,
	BALL_DIRECTION_PULL_MIN,
	BALL_DIRECTION_JUST_MAX,
	BALL_DIRECTION_JUST,
	BALL_DIRECTION_JUST_MIN,
	BALL_DIRECTION_OPPO_MAX,
	BALL_DIRECTION_OPPO_MID,
	BALL_DIRECTION_OPPO_MIN,
	BALL_DIRECTION_OPPO_FOUL,
	BALL_DIRECTION_OPPO_KARABURI,
	BALL_DIRECTION_OPPO_BUFF,
};

#define	NUM_VERTEX											(4)					// 頂点数
#define	NUM_PLAYER											(2)					// ポリゴン数
#define	NUM_ENEMY_VERTEX									(16)					
#define	NUM_ENEMY											(16)					
#define	NUM_POLYGON											(2)	

// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D										(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3				vtx;						//! 頂点座標
	float					rhw;						//! テクスチャのパースペクティブコレクト用
	D3DCOLOR				diffuse;					//! 反射光
	D3DXVECTOR2				tex;						//! テクスチャ座標 
} VERTEX_2D;

// キャラクター構造体
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//! テクスチャへのポリゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		//! 頂点情報格納ワーク
	D3DXVECTOR3				pos;						//! 座標
	D3DXVECTOR3				rot;						//! 回転量
	D3DXVECTOR3				move;						//! 移動量
	D3DXVECTOR3				oldmove;					//! 古い移動量
	int						fps;						//! バッティングのタイミング値
	int						nCountAnim;					//! アニメカウント
	int						nPatternAnim;				//! アニメパターンナンバー 
	int						direction;					//! 移動方向
	bool					motion;						//! 動いてるかどうか
	bool					use;						//! 使用しているかどうか
} CHARACTER;



//各々の画像
#define TEXTURE_GAME_PITCHER								_T("data/TEXTURE/item/pitmachine.png")  
#define TEXTURE_GAME_BATTER									_T("data/TEXTURE/CHAR/bat.png") 
#define TEXTURE_GAME_UFO									_T("data/TEXTURE/CHAR/ufo.png") 
#define TEXTURE_GAME_CAT1									_T("data/TEXTURE/CHAR/cat1.png") 
#define TEXTURE_GAME_SURAIMU								_T("data/TEXTURE/CHAR/suraimu.png") 
#define TEXTURE_GAME_HINOTAMA								_T("data/TEXTURE/CHAR/hinotama.png") 
#define TEXTURE_GAME_SCORE									_T("data/TEXTURE/BG/0-9.png")	
#define	TEXTURE_SENSITIV									_T("data/TEXTURE/sozai/select/kando.png")		
#define	TEXTURE_CONTROLTYPE									_T("data/TEXTURE/sozai/select/ADset.png")		

//各々のテクスチャサイズX,Y
#define TEXTURE_PITCHER_SIZE_X								(60)
#define TEXTURE_PITCHER_SIZE_Y								(60)
#define TEXTURE_BATTER_SIZE_X								(130)
#define TEXTURE_BATTER_SIZE_Y								(130)
#define TEXTURE_CAT_SIZE_X									(50)
#define TEXTURE_CAT_SIZE_Y									(50)
#define TEXTURE_SURAIMU_SIZE_X								(50)
#define TEXTURE_SURAIMU_SIZE_Y								(50)
#define TEXTURE_HINOTAMA_SIZE_X								(50)
#define TEXTURE_HINOTAMA_SIZE_Y								(50)
#define TEXTURE_UFO_SIZE_X									(50)
#define TEXTURE_UFO_SIZE_Y									(50)
#define TEXTURE_CAT_SIZE_X_HALF								(TEXTURE_CAT_SIZE_X/2)
#define TEXTURE_CAT_SIZE_Y_HALF								(TEXTURE_CAT_SIZE_Y/2)

//各々のコリジョン用サイズ
#define TEXTURE_BATTER_COLLISION_BB_SIZE_X					(TEXTURE_BATTER_SIZE_X/2)
#define TEXTURE_BATTER_COLLISION_BB_SIZE_Y					(TEXTURE_BATTER_SIZE_Y*(75/100)) 
#define TEXTURE_CAT_COLLISION_BB_SIZE_X						(TEXTURE_CAT_SIZE_X)
#define TEXTURE_CAT_COLLISION_BB_SIZE_Y						(TEXTURE_CAT_SIZE_Y) 
#define TEXTURE_SURAIMU_COLLISION_BB_SIZE_X					(TEXTURE_SURAIMU_SIZE_X)
#define TEXTURE_SURAIMU_COLLISION_BB_SIZE_Y					(TEXTURE_SURAIMU_SIZE_Y) 
#define TEXTURE_HINOTAMA_COLLISION_BB_SIZE_X				(TEXTURE_HINOTAMA_SIZE_X)
#define TEXTURE_HINOTAMA_COLLISION_BB_SIZE_Y				(TEXTURE_HINOTAMA_SIZE_Y) 
#define TEXTURE_UFO_COLLISION_BB_SIZE_X						(TEXTURE_UFO_SIZE_X)
#define TEXTURE_UFO_COLLISION_BB_SIZE_Y						(TEXTURE_UFO_SIZE_Y) 

//各々のアニメパターンと分割数と切り替わるタイミング
//ピッチャー
#define TEXTURE_PITCHER_PATTERN_DIVIDE_X					(1)
#define TEXTURE_PITCHER_PATTERN_DIVIDE_Y					(1)
#define ANIM_PITCHER_PATTERN_NUM							(TEXTURE_PITCHER_PATTERN_DIVIDE_X*TEXTURE_PITCHER_PATTERN_DIVIDE_Y)
#define TIME_PITCHER_ANIMATION								(4)
//バッター
#define TEXTURE_BATTER_PATTERN_DIVIDE_X						(5)
#define TEXTURE_BATTER_PATTERN_DIVIDE_Y						(1)
#define ANIM_BATTER_PATTERN_NUM								(TEXTURE_BATTER_PATTERN_DIVIDE_X*TEXTURE_BATTER_PATTERN_DIVIDE_Y)
#define TIME_BATTER_ANIMATION_SLOW							(9)
#define TIME_BATTER_ANIMATION_MID							(7)
#define TIME_BATTER_ANIMATION_FAST							(5)
//猫
#define TEXTURE_CAT_PATTERN_DIVIDE_X						(3)
#define TEXTURE_CAT_PATTERN_DIVIDE_Y						(4)
#define ANIM_CAT_PATTERN_NUM								(TEXTURE_CAT_PATTERN_DIVIDE_X*TEXTURE_CAT_PATTERN_DIVIDE_Y)
#define TIME_CAT_ANIMATION_MID								(10)
#define TIME_CAT_MOVECOUNT_MID								(60)
//UFO
#define TEXTURE_UFO_PATTERN_DIVIDE_X						(1)
#define TEXTURE_UFO_PATTERN_DIVIDE_Y						(1)
#define ANIM_UFO_PATTERN_NUM								(TEXTURE_UFO_PATTERN_DIVIDE_X*TEXTURE_UFO_PATTERN_DIVIDE_Y)
#define TIME_UFO_ANIMATION_MID								(10)
#define TIME_UFO_MOVECOUNT_MID								(40)
//スライム
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_X					(3)
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_Y					(4)
#define ANIM_SURAIMU_PATTERN_NUM							(TEXTURE_SURAIMU_PATTERN_DIVIDE_X*TEXTURE_SURAIMU_PATTERN_DIVIDE_Y)
#define TIME_SURAIMU_ANIMATION_MID							(10)
#define TIME_SURAIMU_MOVECOUNT_MID							(40)
//火の玉
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_X					(3)
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y					(4)
#define ANIM_HINOTAMA_PATTERN_NUM							(TEXTURE_HINOTAMA_PATTERN_DIVIDE_X*TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y)
#define TIME_HINOTAMA_ANIMATION_MID							(10)
#define TIME_HINOTAMA_MOVECOUNT_MID							(40)

//エネミー変色スピード
#define TEXTURE_COROLSPEED									(5)

//移動時の速度 感度の部分
#define MOTION_SPEED_MID									(4.0f)
#define MOTION_ROOT_SPEED_MID								(3.41f)
#define MOTION_EFFECT_SPEED_MID								(1.0f)
#define BAT_MOTION_SPEED_MID								(8.0f)
#define BAT_MOTION_ROOT_SPEED_MID							(7.41f)

//ストライクゾーンの基準座標
#define STRIKE_REFERENCE_X									(SCREEN_CENTER_X);
#define STRIKE_REFERENCE_Y									(SCREEN_CENTER_Y+250.0f);
//ボールの基準座標
#define BALL_SHADOW_REFARENCE_X								(SCREEN_CENTER_X)//投球開始時のボール影基準座標X
#define BALL_SHADOW_REFARENCE_Y								(SCREEN_CENTER_Y-200.0f)//投球開始時のボール影基準座標Y

//投球されたボールがバッティングタイミングで赤くなる時のデクリメントされる座標
#define BALL_JUST_TIMING_RED								(50.0f) 

//ボールサイズ変化量
#define BALL_CHENGEVAL_SIZE									(0.01f)		//ボールが向かってくるとき徐々にサイズが変化する
#define BALL_CHENGEVAL_MAX									(1.05f)		//ボールが向かってくるとき徐々にサイズが変化する
#define BALL_CHENGEVAL_MIN									(0.95f)		//ボールが向かってくるとき徐々にサイズが変化する
#define BALL_CHENGEVALTYPEA_SIZE							(0.1f)		//ボールが向かってくるとき徐々にサイズが変化する
#define BALL_CHENGEVALTYPEA_MAX								(5.0f)		//ボールが向かってくるとき徐々にサイズが変化する
#define BALL_CHENGEVALTYPEA_MIN								(-5.0f)		//ボールが向かってくるとき徐々にサイズが変化する


//バッティング時のタイミング
#define BALL_TIMING_PULL_KARABURI							(42.0f)		//当たり　引っ張り　判定タイミング座標
#define BALL_TIMING_PULL_FOUL								(36.0f)		//		　引っ張り　
#define BALL_TIMING_PULL_MAX								(30.0f)		//		　引っ張り　
#define BALL_TIMING_PULL_MID								(24.0f)		//		　引っ張り　
#define BALL_TIMING_PULL_MIN								(18.0f)		//		　引っ張り　
#define BALL_TIMING_JUST_MAX								(12.0f)		//		　ジャスト　
#define BALL_TIMING_JUST									(6.0f)		//		　ジャスト　
#define BALL_TIMING_JUST_MIN								(12.0f)		//		　ジャスト　
#define BALL_TIMING_OPPOSITE_MAX							(18.0f)		//		　流し　	
#define BALL_TIMING_OPPOSITE_MID							(24.0f)		//		　流し　　　
#define BALL_TIMING_OPPOSITE_MIN							(30.0f)		//		　流し　	
#define BALL_TIMING_OPPOSITE_FOUL							(36.0f)		//		　流し　	
#define BALL_TIMING_OPPOSITE_KARABURI						(50.0f)		//		　流し　　　



//バッター、ミートカーソルの座標最大最小値
#define BATCURSOR_MOVE_STOP_X_MAX							(SCREEN_CENTER_X+70.0f)//バッターのX移動最低値
#define BATCURSOR_MOVE_STOP_X_MIN							(SCREEN_CENTER_X-70.0f)//バッターのX移動最低値
#define BATCURSOR_MOVE_STOP_Y_MAX							(SCREEN_CENTER_Y+335.0f)//バッターのX移動最低値
#define BATCURSOR_MOVE_STOP_Y_MIN							(SCREEN_CENTER_Y+165.0f)//バッターのX移動最低値

//プレイヤー、エネミー合計
#define PLAYER_GOUKEI										(2)
#define CAT_H_LEVEL											(80)
#define CAT_GOUKEI											(CAT_H_LEVEL)
#define CAT_M_LEVEL											(CAT_H_LEVEL/5)
#define CAT_L_LEVEL											(CAT_H_LEVEL/10)
#define SURAIMU_GOUKEI										(20)
#define HINOTAMA_GOUKEI										(20)
#define UFO_GOUKEI											(5)
#define ENEMY_GOUKEI										(SURAIMU_GOUKEI+HINOTAMA_GOUKEI)
#define ENEMY_TYPE											(4)

//エネミーのテクスチャサイズを奥行で変更
#define ENEMY_CHENGEVAL_SIZE								(0.2f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief 簡単な説明（～する関数）
* @param[in] a(引数名) 引数の説明
* @param[out] b(引数名) 引数の説明
* @return bool 戻り値の説明
* @details 詳細な説明
*/

/**
* @brief デバイス取得関数
* @return LPDIRECT3DDEVICE9
*/
LPDIRECT3DDEVICE9 GetDevice(void);

/**
* @brief 文字セットする関数
* @param[in] moji 表示したい文字を入力
* @details 打球方向判定用 Debugのみで使用
*/
void SelectText(char *moji);

/**
* @brief 文字を表示する関数
* @details 打球方向判定用 Debugのみで使用
*/
void DrawTextType(void);

/**
* @brief ゲームシーンをセットする関数
* @param[in] Scene 移動先シーンを入力
* @details ゲームシーンはE_STAGEを参照
*/
void SetScene(int Scene);

/**
* @brief 現在のゲームシーンを入手する関数
* @return int 現在のゲームシーンを返す
* @details ゲームシーンはE_STAGEを参照
*/
int GetScene(void);

/**
* @brief ゲームを初期化する関数
* @details ゲーム起動時に使用ゲームループ時に使用
*/
void InitGame(void);

/**
* @brief ゲームを再初期化する関数
* @details ゲームループ時(ゲームループを一周するタイミング)に使用
*/
void ReInitTuto(void);

/**
* @brief アップデートを再初期化する関数
* @details ゲームループ時に使用
*/
void UpdateReInit(void);

/**
* @brief 任意のランダム数値を決める関数
* @param[in] type どのエネミータイプか入力
* @return float エネミーの座標を返す
* @details エネミーの初期座標で使用
*/
float Random(int type);
