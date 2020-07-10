/**
* @file meetstrike.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MEETSTRIKE_GOUKEI							(2)																	//!< �~�[�g�J�[�\���ƃX�g���C�N
																														
//�X�g���C�N�]�[��
#define TEXTURE_GAME_STRIKE							_T("data/TEXTURE/item/strike.png")									//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_STRIKE_SIZE_X						(150/2)																//!< �|���S���̕� 
#define TEXTURE_STRIKE_SIZE_Y						(180/2)																//!< �|���S���̍���
#define TEXTURE_STRIKE_COLLISION_BB_SIZE_X			(150/2)																//!< �����蔻�� BB �|���S���̕�
#define TEXTURE_STRIKE_COLLISION_BB_SIZE_Y			(180/2)																//!< �����蔻�� BB �|���S���̍���
#define TEXTURE_STRIKE_COLLISION_BC_SIZE			((TEXTURE_STRIKE_SIZE_X+TEXTURE_STRIKE_SIZE_Y)/2)					//!< �����蔻�� BC �e�N�X�`���T�C�Y 
#define STRIKE_GOUKEI								(1)																	//!< �X�g���C�N�\���̍��v

//�~�[�g�J�[�\��
#define TEXTURE_GAME_CURSOR							_T("data/TEXTURE/item/batcursor.png")								//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_CURSOR_BIG_SIZE_X					(75/2)																//!< �|���S���̕� ��
#define TEXTURE_CURSOR_BIG_SIZE_Y					(75/2)																//!< �|���S���̍��� �� 
#define TEXTURE_CURSOR_BIG_COLLISION_BC_SIZE		((TEXTURE_CURSOR_BIG_SIZE_X+TEXTURE_CURSOR_BIG_SIZE_Y)/2)			//!< �����蔻�� BC �e�N�X�`���T�C�Y ��
#define TEXTURE_CURSOR_SMALL_SIZE_X					(30/2)																//!< �|���S���̕� ��
#define TEXTURE_CURSOR_SMALL_SIZE_Y					(30/2)																//!< �|���S���̍��� ��
#define TEXTURE_CURSOR_SMALL_COLLISION_BC_SIZE		((TEXTURE_CURSOR_SMALL_SIZE_X+TEXTURE_CURSOR_SMALL_SIZE_Y)/2)		//!< �����蔻�� BC �e�N�X�`���T�C�Y �� 
#define CURSOR_GOUKEI								(1)																	//!< �~�[�g�J�[�\���\���̍��v


//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
/**
*�@@struct MeetStrike
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																			//!< �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];																		//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																						//!< �|���S���̈ړ���
	D3DXVECTOR3				rot;																						//!< �|���S���̉�]��
	int						direction;																					//!< �|���S���̈ړ�����
	int						meet;																						//!< �傩����
	bool					use;																						//!< �g�p���Ă��邩�ǂ���
} MeetStrike;

/**
*�@@struct STRIKE
*�@@brief 2D�|���S�����`����\���� MeetStrike
*/
typedef struct
{
	MeetStrike s;
}STRIKE;

/**
*�@@struct CURSOR
*�@@brief 2D�|���S�����`����\���� MeetStrike
*/
typedef struct
{
	MeetStrike c;
}CURSOR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief MeetStrike�������֐� InitMeetStrike
* @param[in] type �������^�C�v�@INIT_TIME���p�B0:����@0�ȊO: 2��ڈȍ~
* @return HRESULT
*/
HRESULT InitMeetStrike(int type);

/**
* @brief MeetStrike�ď������֐� ReInitMeetStrike
* @details �Q�[�����[�v��̏������ȂǂŎg�p�B���d�Ńe�N�X�`�����̓ǂݍ��݂�h�����߂��̊֐��ŏ��������Ă���
*/
void ReInitMeetStrike(void);

/**
* @brief MeetStrike�J���֐� UninitMeetStrike
*/
void UninitMeetStrike(void);

/**
* @brief MeetStrike�X�V�֐� UpdateMeetStrike
*/
void UpdateMeetStrike(void);

/**
* @brief MeetStrike�`��֐� DrawMeetStrike
*/
void DrawMeetStrike(void);


/**
* @brief MeetStrike�擾�֐� GetStrike
* @return STRIKE
*/
STRIKE *GetStrike(void);

/**
* @brief MeetStrike�擾�֐� Get_Cursor
* @return CURSOR
*/
CURSOR *Get_Cursor(void);

/**
* @brief MeetStrike�擾�֐� SetVertexMeetStrike
* @param[in] CursorType �J�[�\���^�C�v
*/
void SetVertexMeetStrike(int CursorType);

