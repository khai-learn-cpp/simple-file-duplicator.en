#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <unistd.h>

using namespace std;

string getfilecontent (string filename) {
  typedef istreambuf_iterator<char> icsi;
  ifstream file(filename);
  return string(icsi(file), icsi());
}

bool exists (string filename) {
  return access(filename.c_str(), F_OK) != -1;
}

string getoutputfilename (string inputfilename, int number = 0) {
  string outputfilename = inputfilename + to_string(number);
  return exists(outputfilename)
    ? getoutputfilename(inputfilename, number + 1)
    : outputfilename
  ;
}

int main () {
  cout << ""
    "Operating Principle:\n"
    "1. Read file to buffer\n"
    "2. Find a name\n"
    "3. Write content to a file with the new found name\n"
    "4. End\n"
  ;

  string inputfilename;
  cout << "Enter filename: ";
  getline(cin, inputfilename, '\n');

  string outputfilename = getoutputfilename(inputfilename);
  cout << "Writing " << outputfilename << endl;
  ofstream(outputfilename) << getfilecontent(inputfilename);
  cout << "Written " << outputfilename << endl;
  return 0;
}
