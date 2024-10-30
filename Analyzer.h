
#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H

# include <map>
# include "DSString.h"
#include <map>
using namespace std;

class SentimentAnalyzer {
public:
    //to train
    void train(char*);
    //to test
    void test(char*, char*, char*, char*);

private:
    //initialize
   map<DSString, int> dictionary;
   double percentage;
   double accuracyCounter;
   double tweetsClassified; 
};
#endif
