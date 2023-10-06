#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encryptVigenere(const string& plaintext, const string& key) {
    string ciphertext = "";
    for (size_t i = 0; i < plaintext.length(); i++) {
        char plainChar = plaintext[i];
        char keyChar = key[i % key.length()];
        if (isalpha(plainChar)) {
            char base = isupper(plainChar) ? 'A' : 'a';
            char encryptedChar = ((plainChar - base + keyChar - 'A') % 26) + base;
            ciphertext += encryptedChar;
        } else {
            ciphertext += plainChar;
        }
    }
    return ciphertext;
}

string decryptVigenere(const string& ciphertext, const string& key) {
    string plaintext = "";
    for (size_t i = 0; i < ciphertext.length(); i++) {
        char cipherChar = ciphertext[i];
        char keyChar = key[i % key.length()];
        if (isalpha(cipherChar)) {
            char base = isupper(cipherChar) ? 'A' : 'a';
            char decryptedChar = ((cipherChar - base - keyChar + 'A') % 26 + 26) % 26 + base;
            plaintext += decryptedChar;
        } else {
            plaintext += cipherChar;
        }
    }
    return plaintext;
}

int main() {
    int choice;
    string plaintext, key;
    
    do {
        cout << "\n=== Vigenere Cipher ===" << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "\nMasukkan plaintext: ";
                cin.ignore();
                getline(cin, plaintext);
                cout << "Masukkan kunci: ";
                getline(cin, key);
                cout << "Hasil enkripsi: " << encryptVigenere(plaintext, key) << endl;
                break;
            case 2:
                cout << "\nMasukkan ciphertext: ";
                cin.ignore();
                getline(cin, plaintext);
                cout << "Masukkan kunci: ";
                getline(cin, key);
                cout << "Hasil dekripsi: " << decryptVigenere(plaintext, key) << endl;
                break;
            case 3:
                cout << "\nTerima kasih!\n" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (choice != 3);
    
    return 0;
}
