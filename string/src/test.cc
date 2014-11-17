#include<Jing/string>
#include<iostream>

using std::cout;
using std::endl;
using namespace Jing;

int main(int argc, char** argv){
  string splitter("one two three");
  string foo("test");
  string bar(foo);

  cout << "Split string" << endl;
  cout << splitter << endl;
  smart_ptr<List<string>> tmp = splitter.split(' ');
  cout << "list size " << tmp->size() << endl;
  cout << "charat1" << endl;
  cout << foo.charAt(1) << endl;
  cout << "<<foo<<" << endl;
  cout << foo << endl;
  cout << "charat1" << endl;
  cout << foo.charAt(1) << endl;
  cout << "length" << endl;
  cout << foo.length() << endl;

  cout << "charat" << endl;
  cout << bar.charAt(1) << endl;
  cout << "<<bar<<" << endl;
  cout << bar << endl;
  cout << "length" << endl;
  cout << bar.length() << endl;

  return 0;
}
