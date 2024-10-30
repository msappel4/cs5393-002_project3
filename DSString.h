
#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <vector>

class DSString
{

private:
    //initialize
    char *data; 
    size_t len;

public:

    //blank constructor
    DSString(); 
    //constructor that converts cstring
    DSString(const char *);


    //rule of three
    //copy constructor
    DSString(const DSString &);
    //destructor
    ~DSString();
    //assignment operator
    DSString &operator=(const DSString &);

    //length of string
    size_t length() const;

    //character at given index
    char &operator[](size_t);

    //overload operator
    DSString operator+(const DSString &) const;

    //compare and order strings
    bool operator==(const DSString &) const; //pt1
    bool operator<(const DSString &) const; //pt2

    //returns new string object
    //start (start index), numChars (count of characters to copy)
    DSString substring(size_t start, size_t numChars) const;

    //converts to lowercase
    DSString toLower() const; // look at the ASCII table for this!

    //returns pointer to data
    char *c_str() const;

    //ostream returns
    //friend because operates on stream and not object
    friend std::ostream &operator<<(std::ostream &, const DSString &);

    //tokenizer function 
    std::vector<DSString> tokenizeDSString();

};

#endif
