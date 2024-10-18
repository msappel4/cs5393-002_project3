/*
#include <iostream>


int main(int argc, char** argv)
{  
    std::cout << "I will be a sentiment analyzer!" << std::endl;

    return 0;
}
*/

// Megan first try
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "DSString.h"

// Function to tokenize a string based on a delimiter
std::vector<DSString> tokenize(const DSString &str, char delimiter) {
    return str.split(delimiter);
}

// Function to perform sentiment analysis on a tweet (simple keyword-based for demonstration)
std::string analyzeSentiment(const DSString &tweet) {
    // Convert tweet to lowercase for keyword matching
    DSString lowerTweet = tweet.toLower();
    
    // Check for positive and negative keywords
    if (lowerTweet.c_str().find("happy") != std::string::npos || 
        lowerTweet.c_str().find("great") != std::string::npos || 
        lowerTweet.c_str().find("love") != std::string::npos) {
        return "Positive";
    }
    if (lowerTweet.c_str().find("sad") != std::string::npos || 
        lowerTweet.c_str().find("hate") != std::string::npos || 
        lowerTweet.c_str().find("angry") != std::string::npos) {
        return "Negative";
    }
    return "Neutral";
}

int main() {
    std::ifstream file("tweets.csv"); // Replace with your actual CSV file path
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    // Skip the header line
    std::getline(file, line);

    std::vector<DSString> tweets;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id, date, query, user, tweet;

        // Read CSV fields
        std::getline(ss, id, ',');
        std::getline(ss, date, ',');
        std::getline(ss, query, ',');
        std::getline(ss, user, ',');
        std::getline(ss, tweet, ',');
        
        // Create a DSString object for the tweet
        DSString dsTweet(tweet.c_str());
        tweets.push_back(dsTweet);
        
        // Analyze sentiment
        std::string sentiment = analyzeSentiment(dsTweet);
        std::cout << "User: " << user << "\nTweet: " << dsTweet << "\nSentiment: " << sentiment << "\n" << std::endl;
    }

    file.close();
    return 0;
}

