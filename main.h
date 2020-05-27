/**
* @file main.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W���� 
* @date 2019/09/01
*/
#pragma once

/** 
*�@@brief fscanf ��warning�h�~
*/
#define _CRT_SECURE_NO_WARNINGS

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <string.h>

/**
*�@@brief �x���Ώ�
*/
#define DIRECTINPUT_VERSION 0x0800
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
*�@@brief �E�C���h�E�̕�
*/
#define SCREEN_W							(1280)	

/**
*�@@brief �E�C���h�E�̍���
*/
#define SCREEN_H							(960)		

/**
*�@@brief �E�C���h�E�̒��S�w���W
*/
#define SCREEN_CENTER_X						(SCREEN_W / 2)	

/**
*�@@brief �E�C���h�E�̒��S�x���W
*/
#define SCREEN_CENTER_Y						(SCREEN_H / 2)	

/**
*�@@brief BG���s�������W�㕔
*/
#define BG_SIZE_H_TTOP						(240)			

/**
*�@@brief BG���s�������W�㕔2
*/
#define BG_SIZE_H_TOP						(300)			

/**
*�@@brief BG���s�������W����
*/
#define BG_SIZE_H_MID						(400)			

/**
*�@@brief BG���s�������W����
*/
#define BG_SIZE_H_UNDER						(480)			

/**
*�@@brief BG���s�������W����2
*/
#define BG_SIZE_H_UUNDER					(600)			

/**
*�@@brief BG���E�������W ��
*/
#define BG_SIZE_W_TOP						(120)			

/**
*�@@brief BG���E�������W�@��
*/
#define BG_SIZE_W_MID						(250)			

/**
*�@@brief BG���E�������W�@��
*/
#define BG_SIZE_W_UNDER						(450)			

/**
*�@@brief �|���S���̏����ʒuY1
*/
#define PY1_POS_Y							(SCREEN_CENTER_Y-150)	

/**
*�@@brief �|���S���̏����ʒuY2
*/
#define PY2_POS_Y							(SCREEN_CENTER_Y+100)	

/**
*�@@brief �|���S���̏����ʒuX1
*/
#define PX1_POS_X							(SCREEN_CENTER_X-250)	

/**
*�@@brief �|���S���̏����ʒuX2
*/
#define PX2_POS_X							(SCREEN_CENTER_X+250)	


/**
 * @enum E_STAGE
 * ��ʑJ�ڒ萔
 */
enum E_STAGE//�񋓌^�Bdefine�̔ԍ��������Ŋ��蓖�ĂĂ����B
{
	SCENE_TITLE,					//!< 0�B1�߂�����0�B�񋓌^�̗񋓒萔���B��`�������O���V���{�����Ă����̂���ʂ炵���B
	SCENE_TUTORIAL,					//!< 1�`���[�g���A��
	SCENE_TUTORIALMENU,				//!< 2�`���[�g���A��
	SCENE_SELECT,					//!< 3��Փx�I��
	SCENE_GAMECOUNTDOWN,			//!< 4�Q�[���J�n�O�̃J�E���g�_�E��
	SCENE_GAME,						//!< 5�Q�[��
	SCENE_PAUSE,					//!< 6�|�[�Y
	SCENE_OPTION,					//!< 7�I�v�V����
	SCENE_R18SELECT,				//!< 8R18�摜�I��
	SCENE_SENSITIVITY,				//!< 9�I�v�V����
	SCENE_TUTOSENSITIVITY,			//!< 10�I�v�V����
	SCENE_CONTYPE,					//!< 11�I�v�V����
	SCENE_TUTOCONTYPE,				//!< 12�`���[�g���A����A/D�ݒ�
	SCENE_RESULT_CLEAR,				//!< 13�N���A�X�R�A
	SCENE_RESULT_FIELD,				//!< 14���s�X�R�A
	SCENE_REGISTER,					//!< 15�����L���O�o�^
	SCENE_RANKING,					//!< 16�����L���O�\��
	SCENE_MAX						//!< 17��
};

/**
 * @enum GAMEEND
 * �Q�[���N���A�̎��
 */
enum GAMEEND
{
	CLEAR,
	FIELD
};

/**
 * @enum MASTERVOLUMEOLCHENGE
 * ���ʂ̒���
 */
enum MASTERVOLUMEOLCHENGE
{
	VOL_UP,
	VOL_DOWN
};

/**
 * @enum RAND
 * �����_���̎��
 */
enum RAND
{
	X,
	Y
};

/**
 * @enum MEET
 * �~�[�g�J�[�\���̎��
 */
enum MEET
{
	BIG,
	SMALL
};

/**
 * @enum SCORETYPE
 * �X�R�A�̎��
 */
enum SCORETYPE
{
	TIME_VAL,
	ENEMY_VAL,
	SCORE_VAL
};

/**
 * @enum GAMETYPE
 * ��Փx�̎��
 */
enum GAMETYPE
{
	L,
	M,
	H
};

/**
 * @enum PAUSETYPE
 * �|�[�Y���j���[�̎��
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
 * �e�L�X�g�̎��
 */
enum TEXT
{
	TEXT_STRIKE,
	TEXT_BALL,
	TEXT_DEADBALL
};

/**
 * @enum BETYPE
 * �{�[���G�t�F�N�g�̎��
 */
enum BETYPE
{
	BALL_EFFECT1,				//!< �{�[���G�t�F�N�g1
	BALL_EFFECT2				//!< �{�[���G�t�F�N�g2
};

/**
 * @enum PLAYER_TYPE
 * �v���C���[���
 */
enum PLAYER_TYPE
{
	TYPE_PIT,
	TYPE_BAT,
};

/**
 * @enum ENEMY_TYPE
 * �G�l�~�[���
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
 * �o�b�^�[�̕`����
 */
enum BATTERPATTERN
{
	BAT_PATTERN0,	//!< �ʏ�
	BAT_PATTERN1,	//!< �X�C���O1
	BAT_PATTERN2,	//!< �X�C���O2
	BAT_PATTERN3,	//!< �X�C���O3
	BAT_PATTERN4	//!< �A�C�h�����O
};

/**
 * @enum ENEMYRPATTERN
 * �G�l�~�[�̕`����
 */
enum ENEMYRPATTERN
{
	ENEMY_PATTERN0,		//!< ������1
	ENEMY_PATTERN1,		//!< ������2
	ENEMY_PATTERN2,		//!< ������3
	ENEMY_PATTERN3,		//!< ������1
	ENEMY_PATTERN4,		//!< ������2
	ENEMY_PATTERN5,		//!< ������3
	ENEMY_PATTERN6,		//!< �E����1
	ENEMY_PATTERN7,		//!< �E����2
	ENEMY_PATTERN8,		//!< �E����3
	ENEMY_PATTERN9,		//!< �����1
	ENEMY_PATTERN10,	//!< �����2
	ENEMY_PATTERN11		//!< �����3
};

/**
 * @enum DIRECTION
 * �ړ�����
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
 * �ŋ�����
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

/**
*�@@brief �W���Ȓ��_��
*/
#define	NUM_VERTEX											(4)				

/**
*�@@brief �W���|���S����
*/
#define	NUM_POLYGON											(2)				

/**
*�@@brief �G�l�~�[���_��
*/
#define	NUM_ENEMY_VERTEX									(16)			

/**
*�@@brief �G�l�~�[�|���S����
*/
#define	NUM_ENEMY											(16)			

/**
*�@@brief 2D���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
*/
#define	FVF_VERTEX_2D										(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/**
*�@@struct VERTEX_2D
*�@@brief 2D���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
*/
typedef struct
{
	//! ���_���W
	D3DXVECTOR3					vtx;						
	//! �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	float						rhw;						
	//! ���ˌ�
	D3DCOLOR					diffuse;					
	//! �e�N�X�`�����W
	D3DXVECTOR2					tex;						
} VERTEX_2D;

/**
*�@@struct CHARACTER
*�@@brief �L�����N�^�[�W���ϐ��\����
*/
typedef struct
{
	//! �e�N�X�`���ւ̃|�C���^
		LPDIRECT3DTEXTURE9		pD3DTexture = NULL;
	//! ���_���i�[���[�N
		VERTEX_2D				vertexWk[NUM_VERTEX];
	//! ���W
		D3DXVECTOR3				pos;
	//! ��]�p
		D3DXVECTOR3				rot;
	//! �ړ���
		D3DXVECTOR3				move;
	//! �Â��ړ���
		D3DXVECTOR3				oldmove;
	//! �o�b�e�B���O�̃^�C�~���O�l
		int						fps;
	//! �A�j���J�E���g
		int						nCountAnim;
	//! �A�j���p�^�[���i���o�[
		int						nPatternAnim;
	//! �ړ�����
		int						direction;
	//! �����Ă邩�ǂ���
		bool					motion;
	//! �g�p���Ă��邩�ǂ���
		bool					use;						
} CHARACTER;



//�e�X�̉摜
/**
*�@@brief PITCHER�̉摜
*/
#define TEXTURE_GAME_PITCHER								_T("data/TEXTURE/item/pitmachine.png")  

/**
*�@@brief BATTER�̉摜
*/
#define TEXTURE_GAME_BATTER									_T("data/TEXTURE/CHAR/bat.png") 

/**
*�@@brief UFO�̉摜
*/
#define TEXTURE_GAME_UFO									_T("data/TEXTURE/CHAR/ufo.png") 

/**
*�@@brief CAT�̉摜
*/
#define TEXTURE_GAME_CAT									_T("data/TEXTURE/CHAR/cat1.png") 

/**
*�@@brief SURAIMU�̉摜
*/
#define TEXTURE_GAME_SURAIMU								_T("data/TEXTURE/CHAR/suraimu.png") 

/**
*�@@brief HINOTAMA�̉摜
*/
#define TEXTURE_GAME_HINOTAMA								_T("data/TEXTURE/CHAR/hinotama.png") 

/**
*�@@brief SCORE�̉摜
*/
#define TEXTURE_GAME_SCORE									_T("data/TEXTURE/BG/0-9.png")	

/**
*�@@brief SENSITIV�̉摜
*/
#define	TEXTURE_SENSITIV									_T("data/TEXTURE/sozai/select/kando.png")		

/**
*�@@brief CONTROLTYPE�̉摜
*/
#define	TEXTURE_CONTROLTYPE									_T("data/TEXTURE/sozai/select/ADset.png")		


//�e�X�̃e�N�X�`���T�C�YX,Y
/**
*�@@brief PITCHER�̃T�C�YX
*/
#define TEXTURE_PITCHER_SIZE_X								(60)

/**
*�@@brief PITCHER�̃T�C�YY
*/
#define TEXTURE_PITCHER_SIZE_Y								(60)

/**
*�@@brief BATTER�̃T�C�YX
*/
#define TEXTURE_BATTER_SIZE_X								(130)

/**
*�@@brief BATTER�̃T�C�YY
*/
#define TEXTURE_BATTER_SIZE_Y								(130)

/**
*�@@brief CAT�̃T�C�YX
*/
#define TEXTURE_CAT_SIZE_X									(50)

/**
*�@@brief CAT�̃T�C�YY
*/
#define TEXTURE_CAT_SIZE_Y									(50)

/**
*�@@brief SURAIMU�̃T�C�YX
*/
#define TEXTURE_SURAIMU_SIZE_X								(50)

/**
*�@@brief SURAIMU�̃T�C�YY
*/
#define TEXTURE_SURAIMU_SIZE_Y								(50)

/**
*�@@brief HINOTAMA�̃T�C�YX
*/
#define TEXTURE_HINOTAMA_SIZE_X								(50)

/**
*�@@brief HINOTAMA�̃T�C�YY
*/
#define TEXTURE_HINOTAMA_SIZE_Y								(50)

/**
*�@@brief UFO�̃T�C�YX
*/
#define TEXTURE_UFO_SIZE_X									(50)

/**
*�@@brief UFO�̃T�C�YY
*/
#define TEXTURE_UFO_SIZE_Y									(50)

/**
*�@@brief CAT�̔����T�C�YX
*/
#define TEXTURE_CAT_SIZE_X_HALF								(TEXTURE_CAT_SIZE_X/2)

/**
*�@@brief CAT�̔����T�C�YY
*/
#define TEXTURE_CAT_SIZE_Y_HALF								(TEXTURE_CAT_SIZE_Y/2)


//�e�X�̃R���W�����p�T�C�Y
/**
*�@@brief BATTER�̃R���W�����p�T�C�YX
*/
#define TEXTURE_BATTER_COLLISION_BB_SIZE_X					(TEXTURE_BATTER_SIZE_X/2)

/**
*�@@brief BATTER�̃R���W�����p�T�C�YY
*/
#define TEXTURE_BATTER_COLLISION_BB_SIZE_Y					(TEXTURE_BATTER_SIZE_Y*(75/100)) 

/**
*�@@brief CAT�̃R���W�����p�T�C�YX
*/
#define TEXTURE_CAT_COLLISION_BB_SIZE_X						(TEXTURE_CAT_SIZE_X)

/**
*�@@brief CAT�̃R���W�����p�T�C�YY
*/
#define TEXTURE_CAT_COLLISION_BB_SIZE_Y						(TEXTURE_CAT_SIZE_Y) 

/**
*�@@brief CAT�̃R���W�����p�T�C�YY
*/
#define TEXTURE_SURAIMU_COLLISION_BB_SIZE_X					(TEXTURE_SURAIMU_SIZE_X)

/**
*�@@brief SURAIMU�̃R���W�����p�T�C�YY
*/
#define TEXTURE_SURAIMU_COLLISION_BB_SIZE_Y					(TEXTURE_SURAIMU_SIZE_Y) 

/**
*�@@brief HINOTAMA�̃R���W�����p�T�C�YX
*/
#define TEXTURE_HINOTAMA_COLLISION_BB_SIZE_X				(TEXTURE_HINOTAMA_SIZE_X)

/**
*�@@brief HINOTAMA�̃R���W�����p�T�C�YY
*/
#define TEXTURE_HINOTAMA_COLLISION_BB_SIZE_Y				(TEXTURE_HINOTAMA_SIZE_Y) 

/**
*�@@brief UFO�̃R���W�����p�T�C�YX
*/
#define TEXTURE_UFO_COLLISION_BB_SIZE_X						(TEXTURE_UFO_SIZE_X)

/**
*�@@brief UFO�̃R���W�����p�T�C�YY
*/
#define TEXTURE_UFO_COLLISION_BB_SIZE_Y						(TEXTURE_UFO_SIZE_Y) 


//�e�X�̃A�j���p�^�[���ƕ������Ɛ؂�ւ��^�C�~���O
//�s�b�`���[
/**
*�@@brief PITCHER�A�j���p�^�[��X
*/
#define TEXTURE_PITCHER_PATTERN_DIVIDE_X					(1)

/**
*�@@brief PITCHER�A�j���p�^�[��Y
*/
#define TEXTURE_PITCHER_PATTERN_DIVIDE_Y					(1)

/**
*�@@brief PITCHER�A�j���p�^�[��������
*/
#define ANIM_PITCHER_PATTERN_NUM							(TEXTURE_PITCHER_PATTERN_DIVIDE_X*TEXTURE_PITCHER_PATTERN_DIVIDE_Y)

/**
*�@@brief PITCHER�A�j���p�^�[���؂�ւ��^�C�~���O
*/
#define TIME_PITCHER_ANIMATION								(4)

//�o�b�^�[
/**
*�@@brief BATTER�A�j���p�^�[��X
*/
#define TEXTURE_BATTER_PATTERN_DIVIDE_X						(5)

/**
*�@@brief BATTER�A�j���p�^�[��Y
*/
#define TEXTURE_BATTER_PATTERN_DIVIDE_Y						(1)

/**
*�@@brief BATTER�A�j���p�^�[��������
*/
#define ANIM_BATTER_PATTERN_NUM								(TEXTURE_BATTER_PATTERN_DIVIDE_X*TEXTURE_BATTER_PATTERN_DIVIDE_Y)

/**
*�@@brief BATTER�A�j���p�^�[���؂�ւ��^�C�~���O�@�x��
*/
#define TIME_BATTER_ANIMATION_SLOW							(9)

/**
*�@@brief BATTER�A�j���p�^�[���؂�ւ��^�C�~���O�@����
*/
#define TIME_BATTER_ANIMATION_MID							(7)

/**
*�@@brief BATTER�A�j���p�^�[���؂�ւ��^�C�~���O�@����
*/
#define TIME_BATTER_ANIMATION_FAST							(5)

//�L
/**
*�@@brief CAT�A�j���p�^�[��X
*/
#define TEXTURE_CAT_PATTERN_DIVIDE_X						(3)

/**
*�@@brief CAT�A�j���p�^�[��Y
*/
#define TEXTURE_CAT_PATTERN_DIVIDE_Y						(4)

/**
*�@@brief CAT�A�j���p�^�[��������
*/
#define ANIM_CAT_PATTERN_NUM								(TEXTURE_CAT_PATTERN_DIVIDE_X*TEXTURE_CAT_PATTERN_DIVIDE_Y)

/**
*�@@brief CAT�A�j���p�^�[���؂�ւ��^�C�~���O�@����
*/
#define TIME_CAT_ANIMATION_MID								(10)

/**
*�@@brief CAT�s���J�E���g�@����
*/
#define TIME_CAT_MOVECOUNT_MID								(60)

//UFO
/**
*�@@brief UFO�A�j���p�^�[��X
*/
#define TEXTURE_UFO_PATTERN_DIVIDE_X						(1)

/**
*�@@brief UFO�A�j���p�^�[��Y
*/
#define TEXTURE_UFO_PATTERN_DIVIDE_Y						(1)

/**
*�@@brief UFO�A�j���p�^�[��������
*/
#define ANIM_UFO_PATTERN_NUM								(TEXTURE_UFO_PATTERN_DIVIDE_X*TEXTURE_UFO_PATTERN_DIVIDE_Y)

/**
*�@@brief UFO�A�j���p�^�[���؂�ւ��^�C�~���O�@����
*/
#define TIME_UFO_ANIMATION_MID								(10)

/**
*�@@brief UFO�s���J�E���g�@����
*/
#define TIME_UFO_MOVECOUNT_MID								(40)

//�X���C��
/**
*�@@brief SURAIMU�A�j���p�^�[��X
*/
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_X					(3)

/**
*�@@brief SURAIMU�A�j���p�^�[��Y
*/
#define TEXTURE_SURAIMU_PATTERN_DIVIDE_Y					(4)

/**
*�@@brief SURAIMU�A�j���p�^�[��������
*/
#define ANIM_SURAIMU_PATTERN_NUM							(TEXTURE_SURAIMU_PATTERN_DIVIDE_X*TEXTURE_SURAIMU_PATTERN_DIVIDE_Y)

/**
*�@@brief SURAIMU�A�j���p�^�[���؂�ւ��^�C�~���O�@����
*/
#define TIME_SURAIMU_ANIMATION_MID							(10)

/**
*�@@brief SURAIMU�s���J�E���g�@����
*/
#define TIME_SURAIMU_MOVECOUNT_MID							(40)

//�΂̋�
/**
*�@@brief HINOTAMA�A�j���p�^�[��X
*/
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_X					(3)

/**
*�@@brief HINOTAMA�A�j���p�^�[��Y
*/
#define TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y					(4)

/**
*�@@brief HINOTAMA�A�j���p�^�[��������
*/
#define ANIM_HINOTAMA_PATTERN_NUM							(TEXTURE_HINOTAMA_PATTERN_DIVIDE_X*TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y)

/**
*�@@brief HINOTAMA�A�j���p�^�[���؂�ւ��^�C�~���O�@����
*/
#define TIME_HINOTAMA_ANIMATION_MID							(10)

/**
*�@@brief HINOTAMA�s���J�E���g�@����
*/
#define TIME_HINOTAMA_MOVECOUNT_MID							(40)

/**
*�@@brief �G�l�~�[�ϐF�X�s�[�h
*/
#define TEXTURE_COROLSPEED									(5)

//�ړ����̑��x ���x�̕���
/**
*�@@brief �W���ړ��̑��x
*/
#define MOTION_SPEED_MID									(4.0f)

/**
*�@@brief �G�l�~�[�j��G�t�F�N�g���ɃG�l�~�[�����X�Ɋg�傷��l
*/
#define MOTION_EFFECT_SPEED_MID								(1.0f)

/**
*�@@brief �~�[�g�J�[�\���̈ړ����x
*/
#define BAT_MOTION_SPEED_MID								(8.0f)

/**
*�@@brief �~�[�g�J�[�\���̈ړ����x�@�΂�
*/
#define BAT_MOTION_ROOT_SPEED_MID							(7.41f)


/**
*�@@brief �X�g���C�N�]�[���̊���WX
*/
#define STRIKE_REFERENCE_X									(SCREEN_CENTER_X);

/**
*�@@brief �X�g���C�N�]�[���̊���WY
*/
#define STRIKE_REFERENCE_Y									(SCREEN_CENTER_Y+250.0f);

/**
*�@@brief �{�[���e�̊���WX
*/
#define BALL_SHADOW_REFARENCE_X								(SCREEN_CENTER_X)//�����J�n���̃{�[���e����WX

/**
*�@@brief �{�[���e�̊���WY
*/
#define BALL_SHADOW_REFARENCE_Y								(SCREEN_CENTER_Y-200.0f)//�����J�n���̃{�[���e����WY

/**
*�@@brief �������ꂽ�{�[�����o�b�e�B���O�^�C�~���O�ŐԂ��Ȃ鎞�̃f�N�������g�������W
*/
#define BALL_JUST_TIMING_RED								(50.0f) 


//�{�[���T�C�Y�ω���
/**
*�@@brief �{�[�����������Ă���Ƃ����X�ɃT�C�Y���g�k����l
*/
#define BALL_CHENGEVAL_SIZE									(0.01f)	

/**
*�@@brief �{�[�����������Ă���Ƃ��̃T�C�Y�ő�l
*/
#define BALL_CHENGEVAL_MAX									(1.05f)	

/**
*�@@brief �{�[�����������Ă���Ƃ��̃T�C�Y�ŏ��l
*/
#define BALL_CHENGEVAL_MIN									(0.95f)	

/**
*�@@brief �{�[�����㕔�����ɍs���Ƃ��̊g�k�T�C�Y
*/
#define BALL_CHENGEVALTYPEA_SIZE							(0.1f)	

/**
*�@@brief �{�[�����㕔�̃T�C�Y�ő�l
*/
#define BALL_CHENGEVALTYPEA_MAX								(5.0f)	

/**
*�@@brief �{�[���������̃T�C�Y�ŏ��l
*/
#define BALL_CHENGEVALTYPEA_MIN								(-5.0f)	


//�o�b�e�B���O���̃^�C�~���O
/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@��������1
*/
#define BALL_TIMING_PULL1									(42.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@��������2
*/
#define BALL_TIMING_PULL2									(36.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@��������3
*/
#define BALL_TIMING_PULL3									(30.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@��������4
*/
#define BALL_TIMING_PULL4									(24.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@��������5
*/
#define BALL_TIMING_PULL5									(18.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@�W���X�g1
*/
#define BALL_TIMING_JUST1									(12.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@�W���X�g2
*/
#define BALL_TIMING_JUST2									(6.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@�W���X�g3
*/
#define BALL_TIMING_JUST3									(12.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@����1
*/
#define BALL_TIMING_OPPOSITE1								(18.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@����2
*/
#define BALL_TIMING_OPPOSITE2								(24.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@����3
*/
#define BALL_TIMING_OPPOSITE3								(30.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@����4
*/
#define BALL_TIMING_OPPOSITE4								(36.0f)	

/**
*�@@brief �o�b�e�B���O���̃^�C�~���O�@����5
*/
#define BALL_TIMING_OPPOSITE5								(50.0f)	



//�o�b�^�[�A�~�[�g�J�[�\���̍��W�ő�ŏ��l
/**
*�@@brief �o�b�^�[��X�ړ��ő�l
*/
#define BATCURSOR_MOVE_STOP_X_MAX							(SCREEN_CENTER_X+70.0f)

/**
*�@@brief �o�b�^�[��X�ړ��Œ�l
*/
#define BATCURSOR_MOVE_STOP_X_MIN							(SCREEN_CENTER_X-70.0f)

/**
*�@@brief �o�b�^�[��Y�ړ��ő�l
*/
#define BATCURSOR_MOVE_STOP_Y_MAX							(SCREEN_CENTER_Y+335.0f)

/**
*�@@brief �o�b�^�[��Y�ړ��Œ�l
*/
#define BATCURSOR_MOVE_STOP_Y_MIN							(SCREEN_CENTER_Y+165.0f)

//�v���C���[�A�G�l�~�[���v
/**
*�@@brief �v���C���[���v
*/
#define PLAYER_GOUKEI										(2)

/**
*�@@brief CAT��Փx��������v
*/
#define CAT_H_LEVEL											(80)

/**
*�@@brief CAT���v
*/
#define CAT_GOUKEI											(CAT_H_LEVEL)

/**
*�@@brief CAT��Փx���ʎ����v
*/
#define CAT_M_LEVEL											(CAT_H_LEVEL/5)

/**
*�@@brief CAT��Փx�Ⴂ�����v
*/
#define CAT_L_LEVEL											(CAT_H_LEVEL/10)

/**
*�@@brief SURAIMU���v
*/
#define SURAIMU_GOUKEI										(20)

/**
*�@@brief HINOTAMA���v
*/
#define HINOTAMA_GOUKEI										(20)

/**
*�@@brief UFO���v
*/
#define UFO_GOUKEI											(5)

/**
*�@@brief �G�l�~�[���v(SURAIMU_GOUKEI+HINOTAMA_GOUKEI)
*/
#define ENEMY_GOUKEI										(SURAIMU_GOUKEI+HINOTAMA_GOUKEI)

/**
*�@@brief �G�l�~�[�̎�� CAT,SURAIMU,HINOTAMA,UFO
*/
#define ENEMY_TYPE											(4)

/**
*�@@brief �G�l�~�[�̃e�N�X�`���T�C�Y�@��ʉ��s�Ŋg�k
*/
#define ENEMY_CHENGEVAL_SIZE								(0.2f)



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

/**
* @brief �f�o�C�X�擾�֐� GetDevice
* @return LPDIRECT3DDEVICE9
*/
LPDIRECT3DDEVICE9 GetDevice(void);

/**
* @brief �����Z�b�g����֐� SelectText
* @param[in] moji �\�����������������
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
void SelectText(char *moji);

/**
* @brief ������\������֐� DrawTextType
* @details �ŋ���������p Debug�݂̂Ŏg�p
*/
void DrawTextType(void);

/**
* @brief �Q�[���V�[�����Z�b�g����֐� SetScene
* @param[in] Scene �ړ���V�[�������
* @details �Q�[���V�[����E_STAGE���Q��
*/
void SetScene(int Scene);

/**
* @brief ���݂̃Q�[���V�[������肷��֐� GetScene
* @return int ���݂̃Q�[���V�[����Ԃ�
* @details �Q�[���V�[����E_STAGE���Q��
*/
int GetScene(void);

/**
* @brief �Q�[��������������֐� InitGame
* @details �Q�[���N�����Ɏg�p�Q�[�����[�v���Ɏg�p
*/
void InitGame(void);

/**
* @brief �Q�[�����ď���������֐� ReInitTuto
* @details �Q�[�����[�v��(�Q�[�����[�v���������^�C�~���O)�Ɏg�p
*/
void ReInitTuto(void);

/**
* @brief �A�b�v�f�[�g���ď���������֐� UpdateReInit
* @details �Q�[�����[�v���Ɏg�p
*/
void UpdateReInit(void);

/**
* @brief �C�ӂ̃����_�����l�����߂�֐� Random
* @param[in] type �ǂ̃G�l�~�[�^�C�v������
* @return float �G�l�~�[�̍��W��Ԃ�
* @details �G�l�~�[�̏������W�Ŏg�p
*/
float Random(int type);
