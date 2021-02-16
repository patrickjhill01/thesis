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




std::string str2 ("countryName=US");
std::string issuer("Issuer: commonName=");
std::string Country_CH ("countryName=CH");
std::string Country_GB ("countryName=GB");
std::string Country_BE ("countryName=BE");

std::string line;
std::string http_status ("HTTP/1.1 301 Moved Permanently");
//std::string http_status ("Strict");
std::string http_status1 ("HTTP/1.1 302 Redirect");
std::string http_status2 ("1.1 404 Not Found");
std::string hsts_status("Strict-Transport-Security:");
std::string http_status3 ("200");
std::string http_status4 ("HTTP/1.0 302 Moved Temporarily");
std::string http_status5 ("HTTP/1.1 302 Found : Moved Temporarily");
std::string http_status6 ("HTTP/1.1 302 Object Moved");
std::string http_status7 ("HTTP/1.1 302 Found");
std::string http_status8 ("HTTP/1.0 301 Moved Permanently");
std::string http_status9 ("HTTP/1.1 500 Internal Server Error");
std::string http_status10 ("HTTP/1.0 302 Found");
std::string http_status11 ("HTTP/1.1 307 Moved Temporarily");
std::string http_status12 ("HTTP/1.1 301");
std::string http_status13 ("HTTP/1.1 302 Moved Temporarily");

string certificate_issuer_name(string mystring, string line);
string http_check(string line); 
string country_code(string mystring, string line);

string sweet_check = "SWEET32";
string result1 = "result1";

string sweet_find(string mystring){

   string str1 = mystring;
   string str2 = "SWEET32";
   int pos = 0;
   int index;
   string sweet_result;
   if((index = str1.find(str2, pos)) != string::npos) {
      string sweet_result = "VULNERABLE";
      pos = index + 1; //new position is from next element of index
      return sweet_result;
   }else{
           string sweet_result = " NOT VULNERABLE";
           return sweet_result;
      }
        
}

string country_code(string mystring, string line)
{

string sweet_result = sweet_find(mystring);

        if (mystring.find(str2) != std::string::npos) 
        {
                string test =  "Country Code; US;";
                
                result1 = test;

        } else if (mystring.find(Country_CH) != std::string::npos) 
        {
                string test = "Country Code; CH;";

                result1 = test;
        } else if (mystring.find(Country_GB) != std::string::npos) 
        {
             
                  string test = "Country Code; GB;";
               
                  result1 = test;
        } else if (mystring.find(Country_BE) != std::string::npos) 
        {
                  string test = "Country Code; BE;" ;
                  result1 = test;

         }else if (mystring.find("issuer=C = US") != std::string::npos) 
        {
                  string test = "Country Code; US;" ;
        
        }else if (mystring.find("issuer=C = RU") != std::string::npos) 
        {
                  string test = "Country Code; RU;" ;
        
        
        } else {
                  string test = "Country Code; Unknown;" ;
                  result1 = test;
        }

          

                  
      string result1_final = result1 + "SWEET32;" + sweet_result ; 

      return result1_final;
   
}
           

string certificate_issuer_name(string mystring, string line){
      string result2 = "not found";
      string amazon = "EC2AMAZ-C2OVEUI";
      string web02 = "web02";
if (mystring.find(issuer) != std::string::npos) 
            {
        
                size_t s = mystring.find(issuer);
                size_t e = mystring.find("/organizationName=", s);
                string str3 = mystring.substr(s + 19, e - s - 19);
                result2 = str3;
            }
      if (result2.find(amazon) != std::string::npos){
            result2 = "Amazon EC2";
            return result2;
                  }else if (result2.find(web02) != std::string::npos) {
                  result2 = "web02";
                  return result2;
                        
                 } else {
                       return result2;
                 }
   

}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string http_check(string line)
{
      string result3 = "result3";
      FILE *fpipe;
      char *http_command = ""  ;
      char *cstr1 = new char[line.length() + 1];
      strcpy(cstr1, line.c_str());
      char http_result[100];   // array to hold the result.
      strcpy(http_result,http_command); // copy string one into the result.
      strcat(http_result,cstr1); // append string two to the result.
      CURL *curl;
      CURLcode res;
      std::string readBuffer;

      curl = curl_easy_init();
      if(curl) 
      {
            curl_easy_setopt(curl, CURLOPT_URL, http_result);
            curl_easy_setopt(curl, CURLOPT_HEADER, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

 
      
       if (readBuffer.find("HTTP/1.1 301 Moved Permanently") != std::string::npos){
              result3 = "HTTP/1.1 301 Moved Permanently";
             
             } else if (readBuffer.find(http_status1) != std::string::npos){
              result3 = "HTTP/1.1 302 Redirect";
              
             } else if (readBuffer.find(http_status2) != std::string::npos){
              result3 = "1.1 404 Not Found";

            } else if (readBuffer.find(http_status3) != std::string::npos){
              result3 = "HTTP/1.1 200 OK";

            } else if (readBuffer.find(http_status4) != std::string::npos){
              result3 = "HTTP/1.0 302 Moved Temporarily";

            } else if (readBuffer.find(http_status5) != std::string::npos){
             result3 = "HTTP/1.1 302 Found : Moved Temporarily";

             } else if (readBuffer.find(http_status6) != std::string::npos){
             result3 = "HTTP/1.1 302 Object moved";

             } else if (readBuffer.find(http_status7) != std::string::npos){
             result3 = "HTTP/1.1 302 Found";

             } else if (readBuffer.find(http_status8) != std::string::npos){
             result3 = "HTTP/1.0 301 Moved Permanently";

             } else if (readBuffer.find(http_status9) != std::string::npos){
             result3 = "HTTP/1.1 500 Internal Server Error";

             } else if (readBuffer.find(http_status10) != std::string::npos){
             result3 = "HTTP/1.0 302 Found";

            } else if (readBuffer.find(http_status11) != std::string::npos){
            result3 = "HTTP/1.1 307 Moved Temporarily";

             } else if (readBuffer.find(http_status12) != std::string::npos){
            result3 = "HTTP/1.1 301";

             } else if (readBuffer.find(http_status13) != std::string::npos){
            result3 = "HTTP/1.1 302 Moved Temporarily";

            }else
            {
                  result3 = "Unknown";
            }
            
            return result3;
      }
}

string hsts_check(string line){
      string result5 = "result5";
      FILE *fpipe;
      char *hsts_command = "https://"  ;
      char *cstr3 = new char[line.length() + 1];
      strcpy(cstr3, line.c_str());
      char hsts_result[100];   // array to hold the result.
      strcpy(hsts_result,hsts_command); // copy string one into the result.
      strcat(hsts_result,cstr3); // append string two to the result.
      CURL *curl;
      CURLcode res; 
      
      std::string hsts_buffer;
      
      curl = curl_easy_init();
      if(curl) 
      {
            curl_easy_setopt(curl, CURLOPT_URL, hsts_result);
            curl_easy_setopt(curl, CURLOPT_HEADER, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &hsts_buffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
      }
      if (hsts_buffer.find(hsts_status) != std::string::npos){
              result5 = "Strict Trasport Security Found";
           }else
            {
                  result5 = "No HSTS";
            }   

            //cout << hsts_buffer;

           return result5;

}

string heartbleed_check(string mystring){
string hb_str = "heartbleed";
if (mystring.find(hb_str) != std::string::npos) 
            {
              string hb_result = ";Heartbleed;Found";
              return hb_result;
} else {
              string hb_result  = ";Heartbleed;not found";
              return hb_result;
            }
       
        
}

string tls_str = "TLSv1.3";
string tls_str1 = "TLSv1.2";
string tls_str2 = "TLSv1.1";
string tls_str3 = "TLSv1.0";

string tls_check(string mystring){

if (mystring.find("80/tcp  open  http") != std::string::npos) 
            {
              string tls_result = ";PORT 80;Open;";
              return tls_result;
   
    } else {
           string tls_result = ";PORT 80;Closed;";
           return tls_result;

     }      

}
string poodle_check(string mystring)
{
string poodle_str = "poodle";
if (mystring.find(poodle_str) != std::string::npos) 
            {
              string poodle_result = "Poodle;Found;";
              return poodle_result;
            } else {
              string poodle_result  = "Poodle;not found;";
              return poodle_result;
            }
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

string drown_check(string mystring){

      string drown_str = "DROWN";
      if (mystring.find(drown_str) != std::string::npos) 
            {
              string drown_result = ";Drown;Found;";
              return drown_result;
            } else {
              string drown_result  = ";Drown;not found;";
              return drown_result;
            
            }
      
}

string freak_check(string mystring){

      string freak_str = "EXPORT";
      if (mystring.find(freak_str) != std::string::npos) 
            {
              string freak_result = ";freak;Found;";
              return freak_result;
            } else {
              string freak_result  = ";freak;not found;";
              return freak_result;
            
            }

}

int main()
      {
        FILE *fpipe;
     
        ifstream testFile("counties.txt");    
        string line;
        while(getline(testFile, line)){
        
        file2.open ("results.csv", fstream::in | fstream::out | fstream::app);      
        char *cstr = new char[line.length() + 1];
        strcpy(cstr, line.c_str());
        char *command = "nmap -p 80,443 --script=ssl-enum-ciphers,ssl-cert,ssl-poodle,ssl-heartbleed,sslv2-drown " ; //issuer
        char result[200]; // array to hold the result.
        strcpy(result,command); // copy string one into the result.
        strcat(result,cstr); // append string two to the result.
        int exitStatus = 0;
        cout << " Checking: " << line << '\n';
            string mystring = execCommand(result, exitStatus);
        
            string result1 = country_code(mystring, line);
            string result4 = heartbleed_check(mystring);
            string result2 = certificate_issuer_name(mystring, line);
            string result7 = poodle_check(mystring);
            string result6 = tls_check(mystring);
            string result3 = http_check(line);
            string result5 = hsts_check(line);
            string result8 = drown_check(mystring);
            string result9 = freak_check(mystring);
            
           
            file2 << line << ";" << result1 << "; Certificate Issuer; " << result2 <<  "; http_check;" << result3 << result4 << ";" << ";hsts_check;" << result5  << ";" << result6 << result7 << result8 << result9 << endl;
            file2.close();
                 }
       }
      
     

