#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>

using namespace std;

struct content{
    char info;
    content* next;
    content* prev;
};

typedef content* AdrContent;

struct infotype{
    string fungsi;
    AdrContent data;
    AdrContent Cursor;
};

struct Stack{
    infotype info[999];
    int Top;
};

struct listContent{
    AdrContent First;
    AdrContent Last;
};

struct memoryBlock{
    string Name;
    listContent Data;
    memoryBlock* next;
    memoryBlock* prev;
};

typedef memoryBlock* AdrMemoryBlock;

struct MLL{
    AdrMemoryBlock First;
    AdrMemoryBlock Last;
};

MLL createMLL();
listContent createListContent();
AdrMemoryBlock createMemoryBlock(listContent Data, string Nama);
AdrContent createAdrContent(char info);
Stack createStack();
void addMemoryBlock(MLL &Node, AdrMemoryBlock &P);
void addContent(listContent &Data, AdrContent &Cursor, AdrContent &P);
void removeContent(listContent &Data, AdrContent &Cursor, AdrContent &P);
void removeMemoryBlock(MLL &Node, AdrMemoryBlock &Cursor_Block, AdrMemoryBlock &temp);
void editInput(listContent &Data);
void printListContent(listContent Data, AdrContent cursor_pos);
void printmenu(MLL &Data);
void printMemoryBlock(MLL Data, AdrMemoryBlock Cursor);
void dummy(MLL &Data);
void input_memoryBlock(MLL &Data);
void interactiveInputMemoryBlock(string &result);
void save(string fungsi, AdrContent Data, AdrContent Cursor, Stack &S);
void push(Stack &S, infotype &P);
void pop(Stack &S, infotype &P);
bool isEmpty(Stack S);
void undo(listContent &Data, AdrContent &Cursor, Stack &U, Stack &R);
void redo(listContent &Data, AdrContent &Cursor, Stack &U, Stack &R);


#endif // HEADER_H_INCLUDED
