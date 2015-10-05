#ifndef __SUN_CALENDAR_H__
#define __SUN_CALENDAR_H__


/*����̫���ĵ��Ļƾ�(��)��dt������ǧ����*/
double CalcSunEclipticLongitudeEC(double dt);

/*����̫���ĵ��Ļ�γ(��)��dt������ǧ����*/
double CalcSunEclipticLatitudeEC(double dt);

/*����̫���ĵ��Ļƾ���longitude, latitude ������ǰ�����Ļƾ������Ļ�γ(��)��dt������ǧ����������ֵ��λ��*/
double AdjustSunEclipticLongitudeEC(double dt, double longitude, double latitude);

/*����̫���ĵ��Ļ�γ��longitude������ǰ��̫�����Ļƾ�(��)��dt������ǧ����������ֵ��λ��*/
double AdjustSunEclipticLatitudeEC(double dt, double longitude);

/*����*/
double CalcSunEarthRadius(double dt);

/*�õ�ĳ��ʱ���̫�����Ļƾ�(�ӻƾ�)����λ�ȣ�dt������������*/
double GetSunEclipticLongitudeEC2(double dt);

/*�õ�ĳ�������յ�̫�����Ļƾ�(�ӻƾ�)����λ��*/
double GetSunEclipticLongitudeEC(double jde);

/*�õ�ĳ�������յ�̫�����Ļ�γ(�ӻ�γ)����λ��*/
double GetSunEclipticLatitudeEC(double jde);

#endif //__SUN_CALENDAR_H__

