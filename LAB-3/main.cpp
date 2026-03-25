#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;
};

void visitPage(Page*& head, Page*& tail, Page*& current, string url, string title, int h, int m, int s) {
    Page* newPage = new Page();
    newPage->url = url;
    newPage->title = title;
    newPage->accessTime[0] = h;
    newPage->accessTime[1] = m;
    newPage->next = nullptr;
    newPage->prev = nullptr;

    if (head == nullptr) {
        head = newPage;
        tail = newPage;
        current = newPage;
    } else {
        tail->next = newPage;
        newPage->prev = tail;
        tail = newPage;
        current = newPage;
    }
    cout << ">> Sayfa ziyaret edildi: " << title << "\n";
}

void goBack(Page*& current) {
    if (current != nullptr && current->prev != nullptr) {
        current = current->prev;
        cout << ">> Geri gidildi. Su anki sayfa: " << current->title << "\n";
    } else {
        cout << ">> Hata: Geri gidilecek bir sayfa yok!\n";
    }
}

void goForward(Page*& current) {
    if (current != nullptr && current->next != nullptr) {
        current = current->next;
        cout << ">> Ileri gidildi. Su anki sayfa: " << current->title << "\n";
    } else {
        cout << ">> Hata: Ileri gidilecek bir sayfa yok!\n";
    }
}

void deleteCurrent(Page*& head, Page*& tail, Page*& current) {
    if (current == nullptr) {
        cout << ">> Hata: Silinecek sayfa yok!\n";
        return;
    }

    Page* toDelete = current;

    if (toDelete->prev != nullptr) {
        toDelete->prev->next = toDelete->next;
    } else {
        head = toDelete->next;
    }

    if (toDelete->next != nullptr) {
        toDelete->next->prev = toDelete->prev;
    } else {
        
    }

    if (toDelete->prev != nullptr) {
        current = toDelete->prev;
    } else {
        current = toDelete->next;
    }

    cout << ">> '" << toDelete->title << "' gecmisten silindi.\n";
    delete toDelete;
}

void displayHistory(Page* head, Page* current) {
    if (head == nullptr) {
        cout << ">> Tarayici gecmisi bos.\n";
        return;
    }

    cout << "\n--- Tarayici Gecmisi ---\n";
    Page* temp = head;
    while (temp != nullptr) {
        if (temp == current) {
            cout << " [SU AN] -> ";
        } else {
            cout << "            ";
        }

        cout << temp->title << " (" << temp->url << ") - Ziyaret Saati: ";
        
        for (int i = 0; i < 3; i++) {
            if (temp->accessTime[i] < 10) cout << "0";
            cout << temp->accessTime[i];
        }
        cout << "\n";
        temp = temp->next;
    }
    cout << "-------------\n";
}

void freeMemory(Page*& head) {
    Page* temp = head;
    while (temp != nullptr) {
        Page* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    head = nullptr;
    cout << ">> Hafiza temizlendi.\n";
}

int main() {
    Page* head = nullptr;
    Page* tail = nullptr;
    Page* current = nullptr;
    int choice;

    do {
        cout << "\n TARAYICI MENU \n";
        cout << "1. Yeni Sayfa Ziyaret Et\n";
        cout << "2. Geri Git\n";
        cout << "3. Ileri Git\n";
        cout << "4. Su Anki Sayfayi Sil\n";
        cout << "5. Gecmisi Goster\n";
        cout << "6. Cikis\n";
        cout << "Seciminiz: ";
        cin >> choice;

        if (choice == 1) {
            string url, title;
            int h, m, s;
            cout << "URL girin: ";
            cin >> url;
            cin.ignore();
            cout << "Baslik girin: ";
            getline(cin, title);
            cout << "Saati girin: ";
            cin >> h >> m >> s;
            visitPage(head, tail, current, url, title, h, m, s);
        } else if (choice == 2) {
            goBack(current);
        } else if (choice == 3) {
            goForward(current);
        } else if (choice == 4) {
            deleteCurrent(head, tail, current);
        } else if (choice == 5) {
            displayHistory(head, current);
        } else if (choice != 6) {
            cout << "Gecersiz secim!\n";
        }
    } while (choice != 6);

    freeMemory(head); 
    
    return 0;
}