#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

struct content{
    char info;
    content* next;
    content* prev;
};

typedef content* AdrContent;

struct listContent{
    AdrContent First;
    AdrContent Last;
};

struct infotype{
    string fungsi;
    AdrContent data;
    AdrContent Cursor;
    listContent temp;
};

struct Node {
    infotype data;
    Node* next;
};

struct Stack {
    Node* top;
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
void editInput(listContent &Data, listContent &temp);
void printListContent(listContent Data, AdrContent cursor_pos);
void printmenu(MLL &Data, listContent &temp);
void printMemoryBlock(MLL Data, AdrMemoryBlock Cursor);
void dummy(MLL &Data);
void input_memoryBlock(MLL &Data);
void interactiveInputMemoryBlock(string &result);
void save(string fungsi, AdrContent Data, AdrContent Cursor, listContent temp, Stack &S);
void save(string fungsi, AdrContent Data, AdrContent Cursor, listContent temp, Stack &S);
void push(Stack &S, infotype &P);
void pop(Stack &S, infotype &P);
bool isEmpty(Stack S);
void MoveCursorToUnder(listContent Data, AdrContent &Cursor);
void MoveCursorToUp(listContent Data, AdrContent &Cursor);
void block(listContent &Data, listContent &temp, listContent &simpanremove, AdrContent &Cursor, Stack &U);
void undo(listContent &Data, AdrContent &Cursor, listContent &temp, Stack &U, Stack &R);
void redo(listContent &Data, AdrContent &Cursor, listContent &temp, Stack &U, Stack &R);
void setColor(int textColor, int backgroundColor);
void printBlock(listContent Data, listContent temp, AdrContent Cursor, AdrContent Batas);
void copyContent(listContent Data, listContent &temp, AdrContent Cursor, AdrContent Batas);
void pasteContent(listContent &Data, listContent temp, AdrContent &Cursor);


#endif // HEADER_H_INCLUDED
