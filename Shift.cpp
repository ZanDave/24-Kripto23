#include <iostream>
#include <string>

using namespace std;

string caesarEncrypt(string plaintext, int k)
{
	string ciphertext = "";
	for (char c : plaintext)
	{
		if (isalpha(c))
		{
			char shifted = (isupper(c)) ? 'A' + (c - 'A' + k) % 26 : 'a' + (c - 'a' + k) % 26;
			ciphertext += shifted;
		}
		else
		{
			ciphertext += c;
		}
	}
	return ciphertext;
}

// Fungsi untuk melakukan deskripsi dengan Caesar Cipher
string caesarDecrypt(string ciphertext, int k)
{
	return caesarEncrypt(ciphertext, 26 - k); 
}

int main()
{
	int choice;
	cout << "\nProgram Shift Cipher (Caesar Cipher)" << endl;
	do
	{
		cout << "\nMenu:\n";
		cout << "1. Enkripsi\n";
		cout << "2. Dekripsi\n";
		cout << "3. Keluar\n";
		cout << "Pilihan: ";
		cin >> choice;

		if (choice == 1)
		{
			string plaintext;
			int k;
			cout << "\nMasukkan plaintext: ";
			cin.ignore();
			getline(cin, plaintext);
			cout << "Masukkan nilai k (shift): ";
			cin >> k;
			string ciphertext = caesarEncrypt(plaintext, k);
			cout << "\nHasil Enkripsi: " << ciphertext << endl;
		}
		else if (choice == 2)
		{
			string ciphertext;
			int k;
			cout << "\nMasukkan ciphertext: ";
			cin.ignore();
			getline(cin, ciphertext);
			cout << "Masukkan nilai k (shift): ";
			cin >> k;
			string plaintext = caesarDecrypt(ciphertext, k);
			cout << "\nHasil Deskripsi: " << plaintext << endl;
		}
		else if (choice == 3)
		{
			cout << "Keluar dari Program" << endl;
		}
		else {
			cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 3." << endl;
		}
	} while (choice != 3);

	return 0;
}