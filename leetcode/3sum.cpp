#include <iostream>
#include <vector>
 #include <cstdlib>
 #include <algorithm>

using namespace std;

int main()
{

      vector<vector<int>> triplets;
        vector<int> num{-1,0,1,2,-1,-4};
        vector<int> oneTriplet {0,0,0};
		sort(num.begin(), num.end());
        int size = num.size();
        for(int fixIndex = 0; fixIndex < size; fixIndex++)
        {
            int leftIndex = fixIndex + 1; // from left move to right
            int rightIndex = size -1;  // from right move to left
            
            int fixValue = num[fixIndex]; // set one of three num is specific value
            
            while (leftIndex < rightIndex)
            {
                if(num[leftIndex] + num[rightIndex] + fixValue > 0)
                {
                    rightIndex--;
                }
                else if(num[leftIndex] + num[rightIndex] + fixValue < 0)
                {
                    leftIndex++;
                }
                else
                {
                    // a+b+c = 0
                    oneTriplet[0] = fixValue;
                    oneTriplet[1] = num[leftIndex];
                    oneTriplet[2] = num[rightIndex];
				
					bool isDuplicated = false;
				   for(vector<vector<int>>::iterator iter = triplets.begin(); iter != triplets.end(); iter++)
					{
						// cout << (*iter)[0] << " "  <<	(*iter)[1] << " " << (*iter)[2] << endl;
						 isDuplicated = isDuplicated || ((oneTriplet[0] == (*iter)[0]) 
											 && (oneTriplet[1] == (*iter)[1])
											 && (oneTriplet[2] == (*iter)[2]));
						if(isDuplicated) break;
						
					}
					 if(!isDuplicated)
					 {
						  triplets.push_back(oneTriplet);
						  cout << oneTriplet[0] << " "  <<	oneTriplet[1] << " " << oneTriplet[2] << endl;						  
					 }
										
                    leftIndex++;
                    rightIndex--;			
                }
            }// while                       
        }// for 
        
        return 0;		
}