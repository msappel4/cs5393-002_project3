/*
#include <iostream>


int main(int argc, char** argv)
{  
    std::cout << "I will be a sentiment analyzer!" << std::endl;

    return 0;
}
*/

// Megan 
#include <iostream>
#include "Analyzer.h"

using namespace std;

int main(int argc, char** files) {  
    if (argc != 6) {
        cerr << "Error: input 5 arguments\n";
        return 0;
    }

    Analyzer analyzer;

    analyzer.trainfunction(files[1]); // "train_dataset_20k.csv"
    analyzer.predictfunction(files[2]); // "test_dataset_10k.csv"
    analyzer.predictcheck(files[3], files[4], files[5]); // "test_dataset_sentiment_10k.csv", "result.csv", "accuracy.txt"

    return 0;
}
