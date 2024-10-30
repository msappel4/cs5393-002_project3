#include "DSString.h"

// blank constructor
DSString::DSString()
{
    data = new char[1];
    data[0] = '\0';
    len = 0;
}

// constructor that converts a cstring
DSString::DSString(const char *str)
{
    //calculate the length of the input C-string
    len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    //allocate memory and copy the C-string
    data = new char[len + 1];
    for (size_t i = 0; i < len; i++)
    {
        data[i] = str[i];
    }
    data[len] = '\0';
}

//rule of three
//copy constructor
DSString::DSString(const DSString &copy)
{
    data = new char[copy.length() + 1];
    len = copy.length();
    for (int i = 0; i < copy.length(); i++)
    {
        data[i] = copy.data[i];
    }
    data[len] = '\0';
}

//destructor
DSString::~DSString()
{
    delete[] data;
}

//assignment operator
DSString &DSString::operator=(const DSString &newStr)
{
    delete[] data;
    len = newStr.length();
    data = new char[len + 1];
    for (size_t i = 0; i < len; i++)
    {
        *(data + i) = *(newStr.data + i);
    }
    data[len] = '\0'; 
    return *this;
}

//length of string
size_t DSString::length() const
{
    return len;
}

//character at given index
char &DSString::operator[](size_t index)
{
    if (index < length())
    {
        return data[index];
        throw std::out_of_range("Index out of bounds");
    }
}

//overload operator
DSString DSString::operator+(const DSString &adding) const
{
    DSString fullSize;
    fullSize.len = len + adding.len + 1;
    int x = 0;
    for (size_t i = 0; i < len; i++)
    {
        fullSize.data[i] = data[i];
    }
    for (size_t i = len; i < ((len - 0) + adding.len); i++)
    {
        fullSize[i] = adding.data[x];
        x++;
    }
    fullSize.data[fullSize.len] = '\0';
    return fullSize;
}

//compare and order strings pt1
bool DSString::operator==(const DSString &checkEqual) const
{
    if(checkEqual.len != this->len) {
        return false;
    }
    bool a = true;
    char *newCh = checkEqual.c_str();
    for (size_t i = 0; i < len + 1; i++)
    {
        if ((data[i]) != newCh[i])
            a = false;
    }
    return a;
}

//compare and order strings pt2
bool DSString::operator<(const DSString &checkLess) const
{
    size_t minLen = std::min(len, checkLess.len); 
    for (size_t i = 0; i < minLen; i++)
    {
        if (data[i] < checkLess.data[i])
            return true;
        else if (data[i] > checkLess.data[i])
            return false;
    }
    return len < checkLess.len;
}

//returns new string object
//start (start index), numChars (count of characters to copy)
DSString DSString::substring(size_t start, size_t numChars) const
{
    DSString substr;
    substr.len = numChars;
    delete[] substr.data;
    substr.data = new char[numChars + 1];
    for (size_t i = start; i < start + numChars; i++)
    {
        substr.data[i - start] = data[i];
    }
    substr.data[numChars] = '\0';
    return substr;
}

//converts to lowercase
DSString DSString::toLower() const
{
    int lowAsciiVal = 0;
    for (size_t i = 0; i < len; i++)
    {
        if ((data[i] < 91) && (data[i] > 64))
        {
            lowAsciiVal = toascii(data[i]) + 32;
            data[i] = char(lowAsciiVal);
        }
    }
    return data;
} //used ASCII table

//returns pointer to data
char *DSString::c_str() const
{

    return data;
}

//ostream returns
std::ostream &operator<<(std::ostream &output, const DSString &str)
{
    return output << str.data;
}

//tokenizer function
std::vector<DSString> DSString::tokenizeDSString()
{
    std::vector<DSString> words;
    size_t counter = 0;
    DSString currentWord;
    for (size_t i = 0; i < length() + 1; ++i)
    {
        char currentChar = data[i];
        if (currentChar == ' ' || currentChar == ',' || currentChar == ';' || currentChar == '.' || currentChar == ':' || currentChar == '!' || currentChar == '?' || currentChar == '\0'
        && i!= counter)
        {
            currentWord = substring(counter, i - counter);
            words.push_back(currentWord);
            counter = i + 1;
        }
        else if (currentChar == ' ' || currentChar == ',' || currentChar == ';' || currentChar == '.' || currentChar == ':' || currentChar == '!' || currentChar == '?' || currentChar == '\0'
        && i!= counter){
            counter++;
        }
    }
    return words;
}
