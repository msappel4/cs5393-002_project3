
#include <iostream>
#include <vector>
#include <algorithm>

#include "DSString.h"

int main()
{  
    DSString myString = "Hello, World!";
    std::cout << myString << "\n";

    // this uses the one argument constructor in DSString and then the inherited operator=
    myString = "Good bye!";
    std::cout << myString << "\n";

 std::cout << "substr: " << myString.substring(5, 3) << "\n";

    DSString a = "test";
   DSString b = a;

    std::cout << std::boolalpha;
    std::cout << (a == b) << "\n";
  
/////////////////test
DSString tester = "this is a test with a string of words!";
 std::vector<DSString> words = tester.tokenizeDSString();

for(int i = 0; i < words.size(); i++){
 std:: cout << words.at(i) << "\n";
}





////////end test 

    // use initialization list
    std::vector<DSString> strings = {
        DSString("bbb"),
        DSString("aaa"),
        DSString("ddd"),
        DSString("eee"),
        DSString("ccc")};

    // find strings
    for (const auto &s : strings)
        std::cout
            << s << "\n";

     /*
       test to see if the + operator works
       a = "hello";
       b = "there";
       std:: cout << "hi \n" ;
       std::cout << a << " \n"; 
       std::cout << b << " \n"; 
       std::cout << (a + b) << " \n"; 
       std :: cout << "hi";
     */

    std::cout << "found ddd: " << (std::find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << "\n";
    std::cout << "found zzz: " << (std::find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << "\n";

    // sorting using the STL
    std::sort(strings.begin(), strings.end());

    for (const auto &s : strings)
        std::cout
            << s << "\n";

    // now we can do more efficient search using STL binary search
    std::cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << "\n";
    std::cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << "\n";
   



   /////////// put the table in token highkey confused 


    return 0; 
}
