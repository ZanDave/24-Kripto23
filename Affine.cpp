#include <iostream>
#include <string>

using namespace std;

// Fungsi untuk mencari invers modular (menggunakan algoritma Euclidean)
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Invers modular tidak ditemukan
}

// Fungsi untuk mengenkripsi teks dengan Affine Cipher
string encrypt(string plaintext, int a, int b) {
    string ciphertext = "";

    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int x = c - base;
            int encryptedChar = (a * x + b) % 26;
            ciphertext += static_cast<char>(encryptedChar + base);
        } else {
            ciphertext += c;
        }
    }

    return ciphertext;
}

// Fungsi untuk mendekripsi teks dengan Affine Cipher
string decrypt(string ciphertext, int a, int b) {
    string plaintext = "";
    int aInverse = modInverse(a, 26);

    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int y = c - base;
            int decryptedChar = (aInverse * (y - b + 26)) % 26;
            plaintext += static_cast<char>(decryptedChar + base);
        } else {
            plaintext += c;
        }
    }

    return plaintext;
}

int main() {
    int a, b;
    string text;

    while (true) {
        for (int i=0; i <= 11; i++){
            cout <<"--";
        }
        cout << "\n\t\tMenu:\n";
                for (int i=0; i <= 11; i++){
            cout <<"--";
        }
        cout << "\n\t1. | Enkripsi\t|\n";
        cout << "\t2. | Dekripsi\t|\n";
        cout << "\t3. | Keluar\t|\n";
        cout << "Pilih operasi (1/2/3): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Masukkan nilai a (bilangan bulat positif yang relative prima dengan 26): ";
            cin >> a;

            if (a < 0 || a >= 26 || modInverse(a, 26) == -1) {
                cout << "Nilai a tidak valid. Nilai harus antara 0 dan 25 dan relative prima dengan 26." << endl;
                continue;
            }

            cout << "Masukkan nilai b (bilangan bulat): ";
            cin >> b;

            cin.ignore(); // Menghapus karakter newline dari buffer

            cout << "Masukkan teks yang akan dienkripsi: ";
            getline(cin, text);
            string ciphertext = encrypt(text, a, b);
            cout << "Teks Terenkripsi: " << ciphertext << endl;
        } else if (choice == 2) {
            cout << "Masukkan nilai a (bilangan bulat positif yang relative prima dengan 26): ";
            cin >> a;

            if (a < 0 || a >= 26 || modInverse(a, 26) == -1) {
                cout << "Nilai a tidak valid. Nilai harus antara 0 dan 25 dan relative prima dengan 26." << endl;
                continue;
            }

            cout << "Masukkan nilai b (bilangan bulat): ";
            cin >> b;

            cin.ignore(); // Menghapus karakter newline dari buffer

            cout << "Masukkan teks yang akan didekripsi: ";
            getline(cin, text);
            string plaintext = decrypt(text, a, b);
            cout << "Teks Terdekripsi: " << plaintext << endl;
        } else if (choice == 3) {
            cout << "Keluar dari program." << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 3." << endl;
        }
    }

    return 0;
}
