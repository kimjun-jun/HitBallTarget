/**
* @file ui.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once


// �}�N����`
//UI
#define UI_GOUKEI						(2)

//�X�g���C�N�]�[��
#define TEXTURE_GAME_STRIKE	_T("data/TEXTURE/item/strike.png")	// �T���v���p�摜  

#define TEXTURE_STRIKE_SIZE_X	(150/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_STRIKE_SIZE_Y	(180/2) // ����  

#define TEXTURE_STRIKE_COLLISION_BB_SIZE_X	(150/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_STRIKE_COLLISION_BB_SIZE_Y	(180/2) // ����  

#define TEXTURE_STRIKE_COLLISION_BC_SIZE		((TEXTURE_STRIKE_SIZE_X+TEXTURE_STRIKE_SIZE_Y)/2) // �o���b�g�����蔻��BC�e�N�X�`���T�C�Y 


#define STRIKE_TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define STRIKE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define STRIKE_ANIM_PATTERN_NUM			(STRIKE_TEXTURE_PATTERN_DIVIDE_X*STRIKE_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����  
#define STRIKE_TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g  

#define STRIKE_GOUKEI						(1) //�{�[���̍��v

#define STRIKE_NO						(0)

//�~�[�g�J�[�\��
#define TEXTURE_GAME_CURSOR	_T("data/TEXTURE/item/batcursor.png")	// �T���v���p�摜  

#define TEXTURE_CURSOR_BIG_SIZE_X	(75/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_CURSOR_BIG_SIZE_Y	(75/2) // ����  
#define TEXTURE_CURSOR_BIG_COLLISION_BC_SIZE		((TEXTURE_CURSOR_BIG_SIZE_X+TEXTURE_CURSOR_BIG_SIZE_Y)/2) // �o���b�g�����蔻��BC�e�N�X�`���T�C�Y 


#define TEXTURE_CURSOR_SMALL_SIZE_X	(30/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_CURSOR_SMALL_SIZE_Y	(30/2) // ����  
#define TEXTURE_CURSOR_SMALL_COLLISION_BC_SIZE		((TEXTURE_CURSOR_SMALL_SIZE_X+TEXTURE_CURSOR_SMALL_SIZE_Y)/2) // �o���b�g�����蔻��BC�e�N�X�`���T�C�Y 


#define CURSOR_TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define CURSOR_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define CURSOR_ANIM_PATTERN_NUM			(CURSOR_TEXTURE_PATTERN_DIVIDE_X*CURSOR_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����  
#define CURSOR_TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g  

#define CURSOR_GOUKEI						(1) //�{�[���̍��v

#define CURSOR_NO						(1)


//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
typedef struct // �o���b�g�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S�� 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				rot;						// �|���S���̉�]��
	int						nCountAnim;					// �A�j���[�V�����J�E���g 
	int						nPatternAnim;				// �A�j���[�V�����p�^�[���i���o�[ 
	int						direction;					// �|���S���̈ړ�����
	int						meet;
	bool					use;
} Ui;

typedef struct // �o���b�g�\����
{
	Ui s;
}STRIKE;

typedef struct // �o���b�g�\����
{
	Ui c;
}CURSOR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUi(int type);
void ReInitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);

STRIKE *GetStrike(void);
CURSOR *Get_Cursor(void);

HRESULT MakeVertexUi(int i);
void SetTextureUi(int cntPattern, int i);	// 
void SetVertexUi(int i);					// 

