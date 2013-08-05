
// multiThreads.h
// Luocheng.li
// 2013-7-30


#ifndef MULTI_THREADS_H_
#define MULTI_THREADS_H_


class CBuffer
{
	
public:
	static	const int defLineSize = 64;
	int read(char *buf, int bufSize);
	int write(const char *buf, int bufSize);

	CBuffer(int bufSize = defLineSize);
	~CBuffer();

private:
	CBuffer(const CBuffer &cbuf);
	bool loop;
	inline bool canWrite(void){ return (!loop && pWrite >= pRead) || (loop && pWrite < pRead); }
	inline bool canRead(void){ return /*(pWrite != pRead);*/ (0 != *pRead);}
	static	const int defBufLine = 128;
	int   lineSize; 
	char  *pBuf;
	char  *pRead;
	char  *pWrite;
	char  *pEnd;
};


void multiError(const char *errStr);

#endif /* MULTI_THREADS_H_ */
