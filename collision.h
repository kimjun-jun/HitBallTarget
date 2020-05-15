///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	collision.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once
bool CollisionBB(D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2);
bool CollisionBC(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2);
void CheakHit(void);
void LoopInit(void);
