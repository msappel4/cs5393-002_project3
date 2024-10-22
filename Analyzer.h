#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include "DSString.h"

using namespace std;

class Analyzer {

private:
    vector<DSString> specificwords; // words from training data
    vector<int> sentiment; // sentiments from training data
    vector<DSString> testingID;
    vector<DSString> predictions; // sentiment predictions from testing data
    vector<DSString> wordstostop;
    double startanalyze; // start time of analyzing

public:
    Analyzer();
    void trainfunction(char* fileName);
    void predictfunction(char* fileName);
    void predictcheck(char* testingSentimentFile, char* resultsFile, char* accuracyFile);
    vector<DSString> tokenize(DSString& tweet);
    int findwords(DSString word, vector<DSString> vector);
    void readwordstostop();
};

#endif
