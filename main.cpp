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

using namespace std;

int main()
{
	std::ifstream file("counties.txt");
  
  fstream file3;
  
  
	std::string line;
	while (std::getline(file,line)){
    		FILE *fpipe;
                
                char *cstr = new char[line.length() + 1];
                strcpy(cstr, line.c_str());

    		//char *command = "nmap -p 443 --script ssl-poodle ";  //poodle
                // char *command = "nmap -p 443 --script ssl-enum-ciphers ";
                char *command = "nmap --script ssl-cert -p 443 " ; //issuer
                //char *command2 = "curl -i http://" ; //http
                //char *command = "nmap -p 443 --script ssl-heartbleed ";  /heartbleed
                char result[100];   // array to hold the result.
                strcpy(result,command); // copy string one into the result.
                strcat(result,cstr); // append string two to the result.

  		char c = 0;

    	if (0 == (fpipe = (FILE*)popen(result, "r")))
    	 {
        perror("popen() failed.");
        exit(EXIT_FAILURE);
   	 }
         char buffer[30];
         fseek(fpipe , 0, SEEK_END);
         std::string str2 ("302 Found");
         
         while (fread(buffer, sizeof buffer, 1, fpipe))
        {
            {
              
              std::string mystring(buffer);
              if (mystring.find(str2) != std::string::npos) {
                char data[100];
                file3.open ("filename.txt", fstream::in | fstream::out | fstream::app);
                //std::cout << "----------------------" << line << ":Poodle" << '\n';
                std::size_t pos = mystring.find(str2);
                std::string str3 = mystring.substr (pos);
                std::cout << line << " " << '\n';
                file3 << endl;
                
                file3 << line << " HTTP Found";
                file3.close();
                }
              
              //std::cout << mystring;
            }
    }
    pclose(fpipe);	
    file3.close();
    
    
    
    }

    return EXIT_SUCCESS;
}
