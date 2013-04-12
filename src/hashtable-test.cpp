
#include <hash_set>
#include <random>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace __gnu_cxx;


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
	cout << endl;
	copy(let.begin(),let.end(), ostream_iterator<char>(cout, ""));		
	cout << endl;

	return  NULL;
	//return  letters;

}

int main()
{
	hash_set<int> hs;
	hs.insert(12);
	hs.insert(13);
	hs.insert(92);
	hs.insert(52);
	hs.insert(32);
	hs.insert(82);
	for(hash_set<int>::iterator iter = hs.begin(); iter != hs.end(); ++iter )
	{
		cout << *iter << endl;
	}


	srand(time(0))	;
	for (int j = 0; j < 15; j++)
	{
		getRandomString();
	}

	cout << "get random number:" ;
	for (int i = 0; i < 225;i++)
	{
		cout << getRandom(255) << "  ";
	}
	cout << endl;
	cout << "Random value on" << getRandom(255) << endl; 
	return 0;
}

