#include "header.h"

MLL createMLL() {
    MLL P;
    P.First = nullptr;
    P.Last = nullptr;
    return P;
}
AdrMemoryBlock createMemoryBlock(AdrContent Data) {
    AdrMemoryBlock P = new memoryBlock;
    P->Data = Data;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}
AdrContent createAdrContent(char info) {
    AdrContent Q = new content;
    Q->info = info;
    Q->next = nullptr;
    Q->prev = nullptr;
    return Q;
}
void addMemoryBlock(MLL &Node, AdrMemoryBlock P) {
    if (Node != nullptr) {
        P->prev = Node.Last;
        Node.Last->next = P;
        Node.Last = P;
    }else {
        Node.First = P;
        Node.Last = P;
    }
}
void addContent(AdrContent &Data, AdrContent Q) {

}
void removeBlockcontent(AdrContent &Data, AdrContent &temp);
void removeMemoryBlock(AdrMemoryBlock &Node, AdrMemoryBlock &temp);
