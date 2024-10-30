// Megan 
#include "DSString.h"
#include <cctype> // For tolower
#include <stdexcept> // For std::out_of_range
#include <vector>
#include "OleanderStemmingLibrary-english.h" // Include the stemming library

DSString::DSString()
{
    data = new char[1];
    data[0] = '\0';
    len = 0;
}

DSString::DSString(const char *cstr)
{
    len = strlen(cstr);
    data = new char[len + 1];
    strcpy(data, cstr);
}

DSString::DSString(const DSString &str)
{
    len = str.len;
    data = new char[len + 1];
    strcpy(data, str.data);
}

DSString::~DSString()
{
    delete[] data; // Memory cleanup
}

DSString &DSString::operator=(const DSString &str)
{
    if (this != &str)
    {
        delete[] data; // Free existing memory
        len = str.len;
        data = new char[len + 1];
        strcpy(data, str.data); // Copy string
    }
    return *this;
}

size_t DSString::length() const
{
    return len;
}

char &DSString::operator[](size_t index) const
{
    if (index < len)
        return data[index];
    throw std::out_of_range("Index out of range"); // Better error handling
}

DSString DSString::operator+(const DSString &str) const
{
    DSString result;
    result.len = len + str.len;
    result.data = new char[result.len + 1];
    strcpy(result.data, data); // Copy current string
    strcat(result.data, str.data); // Append new string
    return result;
}

bool DSString::operator==(const DSString &str) const
{
    return (len == str.len) && (strcmp(data, str.data) == 0); // Use strcmp for comparison
}

bool DSString::operator<(const DSString &str) const
{
    return strcmp(data, str.data) < 0; // Use strcmp for lexicographical comparison
}

DSString DSString::substring(size_t start, size_t numChars) const
{
    if (start >= len) return DSString(); // Check for valid start
    if (start + numChars > len) numChars = len - start; // Adjust if out of bounds

    char *temp = new char[numChars + 1];
    strncpy(temp, data + start, numChars);
    temp[numChars] = '\0'; // Ensure null-termination
    DSString result(temp);
    delete[] temp; // Clean up temporary memory
    return result;
}

DSString DSString::toLower() const
{
    DSString result;
    result.data = new char[len + 1];
    result.len = len;

    for (size_t i = 0; i < len; i++)
    {
        result.data[i] = tolower(data[i]); // Convert to lowercase
    }
    result.data[len] = '\0'; // Null-terminate
    return result;
}

char *DSString::c_str() const
{
    return data;
}

std::ostream &operator<<(std::ostream &os, const DSString &str)
{
    os << str.data;
    return os;
}

// Remove symbols from the string
DSString DSString::removesymbol()
{
    DSString result;
    result.data = new char[len + 1];
    size_t j = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (isalnum(data[i])) // Check if character is alphanumeric
        {
            result.data[j++] = data[i];
        }
    }
    result.data[j] = '\0'; // Null-terminate
    result.len = j; // Set the new length
    return result;
}

// Find the index of the first occurrence of a character
size_t DSString::findindexchar(char c)
{
    for (size_t i = 0; i < len; i++)
    {
        if (data[i] == c)
            return i;
    }
    return std::string::npos; // Return npos if character is not found
}

DSString DSString::stem()
{
    if (len <= 0 || data == nullptr) {
    // Handle the case where there's nothing to stem
    return DSString(); // or return an empty DSString
    }
    char *tempCStr = new char[len + 1];
    strcpy(tempCStr, data); // Copy current string to temporary C-string
    char *stemmedCStr = stemming::english_stem(tempCStr);
    DSString result(stemmedCStr); // Ensure this constructor handles the string correctly
    delete[] tempCStr; // Free the temporary C-string
    // You may need to free 'stemmedCStr' here if it was dynamically allocated
    return result; // Return the stemmed DSString
}
