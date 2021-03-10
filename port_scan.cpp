
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










int main()
      {
        FILE *fpipe;
     
        ifstream testFile("counties.txt");    
        string line;
        while(getline(testFile, line)){
        
        file2.open ("results.csv", fstream::in | fstream::out | fstream::app);      
        char *cstr = new char[line.length() + 1];
        strcpy(cstr, line.c_str());
        char *command = "nmap " ; //issuer
        char result[200]; // array to hold the result.
        strcpy(result,command); // copy string one into the result.
        strcat(result,cstr); // append string two to the result.
        int exitStatus = 0;
        
        //file2 << score << ";" << line << ";" << result1 << "; Certificate Issuer; " << result2 <<  "; http_check;" << result3 << result4 << ";" << ";hsts_check;" << result5  << ";" << result6 << result7 << result8 << result9 << endl;

        file2.close();
        
        

      system ("./openssl")     ;     
       }