#include <iostream>
#include <vector>

using namespace std;

const int UKURAN_MATRIKS = 3;

// Fungsi untuk menghitung invers matriks 3x3 (mod 26)
bool hitungMatriksInvers(const vector<vector<int>>& matriks, vector<vector<int>>& invers) {
    int determinan = (matriks[0][0] * matriks[1][1] * matriks[2][2] +
                      matriks[0][1] * matriks[1][2] * matriks[2][0] +
                      matriks[0][2] * matriks[1][0] * matriks[2][1]) -
                     (matriks[0][2] * matriks[1][1] * matriks[2][0] +
                      matriks[0][0] * matriks[1][2] * matriks[2][1] +
                      matriks[0][1] * matriks[1][0] * matriks[2][2]);

    if (determinan == 0) {
        cout << "Matriks tidak dapat diinvers (determinan = 0), invers tidak dapat ditemukan." << endl;
        return false;
    }

    int determinanInvers = -1;
    for (int i = 1; i < 26; ++i) {
        if ((determinan * i) % 26 == 1) {
            determinanInvers = i;
            break;
        }
    }

    if (determinanInvers == -1) {
        cout << "Matriks tidak dapat diinvers, invers tidak dapat ditemukan." << endl;
        return false;
    }

    invers.resize(UKURAN_MATRIKS, vector<int>(UKURAN_MATRIKS));

    invers[0][0] = (matriks[1][1] * matriks[2][2] - matriks[1][2] * matriks[2][1]) * determinanInvers % 26;
    invers[0][1] = (matriks[0][2] * matriks[2][1] - matriks[0][1] * matriks[2][2]) * determinanInvers % 26;
    invers[0][2] = (matriks[0][1] * matriks[1][2] - matriks[0][2] * matriks[1][1]) * determinanInvers % 26;
    invers[1][0] = (matriks[1][2] * matriks[2][0] - matriks[1][0] * matriks[2][2]) * determinanInvers % 26;
    invers[1][1] = (matriks[0][0] * matriks[2][2] - matriks[0][2] * matriks[2][0]) * determinanInvers % 26;
    invers[1][2] = (matriks[0][2] * matriks[1][0] - matriks[0][0] * matriks[1][2]) * determinanInvers % 26;
    invers[2][0] = (matriks[1][0] * matriks[2][1] - matriks[1][1] * matriks[2][0]) * determinanInvers % 26;
    invers[2][1] = (matriks[0][1] * matriks[2][0] - matriks[0][0] * matriks[2][1]) * determinanInvers % 26;
    invers[2][2] = (matriks[0][0] * matriks[1][1] - matriks[0][1] * matriks[1][0]) * determinanInvers % 26;

    for (int i = 0; i < UKURAN_MATRIKS; ++i) {
        for (int j = 0; j < UKURAN_MATRIKS; ++j) {
            invers[i][j] = (invers[i][j] + 26) % 26; // Memastikan hasil tetap positif
        }
    }

    return true;
}

// Fungsi untuk mengenkripsi teks dengan Hill Cipher menggunakan matriks kunci
string enkripsi(const string& teks, const vector<vector<int>>& matriksKunci) {
    string teksDimodifikasi = teks;
    int panjang = teks.length();

    while (panjang % UKURAN_MATRIKS != 0) {
        teksDimodifikasi += 'X';
        panjang++;
    }

    string cipherText = "";

    for (int i = 0; i < panjang; i += UKURAN_MATRIKS) {
        vector<int> input(UKURAN_MATRIKS, 0);
        vector<int> output(UKURAN_MATRIKS, 0);

        for (int j = 0; j < UKURAN_MATRIKS; ++j)
            input[j] = teksDimodifikasi[i + j] - 'A';

        for (int j = 0; j < UKURAN_MATRIKS; ++j) {
            for (int k = 0; k < UKURAN_MATRIKS; ++k)
                output[j] += matriksKunci[j][k] * input[k];
            output[j] %= 26;
            cipherText += (char)(output[j] + 'A');
        }
    }

    return cipherText;
}

// Fungsi untuk mendekripsi teks dengan Hill Cipher menggunakan matriks kunci
string dekripsi(const string& cipherText, const vector<vector<int>>& matriksKunci) {
    string teksTerdekripsi = "";
    int panjang = cipherText.length();

    vector<vector<int>> matriksInvers;
    if (!hitungMatriksInvers(matriksKunci, matriksInvers))
        return "";

    for (int i = 0; i < panjang; i += UKURAN_MATRIKS) {
        vector<int> input(UKURAN_MATRIKS, 0);
        vector<int> output(UKURAN_MATRIKS, 0);

        for (int j = 0; j < UKURAN_MATRIKS; ++j)
            input[j] = cipherText[i + j] - 'A';

        for (int j = 0; j < UKURAN_MATRIKS; ++j) {
            for (int k = 0; k < UKURAN_MATRIKS; ++k)
                output[j] += matriksInvers[j][k] * input[k];
            output[j] %= 26;
            teksTerdekripsi += (char)((output[j] + 26) % 26 + 'A');
        }
    }

    return teksTerdekripsi;
}

int main() {
    vector<vector<int>> matriksKunci(UKURAN_MATRIKS, vector<int>(UKURAN_MATRIKS, 0));

    cout << "Masukkan matriks kunci untuk Hill Cipher (3x3):" << endl;
    for (int i = 0; i < UKURAN_MATRIKS; ++i) {
        for (int j = 0; j < UKURAN_MATRIKS; ++j) {
            cout << "Masukkan elemen di posisi (" << i + 1 << ", " << j + 1 << "): ";
            cin >> matriksKunci[i][j];
        }
    }

    while (true) {
        cout << "\nMenu Hill Cipher:\n" << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "3. Temukan Matriks Invers Kunci" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukkan pilihan Anda: ";

        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            string teksBiasa;
            cout << "\nMasukkan plain text (huruf besar) (akan ada 1 huruf tambahan jadi abaikan saja): ";
            cin >> teksBiasa;

            string cipherText = enkripsi(teksBiasa, matriksKunci);
            cout << "cipherText (abaikan 1 huruf terakhir): " << cipherText << endl;
        }
        else if (pilihan == 2) {
            string cipherText;
            cout << "\nMasukkan cipherText (huruf besar)(dibutuhkan 1 huruf tambahan): ";
            cin >> cipherText;

            string teksTerdekripsi = dekripsi(cipherText, matriksKunci);
            cout << "Teks terdekripsi (abaikan 1 huruf terakhir): " << teksTerdekripsi << endl;
        }
        else if (pilihan == 3) {
            vector<vector<int>> matriksInvers;
            if (hitungMatriksInvers(matriksKunci, matriksInvers)) {
                cout << "\nMatriks Invers Kunci:" << endl;
                for (int i = 0; i < UKURAN_MATRIKS; ++i) {
                    for (int j = 0; j < UKURAN_MATRIKS; ++j) {
                        cout << matriksInvers[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        }
        else if (pilihan == 4) {
            cout << "\nKeluar dari program." << endl;
            return 0;
        }
        else {
            cout << "\nPilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}
