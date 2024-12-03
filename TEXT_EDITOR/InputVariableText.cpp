#include "header.h"

void editInput(listContent &Data)
{
    Stack U = createStack();
    Stack R = createStack();
    AdrContent cursor_pos = Data.Last; // Posisi kursor (indeks absolut)
    char ch;                      // Menyimpan karakter input sementara
    system("cls");
    printListContent(Data, cursor_pos);
    while (true)
    {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 27)
            {
                break;
            }
            else if (ch == -32)
            {
                ch = _getch();
                if (ch == 75 && cursor_pos->prev != nullptr)
                { // Panah kiri
                    cursor_pos = cursor_pos->prev;
                }
                else if (ch == 77 && cursor_pos->next != nullptr)
                { // Panah kanan
                    cursor_pos = cursor_pos->next;
                }
                else if (ch == 72)
                { // Panah atas
                    if (cursor_pos != nullptr)
                    {
                        // Cari akhir baris saat ini (node '\n' sebelumnya)
                        AdrContent current_line_start = cursor_pos;
                        while (current_line_start->prev != nullptr && current_line_start->prev->info != '\n')
                        {
                            current_line_start = current_line_start->prev;
                        }

                        // Cari akhir baris sebelumnya (node '\n' sebelum current_line_start)
                        AdrContent prev_line_end = current_line_start->prev;
                        if (prev_line_end != nullptr)
                        {
                            AdrContent prev_line_start = prev_line_end;
                            while (prev_line_start->prev != nullptr && prev_line_start->prev->info != '\n')
                            {
                                prev_line_start = prev_line_start->prev;
                            }

                            // Pindahkan kursor ke posisi horizontal yang sama di baris sebelumnya
                            int horizontal_offset = 0;
                            AdrContent temp = current_line_start;
                            while (temp != cursor_pos && temp != nullptr && temp->info != '\n')
                            {
                                horizontal_offset++;
                                temp = temp->next;
                            }

                            AdrContent target = prev_line_start;
                            for (int i = 0; i < horizontal_offset && target != prev_line_end; i++)
                            {
                                target = target->next;
                            }

                            cursor_pos = target; // Perbarui posisi kursor
                        }
                    }
                }
                else if (ch == 80)
                { // Panah bawah
                    if (cursor_pos != nullptr)
                    {
                        // Cari akhir baris saat ini (node '\n' berikutnya)
                        AdrContent current_line_end = cursor_pos;
                        while (current_line_end != nullptr && current_line_end->info != '\n')
                        {
                            current_line_end = current_line_end->next;
                        }

                        // Cari awal baris berikutnya (node pertama setelah current_line_end)
                        if (current_line_end != nullptr && current_line_end->next != nullptr)
                        {
                            AdrContent next_line_start = current_line_end->next;

                            // Pindahkan kursor ke posisi horizontal yang sama di baris berikutnya
                            int horizontal_offset = 0;
                            AdrContent temp = cursor_pos;
                            while (temp != nullptr && temp->info != '\n')
                            {
                                horizontal_offset++;
                                temp = temp->prev;
                            }

                            AdrContent target = next_line_start;
                            for (int i = 0; i < horizontal_offset && target != nullptr && target->info != '\n'; i++)
                            {
                                target = target->next;
                            }

                            cursor_pos = target; // Perbarui posisi kursor
                        }
                    }
                }
            }
            else if (ch == '\b')
            { // Backspace
                if (cursor_pos->info != 27)
                {
                    R.Top = -1;
                    AdrContent P;
                    removeContent(Data, cursor_pos, P);
                    save("Remove", P,cursor_pos, U);
                }
            }
            else if (ch == '\r')
            {
                R.Top = -1;
                AdrContent O = createAdrContent('\n');
                addContent(Data, cursor_pos, O);
                save("Add", O, cursor_pos, U);
            }
            else if (ch == 96) {
                if (!isEmpty(U)) {
                    undo(Data, cursor_pos, U, R);
                }
            }
            else if (ch == 0 || ch == 224) {
                ch = _getch();
                if (ch == 62) {
                    if (!isEmpty(R)) {
                        redo(Data, cursor_pos, U, R);
                    }
                }
            }
            else
            {
                R.Top = -1;
                AdrContent O = createAdrContent(ch);
                addContent(Data, cursor_pos, O);
                save("Add", O, cursor_pos, U);
            }
            printListContent(Data, cursor_pos);
        }
    }
}
