
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

    std::array<char, 512> buffer;

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
        
        int value = countOccurences(cstr1, word);
       sleep(5);
        string ftp;
        string ssh;
        string telnet;
        string smtp;
        string dns;
        string netbios;
        string smb;
        string rdp;
        string sql;
        string tcp;

        if (mystring.find("21/tcp") != std::string::npos) 
            {
                ftp = ";ftp;";
            
            } 
         if (mystring.find("22/tcp") != std::string::npos) 
            {
                ssh = ";ssh;";
            
            }
        if (mystring.find("23/tcp") != std::string::npos) 
            {
               telnet = ";telnet;";
            
            }
         if (mystring.find("25/tcp") != std::string::npos) 
            {
                smtp = ";smtp;";
            
            }
         if (mystring.find("53/tcp") != std::string::npos) 
            {
                dns = ";dns;";
            
            }
         if (mystring.find("139/tcp") != std::string::npos) 
            {
                netbios = ";netbios;";
            
            }
         if (mystring.find("445/tcp") != std::string::npos) 
            {
                smb = ";smb;";
            
            }
         if (mystring.find("1433/tcp") != std::string::npos) 
            {
                sql = ";sql;";
            
            } 

        if (mystring.find("3389/tcp") != std::string::npos) 
            {
                rdp = ";rdp;";
              }
        if (mystring.find("1434/tcp") != std::string::npos) 
            {
                sql = ";sql;";
            
            }
       if (mystring.find("443/tcp") != std::string::npos) 
            {
                value--;
            
            } else {
                value ;
      
            }
       if (mystring.find("80/tcp") != std::string::npos) 
            {
                tcp = ";port 80;";
                value--;
            
            } else {
                value ;
      
            }
   

            cout << " Checking: " << line << " Open Ports" << '\n';

         file2 << line << ";" << value << ";" << tcp << ftp << ssh << telnet << smtp << dns << netbios <<  smb << rdp << sql << endl;
        //file2 << score << ";" << line << ";" << result1 << "; Certificate Issuer; " << result2 <<  "; http_check;" << result3 << result4 << ";" << ";hsts_check;" << result5  << ";" << result6 << result7 << result8 << result9 << endl;



        file2.close();
       

        }
        system("./openssl"); 
      }