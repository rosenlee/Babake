
#include <hash_set>
#include <random>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <map>

using namespace std;
using namespace __gnu_cxx;

#define MAX_STRING_LEN 52
#define	MAX_FILE_DESCRIPTION	200 
#define	MAX_FILE_PATH	256	
#define	DISTRIBUTION_PATH 	"./distribution/"
#define SOURCE_FILE_PATH	"./random.txt"

void testRandom(void);
int hashFunc(char *str, int len);
char *createFileName(const char *str, int strLen, int num);

bool distribution(FILE *sourceFile);
FILE *getFileDescriptionFromHashTable( map<int, FILE*> *pHashFileMap , int key);

int getRandom(int base)
{
	long randomVar = rand();
	randomVar = randomVar % base;
	return (int)randomVar;
}


class RandomFunc
{
public:
	int operator()(int base)
{
	static 	int rand1 = time(0);
//	cout << rand1<< endl;
	srand(rand1);
	//srand(time(0))	;
	long randomVar = rand();
	rand1 = randomVar+base;
	
	// generate second random number
	srand(rand1);
	long 	randomVar2 = rand();
	rand1 = randomVar2+base;
	randomVar = (randomVar2 % randomVar + randomVar % randomVar2) % base;
	return (int)randomVar;
}

};

template<class RandomIt, class RandomFunc>
void random_shuffle_local(RandomIt first, RandomIt last, RandomFunc &&r)
{
	typename std::iterator_traits<RandomIt>	::difference_type i,n;
	n = last - first;

	for (i = n - 1; i > 0; --i)
	{
		swap(first[i],first[(*r)(i+1)]);	
	}
}



static  char letters[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',

			'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

static bool init = false;
static vector<char> let;

char *getRandomString(void)
{
	if (false == init)
	{
		string temp(letters) ;
		//cout << letters;

		for (int i = 0; i < temp.size(); i ++)
		{
			let.push_back(letters[i]);
		}
		init = true;

	}
//	random_device rd;
//	mt19937 g(rd());

	RandomFunc rf;

	random_shuffle_local(let.begin(), let.end(), &rf);
//	random_shuffle(let.begin(), let.end());
//	cout << endl;
//	copy(let.begin(),let.end(), ostream_iterator<char>(cout, ""));		
//	cout << endl;

	static char retString[MAX_STRING_LEN] = {};
	for(int i = 0; i < MAX_STRING_LEN;i++)
	{
		retString[i] = let[rf(i+1)];	
		//retString[i] = letters[rf(i+1)];	
	}


	return  retString;
	//return  letters;

}

int main(int argc, char** argv)
{
	int loop = 100;

	if (argc > 1)
	{
		loop = (int)atoi(argv[1]);
	}

	hash_set<int> hs;
	hs.insert(12);
	hs.insert(13);
	hs.insert(92);
	hs.insert(52);
	hs.insert(32);
	hs.insert(82);
	for(hash_set<int>::iterator iter = hs.begin(); iter != hs.end(); ++iter )
	{
	//	cout << *iter << endl;
		cout << createFileName("hash",strlen("hash"),*iter)<< endl;
	}


//	srand(time(0))	;
//	for (int j = 0; j < loop; j++)
//	{
//		cout << 	getRandomString() << endl; 
//	}

	FILE *pSource = fopen(SOURCE_FILE_PATH, "r");
	if(NULL != pSource)
	{
		distribution(pSource);	
	}
	return 0;

}

void testRandom(void)
{
	cout << "get random number:" ;
	for (int i = 0; i < 225;i++)
	{
		cout << getRandom(255) << "  ";
	}
	cout << endl;
	cout << "Random value on" << getRandom(255) << endl; 
}

int hashFunc(char *str, int len)
{
	int sum = -1;

	if (NULL != str && len > 0)
	{
		sum = 0; // reset  
		for (int i = 0; i < len; i++)
		{
			sum += str[i] + i;// add the sequence
		}
	}	

	return  sum % MAX_FILE_DESCRIPTION;	
}

char *createFileName(const char *str, int strLen, int num)
{
	static char name[MAX_FILE_PATH] = {};
	if (NULL != str && strLen > 0)
	{
		strcpy(name,DISTRIBUTION_PATH );
		strcat(name,str);
		sprintf(&name[strLen + strlen(DISTRIBUTION_PATH) ], "%d", num );
	}

	return name;
}


/*
*	the main process for distribution
*/
bool distribution(FILE *sourceFile)
{
	if (NULL == sourceFile)
	{
		return false;
	}

	int maxLine = 100; // for test max num
	size_t len = 0;
	ssize_t read = 0;
	char *line = NULL;
	map<int, FILE*> hashFile;
	while(maxLine >= 0 && (read = getline(&line, &len, sourceFile)) != -1)
	{
//		cout << "line num: " << maxLine << " size :" << read << ", " << line << " hash num: " << hashFunc(line, read)<<endl;
		FILE* f= getFileDescriptionFromHashTable(&hashFile, hashFunc(line, read));
		if (NULL != f)
		{
			fwrite(line, sizeof(char), read, f);	
		}
		/* the string will be discarded if there is no file for it*/
		/// reduce calc
		maxLine--;
	}

	hashFile.clear();
	return true;	
}

/*
* get a file description in map, if it does not exist, create one.
*/
FILE *getFileDescriptionFromHashTable( map<int, FILE*> *pHashFileMap , int key)
{
	FILE * ret = NULL;

	if (NULL != pHashFileMap)
	{
		map<int, FILE*> :: iterator iter = pHashFileMap->find(key);
		if (iter != pHashFileMap->end())	
		{
			// we found it
			ret = iter->second;
		}
		else
		{
			//can not find it
			if (pHashFileMap->size() < MAX_FILE_DESCRIPTION	)
			{
				ret = fopen(createFileName("hash",strlen("hash"), key), "a+");
				if (NULL == ret)
				{
					cout << "create file failed" << endl;
				}
			}
		}
	}

	return ret;
}
