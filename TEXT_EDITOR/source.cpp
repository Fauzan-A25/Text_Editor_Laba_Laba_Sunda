#include "header.h"

void setColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}
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
    S.top = nullptr;
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


void printListContent(listContent Data, AdrContent cursor_pos, string namaFile)
{
    system("cls");
    cout << "+--------------------------------------------------+" << endl;
    cout << "|             Notepadd Laba-Laba Sunda             |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << namaFile << endl;
    cout << "+--------------------------------------------------+" << endl;

    AdrContent temp = Data.First->next;
    if (cursor_pos == Data.First) {
        cout << "|";
    }
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

void printmenu(MLL &Data, listContent &temp) {
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
                editInput(Cursor->Data, temp, Cursor->Name);
                printMemoryBlock(Data, Cursor);
            }
        }
    }
}


void printMemoryBlock(MLL Data, AdrMemoryBlock Cursor) {
    // Bersihkan layar
    system("cls");

    AdrMemoryBlock P = Data.First;

    // Header
    if (Data.First == nullptr) {
        cout << "=========================================\n";
        cout << "|     FILE KOSONG - SILAHKAN TAMBAH     |\n";
        cout << "-----------------------------------------\n";
    } else {
        cout << "================================\n";
        cout << "\u25B6 DATA FILE YANG TERSEDIA \u25B6\n";
        cout << "--------------------------------\n";
    }

    // Daftar file
    while (P != nullptr) {
        if (P == Cursor) {
            cout << "-> "; // Penanda posisi cursor
        } else {
            cout << "-  ";
        }
        cout << P->Name << "\n";
        P = P->next;
    }

    // Footer
    cout << "\n================================\n";
    cout << "       TEKAN PILIHAN ANDA       \n";
    cout << "--------------------------------\n";
    cout << "[ESC]   : Keluar dari program\n";
    cout << "[1]     : Menambahkan file\n";
    if (Data.First != nullptr) {
        cout << "[2]     : Menghapus file\n";
        cout << "[ENTER] : Masuk ke dalam file\n";
    }
    cout << "--------------------------------\n";
}


/** void dummy(MLL &Data) {
    listContent item = createListContent();
    AdrMemoryBlock P = createMemoryBlock(item, "File 1");

} **/

void input_memoryBlock(MLL &Data) {
    system("cls");
    string Nama = "";
    listContent item = createListContent();
    cout << "=====================================\n";
    cout << "|   Silakan Masukkan Nama File Anda   |\n";
    cout << "-------------------------------------\n";
    cout << "> ";
    getline(cin, Nama);
    AdrMemoryBlock P = createMemoryBlock(item,Nama);
    addMemoryBlock(Data,P);
}

void push(Stack &S, infotype &P) {
    Node* newNode = new Node;
    newNode->data = P;
    newNode->next = S.top;
    S.top = newNode;
}


void pop(Stack &S, infotype &P) {
    if (!isEmpty(S)) {
        Node* temp = S.top;
        P = temp->data;
        S.top = S.top->next;
        delete temp;
    }
}

bool isEmpty(Stack S) {
    return S.top == nullptr;
}


void save(string fungsi, AdrContent Data, AdrContent Cursor, listContent temp, Stack &S) {
    infotype P;
    P.data = Data;
    P.Cursor = Cursor;
    P.fungsi = fungsi;
    P.temp = temp;
    push(S, P);
}

void undo(listContent &Data, AdrContent &Cursor, listContent &temp, Stack &U, Stack &R) {
    infotype P;
    pop(U, P); // Mengambil data terakhir dari stack undo
    Cursor = P.Cursor; // Mengembalikan posisi cursor

    if (P.fungsi == "Add") {
        removeContent(Data, Cursor, P.data);
        save("Add", P.data, Cursor, temp, R);
    }
    else if (P.fungsi == "Remove") {
        addContent(Data, Cursor, P.data);
        save("Remove", P.data, Cursor, temp, R);
    }
    else if (P.fungsi == "RemoveBlock") {
        AdrContent Sementara = Cursor;
        pasteContent(Data, P.temp, Cursor);
        save("RemoveBlock", nullptr, Sementara, P.temp, R);
    }
    else if (P.fungsi == "AddBlock") {
        removeBlock(Data, P.temp, Cursor, P.temp.Last);
        save("AddBlock", nullptr, Cursor, P.temp, R);
    }
    else if (P.fungsi == "Replace") {
        removeBlock(Data, P.temp, Cursor, P.temp.Last);
        save("Replace", nullptr, Cursor, P.temp, R);
        pop(U, P);
        P.Cursor = Cursor;
        pasteContent(Data, P.temp, Cursor);
        save("Replace", nullptr, P.Cursor, P.temp, R);
    }
}

void redo(listContent &Data, AdrContent &Cursor, listContent &temp, Stack &U, Stack &R) {
    infotype P;
    pop(R,P);
    Cursor = P.Cursor;
    if (P.fungsi == "Remove") {
        removeContent(Data, Cursor, P.data);
        save("Remove", P.data, Cursor, temp, U);
    }else if (P.fungsi == "Add") {
        addContent(Data, Cursor, P.data);
        save("Add", P.data, Cursor, temp, U);
    }else if (P.fungsi == "RemoveBlock") {
        removeBlock(Data, P.temp, Cursor, P.temp.Last);
        save("RemoveBlock", nullptr, Cursor, P.temp, U);
    }else if (P.fungsi == "AddBlock") {
        AdrContent Sementara = Cursor;
        pasteContent(Data, P.temp, Cursor);
        save("AddBlock", nullptr, Sementara, P.temp, U);
    }else if (P.fungsi == "Replace") {
        removeBlock(Data, P.temp, Cursor, P.temp.Last);
        save("Replace", nullptr, Cursor, P.temp, U);
        pop(R, P);
        P.Cursor = Cursor;
        pasteContent(Data, P.temp, Cursor);
        save("Replace", nullptr, P.Cursor, P.temp, U);
    }
}

void MoveCursorToUnder(listContent Data, AdrContent &Cursor) {
    if (Cursor->next != nullptr) {
        if (Cursor->info != '\n' || Cursor->next->info != '\n') {
            // Menentukan awal baris saat ini dan menghitung jarak kursor ke awal baris
            AdrContent current_line_start = Cursor;
            int jarak_cursor_ke_awal_baris = 0;

            if (current_line_start->info != '\n' && current_line_start->info != 27) {
                while (current_line_start->info != 27 && current_line_start->info != '\n') {
                    current_line_start = current_line_start->prev;
                    jarak_cursor_ke_awal_baris++;
                }
            }

            // Menentukan akhir baris saat ini
            AdrContent current_line_end = Cursor->next;
            while (current_line_end->next != nullptr && current_line_end->info != '\n') {
                current_line_end = current_line_end->next;
            }

            // Menentukan awal baris berikutnya
            if (current_line_end->next != nullptr) {
                if (jarak_cursor_ke_awal_baris - 1 < 0) {
                    Cursor = current_line_end;
                }else {
                    if (current_line_end->next->info != '\n') {
                        AdrContent target = current_line_end->next;
                        for (int i = 0; i < jarak_cursor_ke_awal_baris-1 && target->next != nullptr && target->info != '\n'; i++) {
                            target = target->next;
                        }
                        Cursor = target;
                    }else {
                        Cursor = current_line_end;
                    }
                }
            } else if (current_line_end->info == '\n') {
                Cursor = current_line_end;
            }
        } else {
            Cursor = Cursor->next;
        }
    }
}

void MoveCursorToUp(listContent Data, AdrContent &Cursor) {
    if (Cursor->info != 27) { // Pastikan kursor tidak berada di awal file
        // Menentukan awal baris saat ini (node '\n' sebelumnya atau char 27)
        AdrContent current_line_start = Cursor;
        int jarak_cursor_ke_awal_baris = 0;

        // Cari awal baris saat ini sambil menghitung jarak kursor ke awal baris
        while (current_line_start->prev->info != 27 && current_line_start->info != '\n') {
            current_line_start = current_line_start->prev;
            jarak_cursor_ke_awal_baris++;
        }

        // Menentukan akhir baris sebelumnya (node '\n' sebelum current_line_start)
        AdrContent prev_line_end = current_line_start->prev;

        // Pastikan masih ada baris sebelumnya untuk berpindah
        if (prev_line_end->info != 27) {
            // Cari awal baris sebelumnya
            while (prev_line_end->prev != nullptr &&
                   prev_line_end->info != 27 &&
                   prev_line_end->info != '\n') {
                prev_line_end = prev_line_end->prev;
            }

            // Pindahkan kursor ke posisi horizontal yang sama pada baris sebelumnya
            AdrContent target_pos = prev_line_end;
            for (int i = 0; i < jarak_cursor_ke_awal_baris && target_pos->next->info != '\n'; i++) {
                target_pos = target_pos->next;
            }
            Cursor = target_pos;
        }
    }
}

void removeBlock(listContent &Data, listContent &temp, AdrContent &Cursor, AdrContent Batas) {
    AdrContent sementara = Cursor->next->prev;
    AdrContent start = Cursor->next; // Awal blok yang dihapus
    AdrContent end = Batas;   // Akhir blok yang dihapus (sebelum Batas)

    // Hubungkan `Cursor` ke elemen setelah `Batas`
    if (Batas->next != nullptr) {
        Batas->next->prev = Cursor->next->prev;
        Cursor->next = Batas->next;
    } else {
        Data.Last = Cursor->next->prev;
        Cursor->next->prev->next = nullptr;
    }

    // Pisahkan blok dari `Data`
    start->prev = nullptr;
    end->next = nullptr;

    temp = createListContent();
    temp.Last->next = start;
    start->prev = temp.Last;
    temp.Last = end;
    Cursor = sementara;
}


void block(listContent &Data, listContent &temp, AdrContent &Cursor, Stack &U, Stack &R, string namaFile) {
    AdrContent Cursor_Left = nullptr;
    AdrContent Cursor_Right = nullptr;
    char ch;

    // Menentukan posisi awal untuk Cursor_Left
    if (Cursor->next == nullptr) {
        Cursor_Right = Cursor;
        Cursor = Cursor->prev;
    }else {
        Cursor_Left = Cursor;
        Cursor = Cursor->next;
    }

    if (Cursor_Left != nullptr) {
        printBlock(Data,temp, Cursor_Left, Cursor, namaFile);
    }else {
        printBlock(Data,temp, Cursor, Cursor_Right, namaFile);
    }

    while (true) {
        if (_kbhit()) {
            ch = _getch();

            if (Cursor_Left != nullptr) {
                if (ch == 75) { // Panah kiri
                    if (Cursor->prev == Cursor_Left && Cursor_Left->prev != nullptr) {
                        Cursor = Cursor_Left->prev;
                        Cursor_Right = Cursor_Left;
                        Cursor_Left = nullptr;
                    } else if (Cursor->prev != nullptr) {
                        Cursor = Cursor->prev;
                    }
                }
                else if (ch == 77 && Cursor->next != nullptr) { // Panah kanan
                    Cursor = Cursor->next;
                }
                else if (ch == 72) { // Panah atas
                    AdrContent P = Cursor;
                    MoveCursorToUp(Data, Cursor);
                    if (Cursor == P) {
                        if (Cursor_Left == Data.First) {
                            Cursor = Cursor_Left->next;
                        } else {
                            Cursor = Data.First;
                            Cursor_Right = Cursor_Left;
                            Cursor_Left = nullptr;
                        }
                    } else {
                        P = Cursor;
                        while (P->info != '\n' && P != Cursor_Left) {
                            P = P->next;
                        }
                        if (P != Cursor_Left) {
                            P = P->next;
                            while (P->info != '\n' && P != Cursor_Left) {
                                P = P->next;
                            }
                            if (P == Cursor_Left) {
                                Cursor_Right = Cursor_Left;
                                Cursor_Left = nullptr;
                            }
                        }else {
                            if (Cursor == Cursor_Left) {
                                Cursor = Cursor->next;
                            }
                            Cursor_Right = Cursor_Left;
                            Cursor_Left = nullptr;
                        }
                    }
                }
                else if (ch == 80) { // Panah bawah
                    AdrContent P = Cursor;
                    MoveCursorToUnder(Data, Cursor);
                    if (P == Cursor) {
                        Cursor = Data.Last;
                    }
                }
                else if (ch == 7) {
                    copyContent(Data, temp, Cursor_Left, Cursor);
                }
            } else {
                if (ch == 75 && Cursor->prev != nullptr) { // Panah kiri
                    Cursor = Cursor->prev;
                }
                else if (ch == 77 && Cursor->next != nullptr) { // Panah kanan
                    if (Cursor->next == Cursor_Right && Cursor_Right->next != nullptr) {
                        Cursor = Cursor_Right->next;
                        Cursor_Left = Cursor_Right;
                        Cursor_Right = nullptr;
                    } else if (Cursor->next->next != nullptr) {
                        Cursor = Cursor->next;
                    }
                }
                else if (ch == 72) { // Panah atas
                    AdrContent P = Cursor;
                    MoveCursorToUp(Data, Cursor);
                    if (Cursor == P) {
                        Cursor = Data.First;
                    }
                }
                else if (ch == 80) { // Panah bawah
                    AdrContent P = Cursor;
                    MoveCursorToUnder(Data, Cursor);
                    if (P == Cursor) {
                        Cursor = Data.Last;
                        if (Cursor == Cursor_Right) {
                            Cursor = Cursor->prev;
                        }else {
                            Cursor_Left = Cursor_Right;
                            Cursor_Right = nullptr;
                        }
                    }else {
                        P = Cursor;
                        while (P != Cursor_Right && P->info != '\n') {
                            P = P->prev;
                        }
                        if (P != Cursor_Right) {
                            while (P != Cursor_Right && P->info != '\n') {
                                P = P->prev;
                            }
                            if (P == Cursor_Right) {
                                Cursor_Left = Cursor_Right;
                                Cursor_Right = nullptr;
                            }
                        } else {
                            if (Cursor_Right == Data.Last) {
                                Cursor = Cursor_Right->prev;
                            }else if (Cursor == Cursor_Right) {
                                Cursor = Cursor->next;
                                Cursor_Left = Cursor_Right;
                                Cursor_Right = nullptr;
                            }else {
                                Cursor_Left = Cursor_Right;
                                Cursor_Right = nullptr;
                            }
                        }
                    }
                }
                else if (ch == 7) {
                    copyContent(Data, temp, Cursor, Cursor_Right);
                }
            }
            if (ch == 16 && temp.First->next != nullptr) {
                listContent P = duplicateList(temp);
                if (Cursor_Left != nullptr) {
                    removeBlock(Data, temp, Cursor_Left, Cursor);
                    Cursor = Cursor_Left;
                    save("Replace", nullptr, Cursor, temp, U);
                    AdrContent sementara = Cursor;
                    temp = duplicateList(P);
                    pasteContent(Data, temp, Cursor);
                    save("Replace", nullptr, sementara, temp, U);
                }else {
                    removeBlock(Data, temp, Cursor, Cursor_Right);
                    save("Replace", nullptr, Cursor, temp, U);
                    AdrContent sementara = Cursor;
                    temp = duplicateList(P);
                    pasteContent(Data, temp, Cursor);
                    save("Replace", nullptr, sementara, temp, U);
                }
                temp = P;
                R.top = nullptr;
                return;
            }else if (ch == 27) {
                return;
            }else if (ch == '\b') {
                if (Cursor_Left != nullptr) {
                    removeBlock(Data, temp, Cursor_Left, Cursor);
                    Cursor = Cursor_Left;
                }else {
                    removeBlock(Data, temp, Cursor, Cursor_Right);
                }
                save("RemoveBlock", nullptr, Cursor, temp, U);
                R.top = nullptr;
                return;
            }
            if (Cursor_Left != nullptr) {
                printBlock(Data, temp, Cursor_Left, Cursor, namaFile);
            }else {
                printBlock(Data, temp, Cursor, Cursor_Right, namaFile);
            }
        }
    }
}


void printBlock(listContent Data, listContent copyan, AdrContent Cursor, AdrContent Batas, string namaFile) {
    system("cls");
    cout << "+--------------------------------------------------+" << endl;
    cout << "|                Notepadd Laba-Laba Sunda          |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << namaFile << endl;
    cout << "+--------------------------------------------------+" << endl;
    AdrContent temp = Data.First;
    AdrContent P = copyan.First->next;
    while (temp != nullptr)
    {
        if (temp->info != 27) {
            cout << temp->info;
        }
        if (temp == Cursor)
        {
            cout << "[";
            setColor(0, 7);
        }else if (temp == Batas) {
            setColor(7, 0);
            cout << "]";
        }
        temp = temp->next;
    }
    cout << endl;
    cout << "Edit teks (tekan ESC untuk selesai)" << endl;
    cout << "list yang di copy: " << endl;

    while (P != nullptr) {
        cout << P->info;
        P = P->next;
    }
    cout << endl;
}

void copyContent(listContent Data, listContent &temp, AdrContent Cursor, AdrContent Batas) {
    temp = createListContent();
    // Validasi parameter penting
    if (Cursor == NULL || Batas == NULL || Cursor->next == NULL) {
        return; // Tidak ada elemen untuk disalin
    }

    AdrContent P = Cursor->next;
    while (P != NULL && P != Batas) {
        AdrContent Q = createAdrContent(P->info);

        // Menambahkan node baru ke temp (diasumsikan temp.Last selalu valid)
        temp.Last->next = Q;
        Q->prev = temp.Last;
        temp.Last = Q;

        P = P->next;
    }
    AdrContent Q = createAdrContent(P->info);

    // Menambahkan node baru ke temp (diasumsikan temp.Last selalu valid)
    temp.Last->next = Q;
    Q->prev = temp.Last;
    temp.Last = Q;
    temp.Last->next = nullptr;
}


void pasteContent(listContent &Data, listContent &temp, AdrContent &Cursor) {
    // Duplikasi list temp agar node-node baru tidak terhubung ke temp asli
    listContent tempCopy = temp;

    // Sambungkan tempCopy ke Data
    if (Cursor->next != nullptr) {
        tempCopy.Last->next = Cursor->next;
        Cursor->next->prev = tempCopy.Last;
    } else {
        Data.Last = tempCopy.Last;
    }

    tempCopy.First->next->prev = Cursor;
    Cursor->next = tempCopy.First->next;

    // Perbarui posisi Cursor ke elemen terakhir tempCopy
    Cursor = tempCopy.Last;
}


listContent duplicateList(listContent Data) {
    listContent temp = createListContent(); // Buat list baru dengan First yang pasti ada
    AdrContent P = Data.First->next;        // Mulai dari elemen pertama (bukan node dummy)
    AdrContent Q = temp.First;              // Mulai dari node dummy pada temp

    while (P != nullptr) {
        AdrContent newNode = createAdrContent(P->info); // Buat node baru dengan info dari P
        newNode->prev = Q;            // Sambungkan node baru ke akhir list temp
        Q->next = newNode;            // Sambungkan node sebelumnya (Q) ke node baru
        Q = newNode;                  // Pindahkan Q ke node baru
        P = P->next;                  // Pindah ke elemen berikutnya di Data
    }

    temp.Last = Q; // Perbarui Last untuk menunjuk ke elemen terakhir
    return temp;   // Kembalikan list duplikat
}

