/*
 * Y86 Disassembler
 * 
 * Author: Justin Reeves
 * Date: 2/6/2019
 */


#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>

//Flips the endianness of passed addresses or destinations
void flipEndOther(char *tok)
{
   for (int i = 0, j = 15; i < 8; i = i + 2, j = j - 2)     //i tracks the lower bytes, j tracks the upper
    {
        char temp = tok[i];
        tok[i] = tok[j - 1];
        tok[j - 1] = temp;
        temp = tok[i + 1];
        tok[i + 1] = tok[j];
        tok[j] = temp;
    }

    int k = 0;                                              //Used to count number of leading 0s
    while (tok[k] == '0')
    {
        k++;
    }

    if (k == 16)
    {
        std::cout << "0x0";                                 //Prints 0x0 if all numbers in value are 0s
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

//Flips the endianness of a passed quad value
void flipEndQuad(char *tok)
{
    for (int i = 0, j = 15; i < 8; i = i + 2, j = j - 2)    //i tracks the lower bytes, j tracks the upper
    {
        char temp = tok[i];
        tok[i] = tok[j - 1];
        tok[j - 1] = temp;
        temp = tok[i + 1];
        tok[i + 1] = tok[j];
        tok[j] = temp;
    }
}

//Compares a passed character to ASCII values of register identifiers, printing the name of the register
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

//Checks the passed values to determine which to fetch a register ID for and in what order
void checkRegisters(char a, char b)
{
    if (a != 0 && b != 0)
    {
        getRegister(b);
        std::cout << ", ";                      //Places a comma between registers when both need to be fetched
        getRegister(a);
    }

    else if (a != 0 && b == 0)
    {
        getRegister(a);
    }

    else if (a == 0 && b != 0)
    {
        getRegister(b);
    }

    else 
    {
        std::cout<< "ERROR\n";
    }
}

//Determines if an instruction that is 1 byte long is a halt, nop, or return
void oneByte(char* tok)
{
    std::string instOut;
    if (tok[0] == '0' && tok[1] == '0')
    {
        instOut = "halt\n";                     //Prints the data for a HALT code
    }

    else if (tok[0] == '1' && tok[1] == '0')
    {
        instOut = "nop\n";                      //Prints the data for a no operation
    }

    else if (tok[0] == '9' && tok[1] == '0')
    {
        instOut = "ret\n";                      //Prints the data for a return
    }

    else
    {
        instOut = "illegalop\n";
    }

    std::cout << instOut;
}

//Determines if an instruction that is 2 bytes long is a rrmovq, conditional move, operation, push, or pop
void twoBytes(char* tok)
{
    std::string instOut;
    if (tok[0] == '2')
    {
        switch (tok[1])
        {
            case '0':   instOut = "rrmovq";         //Prints the data for a register move
                        break;

            case '1':   instOut = "cmovle";         //Prints the data for a move less than or equal
                        break;

            case '2':   instOut = "cmovl";          //Prints the data for a move less than
                        break;

            case '3':   instOut = "cmove";          //Prints the data for a move equal
                        break;
        
            case '4':   instOut = "cmovne";         //Prints the data for a move not equal
                        break;

            case '5':   instOut = "cmovge";         //Prints the data for a move greater than or equal
                        break;

            case '6':   instOut = "cmovg";          //Prints the data for a move greater than
                        break;

            default:    std::cout << "illegalop";
                        break;
        }
        std::cout << instOut << " ";
        checkRegisters(tok[3], tok[2]);
    }

    else if (tok[0] == '6')
    {
        switch (tok[1])
        {
            case '0':   instOut = "addq ";          //Prints the data for an addition operation
                        break;

            case '1':   instOut = "subq ";          //Prints the data for a subtraction operation
                        break;

            case '2':   instOut = "andq ";          //Prints the data for an and operation
                        break;

            case '3':   instOut = "xorq ";          //Prints the data for an exclusive or operation
                        break;

            default:    std::cout << "illegalop";
                        break;
        }
        std::cout << instOut << " ";
        checkRegisters(tok[3], tok[2]);
    }

    else if ((tok[0] == 'A' || tok[0] == 'a') && tok[1] == '0')
    {
        std::cout << "pushq ";
        checkRegisters(tok[2], 0);
    }

    else if ((tok[0] == 'B' || tok[0] == 'b') && tok[1] == '0')
    {
        std::cout << "popq ";
        checkRegisters(tok[2], 0);
    }

    else
    {
        std::cout << "illegalop";
    }

    std::cout << "\n";
}

//Prints the quad, flipping the endianness of the passed value
void eightBytes(char* tok)
{
    std::string instOut = ".quad ";
    char arr [16];
    arr[16] = '\0';

    for (int i = 0; i < 16; i++)
    {
        arr[i] = tok[i];                            //Copies the value into a new array for flipping
    }

    flipEndQuad(arr);
    std::cout << ".quad 0x";
    std::cout << arr << "\n";
}

//Determines if an instruction that is 9 bytes long is a jump, jump conditional, or a call
void nineBytes(char* tok)
{
    std::string instOut;
    char arr [17];
    arr[16] = '\0';

    for (int i = 0, j = 2; i < 16; i++, j++)
    {
        arr[i] = tok[j];                            //Copies the address/destination value for flipping
    }

    if (tok[0] == '7')
    {
        switch (tok[1])
        {
            case '0':   instOut = "jmp";            //Prints data for a jump always
                        break;

            case '1':   instOut = "jle";            //Prints data for a jump less than or equal
                        break;
            
            case '2':   instOut = "jl";             //Prints data for a jump less than
                        break;

            case '3':   instOut = "je";             //Prints data for a jump equal
                        break;

            case '4':   instOut = "jne";            //Prints data for a jump not equal
                        break;

            case '5':   instOut = "jge";            //Prints data for a jump greater than or equal
                        break;

            case '6':   instOut = "jg";             //Prints data for a jump greater than
                        break;

            default:    std::cout << "illegalop\n";
                        break;
        }
        std::cout << instOut << " ";
        flipEndOther(arr);
    }
    
    else if (tok[0] == '8' && tok[1] == '0')        //Prints data for a call
    {
        std::cout << "call ";
        flipEndOther(arr);
    }

    else 
    {
        std::cout << "illegalop";
    }

    std::cout << "\n";
}

//Determines if an instruction that is 10 bytes long is an irmovq, rmmovq, or mrmovq
void tenBytes(char* tok)
{
    std::string instOut;
    char arr [17];
    arr[16] = '\0';
    
    for (int i = 0, j = 4; i < 16; i++, j++)
    {
        arr[i] = tok[j];                        //Copies the address/destination value for flipping
    }

    if (tok[0] == '3' && tok[1] == '0')         //Prints data for irmovq
    {
        std::cout << "irmovq $";
        flipEndOther(arr);
        std::cout << ", ";
        checkRegisters(0, tok[3]);
    }

    else if (tok[0] == '4' && tok[1] == '0')    //Prints data for rmmovq
    {
        std::cout << "rmmovq ";
        checkRegisters(tok[2], 0);
        std::cout << ", $";
        flipEndOther(arr);
        std::cout << " (";
        checkRegisters(0, tok[3]);
        std::cout << ")";
    }

    else if (tok[0] == '5' && tok[1] == '0')    //Prints data for mrmovq
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
    std::cout << "\n";    
}

//Reads in the length in bytes of each instruction, calls the appropriate function
void readInst(char* tok, int length)
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

    switch (bytes)
    {
        case 0: std::cout << "\n";  //Prints a newline if the instruction is empty
                break;

        case 1: oneByte(tok);       //Calls oneByte for an instruction 1 byte long
                break;

        case 2: twoBytes(tok);      //Calls twoBytes for an instruction 2 bytes long
                break;

        case 8: eightBytes(tok);    //Calls eightBytes for an instruction 8 bytes long
                break;

        case 9: nineBytes(tok);     //Calls nineBytes for an instruction 9 bytes long
                break;

        case 10:tenBytes(tok);      //Calls tenBytes for an instruction 10 bytes long
                break;

        default:std::cout << "An error occured while converting byte to instruction\n"; 
                break;
    }
}

//Begins disassembly by splitting the address from the instruction and calling readInst
void diss(std::ifstream &r)
{
    std::string line;
    while(r)
    {
        std::string delim = ": ";
        std::string tok;
        std::getline(r, line);
        std::istringstream stm(line);
        int lineNum = 1;                            //Tracks which line is address and which is instruction
        while(std::getline(stm, tok, ':'))          //Splits at delim :
        {
            if (lineNum % 2 == 0)
            {
                tok = tok.substr(1, tok.length());  //Removes the leading space from instructions
            }

            if (tok.at(1) == 'x' || tok.at(1) == 'X')
            {
                std::cout << tok << ":    ";        //Prints the memory address
            }

            else
            {
                char char_array [tok.length()];
                std::strcpy(char_array, tok.c_str());
                readInst(char_array, tok.length()); //Calls readInst on y86 instructions
            }
            lineNum++;
        }
    }
}

//Reads in a file from command line arguments. Program will stop if file name is not valid.
int main(int argc, char * argv[])
{
    std::ifstream reader;                           //Open an ifstream
    reader.open(argv[1]);                           //Try to open the file passed as command line argument
    if (!reader)                                    //Check if file was able to be opened
    {
        std::cerr << "Unable to open file, check the filename.\n";
        exit(1);                                    //System will stop if file cannot be found
    }
    diss(reader);                                   //Call the disassembly function
    reader.close();                                 //Close the ifstream before exiting
}
