#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>

void flipEndOther(char *tok)
{
   for (int i = 0, j = 15; i < 8; i = i + 2, j = j - 2)
    {
        char temp = tok[i];
        tok[i] = tok[j - 1];
        tok[j - 1] = temp;
        temp = tok[i + 1];
        tok[i + 1] = tok[j];
        tok[j] = temp;
    }

    int k = 0;
    while (tok[k] == '0')
    {
        k++;
    }

    if (k == 16)
    {
        std::cout << "0x0";
    }
    
    else
    {
        std::cout << "0x";
        for (; k < 16; k++)
        {
            std::cout << tok[k];
        }
    }
}

void flipEndQuad(char *tok)
{
    /*char arr [16];
    arr[16] = '\0';
    for (int i = 0; i < 16; i++)
    {
        arr[i] = tok[i];
    }*/

    /*for (int i = 0, j = 15; i < 8; i = i + 2, j = j - 2)
    {
        char temp = arr[i];
        arr[i] = arr[j - 1];
        arr[j - 1] = temp;
        temp = arr[i + 1];
        arr[i + 1] = arr[j];
        arr[j] = temp;
    }*/

    for (int i = 0, j = 15; i < 8; i = i + 2, j = j - 2)
    {
        char temp = tok[i];
        tok[i] = tok[j - 1];
        tok[j - 1] = temp;
        temp = tok[i + 1];
        tok[i + 1] = tok[j];
        tok[j] = temp;
    }
}

//Add spaces or commas?
void getRegister(char a)
{
    std::string regOut;
    switch (a)
    {
        case '0': regOut = "%rax";
                break;

        case '1': regOut = "%rcx";
                break;

        case '2': regOut = "%rdx";
                break;

        case '3': regOut = "%rbx";
                break;

        case '4': regOut = "%rsp";
                break;

        case '5': regOut = "%rbp";
                break;

        case '6': regOut = "%rsi";
                break;

        case '7': regOut = "%rdi";
                break;

        case '8': regOut = "%r8";
                break;

        case '9': regOut = "%r9";
                break;

        case 'a':regOut = "%r10";
                break;

        case 'A':regOut = "%r10";
                break;

        case 'b':regOut = "%r11";
                break;

        case 'B':regOut = "%r11";
                break;

        case 'c':regOut = "%r12";
                break;

        case 'C':regOut = "%r12";
                break;

        case 'd':regOut = "%r13";
                break;

        case 'D':regOut = "%r13";
                break;

        case 'e':regOut = "%r14";
                break;

        case 'E':regOut = "%r14";
                break;
        
        case 'f':std::cout << "ERROR, REGISTER NOT USED\n";
                break;

        case 'F':std::cout << "ERROR, REGISTER NOT USED\n";
                break;

        default:    std::cout << "REG ERROR";
                    break;
    }

    std::cout << regOut;
}

void checkRegisters(char a, char b)
{
    if (a != 0 && b != 0)
    {
        getRegister(b);
        std::cout << ", ";
        getRegister(a);
    }

    else if (a != 0 && b == 0)
    {
        getRegister(a);
    }

    else if (a == 0 && b != 0)
    {
        //Doesn't need to output F, just placeholder
        //std::cout << "F";
        getRegister(b);
    }

    else 
    {
        std::cout<< "ERROR\n";
    }
}

void oneByte(/*const*/ char* tok)
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
        instOut = "illegalop\n";
    }

    std::cout << instOut;
}

void twoBytes(/*const*/ char* tok)
{
    std::string instOut;
    if (tok[0] == '2')
    {
        switch (tok[1])
        {
            case '0':   instOut = "rrmovq";
                        break;

            case '1':   instOut = "cmovle";
                        break;

            case '2':   instOut = "cmovl";
                        break;

            case '3':   instOut = "cmove";
                        break;

            case '4':   instOut = "cmovne";
                        break;

            case '5':   instOut = "cmovge";
                        break;

            case '6':   instOut = "cmovg";
                        break;

            default:    std::cout << "illegalop";
                        break;
        }
        std::cout << instOut << " ";
        checkRegisters(tok[3], tok[2]);
        //std::cout << "\n";
    }

    else if (tok[0] == '6')
    {
        switch (tok[1])
        {
            case '0':   instOut = "addq ";
                        break;

            case '1':   instOut = "subq ";
                        break;

            case '2':   instOut = "andq ";
                        break;

            case '3':   instOut = "xorq ";
                        break;

            default:    std::cout << "illegalop";
                        break;
        }
        std::cout << instOut << " ";
        checkRegisters(tok[3], tok[2]);
        //std::cout << "\n";
    }

    else if ((tok[0] == 'A' || tok[0] == 'a') && tok[1] == '0')
    {
        std::cout << "pushq ";
        checkRegisters(tok[2], 0);
        //std::cout << "\n";
    }

    else if ((tok[0] == 'B' || tok[0] == 'b') && tok[1] == '0')
    {
        std::cout << "popq ";
        checkRegisters(tok[2], 0);
        //std::cout << "\n";
    }

    else
    {
        std::cout << "illegalop";
    }
    //std::cout << instOut;
    std::cout << "\n";
}

void fourBytes(const char* tok)
{
    //Is this even used?    
}

void eightBytes(/*const*/ char* tok)
{
    std::string instOut = ".quad ";
    char arr [16];
    arr[16] = '\0';
    for (int i = 0; i < 16; i++)
    {
        arr[i] = tok[i];
    }
    flipEndQuad(arr);

    /*for (int i = 0, j = 15; i < 8; i = i + 2, j = j - 2)
    {
        char temp = arr[i];
        arr[i] = arr[j - 1];
        arr[j - 1] = temp;
        temp = arr[i + 1];
        arr[i + 1] = arr[j];
        arr[j] = temp;
    }*/
    std::cout << ".quad 0x";
    std::cout << arr << "\n";
    /*std::stringstream inte;
    inte << tok;
    int swap;
    inte >> swap;
    std::cout << "Before swap: " << std::hex << swap;
    swap = __builtin_bswap64(swap);
    std::cout << "After: " << std::hex << swap;*/
    //std::cout << instOut << "\n";

    //std::cout << instOut << std::hex << swap << "\n";
}

void nineBytes(/*const*/ char* tok)
{
    char arr [17];
    arr[16] = '\0';
    for (int i = 0, j = 2; i < 16; i++, j++)
    {
        arr[i] = tok[j];
    }
    std::string instOut;
    if (tok[0] == '7')
    {
        switch (tok[1])
        {
            case '0':   instOut = "jmp";
                        break;

            case '1':   instOut = "jle";
                        break;
            
            case '2':   instOut = "jl";
                        break;

            case '3':   instOut = "je";
                        break;

            case '4':   instOut = "jne";
                        break;

            case '5':   instOut = "jge";
                        break;

            case '6':   instOut = "jg";
                        break;

            default:    std::cout << "illegalop\n";
                        break;
        }
        std::cout << instOut << " ";
        flipEndOther(arr);
        std::cout << "\n";
    }
    
    else if (tok[0] == '8' && tok[1] == '0')
    {
        //instOut = "call\n";
        std::cout << "call ";
        flipEndOther(arr);
        std::cout << "\n";
    }

    else 
    {
        std::cout << "illegalop\n";
    }

    //d::cout << instOut;
}

void tenBytes(/*const*/ char* tok)
{
    std::string instOut;
    char arr [17];
    arr[16] = '\0';
    for (int i = 0, j = 4; i < 16; i++, j++)
    {
        arr[i] = tok[j];
    }
    if (tok[0] == '3' && tok[1] == '0')
    {
        std::cout << "irmovq $";
        flipEndOther(arr);
        std::cout << ", ";
        checkRegisters(0, tok[3]);
    }

    else if (tok[0] == '4' && tok[1] == '0')
    {
        std::cout << "rmmovq ";
        checkRegisters(tok[2], 0);
        std::cout << ", $";
        flipEndOther(arr);
        std::cout << " (";
        checkRegisters(0, tok[3]);
        std::cout << ")";
    }

    else if (tok[0] == '5' && tok[1] == '0')
    {
        std::cout << "mrmovq $";
        flipEndOther(arr);
        std::cout << " (";
        checkRegisters(0, tok[3]);
        std::cout << "), ";
        checkRegisters(tok[2], 0);
    }

    else
    {
        std::cout << "illegalop";
    }
    //std::cout << instOut;
    std::cout << "\n";    
}

void readInst(/*const*/ char* tok, int length)
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
                std::cout << tok << ":    ";
            }

            else
            {
                char char_array [tok.length()];
                std::strcpy(char_array, tok.c_str());
                readInst(char_array, tok.length());
                //readInst(tok.c_str(), tok.length());
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
