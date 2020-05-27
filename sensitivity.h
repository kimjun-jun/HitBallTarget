/**
* @file sensitivity.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_L1R1								_T("data/TEXTURE/sozai/select/digital.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SENSITIVITYNUM						_T("data/TEXTURE/BG/0-9.png")				//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SENSITIVITYBROAD_SIZE_X				(200)										//!< �|���S���̕�
#define TEXTURE_SENSITIVITYBROAD_SIZE_Y				(100)										//!< �|���S���̍���
#define	SENSITIVITYMAX								(2)											//!< ��ʂ̑I������

/**
*�@@struct SENSITIVITY
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;													//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];												//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																//!< �|���S���̍��W
}SENSITIVITY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Sensitivity�������֐� InitSensitivity
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitSensitivity(int type);

/**
* @brief Sensitivity�ď������֐� ReInitSensitivity
*/
void ReInitSensitivity(void);

/**
* @brief Sensitivity�J���֐� UninitSensitivity
*/
void UninitSensitivity(void);

/**
* @brief Sensitivity�X�V�֐� UpdateSensitivity
*/
void UpdateSensitivity(void);

/**
* @brief SensitivityTUTO�X�V�֐� UpdateTUTOSensitivity
*/
void UpdateTUTOSensitivity(void);

/**
* @brief Sensitivity�`��֐� DrawSensitivity
*/
void DrawSensitivity(void);

/**
* @brief ���x��m�J�[�\�����~�܂��Ă���ꏊ�擾�֐� GetSSENSIkey
* @return int
*/
int GetSSENSIkey(void);
