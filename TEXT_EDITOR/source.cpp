#include "header.h"

MLL createMLL() {
    MLL P;
    P.First = nullptr;
    P.Last = nullptr;
    return P;
}
listContent createListContent() {
    listContent P;
    AdrContent U = createAdrContent(27);
    P.First = U;
    P.Last = P.First;
    return P;
}
AdrMemoryBlock createMemoryBlock(listContent Data, string Nama) {
    AdrMemoryBlock P = new memoryBlock;
    P->Name = Nama;
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
Stack createStack() {
    Stack S;
    S.Top = -1;
    return S;
}
void addMemoryBlock(MLL &Node, AdrMemoryBlock &P) {
    if (Node.First == nullptr) { // List kosong
        Node.First = P;
        Node.Last = P;
        P->prev = nullptr;
        P->next = nullptr;
        return;
    }

    AdrMemoryBlock Cursor = Node.First;

    // Sisipkan di awal jika `P->Name` lebih kecil dari `Node.First->Name`
    if (P->Name < Node.First->Name) {
        P->next = Node.First;
        P->prev = nullptr;
        Node.First->prev = P;
        Node.First = P;
        return;
    }

    // Cari posisi yang tepat di tengah
    while (Cursor->next != nullptr && Cursor->next->Name < P->Name) {
        Cursor = Cursor->next;
    }

    // Sisipkan di akhir jika `Cursor` adalah `Node.Last`
    if (Cursor == Node.Last && Cursor->Name <= P->Name) {
        P->prev = Node.Last;
        P->next = nullptr;
        Node.Last->next = P;
        Node.Last = P;
        return;
    }

    // Sisipkan di tengah
    P->next = Cursor->next;
    P->prev = Cursor;
    if (Cursor->next != nullptr) {
        Cursor->next->prev = P;
    }
    Cursor->next = P;
}

void addContent(listContent &Data, AdrContent &Cursor, AdrContent &P) {
    if (Cursor->next != nullptr){
        //insert After
        P->next = Cursor -> next;
        P->prev = Cursor;
        Cursor -> next -> prev = P;
        Cursor -> next = P;
        Cursor = P;
    }else {
        //insertLast
        P->prev =Cursor;
        Cursor->next = P;
        Cursor = Cursor->next;
        Data.Last = Cursor;
    }
}
void removeContent(listContent &Data, AdrContent &Cursor, AdrContent &P) {
    // remove last atau tengah
    if (Cursor == Data.Last) {
        // remove last
        Data.Last = Cursor->prev;
        Data.Last->next = nullptr;
    } else {
        // remove tengah
        Cursor->prev->next = Cursor->next;
        Cursor->next->prev = Cursor->prev;
    }

    P = Cursor;
    Cursor = Cursor->prev;
}

void removeMemoryBlock(MLL &Node, AdrMemoryBlock &Cursor, AdrMemoryBlock &temp) {
    if (Cursor == nullptr) {
        cout << "Memory Kosong" << endl;
    }

    if (Node.First == Node.Last) { // Hanya ada satu node
        temp = Node.First;
        Node.First = Node.Last = Cursor = nullptr;
    } else if (Cursor == Node.First) { // Hapus node pertama
        temp = Node.First;
        Node.First = Node.First->next;
        Node.First->prev = nullptr;
        temp->next = nullptr;
        Cursor = Node.First;
    } else if (Cursor == Node.Last) { // Hapus node terakhir
        temp = Node.Last;
        Node.Last = Node.Last->prev;
        Node.Last->next = nullptr;
        temp->prev = nullptr;
        Cursor = Node.Last;
    } else { // Hapus node di tengah
        temp = Cursor;
        Cursor = Cursor->prev;
        Cursor->next = temp->next;
        temp->next->prev = Cursor;
        temp->next = temp->prev = nullptr;
    }
}


void printListContent(listContent Data, AdrContent cursor_pos)
{
    system("cls");
    AdrContent temp = Data.First->next;
    while (temp != nullptr)
    {
        cout << temp->info;
        if (temp == cursor_pos)
        {
            cout << "|"; // Tampilkan kursor
        }
        temp = temp->next;
    }
    cout << endl;
    cout << "Edit teks (tekan ESC untuk selesai)" << endl;
}

void printmenu(MLL &Data) {
    AdrMemoryBlock Cursor = Data.First;
    char ch;
    bool running = true;

    // Cetak menu sekali di awal
    printMemoryBlock(Data, Cursor);

    while (running) {
        if (_kbhit()) {
            ch = _getch(); // Ambil input karakter

            // Deteksi tombol panah atau angka
            if (ch == 0 || ch == -32) {
                // Tombol panah memberikan dua karakter, 0 atau -32 diikuti kode spesifik
                ch = _getch();
                switch (ch) {
                    case 72: // Panah atas
                        if (Cursor->prev != nullptr) {
                            Cursor = Cursor->prev;
                        }
                        break;
                    case 80: // Panah bawah
                        if (Cursor->next != nullptr) {
                            Cursor = Cursor->next;
                        }
                        break;
                }
                // Cetak ulang menu setelah kursor berpindah
                printMemoryBlock(Data, Cursor);
            } else if (ch == '1') {
                input_memoryBlock(Data);
                if (Cursor == nullptr) {
                    Cursor = Data.First;
                }
                printMemoryBlock(Data, Cursor);
            } else if (ch == '2' && Data.First != nullptr) {
                AdrMemoryBlock Q;
                removeMemoryBlock(Data, Cursor, Q);
                printMemoryBlock(Data, Cursor);
            } else if (ch == 27) {
                running = false;
            } else if (ch == '\r' && Data.First != nullptr) {
                editInput(Cursor->Data);
                printMemoryBlock(Data, Cursor);
            }
        }
    }
}


void printMemoryBlock(MLL Data, AdrMemoryBlock Cursor) {
    ostringstream buffer; // Buffer untuk mencetak menu
    AdrMemoryBlock P = Data.First;
    if (Data.First == nullptr) {
        buffer << "=========================================\n";
        buffer << "|     FILE KOSONG - SILAHKAN TAMBAH     |\n";
        buffer << "-----------------------------------------\n";
    } else {
        buffer << "================================\n";
        buffer << "\u25B6 DATA FILE YANG TERSEDIA \u25B6\n";
        buffer << "--------------------------------\n";
    }

    while (P != nullptr) {
        if (P == Cursor) {
            buffer << "-> ";
        } else {
            buffer << "-  ";
        }
        buffer << P->Name << "\n";
        P = P->next;
    }

    buffer << "\n================================\n";
    buffer << "       TEKAN PILIHAN ANDA \n";
    buffer << "--------------------------------\n";
    buffer << "[ESC]   : Keluar dari program\n";
    buffer << "[1]     : Menambahkan file\n";
    if (Data.First != nullptr) {
        buffer << "[2]     : Menghapus file\n";
    }
    if (Data.First != nullptr) {
        buffer << "[ENTER] : Masuk ke dalam file\n";
    }
    buffer << "--------------------------------\n";

    // Cetak isi buffer sekaligus
    system("cls");
    cout << buffer.str();
}

/** void dummy(MLL &Data) {
    listContent item = createListContent();
    AdrMemoryBlock P = createMemoryBlock(item, "File 1");

} **/

// Fungsi untuk membuat input dengan tampilan menarik
void interactiveInputMemoryBlock(string &result) {
    char ch;
    int cursorPos = 0;          // Posisi kursor dalam string
    int maxLength = 30;         // Panjang maksimal input

    // Input manual dengan efek kursor
    while (true) {
        // Bersihkan layar bagian input
        cout << "\r> "; // Awal baris input
        cout << result; // Tampilkan hasil input
        for (int i = result.length(); i < maxLength; i++) {
            cout << "_"; // Placeholder untuk karakter kosong
        }

        // Tampilkan kursor di posisi yang sesuai
        cout << "\r> "; // Kembalikan kursor ke awal
        for (int i = 0; i < cursorPos; i++) {
            cout << (i < result.length() ? result[i] : '_');
        }

        cout.flush(); // Pastikan output langsung terlihat

        ch = _getch(); // Membaca karakter tanpa Enter

        // Deteksi tombol panah
        if (ch == 0 || ch == 0xE0) { // Tombol spesial seperti panah
            ch = _getch();           // Baca karakter berikutnya
            if (ch == 0x4B && cursorPos > 0) {        // Panah Kiri
                cursorPos--;
            } else if (ch == 0x4D && cursorPos < result.length()) { // Panah Kanan
                cursorPos++;
            }
        } else if (ch == '\r') { // Jika Enter ditekan
            break;
        } else if (ch == '\b') { // Jika Backspace ditekan
            if (cursorPos > 0) {
                result.erase(cursorPos - 1, 1); // Hapus karakter sebelum kursor
                cursorPos--;
            }
        } else if (result.length() < maxLength) { // Batas panjang input
            result.insert(cursorPos, 1, ch); // Sisipkan karakter pada posisi kursor
            cursorPos++;
        }
    }
    cout << endl; // Pindah ke baris berikutnya setelah input selesai
}

void input_memoryBlock(MLL &Data) {
    system("cls");
    string Nama = "";
    listContent item = createListContent();
    cout << "=====================================\n";
    cout << "|   Silakan Masukkan Nama File Anda   |\n";
    cout << "-------------------------------------\n";
    cout << "> ";
    interactiveInputMemoryBlock(Nama);
    AdrMemoryBlock P = createMemoryBlock(item,Nama);
    addMemoryBlock(Data,P);
}

void push(Stack &S, infotype &P) {
    S.Top += 1;
    S.info[S.Top] = P;
}

void pop(Stack &S, infotype &P) {
    if (S.Top != -1) {
        P = S.info[S.Top];
        S.Top -= 1;
    }
}

bool isEmpty(Stack S) {
    return S.Top == -1;
}

void save(string fungsi, AdrContent Data, AdrContent Cursor, Stack &S) {
    infotype P;
    P.data = Data;
    P.Cursor = Cursor;
    P.fungsi = fungsi;
    push(S, P);
}

void undo(listContent &Data, AdrContent &Cursor, Stack &U, Stack &R) {
    infotype P;
    pop(U,P);
    if (P.Cursor == Cursor) {
        if (P.fungsi == "Add") {
            removeContent(Data, Cursor, P.data);
            save("Add", P.data, Cursor, R);
        }else if (P.fungsi == "Remove") {
            addContent(Data, Cursor, P.data);
            save("Remove", P.data, Cursor, R);
        }
    }else if (P.Cursor != nullptr) {
        if (P.fungsi == "Add") {
            removeContent(Data, P.Cursor, P.data);
            save("Add", P.data, P.Cursor, R);
        }else if (P.fungsi == "Remove") {
            addContent(Data, P.Cursor, P.data);
            save("Remove", P.data, P.Cursor, R);
        }
    }
}

void redo(listContent &Data, AdrContent &Cursor, Stack &U, Stack &R) {
    infotype P;
    pop(R,P);
    if (P.Cursor == Cursor) {
        if (P.fungsi == "Remove") {
            removeContent(Data, Cursor, P.data);
            save("Remove", P.data, Cursor, U);
        }else if (P.fungsi == "Add") {
            addContent(Data, Cursor, P.data);
            save("Add", P.data, Cursor, U);
        }
    }else if (P.Cursor != nullptr) {
        if (P.fungsi == "Remove") {
            removeContent(Data, P.Cursor, P.data);
            save("Remove", P.data, P.Cursor, U);
        }else if (P.fungsi == "Add") {
            addContent(Data, P.Cursor, P.data);
            save("Add", P.data, P.Cursor, U);
        }
    }
}
