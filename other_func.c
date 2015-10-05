#include <math.h>
#include "support.h"
#include "other_func.h"



static double s_stAccInfo[] =
{
    0.00, 1272494.40, 2548020.60, 3830143.80, 5120226.60, 6420865.80,
    7732018.80, 9055272.60, 10388958.00, 11733065.40, 13084292.40, 14441592.00,
    15800560.80, 17159347.20, 18513766.20, 19862002.20, 21201005.40, 22529659.80,
    23846845.20, 25152606.00, 26447687.40, 27733451.40, 29011921.20, 30285477.60
};

//��֪1900��С��ʱ��Ϊ1��6��2:05:00��
const double base1900_SlightColdJD = 2415025.5868055555;

double CalculateSolarTermsByExp(int year, int st)
{
    if((st < 0) || (st > 24))
        return 0.0;

    double stJd = 365.24219878 * (year - 1900) + s_stAccInfo[st] / 86400.0;

    return base1900_SlightColdJD + stJd;

}

/*
���������˷�յľ��鹫ʽ

���쵽1900��1��0�գ������գ��Ĳ��Ϊ���գ���ô��y�꣨1900��0�꣩��x�������Ļ����ǣ�
F = 365.242 * y + 6.2 + 15.22 *x - 1.9 * sin(0.262 * x)

��1900�꿪ʼ�ĵ�m��˷�յĹ�ʽ�ǣ�
M = 1.6 + 29.5306 * m + 0.4 * sin(1 - 0.45058 * m)
*/
double CalculateSolarTermsByFm(int year, int st)
{
    double baseJD = CalculateJulianDay(1900, 1, 1, 0, 0, 0.0) - 1;
    int y = year - 1900;

    double accDay = 365.2422 * y + 6.2 + 15.22 * st - 1.0 * sin(0.262 * st);

    return baseJD + accDay;
}

double CalculateNewMoonByFm(int m)
{
    double baseJD = CalculateJulianDay(1900, 1, 1, 0, 0, 0.0) - 1;

    double accDay = 1.6 + 29.5306 * m + 0.4 * sin(1 - 0.45058 * m);

    return baseJD + accDay;
}
