/*
 * fileio.cpp
 * compile: g++ -std=c++0x fileio.cpp -o fileio.exe
 * run: fileio.exe
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	
  // writing text to file	
  ofstream myfile;
  myfile.open ("example.txt");
  //or just:  ofstream myfile("example.txt");
  if (myfile.is_open())
  {
    myfile << "This is a line.\n";
    myfile << "This is another line.\n";
    myfile.close();
  }
  else cout << "Unable to open file";
  
  // reading text file
  string line;
  ifstream myfile1("example.txt");
  if (myfile1.is_open())
  {
    while ( getline(myfile1,line) )
    {
      cout << line << '\n';
    }
    myfile1.close();
  }
  else cout << "Unable to open file"; 

  // writing binary file 
  char str[] = "this is test";
  ofstream file("example.bin", ios::out|ios::binary);
  if (file.is_open())
  {
    file.write(str, sizeof(str));
    file.close();
  }
  else cout << "Unable to open file" << endl;
  
  
  // reading binary file 
  streampos size;
  char *memblock;
  ifstream file1 ("example.bin", ios::in|ios::binary|ios::ate);  // open file and move to the end of the ifstream
  if (file1.is_open())
  {
    size = file1.tellg();  // returns the current get position of ifstream
    memblock = new char[size];
    file1.seekg (0, ios::beg);    // move to the beginning position of ifstream
    file1.read (memblock, size);  // read bytes from file stream to memory block
    file1.close();	
	cout << memblock << endl;   
    delete[] memblock;
  }
  else cout << "Unable to open file";
  
  // move around file stream buffer 
  streampos begin,end;
  ifstream file2 ("example.bin", ios::binary); // open at the beginning
  begin = file2.tellg();                       // begin is 0
  cout << "size is: " << begin << " bytes.\n";
  file2.seekg(0, ios::end);                    // move the end
  end = file2.tellg();                         // end is the size of the file    
  file2.close();
  cout << "size is: " << (end-begin) << " bytes.\n";
  
  return 0;
}

