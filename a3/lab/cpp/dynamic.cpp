/*
 * dynamic.cpp
 * description: dynamic memory allocation and deallocation using new and delete
 * compile: g++ -std=c++0x dynamic.cpp -o dynamic.exe
 * run: dynamic.exe 
 */
 
#include <iostream>
#include <new>
using namespace std;

int main () {
  int *p;
  
  p = new int(); // dynamic memory allocation using new, similar to C's malloc
  *p = 1;
  cout << *p << endl;
  delete p;     // delete memory space allocated by new, use free() for malloc()
  
  int i, n=2;  
  p = new int[n];    
  for (i=0; i<n; i++) {
	 p[i] = i;
  }
  for (i=0; i<n; i++) {
	 cout << p[i] << " ";
  }
  delete[] p;  

  return 0;
}
