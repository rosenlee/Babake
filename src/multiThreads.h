
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
	int readPos, writePos;
	static const char READ = 1;
	static const char UNREAD = 0;
	static const char WRITE = 1;
	static const char UNWRITE = 0;
	inline bool canRead(void){ return (WRITE == *(pWrite + readPos/lineSize));}
	inline bool canWrite(void){ return (READ == *(pRead + writePos/lineSize));}
	inline void setRead(int pos) { if(pRead){*(pRead + pos/lineSize) = READ;}}
	inline void setWrite(int pos) { if(pWrite){*(pWrite + pos/lineSize) = WRITE;}}
	static	const int defBufLine = 128;
	int   lineSize; 
	char  *pBuf;  	// data buffer
	char  *pRead; 	// record read pos state 
	char  *pWrite; 	// record write pos state
	char  *pEnd;
};


void multiError(const char *errStr);

#endif /* MULTI_THREADS_H_ */
