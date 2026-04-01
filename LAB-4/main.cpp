#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string customerName;
    string transactionType;
};

Customer customerQueue[5];
int qFront = 0;
int qRear = -1;
int qCount = 0;

MoneyBundle* topBundle = nullptr;

void pushMoney(string serial, string currency, int b100, int b50, int b20) {
    MoneyBundle* newBundle = new MoneyBundle();
    newBundle->serialNumber = serial;
    newBundle->currencyType = currency;
    newBundle->billCounts[0] = b100;
    newBundle->billCounts[1] = b50;
    newBundle->billCounts[2] = b20; 
    
    newBundle->next = topBundle;
    topBundle = newBundle;
    cout << ">> Kasa: " << currency << " destesi (Seri: " << serial << ") eklendi.\n";
}

void enqueueCustomer(string name, string type) {
    if (qCount == 5) {
        cout << ">> Hata: Banka sirasi dolu! Yeni musteri alinamiyor.\n";
        return;
    }
    qRear = (qRear + 1) % 5;
    customerQueue[qRear].customerName = name;
    customerQueue[qRear].transactionType = type;
    qCount++;
    cout << ">> Sira: " << name << " banka sirasina katildi (" << type << ").\n";
}

void processTransaction() {
    if (qCount == 0) {
        cout << ">> Hata: Sirada bekleyen musteri yok.\n";
        return;
    }
    if (topBundle == nullptr) {
        cout << ">> Hata: Kasada para destesi kalmadi! Islem yapilamiyor.\n";
        return;
    }

    Customer currentCustomer = customerQueue[qFront];
    qFront = (qFront + 1) % 5;
    qCount--; 
    
    MoneyBundle* moneyToGive = topBundle;
    topBundle = topBundle->next;

    cout << "\n>> ISLEM GERCEKLESIYOR <<\n";
    cout << "Musteri: " << currentCustomer.customerName << " (" << currentCustomer.transactionType << ")\n";
    cout << "Verilen Para: " << moneyToGive->currencyType << " - Seri: " << moneyToGive->serialNumber << "\n";
    
    delete moneyToGive; 
}

void displayStatus() {
    cout << "\n KASA DURUMU (STACK) \n";
    if (topBundle == nullptr) {
        cout << "Kasa bos.\n";
    } else {
        MoneyBundle* temp = topBundle;
        while (temp != nullptr) {
            cout << "[" << temp->currencyType << " - " << temp->serialNumber << "] ";
            cout << "100x" << temp->billCounts[0] << ", 50x" << temp->billCounts[1] << ", 20x" << temp->billCounts[2] << "\n";
            temp = temp->next;
        }
    }

    cout << "\n--- MUSTERI SIRASI (QUEUE) ---\n";
    if (qCount == 0) {
        cout << "Sira bos.\n";
    } else {
        for (int i = 0; i < qCount; i++) {
            int index = (qFront + i) % 5;
            cout << i + 1 << ". Kisi: " << customerQueue[index].customerName << " - " << customerQueue[index].transactionType << "\n";
        }
    }
    cout << "------\n";
}

int main() {
    int choice;
    do {
        cout << "\n=== BANKA YONETIM SISTEMI ===\n";
        cout << "1. Kasaya Para Ekle \n";
        cout << "2. Yeni Musteri Al \n";
        cout << "3. Islem Gerceklestir \n";
        cout << "4. Durumu Goster \n";
        cout << "5. Cikis\n";
        cout << "Secim: ";
        cin >> choice;

        if (choice == 1) {
            string serial, currency;
            int b100, b50, b20;
            cout << "Seri No: ";
            cin >> serial;
            cout << "Para Birimi (TL/USD): ";
            cin >> currency;
            cout << "100'luk, 50'lik ve 20'lik banknot sayilarini girin (Bosluklu): ";
            cin >> b100 >> b50 >> b20;
            pushMoney(serial, currency, b100, b50, b20);
        } else if (choice == 2) {
            string name, type;
            cout << "Musteri Adi: ";
            cin >> name;
            cout << "Islem Tipi (Cekme/Yatirma): ";
            cin >> type;
            enqueueCustomer(name, type);
        } else if (choice == 3) {
            processTransaction();
        } else if (choice == 4) {
            displayStatus();
        }

    } while (choice != 5);

    while (topBundle != nullptr) {
        MoneyBundle* temp = topBundle;
        topBundle = topBundle->next;
        delete temp;
    }

    return 0;
}