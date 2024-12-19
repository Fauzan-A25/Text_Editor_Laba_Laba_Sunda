#include "header.h"

void editInput(listContent &Data, listContent &temp, string namaFile)
{
    Stack U = createStack();
    Stack R = createStack();
    AdrContent cursor_pos = Data.Last;
    namaFile = "   " + namaFile + "     Edit   ";
    char ch;
    system("cls");
    printListContent(Data, cursor_pos, namaFile);
    while (true)
    {
        if (_kbhit())
        {
            ch = getch();
            if (ch == 27)
            {
                break;
            }
            else if (ch == -32)
            {
                ch = getch();
                if (ch == 75 && cursor_pos->prev != nullptr)
                { // Panah kiri
                    cursor_pos = cursor_pos->prev;
                }
                else if (ch == 77 && cursor_pos->next != nullptr)
                { // Panah kanan
                    cursor_pos = cursor_pos->next;
                }
                else if (ch == 72) // Panah atas
                {
                    MoveCursorToUp(Data, cursor_pos);
                }
                else if (ch == 80)
                { // Panah bawah
                    MoveCursorToUnder(Data, cursor_pos);
                }
            }
            else if (ch == '\b')
            { // Backspace
                if (cursor_pos->info != 27)
                {
                    R.top = nullptr;
                    AdrContent P;
                    removeContent(Data, cursor_pos, P);
                    save("Remove", P,cursor_pos, temp, U);
                }
            }
            else if (ch == '\r')
            {
                R.top = nullptr;
                AdrContent O = createAdrContent('\n');
                addContent(Data, cursor_pos, O);
                save("Add", O, cursor_pos, temp, U);
            }
            else if (ch == 26) {
                if (!isEmpty(U)) {
                    undo(Data, cursor_pos, temp, U, R);
                }
            }
            else if (ch == 25) {
                if (!isEmpty(R)) {
                    redo(Data, cursor_pos, temp, U, R);
                }
            }
            else if (ch == 2) {
                if (cursor_pos->next != nullptr || cursor_pos->prev != nullptr) {
                    block(Data,temp, cursor_pos,U,R, namaFile);
                }
            }
            else if (ch == 16) {
                R.top = nullptr;
                listContent P = duplicateList(temp);
                AdrContent sementaraCursor = cursor_pos;
                pasteContent(Data, temp, cursor_pos);
                save("AddBlock", nullptr, sementaraCursor, temp, U);
                temp = P;
            }
            else
            {
                R.top = nullptr;
                AdrContent O = createAdrContent(ch);
                addContent(Data, cursor_pos, O);
                save("Add", O, cursor_pos, temp ,U);
            }
            printListContent(Data, cursor_pos, namaFile);
        }
    }
}
