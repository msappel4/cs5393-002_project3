/*
#include "DSString.h"

/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 *
 * Note that c-strings don's store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable. 
 * DDO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */  
*/

// Megan 
#include "DSString.h"

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
