/**
* @file collision.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief �����蔻��BB�֐� CollisionBB
* @param[in] D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2
* @return bool
* @details BB�œ����蔻�肵�������W�ƃT�C�Y��n��
*/
bool CollisionBB(D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2);

/**
* @brief �����蔻��BC�֐� CollisionBC
* @param[in] D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2
* @return bool
* @details BC�œ����蔻�肵�������W�ƃT�C�Y��n��
*/
bool CollisionBC(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2);

/**
* @brief �����蔻��m�F�֐� CheakHit
*/
void CheakHit(void);

/**
* @brief �{�[�����[�v�̏������֐� LoopInit
*/
void LoopInit(void);
