
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <functional>

using namespace std;


class LotteryTicket
{
public:

	#define LT_RED_NUM (6)
	#define LT_RED_TOTAL_NUM (33)
	#define LT_BLUE_NUM (1)
	#define LT_BLUE_TOTAL_NUM (16)
	
public:

	LotteryTicket(const char *filename);
	LotteryTicket();
	~LotteryTicket();
	bool Init(const char *filename);
	
	int GetLeastTimeOfNumber(int thisNum);
	int GetLMostTimeOfNumber(int thisNum);
	
	// duration is the history interval
	void DisplayLayoutInHistory(int duration);
	void Dump(void);
	void SetOutput(const char *filename);
	
	
private:
	int CompareLong(const void* a, const void*b);
	bool Parse(void);
private:

	FILE *m_fSave;
	FILE *fp;
	vector< vector<long> >  m_srcData; 
	long m_redNum[LT_RED_TOTAL_NUM];
	long m_blueNum[LT_BLUE_TOTAL_NUM];
	
};

LotteryTicket::LotteryTicket(const char *filename)
{
	fp = NULL;
	m_fSave = stdout;
	Init(filename);
}

LotteryTicket::LotteryTicket()
{
	fp = NULL;
	m_fSave = stdout;
}

LotteryTicket::~LotteryTicket()
{
	if(fp)
	{
		fclose(fp);
		fp = NULL;
	}
	
	if(stdout != m_fSave)
	{
		fclose(m_fSave);
	}
	m_srcData.clear();
}

bool LotteryTicket::Init(const char *filename)
{
	FILE *p = fopen(filename, "r");
	if(NULL == p)
	{
		printf("filename:%s does not exist!!!\n", filename);
		return false;
	}
	fp = p;
	
	Parse();
	
	return true;
}

void LotteryTicket::SetOutput(const char *filename)
{
	FILE *fp = fopen(filename, "w");
	if(NULL != fp)
	{
		m_fSave = fp;	
	}
	else
	{
		printf("We can NOT open file [%s] for save result !!!\n", filename);
	}
}

bool LotteryTicket::Parse(void)
{
	if(NULL == fp) return false;
	
	char buffer[1024];
	bzero(buffer, sizeof(buffer));
	
	while(NULL != fgets(buffer, sizeof(buffer), fp))
	{
		vector<long> line;	
		const char *p = buffer;
		char number[3];
		char *pNumber = number;
		bzero(pNumber, sizeof(number));
		while(NULL != p && 0 != *p)
		{				
			if(isdigit(*p))
			{
				*pNumber++ = *p;
			}
			else if(isblank(*p) && (pNumber != number))
			{
				line.push_back(atol(number));			
				pNumber = number;
				bzero(pNumber, sizeof(number));
				
			}
			else if(*p == '\r' || *p == '\n' )
			{
				if(!line.empty())
				{
					m_srcData.push_back(line);
					line.clear();
					
					pNumber = number;
					bzero(pNumber, sizeof(number));
				}
				
				
			}
			p++; // next 
			
		} // while (NULL != p)	
		bzero(buffer, sizeof(buffer));
	} // while fgets()
	
	return true;
}

int LotteryTicket::GetLeastTimeOfNumber(int thisNum)
{
	return 0;
}

int LotteryTicket::GetLMostTimeOfNumber(int thisNum)
{
	return 0;
}

int LotteryTicket::CompareLong(const void* a, const void*b)
{
	const long arg1 = *reinterpret_cast<const long*>(a);
	const long arg2 = *reinterpret_cast<const long*>(b);
	
	return (int)(arg1 - arg2);
}

// duration is the history interval
void LotteryTicket::DisplayLayoutInHistory(int duration)
{	
	vector< vector<long> >::iterator viter = m_srcData.begin();
	bzero(m_blueNum, sizeof(m_blueNum));
	bzero(m_redNum, sizeof(m_redNum));
	
	for(int d = 0; viter != m_srcData.end() && d < duration; viter++,d++)
	{
		int index = 0;
		vector<long>::iterator liter = (*viter).begin();
		for(; liter != (*viter).end(); liter++)
		{
			if(index++ == LT_RED_NUM)
			{
				m_blueNum[*liter-1]++;
			}
			else
			{
				m_redNum[*liter-1]++;
			}
		}		
	}
	
	printf("---------in duration %d \n red ball:\n", duration);
	for(int i = 0; i < sizeof(m_redNum)/sizeof(long);i++  )
	{
		printf("%d %d\n", i+1, m_redNum[i]);
	}
	printf("blue ball:\n");
	for(int i = 0; i < sizeof(m_blueNum)/sizeof(long);i++  )
	{
		printf("%d %d\n", i+1, m_blueNum[i]);
	}
	
	printf("sorting.... ball:\n");
	
	vector<long> vred(m_redNum, m_redNum+LT_RED_TOTAL_NUM);
	vector<long> vblue(m_blueNum, m_blueNum+LT_BLUE_TOTAL_NUM);
	
	sort(vred.begin(), vred.end());
	sort(vblue.begin(), vblue.end());
	
	vector<long>::iterator riter = vred.begin();
	for(int i = 1; riter != vred.end(); riter++, i++)
	{
		printf("%ld %ld\n", i, *riter);
	}
	printf("blue ball:\n");
	vector<long>::iterator biter = vblue.begin();
	for(int i = 1; biter != vblue.end(); biter++, i++)
	{
		printf("%ld %ld\n", i, *biter);
	}
}

void LotteryTicket::Dump(void)
{	
	vector< vector<long> >::iterator viter = m_srcData.begin();
	
	for(; viter != m_srcData.end(); viter++)
	{
		int index = 0;
		vector<long>::iterator liter = (*viter).begin();
		for(; liter != (*viter).end(); liter++)
		{
			if(index++ == LT_RED_NUM)
			{
				printf(" %c ", '|');
			}
			printf("%2ld ", *liter);
		}
		printf("\n");
	}
}

int main()
{

	LotteryTicket lt("caipiao.dat");
	
	lt.Dump();
	
	lt.DisplayLayoutInHistory(20);
	
	lt.DisplayLayoutInHistory(40);
	
	return 0;
}



