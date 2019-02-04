#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

void diss(std::ifstream &r)
{
    std::string line;
    while(r)
    {
        //int linePos = 0;
        std::string delim = ": ";
        std::string tok;
        //linePos = line.find(delim);
        //std::string s = getline(r);
        //std::stringstream stm(line);
        std::getline(r, line);//, ": ");
        std::istringstream stm(line);
        int lineNum = 1;
        while(std::getline(stm, tok, ':'))
        {
            if (lineNum % 2 == 0)
            {
                tok = tok.substr(1, tok.length());
            }
            std::cout << tok << "\n";
            lineNum++;
        }
        //std::string tok1 = line.substr(0, linePos);    
        //std::string tok2 = line.substr(line.find(delim) + 2);
        //line.trim();
        //std::cout << tok1 + "\n";
        //std::cout << tok2 + "\n";
    }
}

int main(int argc, char * argv[])
{
    std::ifstream reader;
    reader.open(argv[1]);
    if (!reader)
    {
        std::cerr << "Unable to open file, check the filename.\n";
        exit(1); //System will stop if file cannot be found
    }
    diss(reader);
    reader.close();
}
