#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

string replacespasi(string str);
string replaceunderscore(string str);
void ReadD();
void Add();
void Del();
void Search();
void Transaksi();
void Saldo(int option);
void Transfer();
void History();

int tempno[100];
int inno[1000];
struct data
{
    int norek;
    char nama[30];
    int saldo;
};
string filename = "NasabahBD.txt";
data nasabah[100] = {};
data temp[100];
data temps[1000];
int s_nasabah = 0;

int main()
{
    system("color 1F");
    int option, k = 1;
    for (int i = 0; i < 1000; i++)
    {
        inno[i] = k++;
    }

    do
    {
        // system("CLS");
        cout << "\n\n========================================"
             << "\n             Program BANK BD              "
             << "\n__________________________________________"
             << "\n                Main Menu                 "
             << "\n=========================================="
             << "\n 1. Tampilkan data nasabah"
             << "\n 2. Tambahkan nasabah"
             << "\n 3. Hapus nasabah"
             << "\n 4. Cari nasabah"
             << "\n 5. Transaksi"
             << "\n 6. Riwayat transaksi"
             << "\n 7. Exit program"
             << "\n\n Pilih : ";
        cin >> option;
        cout << "\n==========================================\n";
        switch (option)
        {
        case 1:
            ReadD();
            break;
        case 2:
            Add();
            break;
        case 3:
            Del();
            break;
        case 4:
            Search();
            break;
        case 5:
            Transaksi();
            break;
        case 6:
            History();
            break;
        default:
            break;
        }
    } while (option != 7);
    return 0;
}

string replacespasi(string str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == ' ')
        {
            str.replace(i, 1, 1, '_');
        }
    }
    return str;
}

string replaceunderscore(string str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '_')
        {
            str.replace(i, 1, 1, ' ');
        }
    }
    return str;
}

void ReadD()
{

    ifstream ifs(filename);
    int count = 0;
    if (ifs.is_open())
    {
        int i = count;
        while (!ifs.eof())
        {
            ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
            i++;
        }
        count += i - 1;
        ifs.close();
    }

    cout << left << setw(5) << "No"
         << setprecision(10) << setw(15) << "No Rekening"
         << setw(30) << "Nama"
         << right << setw(10) << "Saldo" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(5) << i + 1
             << setprecision(10) << setw(15) << temp[i].norek
             << setw(30) << replaceunderscore(temp[i].nama)
             << right << setw(10) << temp[i].saldo << endl;
    }
}

void Add()
{
    bool ulang = 1;
    char option;
    do
    {
        ifstream ifs(filename);
        int count = 0;
        if (ifs.is_open())
        {
            int i = count;
            while (!ifs.eof())
            {
                ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
                i++;
            }
            count += i - 1;
            ifs.close();
        }

        cout << "No rekening : ";
        cin >> nasabah[s_nasabah].norek;

        int index;

        for (int i = 0; i <= count; i++)
        {
            index = ((nasabah[s_nasabah].norek == temp[i].norek)) ? i : count;
            if (index != count)
                break;
        }

        if (index == count)
        {
            cin.ignore(1, '\n');
            cout << "Nama : ";
            gets(nasabah[s_nasabah].nama);
            cout << "Saldo awal : ";
            cin >> nasabah[s_nasabah].saldo;
            int ulangi = 1;
            do
            {
                cout << "Tambahkan " << nasabah[s_nasabah].nama << " sebagai nasabah baru (Y/N)? > ";
                cin >> option;
                if (option == 'y' || option == 'Y')
                {
                    string str = nasabah[s_nasabah].nama;
                    strcpy(nasabah[s_nasabah].nama, replacespasi(str).c_str());

                    ofstream ofs(filename, ios::app);

                    if (ofs.is_open())
                    {
                        ofs << left << setw(5) << count++
                            << setprecision(10) << setw(15) << nasabah[s_nasabah].norek
                            << setw(30) << nasabah[s_nasabah].nama
                            << right << setw(10) << nasabah[s_nasabah].saldo
                            << endl;

                        ofs.close();
                        s_nasabah++;
                        cout << "Berhasil mendaftarkan nasabah baru! \n";
                        ulangi = 0;
                    }
                }
                else if (option == 'n' || option == 'N')
                {
                    cout << "Pendaftaran nasabah dibatalkan. \n";
                    ulangi = 0;
                }
                else
                    cout << "Input tidak valid! \n";
            } while (ulangi == 1);
            ulang = 0;
            break;
        }
        else
        {
            cout << "No rekening sudah terdaftar atas nama " << replaceunderscore(temp[index].nama) << endl;
            ulang = 0;
            break;
        }
    } while (ulang = 1);
}

void Del()
{
    bool ulang = 1;
    char option;
    do
    {
        int inrek, find = 0;
        cout << "Masukkan no rekening : ";
        cin >> inrek;
        ifstream ifs(filename);
        int count = 0;
        int index;
        if (ifs.is_open())
        {
            int i = count;
            while (!ifs.eof())
            {
                ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
                i++;
            }
            count += i - 1;
            ifs.close();
        }

        for (int i = 0; i <= count; i++)
        {
            index = ((inrek == temp[i].norek)) ? i : count;
            if (index != count)
                break;
        }
        if (index == count)
        {
            ulang = 0;
            cout << "Data tidak ditemukan";
            break;
        }
        else
        {
            ofstream ofs("temp.dat", ios::app);
            if (ofs.is_open())
            {
                for (int i = 0; i < count; i++)
                {
                    if (i != index)
                    {
                        ofs << left << setw(5) << tempno[i]
                            << setprecision(10) << setw(15) << temp[i].norek
                            << setw(30) << temp[i].nama
                            << right << setw(10) << temp[i].saldo
                            << endl;
                    }
                }
                ofs.close();
            }
            cout << "Data berhasil dihapus";
            remove("NasabahBD.txt");
            rename("temp.dat", "NasabahBD.txt");
            ulang = 0;
            break;
        }

    } while (ulang = 1);
}

void Search()
{
    int inrek;
    cout << "Masukkan no rekening : ";
    cin >> inrek;
    ifstream ifs(filename);
    int count = 0;
    int index;
    if (ifs.is_open())
    {
        int i = count;
        while (!ifs.eof())
        {
            ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
            i++;
        }
        count += i - 1;
        ifs.close();
    }

    for (int i = 0; i <= count; i++)
    {
        index = ((inrek == temp[i].norek)) ? i : count;
        if (index != count)
            break;
    }

    if (index == count)
    {
        cout << "Data tidak ditemukan";
    }
    else
    {
        cout << "Nama : " << replaceunderscore(temp[index].nama)
             << "\nSaldo : " << temp[index].saldo;
    }
}

void Transaksi()
{
    int optionTransaksi;
    do
    {
        // system("CLS");
        cout << "\n\n========================================"
             << "\n             Program BANK BD              "
             << "\n__________________________________________"
             << "\n                Transaksi                 "
             << "\n=========================================="
             << "\n 1. Isi saldo"
             << "\n 2. Tarik tunai"
             << "\n 3. Transfer"
             << "\n 4. Back"
             << "\n\n Pilih : ";
        cin >> optionTransaksi;
        cout << "\n==========================================\n";
        switch (optionTransaksi)
        {
        case 1:
            Saldo(optionTransaksi);
            break;
        case 2:
            Saldo(optionTransaksi);
            break;
        case 3:
            Transfer();
            break;
        default:
            break;
        }
    } while (optionTransaksi != 4);
}

void History()
{
    int inrek;
    string filehistory = "History.txt";
    cout << "Masukkan no rekening : ";
    cin >> inrek;
    ifstream ifs(filename);
    int count = 0;
    int index;
    if (ifs.is_open())
    {
        int i = count;
        while (!ifs.eof())
        {
            ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
            i++;
        }
        count += i - 1;
        ifs.close();
    }

    for (int i = 0; i <= count; i++)
    {
        index = ((inrek == temp[i].norek)) ? i : count;
        if (index != count)
            break;
    }

    if (index == count)
    {
        cout << "Data tidak ditemukan";
    }
    else
    {
        ifstream ifs(filehistory);
        int counts = 0;
        int indexs;
        if (ifs.is_open())
        {
            int j = counts;
            while (!ifs.eof())
            {
                ifs >> inno[j] >> temps[j].norek >> temps[j].nama >> temps[j].saldo;
                j++;
            }
            counts += j - 1;
            ifs.close();
        }
        cout << "Nama : " << replaceunderscore(temp[index].nama)
             << "\nSaldo : Rp " << temp[index].saldo
             << "\nRiwayat Transaksi\n";

        cout << "==========================================\n"
             << left << setw(5) << "No" << setw(10) << "Transaksi\n"
             << "==========================================\n";
        int n = 1;
        for (int i = 0; i <= counts; i++)
        {
            if (temps[i].norek == temp[index].norek)
            {
                cout << setw(5) << n++ << setw(10) << temps[i].saldo << endl;
            }
        }
    }
}

void Saldo(int option)
{
    int inrek, insal;
    string filehistory = "History.txt";
    cout << "Masukkan no rekening : ";
    cin >> inrek;
    ifstream ifs(filename);
    int count = 0;
    int index;
    if (ifs.is_open())
    {
        int i = count;
        while (!ifs.eof())
        {
            ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
            i++;
        }
        count += i - 1;
        ifs.close();
    }

    for (int i = 0; i <= count; i++)
    {
        index = ((inrek == temp[i].norek)) ? i : count;
        if (index != count)
            break;
    }

    if (index == count)
    {
        cout << "Data tidak ditemukan";
    }
    else
    {
        cout << "Masukkan nominal yang anda inginkan : Rp ";
        cin >> insal;

        ifstream ifs(filehistory);
        int a = 0;

        if (ifs.is_open())
        {
            int j = a;
            while (!ifs.eof())
            {
                ifs >> inno[j] >> temps[j].norek >> temps[j].nama >> temps[j].saldo;
                j++;
            }
            a += j - 1;
            ifs.close();
        }

        switch (option)
        {
        case 1:
        {
            temp[index].saldo += insal;
            ofstream ofs(filehistory, ios::app);
            if (ofs.is_open())
            {
                ofs << left << setw(5) << inno[a]
                    << setprecision(10) << setw(15) << temp[index].norek
                    << setw(30) << temp[index].nama
                    << right << setw(10) << "+" << insal
                    << endl;

                ofs.close();
            }
        }
        break;
        case 2:
        {
            temp[index].saldo -= insal;
            ofstream ofs(filehistory, ios::app);
            if (ofs.is_open())
            {

                ofs << left << setw(5) << inno[a]
                    << setprecision(10) << setw(15) << temp[index].norek
                    << setw(30) << temp[index].nama
                    << right << setw(10) << "-" << insal
                    << endl;

                ofs.close();
            }
        }
        break;
        default:
            break;
        }

        cout << "Saldo anda : Rp " << temp[index].saldo;
        ofstream ofs("tempsal.dat", ios::app);
        if (ofs.is_open())
        {
            for (int i = 0; i < count; i++)
            {

                ofs << left << setw(5) << tempno[i]
                    << setprecision(10) << setw(15) << temp[i].norek
                    << setw(30) << temp[i].nama
                    << right << setw(10) << temp[i].saldo
                    << endl;
            }
            ofs.close();
        }
        cout << "\nSuccess";
        remove("NasabahBD.txt");
        rename("tempsal.dat", "NasabahBD.txt");
    }
}

void Transfer()
{
    int inrek, s_inrek;
    cout << "Masukkan no rekening anda : ";
    cin >> inrek;
    ifstream ifs(filename);
    int count = 0;
    int index;
    if (ifs.is_open())
    {
        int i = count;
        while (!ifs.eof())
        {
            ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
            i++;
        }
        count += i - 1;
        ifs.close();
    }

    for (int i = 0; i <= count; i++)
    {
        index = ((inrek == temp[i].norek)) ? i : count;
        if (index != count)
            break;
    }

    if (index == count)
    {
        cout << "Data tidak ditemukan";
    }
    else
    {
        cout << "Masukkan no rekening yang dituju : ";
        cin >> s_inrek;
        ifstream ifs(filename);
        int count = 0;
        int index;
        if (ifs.is_open())
        {
            int i = count;
            while (!ifs.eof())
            {
                ifs >> tempno[i] >> temp[i].norek >> temp[i].nama >> temp[i].saldo;
                i++;
            }
            count += i - 1;
            ifs.close();
        }

        for (int i = 0; i <= count; i++)
        {
            index = ((inrek == temp[i].norek)) ? i : count;
            if (index != count)
                break;
        }

        if (index == count)
        {
            cout << "Data tidak ditemukan";
        }
        else
        {
            cout << "Masukkan nominal : Rp ";
        }
    }
}