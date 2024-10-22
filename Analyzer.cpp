#include "Analyzer.h"

Analyzer::Analyzer() {}

void Analyzer::trainfunction(char* fileName) {
    auto start = chrono::high_resolution_clock::now();
    readwordstostop();

    bool isPositive;
    ifstream inFS(fileName);
    char line[1000];

    // Read training file
    if (!inFS.is_open()) {
        cerr << "Error reading input file\n";
        return;
    }

    inFS.getline(line, 1000); // Ignore header text in data

    while (inFS.getline(line, 1000, ',')) {
        // Store sentiments in isPositive
        DSString sentiment(line);
        isPositive = (sentiment[0] == '1'); // Adjusted to use the correct condition

        // Read tweets
        for (size_t i = 0; i < 4; i++)
            inFS.getline(line, 1000, ',');
        inFS.getline(line, 1000);
        DSString tweet(line);

        // Clean and tokenize tweet
        tweet = tweet.toLower();
        tweet = tweet.removesymbol(); // Assuming you have this method in DSString
        vector<DSString> tempWords = tokenize(tweet);

        // Increment or decrement word's sentiment value based on tweet's sentiment value
        for (size_t i = 0; i < tempWords.size(); i++) {
            tempWords.at(i) = tempWords.at(i).stem();
            if (findwords(tempWords.at(i), wordstostop) == -1) {
                if (findwords(tempWords.at(i), specificwords) == -1) {
                    specificwords.push_back(tempWords.at(i));
                    sentiment.push_back(isPositive ? 1 : -1);
                } else {
                    int index = findwords(tempWords.at(i), specificwords);
                    sentiment.at(index) += (isPositive ? 1 : -1);
                }
            }
        }
    }
    inFS.close();
    auto end = chrono::high_resolution_clock::now();
    cout << "Training execution time: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds\n";
}

void Analyzer::predictfunction(char* fileName) {
    auto start = chrono::high_resolution_clock::now();
    ifstream inFS(fileName);
    char line[1000];

    if (!inFS.is_open()) {
        cerr << "Error reading input file\n";
        return;
    }

    inFS.getline(line, 1000); // Ignore header text in data
    while (inFS.getline(line, 1000, ',')) {
        // Store testing IDs in vector
        DSString id(line);
        testingID.push_back(id);

        // Store tweet in DSString
        for (size_t i = 0; i < 3; i++)
            inFS.getline(line, 1000, ',');
        inFS.getline(line, 1000);
        DSString tweet(line);

        // Clean and tokenize tweet
        tweet = tweet.toLower();
        tweet = tweet.removesymbol();
        vector<DSString> tempWords = tokenize(tweet);

        // Predict sentiment values of tweet based on sentiments of words in training data
        int prediction = 0;
        for (size_t i = 0; i < tempWords.size(); i++) {
            tempWords.at(i) = tempWords.at(i).stem();
            int index = findwords(tempWords.at(i), specificwords);
            if (index != -1) {
                prediction += sentiments.at(index);
            }
        }

        // Add prediction to vector based on total prediction number
        predictions.push_back(prediction >= 0 ? "4" : "0");
    }

    inFS.close();
    auto end = chrono::high_resolution_clock::now();
    cout << "Classification execution time: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds\n";
}

void Analyzer::predictcheck(char* testingSentimentFile, char* resultsFile, char* accuracyFile) {
    vector<DSString> sentimentsAnswers;
    double correctCount = 0; // Initialize correctCount
    size_t i = 0;

    char line[1000];
    ifstream inFS(testingSentimentFile);
    ofstream resultsFile(resultsFile);

    if (!inFS.is_open()) {
        cerr << "Error reading input file\n";
        return;
    }

    inFS.getline(line, 1000); // Ignore header text in data
    while (inFS.getline(line, 1000, ',')) {
        // Assign first char of each line to sentimentsAnswers
        DSString sentiment(line);
        sentimentsAnswers.push_back(sentiment);

        // Compare predictions and sentimentAnswers
        if (sentimentsAnswers.at(i) == predictions.at(i)) {
            correctCount++;
        }

        // Write to results file
        resultsFile << predictions.at(i) << "," << testingID.at(i) << "\n";

        inFS.getline(line, 1000);
        i++;
    }

    inFS.close();
    resultsFile.close();

    double accuracy = correctCount / sentimentsAnswers.size();

    // Write to accuracyFile
    ofstream accuracyFileStream(accuracyFile);
    accuracyFileStream << fixed << setprecision(3) << accuracy << "\n";
    for (size_t i = 0; i < predictions.size(); i++) {
        if (!(predictions.at(i) == sentimentsAnswers.at(i))) {
            accuracyFileStream << predictions.at(i) << "," << sentimentsAnswers.at(i) << "," << testingID.at(i) << "\n";
        }
    }
    accuracyFileStream.close();
}

vector<DSString> Analyzer::tokenize(DSString& tweet) {
    size_t start = 0;
    vector<DSString> words;
    DSString token;

    for (size_t i = 0; i < tweet.length(); i++) {
        if (tweet[i] == ' ' || i == tweet.length() - 1) {
            if (i == tweet.length() - 1) { // Include last character if it's not a space
                i++;
            }
            token = tweet.substring(start, i - start);
            start = i + 1;
            words.push_back(token);
        }
    }

    return words;
}

int Analyzer::findwords(DSString word, vector<DSString> vector) {
    for (size_t i = 0; i < vector.size(); i++) {
        if (word == vector.at(i))
            return i;
    }
    return -1;
}

void Analyzer::readwordstostop() {
    ifstream inFS("../data/stopwords.txt");
    char line[200];

    if (!inFS.is_open()) {
        cerr << "Error reading input file\n";
        return;
    }

    while (inFS.getline(line, 200)) {
        DSString temp(line);
        wordstostop.push_back(temp);
    }

    inFS.close();
}
