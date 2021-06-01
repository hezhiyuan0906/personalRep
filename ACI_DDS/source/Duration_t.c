#include "../Include/GlobalDefine.h"

/*
* ������Duration_tֵ
*/
const int DURATION_INFINITE_SEC = 0x7fffffff;    // ������
const int DURATION_ZERO_SEC = 0x00000000;    // 0��
const unsigned int DURATION_INFINITE_NSEC = 0xffffffff;// ��������
const unsigned int DURATION_ZERO_NSEC = 0x00000000;    // 0����

// Э���õ���һЩDuration_t��Ĭ��ֵ
// ��Ч��ֵ
const Duration_t INVALID_DURATION = {-1, 0};

// HB�ӳ���Ӧʱ�䣨����ACKNACK����100ms
const Duration_t DEFALUT_HB_RESP_DELAY = {0, 100 * 1000 * 1000};

// HB���ƣ���ֹ������յ�HB, 0s
const Duration_t DEFALUT_HB_SUPPRESSION = {0, 100 * 1000 * 1000};

// д��HistoryCache������ӳ�ʱ��,100ms
const Duration_t DEFALUT_MAX_BLOCKING_TIME = {0, 100 * 1000 * 1000};

// ����HB������
const Duration_t DEFALUT_HB_PERIOD = {0, 1000 * 1000 * 1000};

// ACKNACK����Ӧ�ӳ�ʱ��,200ms
const Duration_t DEFALUT_NACK_RESP_DELAY = {0, 200 * 1000 * 1000};

// NACK���ƣ�SENT���Unacknowledged״̬(Э��������)��10ms
const Duration_t DEFALUT_NACK_SUPPRESSION = {0, 100 * 1000 * 1000};

// ����Participant����ʱ��
const Duration_t DEFALUT_UPDATE_PARTICIPANT = {30, 0};

// Participant����ʱ��,15s
const Duration_t DEFALUT_PARTICIPANT_LEASE = {100, 0};

// ParticipantReader������Participant�����Ϣ�ļ��
const Duration_t DEFALUT_CHECK_PARTICIPANT_STALE = {1, 0};

// Writerˢ����Ӧ��ʱ����
const Duration_t DEFALUT_REFRESH_UNACK = {0, 10 * 1000 * 1000};

// ʱ�䳣��
const Time_t TIME_ZERO = {0, 0};
const Time_t TIME_INVALID = {-1, 0xffffffff};
const Time_t TIME_INFINITE = {0x7fffffff, 0xffffffff};

/* TODO ���ӻ�ȡ��ǰʱ��ʵ�� */
Time_t GetNowTime()
{
    Time_t t = { 0, 0 };
    t.sec = (int)time(NULL);
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	t.nanosec = sys.wMilliseconds * 1000 * 1000;
    return t;
}

/* �Ӽ����� */
Duration_t Add_Duration(Duration_t left, Duration_t right)
{
    EX_UINT32 resNanosec = left.nanosec + right.nanosec;
    EX_INT32 resSec = left.sec + right.sec;
    if (resNanosec < right.nanosec)
    {
        ++resSec;
    }
    /* �Ƿ񳬹����� */
    if (resSec < left.sec)
    {
        return TIME_INFINITE;
    }
    Duration_t result = { resSec, resNanosec };
    return result;
}
Duration_t Sub_Duration(Duration_t left, Duration_t  right)
{
    
    EX_INT32 resSec = left.sec - right.sec;
    EX_UINT32 resNanosec;
    if (left.nanosec >= right.nanosec)
    {
        resNanosec = left.nanosec - right.nanosec;

    }
    else
    {
        resNanosec = 1000000000 - right.nanosec + left.nanosec;
        --resSec;
    }

    /* TODO �ж��Ƿ񳬹����� */

    Duration_t result = { resSec, resNanosec };
    return result;
}

BOOL Compare_Duration(Duration_t left, Duration_t  right)
{
	if (left.sec > right.sec)
	{
		return TRUE;
	}
	else if (left.sec < right.sec)
	{
		return FALSE;
	}
	else
	{
		if (left.nanosec > right.nanosec)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

BOOL Duration_IsEqual(Duration_t left, Duration_t  right)
{
    if (left.sec == right.sec && left.nanosec == right.nanosec)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}