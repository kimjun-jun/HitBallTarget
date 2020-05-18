/**
* @file effect.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

// �}�N����`
#define BE_TEXTURE_FILE_00		_T("data/TEXTURE/effect/bom.png")	// �T���v���p�摜
#define BE_SIZE_W			(20)	// �e�N�X�`���T�C�Yl
#define BE_SIZE_H			(20)	// ����


#define BE_TEXTURE_PATTERN_DIVIDE_X	(6)	// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define BE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define BE_ANIM_PATTERN_NUM			(BE_TEXTURE_PATTERN_DIVIDE_X*BE_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����  
#define BE_TIME_ANIMATION				(6)	// �A�j���[�V�����̐؂�ւ��J�E���g  


typedef struct // �L�����N�^�[�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �w�i�̈ʒu
	int						nCountAnim;					// �A�j��?�V�����J�E���g 
	int						nPatternAnim;				// �A�j��?�V�����p??���i���o? 
	bool					motion;						// ?�������Ă��� �U�������Ă��Ȃ�
	bool					use;						// �g�p���Ă��邩�ǂ���
} BE;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBE(int type);
void ReInitBE(void);
void UninitBE(void);
void UpdateBE(void);
void DrawBE(void);
HRESULT MakeVertexBE(void);
void SetTextureBe(int cntPattern);
void SetVertexBE(void);
void SelectBE(int type);
void DeadEffect(int i, int type);
BE *GetBE(int i);