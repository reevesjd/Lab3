#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void diss(std::ifstream &r)
{
    std::string line;
    while(r)
    {
        std::string s = line.substr(0,1);
        getline(r, line);
        std::stringstream stm(line);
        std::cout << s + "\n";
    }
}

int main(int argc, char * argv[])
{
    std::ifstream reader;
    reader.open(argv[1]);
    diss(reader);
    reader.close();
}
