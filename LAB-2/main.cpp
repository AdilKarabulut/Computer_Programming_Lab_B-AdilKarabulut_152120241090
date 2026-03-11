#include <iostream>
#include <string>

using namespace std;

struct Node {
    string songTitle;
    Node* next;
};

void addSong(Node* head, string title) {
    Node* newNode = new Node();
    newNode->songTitle = title;
    newNode->next = head;
    head = newNode;
    cout << ">> '" << title << "' listeye eklendi\n";
}

void searchSong(Node* head, string title) {
    Node* temp = head;
    while (temp->next != nullptr) {
        if (temp->songTitle == title) {
            cout << ">> Bulundu: '" << title << "' calma listesinde mevcut\n";
        }
        temp = temp->next;
    }
    cout << ">> Hata: '" << title << "' calma listesinde bulunamadi\n";
}

void displaySongs(Node* head) {
    if (head == nullptr) {
        cout << ">> Calma listesi su an bos\n";
        return;
    }
    
    Node* temp = head;
    int order = 1;
    cout << "\n Calma Listesi \n";
    while (temp != nullptr) {
        cout << order << ". " << temp->songTitle << "\n";
        temp = temp->next;
        order++;
    }
    cout << "---------\n";
}

int main() {
    Node* head;
    int choice;
    string title;

    do {
        cout << "\n MENu \n";
        cout << "1. Add (Ekle)\n";
        cout << "2. Search (Ara)\n";
        cout << "3. List (Listele)\n";
        cout << "4. Exit (Cikis)\n";
        cout << "Seciminiz ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Eklenecek sarkinin adini girin ";
                getline(cin, title);
                addSong(head, title);
                break;
            case 2:
                cout << "Aranacak sarkinin adini girin ";
                getline(cin, title);
                searchSong(head, title);
                break;
            case 3:
                displaySongs(head);
                break;
            case 4:
                cout << "Programdan cikiliyor\n";
                break;
            default:
                cout << "Gecersiz secim Lutfen 1-4 arasi bir rakam girin\n";
        }
    } while (choice != 4);

    return 0;
}