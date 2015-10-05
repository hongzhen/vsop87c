#ifndef __VSOP87_DATA_H__
#define __VSOP87_DATA_H__

typedef struct
{
    double A;
    double B;
    double C;
} VSOP87_COEFFICIENT;

/*������Դ�ǣ������ļ��㡷 ��¼II*/
// ����̫���ƾ�������
extern const VSOP87_COEFFICIENT Earth_L0[64];
extern const VSOP87_COEFFICIENT Earth_L1[34];
extern const VSOP87_COEFFICIENT Earth_L2[20];
extern const VSOP87_COEFFICIENT Earth_L3[ 7];
extern const VSOP87_COEFFICIENT Earth_L4[ 3];
extern const VSOP87_COEFFICIENT Earth_L5[ 1];



// ����̫����γ������
extern const VSOP87_COEFFICIENT Earth_B0[ 5];
extern const VSOP87_COEFFICIENT Earth_B1[ 2];
extern const VSOP87_COEFFICIENT Earth_B2[ 4];
extern const VSOP87_COEFFICIENT Earth_B3[ 4];
extern const VSOP87_COEFFICIENT Earth_B4[ 1];

// �����յؾ�����������
extern const VSOP87_COEFFICIENT Earth_R0[40];
extern const VSOP87_COEFFICIENT Earth_R1[10];
extern const VSOP87_COEFFICIENT Earth_R2[ 6];
extern const VSOP87_COEFFICIENT Earth_R3[ 2];
extern const VSOP87_COEFFICIENT Earth_R4[ 1];

#endif //__VSOP87_DATA_H__

