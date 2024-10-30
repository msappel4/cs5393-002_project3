
#include "Analyzer.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "DSString.h"
#include <map>
#include <iomanip>

//to train
void SentimentAnalyzer::train(char* argv) {
    //read file
    std::ifstream file(argv);
    if (!file.good())
    {
        throw std::invalid_argument("file could not be opened");
    }
    //new buffer
    char* buffer = new char[1000];
    size_t counter = 0;
    file.ignore(1000,'\n');
    while (file.getline(buffer, 1000, ',')) {
    //stores the sentiment value
    DSString sentiment(buffer);
    //ignore lines
    file.ignore(1000,',');
    file.ignore(1000,',');
    file.ignore(1000,',');
    file.ignore(1000,',');
    //get tweet 
    file.getline(buffer, 10000, '\n');
    DSString tweetDSString(buffer);
    //tokenize tweet
    vector<DSString> words = tweetDSString.tokenizeDSString();
    //add map
    //toLower for no duplicates
    //determines sentiment
    //updates key value
    for (DSString& curTweetWord : words) {
      curTweetWord.toLower(); 
         if (sentiment == "4"){
        dictionary[curTweetWord]++;

     }
     else if(sentiment == "0"){
        dictionary[curTweetWord]--;
     }
    }
   }
    cout << counter << endl;
   delete[]  buffer;
}

//to test
void SentimentAnalyzer::test(char* argv, char* argv2, char* argv3, char* argv4) {
//initialize
vector<DSString> forOutput;
vector<DSString> forOutput2;
vector<DSString> forOutput3;
    std::ofstream outFile;
    std::ofstream outFile2;
    
    //open output files
    outFile.open(argv3);
    outFile2.open(argv4);
    //check if open
    if (!outFile) {
        throw std::invalid_argument("file could not be opened");
        std:: cout << "NO";
    }
    //open the first file
    std::ifstream file(argv);
    if (!file.good()) {
        throw std::invalid_argument("file could not be opened");
    }
    //buffer
    char buffer[10000];  
    double counter = 0;
    int idVectorCounter = 0;
    vector<DSString> guessedSentiments;
    vector<DSString> ids;
    //ignore line
    file.ignore(1000, '\n');
  
    while (file.getline(buffer, 1000, ',')) {
        //read it
        DSString idValue(buffer);
        ids.push_back(idValue);
        //ignore lines
        file.ignore(1000, ','); 
        file.ignore(1000, ','); 
        file.ignore(1000, ','); 
        //read tweet
        file.getline(buffer, 1000, '\n'); 
        DSString tweetDSString(buffer);
        //tokenize tweet
        vector<DSString> words = tweetDSString.tokenizeDSString();
            for (size_t i = 0; i < words.size(); i++) {
             DSString lowerWord = (words.at(i).toLower());
             auto indWord = dictionary.find(lowerWord);
            //adds to dictionary
            //sorts word
            if (indWord != dictionary.end()) {
                if (indWord->second >= 0) {
                    counter++;
                } else if (indWord->second < 0) {
                    counter --;
                }
            }
        }
        //tweet positive 4, else negative 0
        if (counter > 0) {
            guessedSentiments.push_back("4");
        } else {
            guessedSentiments.push_back("0");
        }
        counter = 0;
        idVectorCounter++;
    }

    //open the second file
    std::ifstream file2(argv2);
    if (!file2.good()) {
        throw std::invalid_argument("file could not be opened");
    }
    //buffer
    char buffer2[1000];
    accuracyCounter = 0;
    tweetsClassified = 0;
    //ignore line
    file2.ignore(1000, '\n');
    //while other lines get the sentiment 
    while (file2.getline(buffer2, 1000, ',')) {
    DSString tempTrueSentiment(buffer2);  
    //get id
    file2.getline(buffer2, 1000, '\n');  
    DSString tempId(buffer2);
        //compare ids
        for (size_t i = 0; i < ids.size(); i++) {
            if (ids.at(i) == tempId) {
                tweetsClassified++;
                //if correct, increment counter
                if (guessedSentiments.at(i) == tempTrueSentiment) {
                    accuracyCounter++;
                    outFile << guessedSentiments.at(i) << ","  << ids.at(i) << '\n';
                }
                //output a file with sentiments, correct id
                else{
                    outFile << guessedSentiments.at(i) << ","  << ids.at(i) << '\n';
                    //vectors
                    DSString tempA = guessedSentiments.at(i);
                    DSString tempB = tempTrueSentiment;
                    DSString tempC = ids.at(i);
                    //push to vector
                    forOutput.push_back(tempA);
                    forOutput2.push_back(tempB);
                    forOutput3.push_back(tempC);
                }
            }
        } 
     }

    //cout
    std::cout << "accuracy level: " << accuracyCounter << endl;
    std::cout << "totalTweetsAssesed: " << tweetsClassified << endl;
    percentage = (accuracyCounter)/tweetsClassified;
    std::cout << std::fixed << std::setprecision(3) << "percent correct: " << percentage <<"%" << endl;
    outFile2 << std::fixed << std::setprecision(3) <<percentage << "\n";
      //print to files
      for (size_t i = 0; i < forOutput.size(); i++){
       outFile2 << forOutput.at(i) << "," << forOutput2.at(i) << "," << forOutput3.at(i) << '\n';
       }
    //close files
    outFile.close();
    outFile2.close();
}
