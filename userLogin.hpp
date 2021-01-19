#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class userLogin {

public:
    userLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password

private:
    unordered_map< string, string > table;

};

userLogin::userLogin() {
}

// COMPLETE THE FOLLOWING FUNCTIONS
//written by Vincent Diep
void userLogin::readIn(const string& filename) {

    ifstream inData;        
    inData.open(filename);         // use fstream to open file

    if (!inData)
    {
        cerr << "File could not be opened." << endl;
    }

    std::string key, value;

    while (inData >> key >> value)  // while there is text, read in data
    {
        table[key] = value;     // add keys and their values into table
    }
}
//written by Vincent Diep
size_t userLogin::numberOfUsers() {

    return table.size();        // returns number of elements in table
}
//written by Vincent Diep
string userLogin::passWordCheck(const string& userName) {

    if (table.find(userName) != table.end())    // find user
    {
        return table[userName];     // return password associated with userName
    }
    return "Non-existent User";
}
//written by Vincent Diep
size_t userLogin::wordBucketIdMethod1(const string& userName) {

    return table.bucket(userName);
}
//written by Vincent Diep
size_t userLogin::wordBucketIdMethod2(const string& userName) {

    size_t bucketCount = table.bucket_count();

    for (size_t i = 0; i < bucketCount; i++)    // iterate to a new bucket
    {
        for (auto it = table.begin(i); it != table.end(i); it++)    // iterate through bucket
        {
            if (it->first == userName)      // if userName found, return index
            {
                return i;
            }
        }
    }
    throw std::range_error("Username not found.");
}
//written by Vincent Diep
bool userLogin::validateUser(const string& userName) {

    if (table.find(userName) != table.end())   
    {
        return true;
    }
    return false;
}
//written by Vincent Diep
bool userLogin::authenticateUser(const string& userName, const string& passWord) {

    if (validateUser(userName))     // authenticate userName
    {
        return ((table.find(userName))->second == passWord);    // authenticate passWord
    }
    return false;
}
