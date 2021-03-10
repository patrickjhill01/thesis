
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <sstream>
#include <fstream>
#include <string> 
#include <cstdlib>
#include <unistd.h>
#include <iterator> 
#include <list> 
#include <algorithm>
#include <iomanip>
#include <curl/curl.h>
#include <mutex>
#include <array>
#include<unistd.h>
using namespace std;
fstream file3;
fstream file2;
fstream file4;
fstream file22;
char buffer[4000];
char buffer2[50];

#include <bits/stdc++.h> 
using namespace std; 
int countOccurences(char *str, string word) 
{ 
  cout << "we are here";
    char *p; 
  
    // split the string by spaces in a 
    vector<string> a; 
  
    p = strtok(str, " "); 
    while (p != NULL) 
    { 
        a.push_back(p); 
        p = strtok(NULL, " "); 
    } 
  
    // search for pattern in a 
    int c = 0; 
    for (int i = 0; i < a.size(); i++) 
  
        // if match found increase count 
        if (word == a[i]) 
            c++; 
    return c; 
} 

std::string execCommand(string cmd, int& out_exitStatus)
{
    out_exitStatus = 0;
    auto pPipe = ::popen(cmd.c_str(), "r");
    if(pPipe == nullptr)
    {
        throw std::runtime_error("Cannot open pipe");
    }

    std::array<char, 256> buffer;

    std::string result;

    while(not std::feof(pPipe))
    {
        auto bytes = std::fread(buffer.data(), 1, buffer.size(), pPipe);
        result.append(buffer.data(), bytes);
    }

    auto rc = ::pclose(pPipe);

    if(WIFEXITED(rc))
    {
        out_exitStatus = WEXITSTATUS(rc);
    }

    return result;
}


int main()
      {
        FILE *fpipe;
     
        ifstream testFile("counties.txt");    
        string line;
        while(getline(testFile, line)){
        
        file2.open ("results_scan.csv", fstream::in | fstream::out | fstream::app);      
        char *cstr = new char[line.length() + 1];
        strcpy(cstr, line.c_str());
        char *command = "nmap " ; //issuer
        char result[200]; // array to hold the result.
        strcpy(result,command); // copy string one into the result.
        strcat(result,cstr); // append string two to the result.
        int exitStatus = 0;
        string mystring = execCommand(result, exitStatus);
        string word = "open"; 
        string str = mystring ;
        char *cstr1 = &str[0]; 
        
        countOccurences(cstr1, word) ;     
        
        cout << countOccurences(cstr1, word);
        //file2 << score << ";" << line << ";" << result1 << "; Certificate Issuer; " << result2 <<  "; http_check;" << result3 << result4 << ";" << ";hsts_check;" << result5  << ";" << result6 << result7 << result8 << result9 << endl;



        file2.close();
        
        
      // syste
        }
      }