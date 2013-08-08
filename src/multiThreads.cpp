
// multiThreads.cpp
// Luocheng.Li
// 2013-7-30

#include "multiThreads.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;


CBuffer::CBuffer(int bufSize)
{
/*	if(NULL != pBuf)
	{
		delete [] pBuf;
	}
*/

	int total = bufSize * defBufLine;
	pBuf = (char*)malloc(total*sizeof(char));	
	if(pBuf)
	{
		memset(pBuf, 0x00, total);
		lineSize = bufSize;
		pEnd = pBuf + total;
	}

	pRead = (char*)malloc(sizeof(char)*defBufLine);
	if(pRead)
	{ 
		memset(pRead, READ, sizeof(char)*defBufLine);
	}
	else
	{
		multiError("constructor failed, malloc fail!");		
	}

	pWrite = (char*)malloc(sizeof(char)*defBufLine);
	if(pWrite)
	{
		memset(pWrite, UNWRITE, sizeof(char)*defBufLine);
	}
	else
	{
		multiError("constructor failed, malloc fail!");		
	}
	readPos = writePos = 0;
}

CBuffer::~CBuffer()
{
	if(NULL != pBuf)	
	{
		free(pBuf);
		pBuf = pRead = pWrite = NULL;
	}

}

int CBuffer::read(char *buf, int bufSize)
{
	int retVal = 0;
	if(canRead())
	{
		int len = bufSize > lineSize? lineSize : bufSize;
		memcpy(buf, pBuf + readPos, len);
		buf[len-1] = 0;

		setRead(readPos);
		//cout << "read pointer " << hex << (int)pRead << endl;
		// sign it is read

		readPos = (readPos + lineSize) % lineSize;
		retVal = len;
	}
	return retVal;
}

int CBuffer::write(const char *buf, int bufSize)
{
	int retVal = 0;
	if(canWrite())
	{
		int len = bufSize > lineSize? lineSize : bufSize;
		memcpy(pBuf + writePos, buf, len);
		setWrite(writePos);
		writePos = (writePos + lineSize) % lineSize;

		//cout << "write pointer " << hex << (int)pWrite << endl;
		retVal = len;
		
	}

	return retVal;
}


static void *readThread(void *arg);
static void *writeThread(void *arg);

int main()
{
	int s;
	void *resRead, *resWrite;
	pthread_t	readId, writeId;

	CBuffer cbuf;

	// read thread
	s = pthread_create(&readId, NULL, &readThread, (void*)&cbuf);
	if(0 != s)
	{
		cout << ("create thread fail!") << endl;
	}

	// write thread
	s = pthread_create(&writeId, NULL, &writeThread, (void*)&cbuf);
	if(0 != s)
	{
		cout << ("create thread fail!") << endl;
	}

	s = pthread_join(readId, &resRead);
	if(0 != s)
	{
			cout << "pthread——join fail!" << endl;
	}

	s = pthread_join(writeId, &resWrite);
	if(0 != s)
	{
			cout << "pthread——join fail!" << endl;
	}

	return 0;
}



static void *readThread(void *arg)
{
	CBuffer *pcb = (CBuffer*) arg;

	if(NULL != arg)
	{
		cout << "create read thread now..."	<< endl;
	}	

	const int bufLen = CBuffer::defLineSize;
//	const int bufLen = 64;
	char	buf[bufLen] = {0}; 
	while(1)	
	{
		int readBytes = pcb->read(buf, bufLen);
		if(readBytes > 0)
		{
			buf[bufLen-1]	= 0;
			cout << "read thread:" <<  buf << endl;
		}
		else
		{
			multiError("read fail " );
		}
		bzero(buf, bufLen);
		//sleep(1);
	}


	cout << "read thread exit" << endl;
	return 0;
}


static void *writeThread(void *arg)
{
	CBuffer *pcb = (CBuffer*) arg;

	if(NULL != arg)
	{
		cout << "create read thread now..."	<< endl;
	}	

	const int bufLen = CBuffer::defLineSize;

	//const int bufLen = 64;
	char	buf[bufLen] = {0}; 
	int		cnt = 0;
	while(1)	
	{
		bzero(buf, bufLen);

		time_t timer;
		timer = time(NULL);	
		snprintf(buf, bufLen, "time is %s - %d.\n", asctime(localtime(&timer)) , cnt++);	

		int writeBytes = pcb->write(buf, bufLen);
		if(writeBytes <= 0)
		{
			multiError("write thread fail!" );
		}
		else
		{
			cout << "write  threads:  " << buf << endl; 
		}
		//sleep(1);
	}

	cout << "write thread exit" << endl;

	return 0;

}

void multiError(const char *errStr)
{
	cout << errStr << endl; 
}

