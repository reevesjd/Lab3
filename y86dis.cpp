#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void diss(std::ifstream &r)
{
    std::string line;
    while(r)
    {
        //std::string s = getline(r);
        //std::stringstream stm(line);
        std::getline(r, line, '\n');
        std::cout << line + "\n";
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
