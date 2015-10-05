#include "td_utc.h"

/*���ļ�����������������������������ҵӦ�ã�����ѯ����ΰ����*/


typedef struct
{
    int year;
    double d1, d2, d3, d4;
}TD_UTC_DELTA;

// TD - UT1 �����
const TD_UTC_DELTA deltaTbl[] =
{
    { -4000,108371.7,-13036.80,392.000, 0.0000 },
    { -500, 17201.0,  -627.82, 16.170,-0.3413  },
    {  -150, 12200.6,  -346.41,  5.403,-0.1593 },
    { 150,  9113.8,  -328.13, -1.647, 0.0377   },
    { 500,  5707.5,  -391.41,  0.915, 0.3145   },
    { 900,  2203.4,  -283.45, 13.034,-0.1778   },
    { 1300,   490.1,   -57.35,  2.085,-0.0072  },
    { 1600,   120.0,    -9.81, -1.532, 0.1403  },
    { 1700,    10.2,    -0.91,  0.510,-0.0370  },
    { 1800,    13.4,    -0.72,  0.202,-0.0193  },
    { 1830,     7.8,    -1.81,  0.416,-0.0247  },
    { 1860,     8.3,    -0.13, -0.406, 0.0292  },
    { 1880,    -5.4,     0.32, -0.183, 0.0173  },
    { 1900,    -2.3,     2.06,  0.169,-0.0135  },
    { 1920,    21.2,     1.69, -0.304, 0.0167  },
    { 1940,    24.2,     1.22, -0.064, 0.0031  },
    { 1960,    33.2,     0.51,  0.231,-0.0109  },
    { 1980,    51.0,     1.29, -0.026, 0.0032  },
    { 2000,    63.87,    0.1,   0.0,     0.0   },
    { 2005,    0.0,      0.0,   0.0,   0.0     }
};

//������������
double deltatExt(double y, int jsd)
{
    double dy = (y - 1820.0) / 100.0;
    return -20.0 + jsd * dy * dy;
}

double TdUtcDeltatT(double y)
{
    //��������ʱ��ԭ��ʱ֮��,������
    if(y >= 2005)
    {
         //sd��2005��֮���꣨һֵ��y1�꣩���ٶȹ��ơ�
         //sjd��y1��֮��ļ��ٶȹ��ơ���ʿ������jsd=31,NASA��վjsd=32,skmap��jsd=29
         int y1 = 2014;
         double sd = 0.4;
         int jsd = 31;
         if(y <= y1)
             return 64.7 + (y - 2005) * sd; //ֱ������
         double v = deltatExt(y, jsd);        //������������
         double dv = deltatExt(y1, jsd) - ( 64.7 + (y1 - 2005) * sd ); //y1��Ķ���������ֱ�����ƵĲ�
         if(y < y1 + 100)
             v -= dv * (y1 + 100 - y) / 100;
         return v;
    }
    else
    {
        int i;
        for(i = 0; i < sizeof(deltaTbl) / sizeof(deltaTbl[0]); i++)
        {
            if(y < deltaTbl[i + 1].year)
                break;
        }
        double t1 = (double)(y - deltaTbl[i].year)/(double)(deltaTbl[i + 1].year - deltaTbl[i].year) * 10.0;
        double t2 = t1 * t1;
        double t3 = t2 * t1;

        return deltaTbl[i].d1 + deltaTbl[i].d2 * t1 + deltaTbl[i].d3 * t2 + deltaTbl[i].d4 * t3;
    }
}

double TdUtcDeltatT2(double jd2k)
{
    //����������(J2000����),����TD-UT(��λ:��)
    return TdUtcDeltatT(jd2k/365.2425 + 2000) / 86400.0;
}

