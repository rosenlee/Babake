 // addBinary.cpp
 // Rosen
 // 2013-7-4
 // http://leetcode.com/onlinejudge - add Binary

 string addBinary(string a, string b) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string sum;
        int ia = 0, ib = 0;
        
        for (int index = 0; index < a.size() && index < sizeof(int) * 8; index++)
        {
            ia = ia << 1;
            ia = ia + a[index] - '0';
        }
        
        for (int index = 0; index < b.size() && index < sizeof(int) * 8; index++)
        {
            ib = ib << 1;
            ib = ib + b[index] - '0';
        }
        
        int s = ia + ib;
        bool end = false;
        for(int index = 0; index < sizeof(int)*8 && !end; index++)
        {
            if(!(s & 0xffff)) break;  
             
            char newValue = (s & 0x0001) + 0x30;
            sum.insert(0, 1, newValue);         
                 
            s = s >> 1;
        }
        
        if(sum.empty())sum = "0";
        
        return sum;  
    }