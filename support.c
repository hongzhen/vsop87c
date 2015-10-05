#include "support.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "consts.h"
#include "td_utc.h"



const static int daysOfMonth[MONTHES_FOR_YEAR] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


bool IsLeapYear(int year)
{
    return ( (year % 4 == 0) && (year % 100 != 0) ) || (year % 400 == 0);
}

/*
�ж��Ƿ������ø������Ժ������
1582�꣬����̻ʽ�1582��10��4��ָ��Ϊ1582��10��15�գ��Ӵ˷�ֹ�˿�������ƶ�����������
���ø�����
*/
bool IsGregorianDays(int year, int month, int day)
{
    if(year < 1582)
        return false;

    if(year == 1582)
    {
        if( (month < 10) || ((month == 10) && (day < 15)) )
            return false;
    }

    return true;
}

int GetDaysOfMonth(int year, int month)
{
    if((month < 1) || (month > 12))
        return 0;

    int days = daysOfMonth[month - 1];
    if((month == 2) && IsLeapYear(year))
    {
        days++;
    }

    return days;
}

/*����һ���й�ȥ������������ָ������һ��*/
int CalcYearPassedDays(int year, int month, int day)
{
    int passedDays = 0;

    int i;
    for(i = 0; i < month - 1; i++)
    {
        passedDays += daysOfMonth[i];
    }

    passedDays += day;
    if((month > 2) && IsLeapYear(year))
        passedDays++;

    return passedDays;
}

/*����һ���л�ʣ�µ�������������ָ������һ��*/
int CalcYearRestDays(int year, int month, int day)
{
    int leftDays = daysOfMonth[month - 1] - day;

    int i;
    for(i = month; i < MONTHES_FOR_YEAR; i++)
    {
        leftDays += daysOfMonth[i];
    }

    if((month <= 2) && IsLeapYear(year))
        leftDays++;

    return leftDays;
}

/*
����years��1��1�պ�yeare��1��1��֮���������
����years��1��1�գ����ǲ�����yeare��1��1��
*/
int CalcYearsDays(int years, int yeare)
{
    int days = 0;

    int i;
    for(i = years; i < yeare; i++)
    {
        if(IsLeapYear(i))
            days += DAYS_OF_LEAP_YEAR;
        else
            days += DAYS_OF_NORMAL_YEAR;
    }

    return days;
}

int CalculateDays(int ys, int ms, int ds, int ye, int me, int de)
{
    int days = CalcYearRestDays(ys, ms, ds);

    if(ys != ye) /*����ͬһ�������*/
    {
        if((ye - ys) >= 2) /*�������һ�꣬Ҫ������������ʱ��*/
        {
            days += CalcYearsDays(ys + 1, ye);
        }
        days += CalcYearPassedDays(ye, me, de);
    }
    else
    {
        days = days - CalcYearRestDays(ye, me, de);
    }

    return days;
}

int TotalWeek(int year, int month, int day)
{
    int d = CalcYearPassedDays(year, month, day);
    int y = year - 1;
    int w = y * DAYS_OF_NORMAL_YEAR + y / 4 - y / 100 + y / 400 + d;

    return w % 7;
}

int ZellerWeek(int year, int month, int day)
{
    int m = month;
    int d = day;

    if(month <= 2) /*��С��2���·ݽ�������*/
    {
        year--;
        m = month + 12;
    }

    int y = year % 100;
    int c = year / 100;

    int w = (y + y / 4 + c / 4 - 2 * c + (13 * (m + 1) / 5) + d - 1) % 7;
    if(w < 0) /*�����������Ǹ��������*/
        w += 7;

    return w;
}

double CalculateJulianDay(int year, int month, int day, int hour, int minute, double second)
{
    if(month <= 2)
    {
        month += 12;
        year -= 1;
    }
    int B = -2;
    if(IsGregorianDays(year, month, day))
    {
        B = year / 400 - year / 100;
    }

    double a = 365.25 * year;
    double b = 30.6001 * (month + 1);
    return (int)a + (int)b + B + 1720996.5 + day + hour / 24.0 + minute / 1440.0 + second / 86400.0;
}

double CalculateJulianDay2(WZDAYTIME *pDT)
{
    return CalculateJulianDay(pDT->year, pDT->month, pDT->day, pDT->hour, pDT->minute, pDT->second);
}

void GetDayTimeFromJulianDay(double jd, WZDAYTIME *pDT)
{
    int cna, cnd;
    double cnf;

    double jdf = jd + 0.5;
    cna = (int)(jdf);
    cnf = jdf - cna;
    if(cna > 2299161)
    {
        cnd = (int)((cna - 1867216.25) / 36524.25);
        cna = cna + 1 + cnd - (int)(cnd / 4);
    }
    cna = cna + 1524;
    int year = (int)((cna - 122.1) / 365.25);
    cnd = cna - (int)(365.25 * year);
    int month = (int)(cnd / 30.6001);
    int day = cnd - (int)(month * 30.6001);
    year = year - 4716;
    month = month - 1;
    if(month  > 12)
        month = month - 12;
    if(month <= 2)
        year = year + 1;
    if(year < 1)
        year = year - 1;
    cnf = cnf * 24.0;
    pDT->hour = (int)(cnf);
    cnf = cnf - pDT->hour;
    cnf = cnf * 60.0;
    pDT->minute = (int)(cnf);
    cnf = cnf - pDT->minute;
    //cnf = cnf * 60.0;
    pDT->second = cnf * 60.0;
    pDT->year = year;
    pDT->month = month;
    pDT->day = day;
}

// ------------------------------------------------------------------------
//
// ��������ʱ��ת����ʱ�䣨�Ը�������ʾ����ʱ�䣩
//
// ------------------------------------------------------------------------
void UTCToLocalTime(int *year, int *month, int *day, int *hour, int *minute, double *second)
{
    // ���㱾��ʱ��ͱ�׼ʱ���ʱ���λ���룩
    int nDifference_hour = (int)(__timezone / 3600);
    int nDifference_minute = (int)((__timezone - nDifference_hour * 3600) / 60);
    int nDifference_second = (int)((__timezone - nDifference_hour * 3600) - nDifference_minute * 60);

    // ��������ʱ�� + ʱ�� = ����ʱ��

    // ��
    *second = (*second) - nDifference_second;
    if(*second >= 60 || *second < 0)
    {
        *minute = *second > 0 ? *minute + 1 : *minute - 1 ;
        *second = fabs(fabs(*second) - 60);
    }

    // ��
    *minute = *minute - nDifference_minute;
    if(*minute >= 60 || *minute < 0)
    {
        *hour = *minute > 0 ? *hour + 1 : *hour - 1;
        *minute = abs(abs(*minute) - 60);
    }

    // ʱ
    *hour = *hour - nDifference_hour;
    if(*hour >= 24 || *hour < 0)
    {
        *day = (*hour >= 24 || *hour == 0) ? *day + 1 : *day - 1;
        *hour = abs(abs(*hour) - 24);
    }

    // ��
    int nDaysOfMonth = GetDaysOfMonth(*year, *month);
    if(*day > nDaysOfMonth || *day <= 0)
    {
        if(*day > nDaysOfMonth)
           (*month)++;
        if(*day < nDaysOfMonth || *day <= 0)
           (*month)--;

        *day = abs(abs(*day) - nDaysOfMonth);
    }
    // ��
    if(*month > 12 || *month <= 0)
    {
        *year = *month > 0 ? *year + 1 : *year - 1;
        *month = *month > 0 ? abs(*month - 12) : abs(12 + *month);
    }
}

// ------------------------------------------------------------------------
//
// ����ʱ��ת��������ʱ�䣨�Ը�������ʾ��
//
// ------------------------------------------------------------------------
void LocalTimetoUTC(int *year, int *month, int *day, int *hour, int *minute, double *second)
{
    // ���㱾��ʱ��ͱ�׼ʱ���ʱ���λ���룩
    int nDifference_hour = (int)(__timezone / 3600);
    int nDifference_minute = (int)((__timezone - nDifference_hour * 3600) / 60);
    int nDifference_second = (int)((__timezone - nDifference_hour * 3600) - nDifference_minute * 60);

    // ����ʱ�� - ʱ�� = ��������ʱ��

    // ��
    *second = *second + nDifference_second;
    if(*second >= 60 || *second < 0)
    {
        *minute = *second > 0 ? *minute + 1 : *minute - 1 ;
        *second = abs((int)fabs(*second) - 60);
    }

    // ��
    *minute = *minute + nDifference_minute;
    if(*minute >= 60 || *minute < 0)
    {
        *hour = *minute > 0 ? *hour + 1 : *hour - 1;
        *minute = abs(abs(*minute) - 60);
     }

    // ʱ
    *hour = *hour + nDifference_hour;
    if(*hour >= 24 || *hour < 0)
    {
        *day = (*hour >= 24 || *hour == 0) ? *day + 1 : *day - 1;
        *hour = abs(abs(*hour) - 24);
    }

    // ��
    int nDaysOfMonth = GetDaysOfMonth(*year,*month);
    if(*day > nDaysOfMonth || *day <= 0)
    {
        if(*day > nDaysOfMonth)
             (*month)++;
        if(*day < nDaysOfMonth || *day <= 0)
           (*month)--;

        *day = abs(abs(*day) - nDaysOfMonth);
    }
    // ��
    if(*month > 12 || *month <= 0)
    {
        *year = *month > 0 ? *year + 1 : *year - 1;
        *month = *month > 0 ? abs(*month - 12) : abs(12 + *month);
    }
}

double JDUTCToLocalTime(double utcJD)
{
    return utcJD - (double)__timezone / 86400.0;
}

double JDLocalTimetoUTC(double localJD)
{
     return localJD + (double)__timezone / 86400.0;
}

/*
double JDUTCToLocalTime(double utcJD)
{
    WZDAYTIME dt;
    GetDayTimeFromJulianDay(utcJD, &dt);

    UTCToLocalTime(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);

    return CalculateJulianDay(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
}

double JDLocalTimetoUTC(double localJD)
{
    WZDAYTIME dt;
    GetDayTimeFromJulianDay(localJD, &dt);
    LocalTimetoUTC(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);

    return CalculateJulianDay(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
}
*/
double JDUTCtoTD(double utcJD)
{
	double jd2K = utcJD - JD2000;
	double tian = TdUtcDeltatT2(jd2K);
	utcJD += tian;

	return utcJD;
}

double JDTDtoUTC(double tdJD)
{
	double jd2K = tdJD - JD2000;
	double tian = TdUtcDeltatT2(jd2K);
	tdJD -= tian;

    return tdJD;
}

double JDLocalTimetoTD(double localJD)
{
    double tmp = JDLocalTimetoUTC(localJD);

    return JDUTCtoTD(tmp);
}

double JDTDtoLocalTime(double tdJD)
{
    double tmp = JDTDtoUTC(tdJD);

    return JDUTCToLocalTime(tmp);
}

double RadianToDegree(double radian)
{
	return radian * 180.0 / PI;
}

double DegreeToRadian(double degree)
{
	return degree * PI / 180.0;
}

double Mod360Degree(double degrees)
{
   double dbValue = degrees;

   while(dbValue < 0.0)
     dbValue += 360.0;

   while(dbValue > 360.0)
     dbValue -= 360.0;

   return dbValue;
}

int JDtoString(double jd, char *strBuf, int bufSize)
{
    WZDAYTIME dt;

    GetDayTimeFromJulianDay(jd, &dt);

    return snprintf(strBuf, bufSize, "%04d-%02d-%02d, %02d:%02d:%4.2f",
                     dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
}

