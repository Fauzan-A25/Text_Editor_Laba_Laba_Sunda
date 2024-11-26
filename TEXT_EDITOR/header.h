#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>

using namespace std;

struct content{
    char info;
    content* next;
    content* prev;
};

struct memoryBlock{
    content* Data;
    memoryBlock* next;
    memoryBlock* prev;
};

typedef memoryBlock* AdrMemoryBlock;
typedef content* AdrContent;

struct MLL{
    AdrMemoryBlock First;
    AdrMemoryBlock Last;
};

MLL createMLL();
AdrMemoryBlock createMemoryBlock(AdrContent Data);
AdrContent createAdrContent(char info);
void addMemoryBlock(AdrMemoryBlock &Node, AdrMemoryBlock P);
void addContent(AdrContent &Data, AdrContent Q);
void removeBlockcontent(AdrContent &Data, AdrContent &temp);
void removeMemoryBlock(AdrMemoryBlock &Node, AdrMemoryBlock &temp);


#endif // HEADER_H_INCLUDED
