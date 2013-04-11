
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
	long randomVar = rand();
	randomVar = randomVar % base;
	return (int)randomVar;
}

};

char *getRandomString(void)
{
	static  char letters[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',

			'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

	string temp(letters) ;
	//cout << letters;

	vector<char> let;
	for (int i = 0; i < temp.size(); i ++)
	{
		let.push_back(letters[i]);
	}

//	random_device rd;
//	mt19937 g(rd());

	RandomFunc rf;

//	random_shuffle(let.begin(), let.end(), &rf);
	random_shuffle(let.begin(), let.end());
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


	getRandomString();

	srand(time(0))	;
	cout << "get random number:" ;
	for (int i = 0; i < 225;i++)
	{
		cout << getRandom(255) << "  ";
	}
	cout << endl;
	cout << "Random value on" << getRandom(255) << endl; 
	return 0;
}

