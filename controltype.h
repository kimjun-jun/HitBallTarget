/**
* @file controltype.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_DIGITAL							_T("data/TEXTURE/sozai/select/digital.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ANALOG							_T("data/TEXTURE/sozai/select/analog.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CONTYPECURSOR					_T("data/TEXTURE/sozai/select/nowselect.png")	//!< �ǂݍ��ރe�N�X�`���t�@�C����	
#define TEXTURE_CONTYPEBROAD_SIZE_X				(200)											//!< �|���S���̕�
#define TEXTURE_CONTYPEBROAD_SIZE_Y				(100)											//!< �|���S���̍���
#define	CONTYPEMAX								(3)												//!< ��ʂ̑I������

/**
*�@@struct CONTYPE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;													//!< �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];												//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																//!< �|���S���̍��W
}CONTYPE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief �R���g���[���^�C�v��m�������֐� InitContype
* @param[in] type �������^�C�v�@INIT_TIME���p�B0:����@0�ȊO: 2��ڈȍ~
* @return HRESULT
*/
HRESULT InitContype(int type);

/**
* @brief �R���g���[���^�C�v��m�ď������֐� ReInitContype
*/
void ReInitContype(void);

/**
* @brief �R���g���[���^�C�v��m�J���֐� UninitContype
*/
void UninitContype(void);

/**
* @brief �R���g���[���^�C�v��m�X�V�֐� UpdateContype
*/
void UpdateContype(void);

/**
* @brief �R���g���[���^�C�v��m�X�V�֐� UpdateTUTOContype
*/
void UpdateTUTOContype(void);

/**
* @brief �R���g���[���^�C�v��m�`��֐� DrawContype
*/
void DrawContype(void);

/**
* @brief �R���g���[���^�C�v��m�J�[�\�����~�܂��Ă���ꏊ�擾�֐� GetSCONkeypos
* @return int
*/
int GetSCONkeypos(void);
