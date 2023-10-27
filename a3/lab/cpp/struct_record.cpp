/*
 * structure
 * compile: g++ -std=c++0x struct_record.cpp -o struct_record.exe
 * run: struct_record.exe
 * HBF
 */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct record {
  string name;
  float score;
};

void printRecord(record rc);  

int main ()
{
  record r1;
  r1.name = "John";
  r1.score = 80;
  cout << "Record data is:\n";
  printRecord(r1);
  
  cout << "Enter name: ";
  getline (cin, r1.name);
  cout << "Enter score: ";
  string str;  
  getline (cin, str);
  stringstream(str) >> r1.score;  // string to typed data 
  cout << "New record data is:\n";
  printRecord(r1);
  return 0;
}

void printRecord(record rc)
{
  cout << "Name:"<<rc.name << endl;
  cout << "Score:" << rc.score << endl;
}