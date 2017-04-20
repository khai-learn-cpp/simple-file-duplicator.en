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
    "Hoạt động:\n"
    "1. Đọc nội dung file, lưu vào bộ nhớ đệm\n"
    "2. Tìm tên file\n"
    "3. Viết nội dung file vào tên mới\n"
    "4. Kết thúc\n"
  ;

  string inputfilename;
  cout << "Nhập tên file: ";
  getline(cin, inputfilename, '\n');

  string outputfilename = getoutputfilename(inputfilename);
  cout << "Đang viết vào file " << outputfilename << endl;
  ofstream(outputfilename) << getfilecontent(inputfilename);
  cout << "Đã viết vào file " << outputfilename << endl;
  return 0;
}
