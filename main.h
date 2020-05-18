/**
* @file main.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W���� 
* @date 2019/09/01
*/
#pragma once

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <string.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

/**
* @def _TEST
* @brief �ȒP�Ȑ���
* @details �ڍׂȐ���
*/
#define SCREEN_W							(1280)						// �E�C���h�E�̕�
#define SCREEN_H							(960)						// �E�C���h�E�̍���
#define SCREEN_CENTER_X						(SCREEN_W / 2)					// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y						(SCREEN_H / 2)					// �E�C���h�E�̒��S�x���W


#define BG_SIZE_H_TTOP						(240)						// BG���s�������W�㕔
#define BG_SIZE_H_TOP						(300)						// BG���s�������W�㕔
#define BG_SIZE_H_MID						(400)						// �@�@�@�@�@�@�@����
#define BG_SIZE_H_UNDER						(480)						// �@�@�@�@�@�@�@����
#define BG_SIZE_H_UUNDER					(600)						// �@�@�@�@�@�@�@����
#define BG_SIZE_W_TOP						(120)						// BG���E�������W
#define BG_SIZE_W_MID						(250)						// �@�@�@�@�@�@�@
#define BG_SIZE_W_UNDER						(450)						// �@�@�@�@�@�@�@


#define PY1_POS_Y							(SCREEN_CENTER_Y-150)		// �|���S���̏����ʒuX
#define PY2_POS_Y							(SCREEN_CENTER_Y+100)		// �|���S���̏����ʒuX
#define PX1_POS_X							(SCREEN_CENTER_X-250)		// ����
#define PX2_POS_X							(SCREEN_CENTER_X+250)		// ����




// ��ʑJ�ڒ萔
enum E_STAGE//�񋓌^�Bdefine�̔ԍ��������Ŋ��蓖�ĂĂ����B
{
	SCENE_TITLE,					//0�B1�߂�����0�B�񋓌^�̗񋓒萔���B��`�������O���V���{�����Ă����̂���ʂ炵���B
	SCENE_TUTORIAL,					//1�`���[�g���A��
	SCENE_TUTORIALMENU,				//2�`���[�g���A��
	SCENE_SELECT,					//3��Փx�I��
	SCENE_GAMECOUNTDOWN,			//4�Q�[���J�n�O�̃J�E���g�_�E��
	SCENE_GAME,						//5�Q�[��
	SCENE_PAUSE,					//6�|�[�Y
	SCENE_OPTION,					//7�I�v�V����
	SCENE_R18SELECT,				//8R18�摜�I��
	SCENE_SENSITIVITY,				//9�I�v�V����
	SCENE_TUTOSENSITIVITY,			//10�I�v�V����
	SCENE_CONTYPE,					//11�I�v�V����
	SCENE_TUTOCONTYPE,				//12�`���[�g���A����A/D�ݒ�
	SCENE_RESULT_CLEAR,				//13�N���A�X�R�A
	SCENE_RESULT_FIELD,				//14���s�X�R�A
	SCENE_REGISTER,					//15�����L���O�o�^
	SCENE_RANKING,					//16�����L���O�\��
	SCENE_MAX						//17��
};

//�Q�[���N���A�̎��
enum GAMEEND
{
	CLEAR,
	FIELD,
};

//�Q�[���N���A�̎��
enum MASTERVOLUMEOLCHENGE
{
	VOLUP,
	VOLDOWN,
};

//�����_���̎��
enum RAND
{
	X,
	Y,
};

//�~�[�g�J�[�\���傫���̎��
enum MEET
{
	BIG,
	SMALL,
};

//�X�R�A�̎��
enum SCORETYPE
{
	TIMEV,
	E,
	SCOREVAL,
};

//��Փx�̎��
enum GAMETYPE
{
	L,
	M,
	H,
};

//�|�[�Y�̎��
enum PAUSETYPE
{
	PAUSEHAJIMEKARA,
	PAUSECANCEL,
	PAUSEMODESELECT,
	PAUSEOPTION,
	PAUSEEND,
};

//�e�L�X�g�̎��
enum TEXT
{
	TEXT_STRIKE,
	TEXT_BALL,
	TEXT_DEADBALL,
};

//�w�i�̎��
enum BGTYPE
{
	OBG,				//���Ŕw�i
	DBG					//�瑫�w�i
};

//�{�[���G�t�F�N�g�̎��
enum BETYPE
{
	BE1,				//���Ŕw�i
	BE2					//�瑫�w�i
};

//�v���C���[���
enum PLAYER_TYPE
{
	TYPE_PIT,
	TYPE_BAT,
};

//�G�l�~�[���
enum ENEMY_TYPE
{
	TYPE_CAT,
	TYPE_SURAIMU,
	TYPE_HINOTAMA,
	TYPE_UFO
};

//�o�b�^�[�̕`����
enum BATTERPATTERN
{
	BAT_PATTERN0,	// �ʏ�
	BAT_PATTERN1,	// �X�C���O1
	BAT_PATTERN2,	// �X�C���O2
	BAT_PATTERN3,	// �X�C���O3
	BAT_PATTERN4,	// �A�C�h�����O
};

//�G�l�~�[�̕`����
enum ENEMYRPATTERN
{
	ENEMY_PATTERN0,		// ������
	ENEMY_PATTERN1,		// 
	ENEMY_PATTERN2,		// 
	ENEMY_PATTERN3,		// ������
	ENEMY_PATTERN4,		// 
	ENEMY_PATTERN5,		// 
	ENEMY_PATTERN6,		// �E����
	ENEMY_PATTERN7,		// 
	ENEMY_PATTERN8,		// 
	ENEMY_PATTERN9,		// �����
	ENEMY_PATTERN10,	// 
	ENEMY_PATTERN11,	// 
};

//�ړ�����
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
	BALL_DIRECTION_PULL_BUFF,			//�ŋ�����
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

#define	NUM_VERTEX											(4)					// ���_��
#define	NUM_PLAYER											(2)					// �|���S����
#define	NUM_ENEMY_VERTEX									(16)					
#define	NUM_ENEMY											(16)					
#define	NUM_POLYGON											(2)	

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D										(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3				vtx;						//! ���_���W
	float					rhw;						//! �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR				diffuse;					//! ���ˌ�
	D3DXVECTOR2				tex;						//! �e�N�X�`�����W 
} VERTEX_2D;

// �L�����N�^�[�\����
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//! �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		//! ���_���i�[���[�N
	D3DXVECTOR3				pos;						//! ���W
	D3DXVECTOR3				rot;						//! ��]��
	D3DXVECTOR3				move;						//! �ړ���
	D3DXVECTOR3				oldmove;					//! �Â��ړ���
	int						fps;						//! �o�b�e�B���O�̃^�C�~���O�l
	int						nCountAnim;					//! �A�j���J�E���g
	int						nPatternAnim;				//! �A�j���p�^�[���i���o�[ 
	int						direction;					//! �ړ�����
	bool					motion;						//! �����Ă邩�ǂ���
	bool					use;						//! �g�p���Ă��邩�ǂ���
} CHARACTER;



//�e�X�̉摜
#define TEXTURE_GAME_PITCHER								_T("data/TEXTURE/item/pitmachine.png")  
#define TEXTURE_GAME_BATTER									_T("data/TEXTURE/CHAR/bat.png") 
#define TEXTURE_GAME_UFO									_T("data/TEXTURE/CHAR/ufo.png") 
#define TEXTURE_GAME_CAT1									_T("data/TEXTURE/CHAR/cat1.png") 
#define TEXTURE_GAME_SURAIMU								_T("data/TEXTURE/CHAR/suraimu.png") 
#define TEXTURE_GAME_HINOTAMA								_T("data/TEXTURE/CHAR/hinotama.png") 
#define TEXTURE_GAME_SCORE									_T("data/TEXTURE/BG/0-9.png")	
#define	TEXTURE_SENSITIV									_T("data/TEXTURE/sozai/select/kando.png")		
#define	TEXTURE_CONTROLTYPE									_T("data/TEXTURE/sozai/select/ADset.png")		

//�e�X�̃e�N�X�`���T�C�YX,Y
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

//�e�X�̃R���W�����p�T�C�Y
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

//�e�X�̃A�j���p�^�[���ƕ������Ɛ؂�ւ��^�C�~���O
//�s�b�`���[
#define TEXTURE_PITCHER_PATTERN_DIVIDE_X					(1)
#define TEXTURE_PITCHER_PATTERN_DIVIDE_Y					(1)
#define ANIM_PITCHER_PATTERN_NUM							(TEXTURE_PITCHER_PATTERN_DIVIDE_X*TEXTURE_PITCHER_PATTERN_DIVIDE_Y)
#define TIME_PITCHER_ANIMATION								(4)
//�o�b�^�[
#define TEXTURE_BATTER_PATTERN_DIVIDE_X						(5)
#define TEXTURE_BATTER_PATTERN_DIVIDE_Y						(1)
#define ANIM_BATTER_PATTERN_NUM								(TEXTURE_BATTER_PATTERN_DIVIDE_X*TEXTURE_BATTER_PATTERN_DIVIDE_Y)
#define TIME_BATTER_ANIMATION_SLOW							(9)
#define TIME_BATTER_ANIMATION_MID							(7)
#define TIME_BATTER_ANIMATION_FAST							(5)
//�L
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
//�X���C��
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_X					(3)
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_Y					(4)
#define ANIM_SURAIMU_PATTERN_NUM							(TEXTURE_SURAIMU_PATTERN_DIVIDE_X*TEXTURE_SURAIMU_PATTERN_DIVIDE_Y)
#define TIME_SURAIMU_ANIMATION_MID							(10)
#define TIME_SURAIMU_MOVECOUNT_MID							(40)
//�΂̋�
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_X					(3)
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y					(4)
#define ANIM_HINOTAMA_PATTERN_NUM							(TEXTURE_HINOTAMA_PATTERN_DIVIDE_X*TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y)
#define TIME_HINOTAMA_ANIMATION_MID							(10)
#define TIME_HINOTAMA_MOVECOUNT_MID							(40)

//�G�l�~�[�ϐF�X�s�[�h
#define TEXTURE_COROLSPEED									(5)

//�ړ����̑��x ���x�̕���
#define MOTION_SPEED_MID									(4.0f)
#define MOTION_ROOT_SPEED_MID								(3.41f)
#define MOTION_EFFECT_SPEED_MID								(1.0f)
#define BAT_MOTION_SPEED_MID								(8.0f)
#define BAT_MOTION_ROOT_SPEED_MID							(7.41f)

//�X�g���C�N�]�[���̊���W
#define STRIKE_REFERENCE_X									(SCREEN_CENTER_X);
#define STRIKE_REFERENCE_Y									(SCREEN_CENTER_Y+250.0f);
//�{�[���̊���W
#define BALL_SHADOW_REFARENCE_X								(SCREEN_CENTER_X)//�����J�n���̃{�[���e����WX
#define BALL_SHADOW_REFARENCE_Y								(SCREEN_CENTER_Y-200.0f)//�����J�n���̃{�[���e����WY

//�������ꂽ�{�[�����o�b�e�B���O�^�C�~���O�ŐԂ��Ȃ鎞�̃f�N�������g�������W
#define BALL_JUST_TIMING_RED								(50.0f) 

//�{�[���T�C�Y�ω���
#define BALL_CHENGEVAL_SIZE									(0.01f)		//�{�[�����������Ă���Ƃ����X�ɃT�C�Y���ω�����
#define BALL_CHENGEVAL_MAX									(1.05f)		//�{�[�����������Ă���Ƃ����X�ɃT�C�Y���ω�����
#define BALL_CHENGEVAL_MIN									(0.95f)		//�{�[�����������Ă���Ƃ����X�ɃT�C�Y���ω�����
#define BALL_CHENGEVALTYPEA_SIZE							(0.1f)		//�{�[�����������Ă���Ƃ����X�ɃT�C�Y���ω�����
#define BALL_CHENGEVALTYPEA_MAX								(5.0f)		//�{�[�����������Ă���Ƃ����X�ɃT�C�Y���ω�����
#define BALL_CHENGEVALTYPEA_MIN								(-5.0f)		//�{�[�����������Ă���Ƃ����X�ɃT�C�Y���ω�����


//�o�b�e�B���O���̃^�C�~���O
#define BALL_TIMING_PULL_KARABURI							(42.0f)		//������@��������@����^�C�~���O���W
#define BALL_TIMING_PULL_FOUL								(36.0f)		//		�@��������@
#define BALL_TIMING_PULL_MAX								(30.0f)		//		�@��������@
#define BALL_TIMING_PULL_MID								(24.0f)		//		�@��������@
#define BALL_TIMING_PULL_MIN								(18.0f)		//		�@��������@
#define BALL_TIMING_JUST_MAX								(12.0f)		//		�@�W���X�g�@
#define BALL_TIMING_JUST									(6.0f)		//		�@�W���X�g�@
#define BALL_TIMING_JUST_MIN								(12.0f)		//		�@�W���X�g�@
#define BALL_TIMING_OPPOSITE_MAX							(18.0f)		//		�@�����@	
#define BALL_TIMING_OPPOSITE_MID							(24.0f)		//		�@�����@�@�@
#define BALL_TIMING_OPPOSITE_MIN							(30.0f)		//		�@�����@	
#define BALL_TIMING_OPPOSITE_FOUL							(36.0f)		//		�@�����@	
#define BALL_TIMING_OPPOSITE_KARABURI						(50.0f)		//		�@�����@�@�@



//�o�b�^�[�A�~�[�g�J�[�\���̍��W�ő�ŏ��l
#define BATCURSOR_MOVE_STOP_X_MAX							(SCREEN_CENTER_X+70.0f)//�o�b�^�[��X�ړ��Œ�l
#define BATCURSOR_MOVE_STOP_X_MIN							(SCREEN_CENTER_X-70.0f)//�o�b�^�[��X�ړ��Œ�l
#define BATCURSOR_MOVE_STOP_Y_MAX							(SCREEN_CENTER_Y+335.0f)//�o�b�^�[��X�ړ��Œ�l
#define BATCURSOR_MOVE_STOP_Y_MIN							(SCREEN_CENTER_Y+165.0f)//�o�b�^�[��X�ړ��Œ�l

//�v���C���[�A�G�l�~�[���v
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

//�G�l�~�[�̃e�N�X�`���T�C�Y�����s�ŕύX
#define ENEMY_CHENGEVAL_SIZE								(0.2f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief �ȒP�Ȑ����i�`����֐��j
* @param[in] a(������) �����̐���
* @param[out] b(������) �����̐���
* @return bool �߂�l�̐���
* @details �ڍׂȐ���
*/

/**
* @brief �f�o�C�X�擾�֐�
* @return LPDIRECT3DDEVICE9
*/
LPDIRECT3DDEVICE9 GetDevice(void);

/**
* @brief �����Z�b�g����֐�
* @param[in] moji �\�����������������
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
void SelectText(char *moji);

/**
* @brief ������\������֐�
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
void DrawTextType(void);

/**
* @brief �Q�[���V�[�����Z�b�g����֐�
* @param[in] Scene �ړ���V�[�������
* @details �Q�[���V�[����E_STAGE���Q��
*/
void SetScene(int Scene);

/**
* @brief ���݂̃Q�[���V�[������肷��֐�
* @return int ���݂̃Q�[���V�[����Ԃ�
* @details �Q�[���V�[����E_STAGE���Q��
*/
int GetScene(void);

/**
* @brief �Q�[��������������֐�
* @details �Q�[���N�����Ɏg�p�Q�[�����[�v���Ɏg�p
*/
void InitGame(void);

/**
* @brief �Q�[�����ď���������֐�
* @details �Q�[�����[�v��(�Q�[�����[�v���������^�C�~���O)�Ɏg�p
*/
void ReInitTuto(void);

/**
* @brief �A�b�v�f�[�g���ď���������֐�
* @details �Q�[�����[�v���Ɏg�p
*/
void UpdateReInit(void);

/**
* @brief �C�ӂ̃����_�����l�����߂�֐�
* @param[in] type �ǂ̃G�l�~�[�^�C�v������
* @return float �G�l�~�[�̍��W��Ԃ�
* @details �G�l�~�[�̏������W�Ŏg�p
*/
float Random(int type);
