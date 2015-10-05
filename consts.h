#ifndef __CALENDAR_CONST_H__
#define __CALENDAR_CONST_H__

const static int MONTHES_FOR_YEAR = 12;
const static int DAYS_FOR_WEEK = 7;

const static int DAYS_OF_LEAP_YEAR = 366;
const static int DAYS_OF_NORMAL_YEAR = 365;

const static int SOLAR_TERMS_COUNT = 24;

const static int HEAVENLY_STEMS = 10;
const static int EARTHLY_BRANCHES = 12;
const static int CHINESE_SHENGXIAO = 12;
const static int MAX_GREGORIAN_MONTH_DAYS = 31;

const static int MAX_CHINESE_MONTH_DAYS = 30;
const static int CHINESE_L_MONTH_DAYS = 30;
const static int CHINESE_S_MONTH_DAYS = 29;
const static int MAX_CHINESE_MONTH_FOR_YEAR = 13;

const static double JD2000 = 2451545.0;
// Բ����
const static double PI = 3.1415926535897932384626433832795;

//ÿ���ȵĽ�����
static double ARC_SEC_PER_RADIAN = 180.0 * 3600.0 / PI;
// һ�ȴ���Ļ���
static double RADIAN_PER_ANGLE = PI / 180.0;

static double SUN_EL_V = 360.0 / 365.2422;
//const static double MOON_EL_V = 360.0 / 29.53058886;
static double MOON_EL_V = 360.0 / 27.32;

typedef int SOLAR_TERMS;

// ��������
const static int VERNAL_EQUINOX      = 0;    // ����
const static int CLEAR_AND_BRIGHT    = 1;    // ����
const static int GRAIN_RAIN          = 2;    // ����
const static int SUMMER_BEGINS       = 3;    // ����
const static int GRAIN_BUDS          = 4;    // С��
const static int GRAIN_IN_EAR        = 5;    // â��
const static int SUMMER_SOLSTICE     = 6;    // ����
const static int SLIGHT_HEAT         = 7;    // С��
const static int GREAT_HEAT          = 8;    // ����
const static int AUTUMN_BEGINS       = 9;    // ����
const static int STOPPING_THE_HEAT   = 10;   // ����
const static int WHITE_DEWS          = 11;   // ��¶
const static int AUTUMN_EQUINOX      = 12;   // ���
const static int COLD_DEWS           = 13;   // ��¶
const static int HOAR_FROST_FALLS    = 14;   // ˪��
const static int WINTER_BEGINS       = 15;   // ����
const static int LIGHT_SNOW          = 16;   // Сѩ
const static int HEAVY_SNOW          = 17;   // ��ѩ
const static int WINTER_SOLSTICE     = 18;   // ����
const static int SLIGHT_COLD         = 19;   // С��
const static int GREAT_COLD          = 20;   // ��
const static int SPRING_BEGINS       = 21;   // ����
const static int THE_RAINS           = 22;   // ��ˮ
const static int INSECTS_AWAKEN      = 23;   // ����


#define COUNT_ITEM(x)   (sizeof(x) / sizeof(x[0]))

#endif //__CALENDAR_CONST_H__

