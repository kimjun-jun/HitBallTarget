///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	sensitivity.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_L1R1				_T("data/TEXTURE/sozai/select/digital.png")		
#define	TEXTURE_SENSITIVITYNUM		_T("data/TEXTURE/BG/0-9.png")		

#define TEXTURE_SENSITIVITYBROAD_SIZE_X		(200)										// �^�C�g�����S�̕�
#define TEXTURE_SENSITIVITYBROAD_SIZE_Y		(100)										// �^�C�g�����S�̍���


#define SENSITIVITY_TEXTURE_PATTERN_DIVIDE_X	(10)	// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define SENSITIVITY_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define SENSITIVITY_ANIM_PATTERN_NUM			(SENSITIVITY_TEXTURE_PATTERN_DIVIDE_X*SENSITIVITY_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����  


#define	SENSITIVITYMAX		(2)						//�|�[�Y��ʂ̑I������

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N

	D3DXVECTOR3				pos;						// ?���S���̈ړ���
}SENSITIVITY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSensitivity(int type);
void ReInitSensitivity(void);
void UninitSensitivity(void);
void UpdateSensitivity(void);
void UpdateTUTOSensitivity(void);
void DrawSensitivity(void);
void SetTextureSensitivity(void);
void SetVertexSensitivity(void);
int GetSSENSIkey(void);
