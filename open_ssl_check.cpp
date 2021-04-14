#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream> 
#include <sstream>
#include <string> 
#include <fstream>
#include <array>

using namespace std;
char buffer[6000];
fstream file2;
int score1 = 0;
std::string execCommand(string cmd, int& out_exitStatus)
{
    out_exitStatus = 0;
    auto pPipe = ::popen(cmd.c_str(), "r");
    if(pPipe == nullptr)
    {
        throw std::runtime_error("Cannot open pipe");
    }

    std::array<char, 1024> buffer;

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



string state_issuer(string mystring)

{
    string result2;
     if (mystring.find("C = US") != std::string::npos) 
        {
                string test =  "Country Code; US;";
                ++score1;
                result2 = test;
                return result2;

        } else if (mystring.find("C = CH") != std::string::npos) 
        {
                string test = "Country Code; CH;";

                result2 = test;
                return result2;
        } else if (mystring.find("C = GB") != std::string::npos) 
        {
             
                  string test = "Country Code; GB;";
               
                  result2 = test;
                  return result2;
        } else if (mystring.find("C = BE") != std::string::npos) 
        {
                  string test = "Country Code; BE;" ;
                  result2 = test;
                  return result2;

         }else if (mystring.find("C = RU") != std::string::npos) 
        {
                  string test = "Country Code; RU;" ;
                  result2 = test;
                  return result2;
        }else if (mystring.find("issuer=C = RU") != std::string::npos) 
        {
                  string test = "Country Code; RU;" ;
                    result2 = test;
                    return result2;
        
        } else {
                  string test = "Country Code; Unknown;" ;
                  result2 = test;
                  return result2;
        }

}


int main()
      {
        FILE *fpipe;
     
        ifstream testFile("counties.txt"); 
       
        string line;
        string line2;
        
        while(getline(testFile, line)){
          
        line2 = line;
        file2.open ("./openssl_file.csv", fstream::in | fstream::out | fstream::app);      
        char *cstr = new char[line.length() + 1];
        char *port = ":443" ;
        strcpy(cstr, line.c_str());
        char *command = "echo 'Q' | openssl s_client -connect " ; //issuer
        char result[200]; // array to hold the result.
        strcpy(result,command); // copy string one into the result.
        strcat(result,cstr); // append string two to the result.
        strcat(result,port);
        int exitStatus = 0;
        string mystring = execCommand(result, exitStatus);
        string tls_value;
        string self = "expired";
        string self1;
        string expired;
        string result3 = state_issuer(mystring);
        if (mystring.find("1.2") != std::string::npos){
            tls_value = "TLS 1.2";
            ++score1;++score1;
        } else if (mystring.find("1.1") != std::string::npos){
            tls_value = "TLS 1.1";
            ++score1;
        } else if (mystring.find("1.3") != std::string::npos){
            tls_value = "TLS 1.3";
            ++score1;++score1;++score1;
       
        } else if (mystring.find("1.0") != std::string::npos){
            tls_value = "TLS 1.0";
          
        } else if (mystring.find("Cipher is (NONE)") != std::string::npos){
            tls_value = "No TLS";
        
               
        }else {
            tls_value = "unknown";
        }

        if (mystring.find("self") != std::string::npos){
            self1 = ";certificate;self-signed;";

        } else {

            self1 = ";certficate; not self-signed;";
            ++score1;
        }


        if (mystring.find(self) != std::string::npos) 
            {
                expired = "certificate; expired;";
            
            } else {
                expired = "certificate; not expired;";
                ++score1;
      
            }
        string domain; 
        if (line2.find(".gov") != std::string::npos) 
            {
                domain = "domain; .gov;";
                ++score1;++score1;
            }
        else if (line2.find(".net") != std::string::npos) 
            {
                domain = "domain; .net;";
            }
        else if (line2.find(".us") != std::string::npos) 
            {
                domain = "domain; .us;";
                ++score1;
            }
        else if (line2.find(".org") != std::string::npos) 
            {
                domain = "domain; .org;";  

            }
        else if (line2.find(".com") != std::string::npos) 
            {
                domain = "domain; .com;";
            } 
        else{
                domain = "domain; unknown;";
            }

    //test

            

        string cert_type;

        

        if (mystring.find("EV") != std::string::npos) 
            {
                cert_type = "cert_type; EV;";
            } else if (mystring.find("Extended Validation") != std::string::npos) 
            {
                cert_type = "cert_type; EV;";
                ++score1;
            } 
            else {

                
                cert_type = "cert_type; non-EV;";
                
            }
        cout << " Checking: " << line << "Certificate Country Code, Certificate Issuer, Certificate Typer, Certificate Signing and Expiry Status" << '\n';
        file2 << score1 << ";" << line2 << ";" << tls_value << ";" << expired << self1 << result3 << domain << cert_type << endl;
              
            file2.close();

            score1 = 0;
                 }

       
       }
      