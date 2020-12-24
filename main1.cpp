#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <sstream>
#include <fstream>
#include <iostream>
#include <string> 
#include <cstdlib>
#include <unistd.h>
#include <iterator> 
#include <list> 

using namespace std;
fstream file3;
fstream file2;
fstream file4;
char buffer[600];
char buffer2[600];

std::string str2 ("countryName=US");
std::string issuer("Issuer: commonName=");
std::string Country_CH ("countryName=CH");
std::string Country_GB ("countryName=GB");
std::string Country_BE ("countryName=BE");
std::ifstream file("counties.txt");
std::string line;
std::string http_status ("1.1 301 Moved Permanently");
std::string http_status1 ("302 Found");
std::string http_status2 ("1.1 404 Not Found");
std::string http_status3 ("HTTP/1.1 200 OK");
 
char certificate_issuer_name(string mystring, string line, string test);
char http_check(string line, string mystring);
char write_county_name(string mystring);

char write_county_name(string line){

file2.open ("county_write.txt", fstream::in | fstream::out | fstream::app);
                string test = line;
                file2 << test << "\n";
                file2.close();
}



char country_code(string mystring, string status)
      {
        
        if (mystring.find(str2) != std::string::npos) 
        {
                string test =  line + ": Country Code: US:" + status ;
                file2 << test << "\n";
                file2.close();
                certificate_issuer_name(mystring, line, test);
                           

        } else if (mystring.find(Country_CH) != std::string::npos) 
        {
                file2.open ("county_code.csv", fstream::in | fstream::out | fstream::app);
                string test = line + ": Country Code: CH:"+ status;
                file2 << test << "\n";
                file2.close();
                
                certificate_issuer_name(mystring, line, test);

        } else if (mystring.find(Country_GB) != std::string::npos) 
        {
                  file2.open ("county_code.csv", fstream::in | fstream::out | fstream::app);
                  string test = line + ": Country Code: GB:" + status ;
                  file2 << test << "\n";
                  file2.close();
                  
                  
                  certificate_issuer_name(mystring, line, test);

        } else if (mystring.find(Country_BE) != std::string::npos) 
        {
                  file2.open ("county_code.csv", fstream::in | fstream::out | fstream::app);
                  string test = line + ": Country Code: BE:" ;
                  file2 << test << "\n";
                  file2.close();
                  
                  certificate_issuer_name(mystring, line, test);
        } else {
          file2.open ("county_code.csv", fstream::in | fstream::out | fstream::app);
                  string test = line + ": Unknown: Unknown:" ;
                  file2 << test << "\n";
                  file2.close();
                  
                  certificate_issuer_name(mystring, line, test);
        }
       
      }

    char certificate_issuer_name(string mystring, string line, string test){
    
      if (mystring.find(issuer) != std::string::npos) {
                file4.open ("certificate_issuer_name.csv", fstream::in | fstream::out | fstream::app);
                size_t s = mystring.find(issuer);
                size_t e = mystring.find("/organizationName=", s);
                string str3 = mystring.substr(s + 19, e - s - 19);
                file4 << test << ": Certificate Issuer: " << str3 << endl;
                file4.close();
                }
    }

char http_check(string line, string mystring){
      FILE *fpipe;
      file3.open ("http.csv", fstream::in | fstream::out | fstream::app);
      char *http_command = "curl -I "  ;
      char *cstr1 = new char[line.length() + 1];
      strcpy(cstr1, line.c_str());
      char http_result[100];   // array to hold the result.
      strcpy(http_result,http_command); // copy string one into the result.
      strcat(http_result,cstr1); // append string two to the result.
      system(http_result);
       if (0 == (fpipe = (FILE*)popen(http_result, "r")))
    	     {
            perror("popen() failed.");
            exit(EXIT_FAILURE);
   	       }
         std::string status;
        fseek(fpipe , 0, SEEK_END);
        while (fread(buffer2, sizeof buffer2, 1, fpipe))
        {
          std::string mystring1(buffer2);
          if (mystring1.find(http_status) != std::string::npos) 
        {
              string status = "no http";
              file3 << line << ":no http" << "\n";
              country_code(mystring,status); 
                
        } else if (mystring1.find(http_status1) != std::string::npos)
        
        {
              string status = "302 Found";
              file3 << line << ":302 Found" << "\n";
              country_code(mystring,status); 

        } else if (mystring1.find(http_status2) != std::string::npos){
              string status = "no http";
              file3 << line << ":no http" << "\n";
              country_code(mystring,status); 
        } else if (mystring1.find(http_status3) != std::string::npos)
        {
              string status = "http";
              file3 <<  line << ":found http" << "\n";
              country_code(mystring,status); 
        }else {
              string status = "dunno";
              file3 <<  line << ":dunno" << "\n";
              country_code(mystring,status); 
        }
        
        }

}

int main()
{
	while (std::getline(file,line)){
    		FILE *fpipe;
        
        char *cstr = new char[line.length() + 1];
        strcpy(cstr, line.c_str());
        char *command = "nmap --script ssl-cert -p 443 " ; //issuer
        char result[100];   // array to hold the result.
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
                   
        //certificate_issuer_name(mystring, line);
        write_county_name(mystring);
        http_check(line, mystring);

        }
    
    pclose(fpipe);	
    file3.close();
  
    }

    return EXIT_SUCCESS;
}
