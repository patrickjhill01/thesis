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



using namespace std;
fstream file3;
fstream file2;
fstream file4;
fstream file22;
char buffer[600];
char buffer2[50];
char hb_buffer[600];
char tls_buffer[1000];

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
std::string http_status3 ("HTTP/1.1 200 OK");
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


string country_code(string mystring, string line){
{
        string result1 = "result1";
        if (mystring.find(str2) != std::string::npos) 
        {
                string test =  "Country Code: US:";
                
                result1 = test;

        } else if (mystring.find(Country_CH) != std::string::npos) 
        {
                
                string test = "Country Code: CH:";
               
                result1 = test;
        } else if (mystring.find(Country_GB) != std::string::npos) 
        {
             
                  string test = "Country Code: GB:";
               
                  result1 = test;
        } else if (mystring.find(Country_BE) != std::string::npos) 
        {
                  string test = "Country Code: BE:" ;
                  result1 = test;
        } else {
                  string test = "Unknown: Unknown:" ;
                  result1 = test;
        }
        return result1;
      }
     
      
}
           

string certificate_issuer_name(string mystring, string line){
      string result2 = "not found";
if (mystring.find(issuer) != std::string::npos) 
            {
        
                size_t s = mystring.find(issuer);
                size_t e = mystring.find("/organizationName=", s);
                string str3 = mystring.substr(s + 19, e - s - 19);
                result2 = str3;
            }
       return result2;
     


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

                  
      
       if (readBuffer.find(http_status) != std::string::npos){
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
             result3 = "HTTP/1.1 302 Object Moved";

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
                  result3 = "dunno";
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




string heartbleed_check(string line){
      FILE *fpipe;
      string hb_str = "VULNERABLE";
      char *cstr2 = new char[line.length() + 1];
      strcpy(cstr2, line.c_str());
      string hb_return = "clear";
      char *hb_command = "nmap -p 443 --script ssl-heartbleed ";
      char HB_result[100];
      strcpy(HB_result, hb_command);
      strcat(HB_result,cstr2);
      cout << " hb_check line: " << HB_result << '\n';
      if (0 == (fpipe = (FILE*)popen(HB_result, "r")))
            {
            perror("popen() failed.");
            exit(EXIT_FAILURE);
            }
      fseek(fpipe , 0, SEEK_END);
            while (fread(hb_buffer, sizeof hb_buffer, 1, fpipe))
            {
                  perror("popen() failed.");
            exit(EXIT_FAILURE);
                  }
            fseek(fpipe , 0, SEEK_END);
            while (fread(hb_buffer, sizeof hb_buffer, 1, fpipe))
                  {
            std::string hb_string(hb_buffer);
            
            if (hb_string.find(hb_str) != std::string::npos) 
                  {
                string hb_return =  "Vulnerable";
                  }
            return hb_return;  
      }


}

string tls_check(string line){
FILE *fpipe;
      string tls_str = "SWEET32";
      char *cstr4 = new char[line.length() + 1];
      strcpy(cstr4, line.c_str());
      char *tls_command = "nmap -p 443 --script=ssl-enum-ciphers ";
      char tls_result[1000];
      strcpy(tls_result, tls_command);
      strcat(tls_result,cstr4);
      
      if (0 == (fpipe = (FILE*)popen(tls_result, "r")))
            {
            perror("popen() failed.");
            exit(EXIT_FAILURE);
                  }
            fseek(fpipe , 0, SEEK_END);
            while (fread(tls_buffer, sizeof tls_buffer, 1, fpipe))
                  {
                  std::string tls_string(tls_buffer);
                  if (tls_string.find(tls_str) != std::string::npos) 
                   {
                   string tls_return =  "SWEET32 Vulnerable";
                   return tls_return;
                   }else{
                  string tls_return = "clear";
                  return tls_return;
                  }
        }
}

int main()
      {
       FILE *fpipe;
     
       ifstream testFile("counties.txt");    
       string line;
       while(getline(testFile, line)){
       cout << " Checking: " << line << '\n';
        std::replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        //concatinate the county name and the nmap string        
        char *cstr = new char[line.length() + 1];
        strcpy(cstr, line.c_str());
        char *command = "nmap --script ssl-cert -p 443 " ; //issuer
        char result[100]; // array to hold the result.
        strcpy(result,command); // copy string one into the result.
        strcat(result,cstr); // append string two to the result.
        if (0 == (fpipe = (FILE*)popen(result, "r")))
            {
            perror("popen() failed.");
            exit(EXIT_FAILURE);
                  }
            fseek(fpipe , 0, SEEK_END);
            while (fread(buffer, sizeof buffer, 1, fpipe))
                  {
            std::string mystring(buffer);
            file2.open ("results.csv", fstream::in | fstream::out | fstream::app);      
            
            //string result1 = country_code(mystring, line);
            //string result2 = certificate_issuer_name(mystring, line);
            //string result3 = http_check(line);
            //string result4 = heartbleed_check(line);
            //string result5 = hsts_check(line);
            string result6 = tls_check(line);
            cout << result6 << endl; 
            //file2 << line << ":" << result1 << ": Certificate Issuer: " << result2 <<  ": http_check:" << result3 << ":Heartbleed: " << result4 << ":hsts_check:" << result5 << endl;
            file2.close();
                 }
      }
      return 0;
}
