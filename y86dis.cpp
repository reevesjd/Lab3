#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

//Add spaces or commas?
void getRegister(int a)
{
    std::string regOut;
    switch (a)
    {
        case 0: regOut = "%rax";
                break;

        case 1: regOut = "%rcx";
                break;

        case 2: regOut = "%rdx";
                break;

        case 3: regOut = "%rbx";
                break;

        case 4: regOut = "%rsp";
                break;

        case 5: regOut = "%rbp";
                break;

        case 6: regOut = "%rsi";
                break;

        case 7: regOut = "%rdi";
                break;

        case 8: regOut = "%r8";
                break;

        case 9: regOut = "%r9";
                break;

        case 10:regOut = "%r10";
                break;

        case 11:regOut = "%r11";
                break;

        case 12:regOut = "%r12";
                break;

        case 13:regOut = "%r13";
                break;

        case 14:regOut = "%r14";
                break;
        
        case 15:    std::cout << "ERROR, REGISTER NOT USED\n";
                    break;

        default:    std::cout << "ERROR\n";
                    break;
    }

    std::cout << regOut;
}

void checkRegisters(char a, char b)
{
    if (a != NULL && b != NULL)
    {

    }

    else if (a != NULL && b == NULL)
    {
        
    }

    else if (a == NULL && b != NULL)
    {
        //Doesn't need to output F, just placeholder
        std::cout << "F";
        getRegister(b - '0');
    }

    else 
    {
        std::cout<< "ERROR\n";
    }
}
void oneByte(const char* tok)
{
    std::string instOut;
    if (tok[0] == '0' && tok[1] == '0')
    {
        instOut = "halt\n";
    }

    else if (tok[0] == '1' && tok[1] == '0')
    {
        instOut = "nop\n";
    }

    else if (tok[0] == '9' && tok[1] == '0')
    {
        instOut = "ret\n";
    }

    else
    {
        instOut = "ERROR\n";
    }

    std::cout << instOut;
}

void twoBytes(const char* tok)
{
    std::string instOut;
    if (tok[0] == '2')
    {
        switch (tok[1])
        {
            case '0':   instOut = "rrmovq\n";
                        break;

            case '1':   instOut = "cmovle\n";
                        break;

            case '2':   instOut = "cmovl\n";
                        break;

            case '3':   instOut = "cmove\n";
                        break;

            case '4':   instOut = "cmovne\n";
                        break;

            case '5':   instOut = "cmovge\n";
                        break;

            case '6':   instOut = "cmovg\n";
                        break;

            default:    std::cout << "ERROR";
                        break;
        }
    }

    else if (tok[0] == '6')
    {
        switch (tok[1])
        {
            case '0':   instOut = "addq\n";
                        break;

            case '1':   instOut = "subq\n";
                        break;

            case '2':   instOut = "andq\n";
                        break;

            case '3':   instOut = "xorq\n";
                        break;

            default:    std::cout << "ERROR";
                        break;
        }
    }

    else if ((tok[0] == 'A' || tok[0] == 'a') && tok[1] == 0)
    {
        instOut = "pushq\n";
    }

    else if ((tok[0] == 'B' || tok[0] == 'b') && tok[1] == 0)
    {
        instOut = "popq\n";
    }

    else
    {
        std::cout << "ERROR\n";
    }
    std::cout << instOut;
}

void fourBytes(const char* tok)
{
    //Is this even used?    
}

void eightBytes(const char* tok)
{
    std::string instOut = ".quad\n";
    std::cout << instOut;
}

void nineBytes(const char* tok)
{
    std::string instOut;
    if (tok[0] == '7')
    {
        switch (tok[1])
        {
            case '0':   instOut = "jmp\n";
                        break;

            case '1':   instOut = "jle\n";
                        break;
            
            case '2':   instOut = "jl\n";
                        break;

            case '3':   instOut = "je\n";
                        break;

            case '4':   instOut = "jne\n";
                        break;

            case '5':   instOut = "jge\n";
                        break;

            case '6':   instOut = "jg\n";
                        break;

            default:    std::cout << "ERROR\n";
                        break;
        }
    }
    
    else if (tok[0] == '8' && tok[1] == '0')
    {
        instOut = "call\n";
    }

    else 
    {
        std::cout << "ERROR\n";
    }

    std::cout << instOut;
}

void tenBytes(const char* tok)
{
    std::string instOut;
    if (tok[0] == '3' && tok[1] == '0')
    {
        instOut = "irmovq\n";
        checkRegisters(NULL, tok[3]);
    }

    else if (tok[0] == '4' && tok[1] == '0')
    {
        instOut = "rmmovq\n";
    }

    else if (tok[0] == '5' && tok[1] == '0')
    {
        instOut = "mrmovq\n";
    }

    else
    {
        std::cout << "ERROR\n";
    }

    std::cout << instOut;
}

void readInst(const char* tok, int length)
{
    int bytes = 0;
    for (int i = 0; i < length; i++)
    {
        if (tok[i] != '\n' && tok[i] != ' ' && tok[i] != '\t')
        {
            bytes++;
        }
    }
    bytes = bytes / 2;
    //char firstByte = tok[1];
    switch (bytes)
    {
        case 0: std::cout << "\n";
                break;

        case 1: oneByte(tok);
                break;

        case 2: twoBytes(tok);
                break;

        case 4: fourBytes(tok);
                break;

        case 8: eightBytes(tok);
                break;

        case 9: nineBytes(tok);
                break;

        case 10:tenBytes(tok);
                break;

        default:std::cout << "An error occured while converting byte to instruction\n"; 
                break;
    }
}

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

            if (tok.at(1) == 'x' || tok.at(1) == 'X')
            {
                std::cout << tok << ": ";
            }

            else
            {
                readInst(tok.c_str(), tok.length());
            }
            
            //std::cout << tok << "\n";
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
