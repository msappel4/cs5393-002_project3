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

// Megan first try
#include "DSString.h"

// Default constructor
DSString::DSString() : data(new char[1]), len(0) {
    data[0] = '\0'; // Initialize with an empty string
}

// Constructor from a C-string
DSString::DSString(const char *str) {
    if (str) {
        len = 0;
        while (str[len] != '\0') {
            len++;
        }
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            data[i] = str[i]; // Copy character by character
        }
        data[len] = '\0'; // Null-terminate
    } else {
        len = 0;
        data = new char[1];
        data[0] = '\0'; // Handle null pointer
    }
}

// Copy constructor
DSString::DSString(const DSString &other) : len(other.len) {
    data = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        data[i] = other.data[i]; // Copy data
    }
    data[len] = '\0'; // Null-terminate
}

// Copy assignment operator
DSString &DSString::operator=(const DSString &other) {
    if (this != &other) {
        delete[] data; // Free existing resource
        len = other.len;
        data = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            data[i] = other.data[i]; // Copy data
        }
        data[len] = '\0'; // Null-terminate
    }
    return *this;
}

// Destructor
DSString::~DSString() {
    delete[] data; // Free memory
}

// Returns the length of the string
size_t DSString::length() const {
    return len;
}

// Returns a reference to the character at the index
char &DSString::operator[](size_t index) {
    if (index >= len) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Overloaded operator+ for string concatenation
DSString DSString::operator+(const DSString &other) const {
    DSString result;
    result.len = len + other.len;
    result.data = new char[result.len + 1];

    for (size_t i = 0; i < len; ++i) {
        result.data[i] = data[i]; // Copy current string
    }
    for (size_t i = 0; i < other.len; ++i) {
        result.data[len + i] = other.data[i]; // Append other string
    }
    result.data[result.len] = '\0'; // Null-terminate

    return result;
}

// Equality operator
bool DSString::operator==(const DSString &other) const {
    if (len != other.len) return false;
    for (size_t i = 0; i < len; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

// Less-than operator
bool DSString::operator<(const DSString &other) const {
    for (size_t i = 0; i < len && i < other.len; ++i) {
        if (data[i] < other.data[i]) {
            return true;
        } else if (data[i] > other.data[i]) {
            return false;
        }
    }
    return len < other.len; // If equal, shorter is "less"
}

// Substring method
DSString DSString::substring(size_t start, size_t numChars) const {
    if (start >= len) {
        throw std::out_of_range("Start index out of range");
    }
    size_t actualNumChars = (start + numChars > len) ? len - start : numChars;
    DSString result;
    result.len = actualNumChars;
    result.data = new char[result.len + 1];

    for (size_t i = 0; i < actualNumChars; ++i) {
        result.data[i] = data[start + i];
    }
    result.data[actualNumChars] = '\0'; // Null-terminate

    return result;
}

// Converts string to lowercase
DSString DSString::toLower() const {
    DSString result;
    result.len = len;
    result.data = new char[len + 1];

    for (size_t i = 0; i < len; ++i) {
        result.data[i] = (data[i] >= 'A' && data[i] <= 'Z') ? data[i] + 32 : data[i]; // Convert to lowercase
    }
    result.data[len] = '\0'; // Null-terminate

    return result;
}

// Returns a pointer to a null-terminated C-string
const char *DSString::c_str() const {
    return data;
}

// Split method to tokenize the string based on a delimiter
std::vector<DSString> DSString::split(char delimiter) const {
    std::vector<DSString> tokens;
    size_t start = 0;
    size_t end = 0;

    while (end < len) {
        // Find the next occurrence of the delimiter
        while (end < len && data[end] != delimiter) {
            end++;
        }
        // Create a substring for the token
        tokens.emplace_back(substring(start, end - start));
        start = end + 1; // Move past the delimiter
        end++;
    }

    return tokens;
}

// Overloaded stream insertion operator
std::ostream &operator<<(std::ostream &os, const DSString &str) {
    os << str.c_str();
    return os;
}
