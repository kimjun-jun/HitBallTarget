/**
* @file main.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン 
* @date 2019/09/01
*/
#pragma once

/** 
*　@brief fscanf のwarning防止
*/
#define _CRT_SECURE_NO_WARNINGS

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <string.h>

/** @def
* 警告対処
*/
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#include "mmsystem.h"


#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

/** @def
* ウインドウの幅
*/
#define SCREEN_W							(1280)	

/** @def
* ウインドウの高さ
*/
#define SCREEN_H							(960)		

/** @def
* ウインドウの中心Ｘ座標
*/
#define SCREEN_CENTER_X						(SCREEN_W / 2)	

/** @def
* ウインドウの中心Ｙ座標
*/
#define SCREEN_CENTER_Y						(SCREEN_H / 2)	

/** @def
* BG奥行制限座標上部
*/
#define BG_SIZE_H_TTOP						(240)			

/** @def
* BG奥行制限座標上部
*/
#define BG_SIZE_H_TOP						(300)			

/** @def
*  BG奥行制限座標中部
*/
#define BG_SIZE_H_MID						(400)			

/** @def
*  BG奥行制限座標下部
*/
#define BG_SIZE_H_UNDER						(480)			

/** @def
*  BG奥行制限座標下部2
*/
#define BG_SIZE_H_UUNDER					(600)			

/** @def
* BG左右制限座標 低
*/
#define BG_SIZE_W_TOP						(120)			

/** @def
* BG左右制限座標　中
*/
#define BG_SIZE_W_MID						(250)			

/** @def
* BG左右制限座標　高
*/
#define BG_SIZE_W_UNDER						(450)			

/** @def
* ポリゴンの初期位置Y1
*/
#define PY1_POS_Y							(SCREEN_CENTER_Y-150)	

/** @def
* ポリゴンの初期位置Y2
*/
#define PY2_POS_Y							(SCREEN_CENTER_Y+100)	

/** @def
* ポリゴンの初期位置X1
*/
#define PX1_POS_X							(SCREEN_CENTER_X-250)	

/** @def
* ポリゴンの初期位置X2
*/
#define PX2_POS_X							(SCREEN_CENTER_X+250)	


/**
 * @enum E_STAGE
 * 画面遷移定数
 */
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

/**
 * @enum GAMEEND
 * ゲームクリアの種類
 */
enum GAMEEND
{
	CLEAR,
	FIELD
};

/**
 * @enum MASTERVOLUMEOLCHENGE
 * 音量の調整
 */
enum MASTERVOLUMEOLCHENGE
{
	VOL_UP,
	VOL_DOWN
};

/**
 * @enum RAND
 * ランダムの種類
 */
enum RAND
{
	X,
	Y
};

/**
 * @enum MEET
 * ミートカーソルの種類
 */
enum MEET
{
	BIG,
	SMALL
};

/**
 * @enum SCORETYPE
 * スコアの種類
 */
enum SCORETYPE
{
	TIME_VAL,
	ENEMY_VAL,
	SCORE_VAL
};

/**
 * @enum GAMETYPE
 * 難易度の種類
 */
enum GAMETYPE
{
	L,
	M,
	H
};

/**
 * @enum PAUSETYPE
 * ポーズメニューの種類
 */
enum PAUSETYPE
{
	PAUSE_HAJIMEKARA,
	PAUSE_CANCEL,
	PAUSE_MODESELECT,
	PAUSE_OPTION,
	PAUSE_END
};

/**
 * @enum TEXT
 * テキストの種類
 */
enum TEXT
{
	TEXT_STRIKE,
	TEXT_BALL,
	TEXT_DEADBALL
};

/**
 * @enum BETYPE
 * ボールエフェクトの種類
 */
enum BETYPE
{
	BALL_EFFECT1,				//ボールエフェクト1
	BALL_EFFECT2				//ボールエフェクト2
};

/**
 * @enum PLAYER_TYPE
 * プレイヤー種類
 */
enum PLAYER_TYPE
{
	TYPE_PIT,
	TYPE_BAT,
};

/**
 * @enum ENEMY_TYPE
 * エネミー種類
 */
enum ENEMY_TYPE
{
	TYPE_CAT,
	TYPE_SURAIMU,
	TYPE_HINOTAMA,
	TYPE_UFO
};

/**
 * @enum BATTERPATTERN
 * バッターの描画種類
 */
enum BATTERPATTERN
{
	BAT_PATTERN0,	// 通常
	BAT_PATTERN1,	// スイング1
	BAT_PATTERN2,	// スイング2
	BAT_PATTERN3,	// スイング3
	BAT_PATTERN4	// アイドリング
};

/**
 * @enum ENEMYRPATTERN
 * エネミーの描画種類
 */
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
	ENEMY_PATTERN11		// 
};

/**
 * @enum DIRECTION
 * 移動方向
 */
enum DIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFTUP,
	DIRECTION_RIGHTUP,
	DIRECTION_LEFTDOWN,
	DIRECTION_RIGHTDOWN
};

/**
 * @enum BALLDERECTION
 * 打球方向
 */
enum BALLDERECTION
{
	BALL_DIRECTION_PULL_BUFF,
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
	BALL_DIRECTION_OPPO_BUFF
};

/** @def
*  標準な頂点数
*/
#define	NUM_VERTEX											(4)				

/** @def
* 標準ポリゴン数
*/
#define	NUM_POLYGON											(2)				

/** @def
* エネミー頂点数
*/
#define	NUM_ENEMY_VERTEX									(16)			

/** @def
* エネミーポリゴン数
*/
#define	NUM_ENEMY											(16)			

/** @def
* 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
*/
#define	FVF_VERTEX_2D										(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	//! 頂点座標
	D3DXVECTOR3					vtx;						
	//! テクスチャのパースペクティブコレクト用
	float						rhw;						
	//! 反射光
	D3DCOLOR					diffuse;					
	//! テクスチャ座標
	D3DXVECTOR2					tex;						
} VERTEX_2D;

// キャラクター構造体
typedef struct
{
	//! テクスチャへのポリゴン
		LPDIRECT3DTEXTURE9		pD3DTexture = NULL;
	//! 頂点情報格納ワーク
		VERTEX_2D				vertexWk[NUM_VERTEX];
	//! 座標
		D3DXVECTOR3				pos;
	//! 回転量
		D3DXVECTOR3				rot;
	//! 移動量
		D3DXVECTOR3				move;
	//! 古い移動量
		D3DXVECTOR3				oldmove;
	//! バッティングのタイミング値
		int						fps;
	//! アニメカウント
		int						nCountAnim;
	//! アニメパターンナンバー
		int						nPatternAnim;
	//! 移動方向
		int						direction;
	//! 動いてるかどうか
		bool					motion;
	//! 使用しているかどうか
		bool					use;						
} CHARACTER;



//各々の画像
/** @def
* PITCHERの画像
*/
#define TEXTURE_GAME_PITCHER								_T("data/TEXTURE/item/pitmachine.png")  

/** @def
* BATTERの画像
*/
#define TEXTURE_GAME_BATTER									_T("data/TEXTURE/CHAR/bat.png") 

/** @def
* UFOの画像
*/
#define TEXTURE_GAME_UFO									_T("data/TEXTURE/CHAR/ufo.png") 

/** @def
* CATの画像
*/
#define TEXTURE_GAME_CAT									_T("data/TEXTURE/CHAR/cat1.png") 

/** @def
* SURAIMUの画像
*/
#define TEXTURE_GAME_SURAIMU								_T("data/TEXTURE/CHAR/suraimu.png") 

/** @def
* HINOTAMAの画像
*/
#define TEXTURE_GAME_HINOTAMA								_T("data/TEXTURE/CHAR/hinotama.png") 

/** @def
* SCOREの画像
*/
#define TEXTURE_GAME_SCORE									_T("data/TEXTURE/BG/0-9.png")	

/** @def
* SENSITIVの画像
*/
#define	TEXTURE_SENSITIV									_T("data/TEXTURE/sozai/select/kando.png")		

/** @def
* CONTROLTYPEの画像
*/
#define	TEXTURE_CONTROLTYPE									_T("data/TEXTURE/sozai/select/ADset.png")		


//各々のテクスチャサイズX,Y
/** @def
* PITCHERのサイズX
*/
#define TEXTURE_PITCHER_SIZE_X								(60)

/** @def
* PITCHERのサイズY
*/
#define TEXTURE_PITCHER_SIZE_Y								(60)

/** @def
* BATTERのサイズX
*/
#define TEXTURE_BATTER_SIZE_X								(130)

/** @def
* BATTERのサイズY
*/
#define TEXTURE_BATTER_SIZE_Y								(130)

/** @def
* CATのサイズX
*/
#define TEXTURE_CAT_SIZE_X									(50)

/** @def
* CATのサイズY
*/
#define TEXTURE_CAT_SIZE_Y									(50)

/** @def
* SURAIMUのサイズX
*/
#define TEXTURE_SURAIMU_SIZE_X								(50)

/** @def
* SURAIMUのサイズY
*/
#define TEXTURE_SURAIMU_SIZE_Y								(50)

/** @def
* HINOTAMAのサイズX
*/
#define TEXTURE_HINOTAMA_SIZE_X								(50)

/** @def
* HINOTAMAのサイズY
*/
#define TEXTURE_HINOTAMA_SIZE_Y								(50)

/** @def
* UFOのサイズX
*/
#define TEXTURE_UFO_SIZE_X									(50)

/** @def
* UFOのサイズY
*/
#define TEXTURE_UFO_SIZE_Y									(50)

/** @def
* CATの半分サイズX
*/
#define TEXTURE_CAT_SIZE_X_HALF								(TEXTURE_CAT_SIZE_X/2)

/** @def
* CATの半分サイズY
*/
#define TEXTURE_CAT_SIZE_Y_HALF								(TEXTURE_CAT_SIZE_Y/2)


//各々のコリジョン用サイズ
/** @def
* BATTERのコリジョン用サイズX
*/
#define TEXTURE_BATTER_COLLISION_BB_SIZE_X					(TEXTURE_BATTER_SIZE_X/2)

/** @def
* BATTERのコリジョン用サイズY
*/
#define TEXTURE_BATTER_COLLISION_BB_SIZE_Y					(TEXTURE_BATTER_SIZE_Y*(75/100)) 

/** @def
* CATのコリジョン用サイズX
*/
#define TEXTURE_CAT_COLLISION_BB_SIZE_X						(TEXTURE_CAT_SIZE_X)

/** @def
* CATのコリジョン用サイズY
*/
#define TEXTURE_CAT_COLLISION_BB_SIZE_Y						(TEXTURE_CAT_SIZE_Y) 

/** @def
* SURAIMUのコリジョン用サイズX
*/
#define TEXTURE_SURAIMU_COLLISION_BB_SIZE_X					(TEXTURE_SURAIMU_SIZE_X)

/** @def
* SURAIMUのコリジョン用サイズY
*/
#define TEXTURE_SURAIMU_COLLISION_BB_SIZE_Y					(TEXTURE_SURAIMU_SIZE_Y) 

/** @def
* HINOTAMAのコリジョン用サイズX
*/
#define TEXTURE_HINOTAMA_COLLISION_BB_SIZE_X				(TEXTURE_HINOTAMA_SIZE_X)

/** @def
* HINOTAMAのコリジョン用サイズY
*/
#define TEXTURE_HINOTAMA_COLLISION_BB_SIZE_Y				(TEXTURE_HINOTAMA_SIZE_Y) 

/** @def
* UFOのコリジョン用サイズX
*/
#define TEXTURE_UFO_COLLISION_BB_SIZE_X						(TEXTURE_UFO_SIZE_X)

/** @def
* UFOのコリジョン用サイズY
*/
#define TEXTURE_UFO_COLLISION_BB_SIZE_Y						(TEXTURE_UFO_SIZE_Y) 


//各々のアニメパターンと分割数と切り替わるタイミング
//ピッチャー
/** @def
* PITCHERアニメパターンX
*/
#define TEXTURE_PITCHER_PATTERN_DIVIDE_X					(1)

/** @def
* PITCHERアニメパターンY
*/
#define TEXTURE_PITCHER_PATTERN_DIVIDE_Y					(1)

/** @def
* PITCHERアニメパターン分割数
*/
#define ANIM_PITCHER_PATTERN_NUM							(TEXTURE_PITCHER_PATTERN_DIVIDE_X*TEXTURE_PITCHER_PATTERN_DIVIDE_Y)

/** @def
* PITCHERアニメパターン切り替わりタイミング
*/
#define TIME_PITCHER_ANIMATION								(4)

//バッター
/** @def
* BATTERアニメパターンX
*/
#define TEXTURE_BATTER_PATTERN_DIVIDE_X						(5)

/** @def
* BATTERアニメパターンY
*/
#define TEXTURE_BATTER_PATTERN_DIVIDE_Y						(1)

/** @def
* BATTERアニメパターン分割数
*/
#define ANIM_BATTER_PATTERN_NUM								(TEXTURE_BATTER_PATTERN_DIVIDE_X*TEXTURE_BATTER_PATTERN_DIVIDE_Y)

/** @def
* BATTERアニメパターン切り替わりタイミング　遅い
*/
#define TIME_BATTER_ANIMATION_SLOW							(9)

/** @def
* BATTERアニメパターン切り替わりタイミング　普通
*/
#define TIME_BATTER_ANIMATION_MID							(7)

/** @def
* BATTERアニメパターン切り替わりタイミング　早い
*/
#define TIME_BATTER_ANIMATION_FAST							(5)

//猫
/** @def
* CATアニメパターンX
*/
#define TEXTURE_CAT_PATTERN_DIVIDE_X						(3)

/** @def
* CATアニメパターンY
*/
#define TEXTURE_CAT_PATTERN_DIVIDE_Y						(4)

/** @def
* CATアニメパターン分割数
*/
#define ANIM_CAT_PATTERN_NUM								(TEXTURE_CAT_PATTERN_DIVIDE_X*TEXTURE_CAT_PATTERN_DIVIDE_Y)

/** @def
* CATアニメパターン切り替わりタイミング　普通
*/
#define TIME_CAT_ANIMATION_MID								(10)

/** @def
* CAT行動カウント　普通
*/
#define TIME_CAT_MOVECOUNT_MID								(60)

//UFO
/** @def
* UFOアニメパターンX
*/
#define TEXTURE_UFO_PATTERN_DIVIDE_X						(1)

/** @def
* UFOアニメパターンY
*/
#define TEXTURE_UFO_PATTERN_DIVIDE_Y						(1)

/** @def
* UFOアニメパターン分割数
*/
#define ANIM_UFO_PATTERN_NUM								(TEXTURE_UFO_PATTERN_DIVIDE_X*TEXTURE_UFO_PATTERN_DIVIDE_Y)

/** @def
* UFOアニメパターン切り替わりタイミング　普通
*/
#define TIME_UFO_ANIMATION_MID								(10)

/** @def
* UFO行動カウント　普通
*/
#define TIME_UFO_MOVECOUNT_MID								(40)

//スライム
/** @def
* SURAIMUアニメパターンX
*/
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_X					(3)

/** @def
* SURAIMUアニメパターンY
*/
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_Y					(4)

/** @def
* SURAIMUアニメパターン分割数
*/
#define ANIM_SURAIMU_PATTERN_NUM							(TEXTURE_SURAIMU_PATTERN_DIVIDE_X*TEXTURE_SURAIMU_PATTERN_DIVIDE_Y)

/** @def
* SURAIMUアニメパターン切り替わりタイミング　普通
*/
#define TIME_SURAIMU_ANIMATION_MID							(10)

/** @def
* SURAIMU行動カウント　普通
*/
#define TIME_SURAIMU_MOVECOUNT_MID							(40)

//火の玉
/** @def
* HINOTAMAアニメパターンX
*/
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_X					(3)

/** @def
* HINOTAMAアニメパターンY
*/
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y					(4)

/** @def
* HINOTAMAアニメパターン分割数
*/
#define ANIM_HINOTAMA_PATTERN_NUM							(TEXTURE_HINOTAMA_PATTERN_DIVIDE_X*TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y)

/** @def
* HINOTAMAアニメパターン切り替わりタイミング　普通
*/
#define TIME_HINOTAMA_ANIMATION_MID							(10)

/** @def
* HINOTAMA行動カウント　普通
*/
#define TIME_HINOTAMA_MOVECOUNT_MID							(40)

/** @def
* エネミー変色スピード
*/
#define TEXTURE_COROLSPEED									(5)

//移動時の速度 感度の部分
/** @def
* 標準移動の速度
*/
#define MOTION_SPEED_MID									(4.0f)

/** @def
* エネミー破壊エフェクト時にエネミーが徐々に拡大する値
*/
#define MOTION_EFFECT_SPEED_MID								(1.0f)

/** @def
* ミートカーソルの移動速度
*/
#define BAT_MOTION_SPEED_MID								(8.0f)

/** @def
* ミートカーソルの移動速度　斜め
*/
#define BAT_MOTION_ROOT_SPEED_MID							(7.41f)


/** @def
* ストライクゾーンの基準座標X
*/
#define STRIKE_REFERENCE_X									(SCREEN_CENTER_X);

/** @def
* ストライクゾーンの基準座標Y
*/
#define STRIKE_REFERENCE_Y									(SCREEN_CENTER_Y+250.0f);

/** @def
* ボール影の基準座標X
*/
#define BALL_SHADOW_REFARENCE_X								(SCREEN_CENTER_X)//投球開始時のボール影基準座標X

/** @def
* ボール影の基準座標Y
*/
#define BALL_SHADOW_REFARENCE_Y								(SCREEN_CENTER_Y-200.0f)//投球開始時のボール影基準座標Y

/** @def
* 投球されたボールがバッティングタイミングで赤くなる時のデクリメントされる座標
*/
#define BALL_JUST_TIMING_RED								(50.0f) 


//ボールサイズ変化量
/** @def
* ボールが向かってくるとき徐々にサイズが拡縮する値
*/
#define BALL_CHENGEVAL_SIZE									(0.01f)	

/** @def
* ボールが向かってくるときのサイズ最大値
*/
#define BALL_CHENGEVAL_MAX									(1.05f)	

/** @def
* ボールが向かってくるときのサイズ最小値
*/
#define BALL_CHENGEVAL_MIN									(0.95f)	

/** @def
* ボールが上部下部に行くときの拡縮サイズ
*/
#define BALL_CHENGEVALTYPEA_SIZE							(0.1f)	

/** @def
* ボールが上部のサイズ最大値
*/
#define BALL_CHENGEVALTYPEA_MAX								(5.0f)	

/** @def
* ボールが下部のサイズ最小値
*/
#define BALL_CHENGEVALTYPEA_MIN								(-5.0f)	


//バッティング時のタイミング
/** @def
*　バッティング時のタイミング　引っ張り1
*/
#define BALL_TIMING_PULL1									(42.0f)	

/** @def
*　バッティング時のタイミング　引っ張り2
*/
#define BALL_TIMING_PULL2									(36.0f)	

/** @def
*　バッティング時のタイミング　引っ張り3
*/
#define BALL_TIMING_PULL3									(30.0f)	

/** @def
*　バッティング時のタイミング　引っ張り4
*/
#define BALL_TIMING_PULL4									(24.0f)	

/** @def
*　バッティング時のタイミング　引っ張り5
*/
#define BALL_TIMING_PULL5									(18.0f)	

/** @def
*　バッティング時のタイミング　ジャスト1
*/
#define BALL_TIMING_JUST1									(12.0f)	

/** @def
*　バッティング時のタイミング　ジャスト2
*/
#define BALL_TIMING_JUST2									(6.0f)	

/** @def
*　バッティング時のタイミング　ジャスト3
*/
#define BALL_TIMING_JUST3									(12.0f)	

/** @def
*　バッティング時のタイミング　流し1
*/
#define BALL_TIMING_OPPOSITE1								(18.0f)	

/** @def
*　バッティング時のタイミング　流し2
*/
#define BALL_TIMING_OPPOSITE2								(24.0f)	

/** @def
*　バッティング時のタイミング　流し3
*/
#define BALL_TIMING_OPPOSITE3								(30.0f)	

/** @def
*　バッティング時のタイミング　流し4
*/
#define BALL_TIMING_OPPOSITE4								(36.0f)	

/** @def
*　バッティング時のタイミング　流し5
*/
#define BALL_TIMING_OPPOSITE5								(50.0f)	



//バッター、ミートカーソルの座標最大最小値
/** @def
* バッターのX移動最大値
*/
#define BATCURSOR_MOVE_STOP_X_MAX							(SCREEN_CENTER_X+70.0f)

/** @def
* バッターのX移動最低値
*/
#define BATCURSOR_MOVE_STOP_X_MIN							(SCREEN_CENTER_X-70.0f)

/** @def
* バッターのY移動最大値
*/
#define BATCURSOR_MOVE_STOP_Y_MAX							(SCREEN_CENTER_Y+335.0f)

/** @def
* バッターのY移動最低値
*/
#define BATCURSOR_MOVE_STOP_Y_MIN							(SCREEN_CENTER_Y+165.0f)

//プレイヤー、エネミー合計
/** @def
* プレイヤー合計
*/
#define PLAYER_GOUKEI										(2)

/** @def
* CAT難易度難しい時合計
*/
#define CAT_H_LEVEL											(80)

/** @def
* CAT合計
*/
#define CAT_GOUKEI											(CAT_H_LEVEL)

/** @def
* CAT難易度普通時合計
*/
#define CAT_M_LEVEL											(CAT_H_LEVEL/5)

/** @def
* CAT難易度低い時合計
*/
#define CAT_L_LEVEL											(CAT_H_LEVEL/10)

/** @def
* SURAIMU合計
*/
#define SURAIMU_GOUKEI										(20)

/** @def
* HINOTAMA合計
*/
#define HINOTAMA_GOUKEI										(20)

/** @def
* UFO合計
*/
#define UFO_GOUKEI											(5)

/** @def
* エネミー合計(SURAIMU_GOUKEI+HINOTAMA_GOUKEI)
*/
#define ENEMY_GOUKEI										(SURAIMU_GOUKEI+HINOTAMA_GOUKEI)

/** @def
* エネミーの種類 CAT,SURAIMU,HINOTAMA,UFO
*/
#define ENEMY_TYPE											(4)

/** @def
* エネミーのテクスチャサイズ　画面奥行で拡縮
*/
#define ENEMY_CHENGEVAL_SIZE								(0.2f)



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

/**
* @brief デバイス取得関数 GetDevice
* @return LPDIRECT3DDEVICE9
*/
LPDIRECT3DDEVICE9 GetDevice(void);

/**
* @brief 文字セットする関数 SelectText
* @param[in] moji 表示したい文字を入力
* @details 打球方向判定用 Debugのみで使用
*/
void SelectText(char *moji);

/**
* @brief 文字を表示する関数 DrawTextType
* @details 打球方向判定用 Debugのみで使用
*/
void DrawTextType(void);

/**
* @brief ゲームシーンをセットする関数 SetScene
* @param[in] Scene 移動先シーンを入力
* @details ゲームシーンはE_STAGEを参照
*/
void SetScene(int Scene);

/**
* @brief 現在のゲームシーンを入手する関数 GetScene
* @return int 現在のゲームシーンを返す
* @details ゲームシーンはE_STAGEを参照
*/
int GetScene(void);

/**
* @brief ゲームを初期化する関数 InitGame
* @details ゲーム起動時に使用ゲームループ時に使用
*/
void InitGame(void);

/**
* @brief ゲームを再初期化する関数 ReInitTuto
* @details ゲームループ時(ゲームループを一周するタイミング)に使用
*/
void ReInitTuto(void);

/**
* @brief アップデートを再初期化する関数 UpdateReInit
* @details ゲームループ時に使用
*/
void UpdateReInit(void);

/**
* @brief 任意のランダム数値を決める関数 Random
* @param[in] type どのエネミータイプか入力
* @return float エネミーの座標を返す
* @details エネミーの初期座標で使用
*/
float Random(int type);
