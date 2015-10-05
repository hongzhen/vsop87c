#include <time.h>
#include <math.h>
#include <stdio.h>
#include "consts.h"
#include "funcs.h"
#include "sun.h"
#include "moon.h"
#include "support.h"

double GetInitialEstimateSolarTerms(int year, int angle)
{
    int STMonth = (int)ceil((double)(angle + 90.0) / 30.0);
    STMonth = STMonth > 12 ? STMonth - 12 : STMonth;

    /* ÿ�µ�һ�������������ڻ�����4-9��֮�䣬�ڶ��������ķ������ڶ���16��24��֮��*/
    if((angle % 15 == 0) && (angle % 30 != 0))
    {
    	return CalculateJulianDay(year, STMonth, 6, 12, 0, 0.00);
    }
    else
    {
    	return CalculateJulianDay(year, STMonth, 20, 12, 0, 0.00);
    }
}

// ����ָ����ݵ����������angle�ǽ����ڻƵ��ϵĶ���
// ����ָ��������������ʱ��(��ѧʱ)
double CalculateSolarTerms(int year, int angle)
{
    double JD0, JD1,stDegree,stDegreep;

	JD1 = GetInitialEstimateSolarTerms(year, angle);
    printf("jd1 -> %f \n", JD1);
    do
    {
    	JD0 = JD1;
        stDegree = GetSunEclipticLongitudeEC(JD0);
        printf ("stDegree -> %f\n", stDegree);
        /*
            �Իƾ�0�ȵ����ƽ�ʱ�����ڽǶ�360��Բ���ԣ�����ƾ�ֵ������(345,360]��[0,15)�������䣬
            ���ֵ����ǰһ�����䣬��Ҫ��������
        */
        stDegree = ((angle == 0) && (stDegree > 345.0)) ? stDegree - 360.0 : stDegree;
		stDegreep = (GetSunEclipticLongitudeEC(JD0 + 0.000005)
                      - GetSunEclipticLongitudeEC(JD0 - 0.000005)) / 0.00001;
		JD1 = JD0 - (stDegree - angle) / stDegreep;
        printf ("jd0 -> %f, jd1 -> %f\n", JD0, JD1);
    }while((fabs(JD1 - JD0) > 0.0000001));

    return JD1;
}

/*
�õ�������ʱ������һ�����º�˷��ʱ�䣬ƽ�����С��3��
���������ָ��ʱ�����ѧʱ��������
����ֵ�����º�˷����ѧʱ��������
*/
double CalculateMoonShuoJD(double tdJD)
{
    double JD0, JD1,stDegree,stDegreep;

	JD1 = tdJD;
    do
    {
    	JD0 = JD1;
		double moonLongitude = GetMoonEclipticLongitudeEC(JD0);
		double sunLongitude = GetSunEclipticLongitudeEC(JD0);
        if((moonLongitude > 330.0) && (sunLongitude < 30.0))
        {
            sunLongitude = 360.0 + sunLongitude;
        }
        if((sunLongitude > 330.0) && (moonLongitude < 30.0))
        {
            moonLongitude = 60.0 + moonLongitude;
        }

		stDegree = moonLongitude - sunLongitude;
		if(stDegree >= 360.0)
			stDegree -= 360.0;

		if(stDegree < -360.0)
			stDegree += 360.0;

        stDegreep = (GetMoonEclipticLongitudeEC(JD0 + 0.000005) - GetSunEclipticLongitudeEC(JD0 + 0.000005) - GetMoonEclipticLongitudeEC(JD0 - 0.000005) + GetSunEclipticLongitudeEC(JD0 - 0.000005)) / 0.00001;
		JD1 = JD0 - stDegree / stDegreep;
    }while((fabs(JD1 - JD0) > 0.00000001));

    return JD1;
}

void CalculateStemsBranches(int year, int *stems, int *branches)
{
    int sc = year - 2000;
    *stems = (7 + sc) % 10;
    *branches = (5 + sc) % 12;

    if(*stems < 0)
        *stems += 10;
    if(*branches < 0)
        *branches += 12;
}
