#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// 🛠️ FUNGSI MENGUBAH SPASI
string replacespasi(string str);      // Mengubah " " --> "_"
string replaceunderscore(string str); // Mengembalikan " "

// ⚙️ FUNGSI CRUD
void ReadD();  // Membaca data nasabah
void Add();    // Menambahkan nasabah baru
void Del();    // Menghapus data nasabah berdasarkan no.rekening
void Search(); // Mencari data nasabah berdasarkan no.rekening

// 💵 FUNGSI TRANSAKSI
void Transaksi();       // Menu Transaksi
void Saldo(int option); // Fungsi tambah saldo dan penarikan
void Transfer();        // Fungsi transfer ((belum bisa ke bank lain))
void History();         // Menampilkan riwayat transaksi

// 📋 LAINNYA
void sorting1(int n); // Sorting data berdasarkan nama
void sorting2(int n); // Sorting data berdasarkan jumlah saldo
void PressAnyKey();   // Print "press any key"

// 🏢 DATA NASABAH
struct riwayat
{
    string trsaksi;
    time_t waktu;
};
struct data
{
    int norek;
    char nama[30];
    int saldo;
};
string filename = "NasabahBD.txt";  // Memberikan nama file data nasabah
string filehistory = "History.txt"; // Memberikan nama file riwayat transaksi

// 👫 DATA NASABAH
data nasabah[100];
data temp_sort;
data temp[100];
int s_nasabah = 0;

// 📝👫 DATA RIWAYAT TRANSAKSI
riwayat temp_log[100];
data temps[1000];
riwayat transaksi[100];
string temp_waktu[100];
int tempno[100];
int inno[1000];

int main()
{
    system("color 1F"); // Mengubah warna background
    int option, k = 1;
    // Print nomor 1-1000
    for (int i = 0; i < 1000; i++)
    {
        inno[i] = k++;
    }
    // Main Menu
    do
    {
        system("CLS");
        cout << "\n\n============================================================="
             << "\n                        Program BANK KRUD                    "
             << "\n_____________________________________________________________"
             << "\n                           Main Menu                         "
             << "\n============================================================="
             << "\n 1. Tampilkan data nasabah"
             << "\n 2. Tambahkan nasabah"
             << "\n 3. Hapus nasabah"
             << "\n 4. Cari nasabah"
             << "\n 5. Transaksi"
             << "\n 6. Riwayat transaksi"
             << "\n 7. Exit program"
             << "\n\n Pilih : ";
        cin >> option;
        cout << "\n============================================================\n";
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
    int tampilan;
    // Membaca file nasabah yang sudah ada
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

    if (count == 0)
    {
        cout << "Belum ada Nasabah !! ";
    }

    else
    {
        do
        { // Menu read data
            cout << "Daftar Nasabah Akan Ditampilkan Secara Ascending Berdasarkan :\n"
                 << "1. Nama\n"
                 << "2. Saldo\n"
                 << "Masukkan Pilihan (1-2) : ";
            cin >> tampilan;

            if (tampilan != 1 && tampilan != 2)
            {
                cout << "\nPilihan Tidak ditemukan\n"
                     << "Mohon memilih 1 atau 2 !! ";
                getch();
                cout << "\n\n";
            }
        } while (tampilan != 1 && tampilan != 2);
        // Menentukan sorting berdasarkan nama/saldo
        if (tampilan == 1)
        {
            sorting1(count);
        }
        else if (tampilan == 2)
        {
            sorting2(count);
        }
        // Menampilkan data nasabah
        system("cls");
        cout << "Menampilkan " << count << " Nasabah Terdaftar :\n";

        if (tampilan == 1)
        {
            cout << "* Nama dengan huruf depan kapital ditampilkan paling atas\n";
        }

        cout << "\n"
             << left << setw(5) << "No"
             << setw(15) << "No.Rekening"
             << setw(20) << "Nama"
             << "Saldo"
             << "\n";

        cout << "=================================================\n";

        for (int i = 0; i < count; i++)
        {
            cout << setw(5) << i + 1 << setw(15) << temp[i].norek
                 << setw(20) << replaceunderscore(temp[i].nama) << temp[i].saldo << "\n";
        }

        cout << "=================================================\n";
    }
    PressAnyKey();
}

void Add()
{
    // initialize
    bool ulang = 1;
    char option;
    do
    { // Membaca file nasabah
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
        // input no.rekening yang ingin ditambahkan
        cout << "No rekening : ";
        cin >> nasabah[s_nasabah].norek;
        // Mengecek no.rekening yang di input sudah ada/belum
        int index;
        for (int i = 0; i <= count; i++)
        {
            index = ((nasabah[s_nasabah].norek == temp[i].norek)) ? i : count;
            if (index != count)
                break;
        }
        // Input data
        if (index == count)
        {
            cin.ignore(1, '\n');
            cout << "Nama        : ";
            gets(nasabah[s_nasabah].nama);
            cout << "Saldo awal  : ";
            cin >> nasabah[s_nasabah].saldo;
            int ulangi = 1;
            do
            {
                cout << "Tambahkan " << nasabah[s_nasabah].nama << " sebagai nasabah baru (Y/N)? > ";
                cin >> option;
                if (option == 'y' || option == 'Y') // Menambahkan data
                {
                    string str = nasabah[s_nasabah].nama;                       // Mengubah char array menjadi string
                    strcpy(nasabah[s_nasabah].nama, replacespasi(str).c_str()); // Mengubah string menjadi c_str/char array dan memasukkan ke data nasabah
                    // Menulis data baru ke file nasabah
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
                else if (option == 'n' || option == 'N') // Data tidak jadi ditambahkan
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
    PressAnyKey();
}

void Del()
{ // initialize
    bool ulang = 1;
    char option;
    do
    {
        int inrek, find = 0;
        cout << "Masukkan no rekening : ";
        cin >> inrek;
        // Membaca file nasabah
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
        // Membaca file riwayat transaksi
        ifstream ifs_hist(filehistory);
        int counts = 0;
        if (ifs_hist.is_open())
        {
            int j = counts;
            while (!ifs_hist.eof())
            {
                ifs_hist >> inno[j] >> temps[j].norek >> temps[j].nama >> temps[j].saldo >> temp_log[j].trsaksi >> temp_waktu[j];
                j++;
            }
            counts += j - 1;
            ifs_hist.close();
        }
        // Melakukan pengecekan no.rekening
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
            int no = 1;
            // Menulis ulang file data riwayat transaksi yang baru
            ofstream ofs_history("temps.dat", ios::app);
            if (ofs_history.is_open())
            {
                for (int i = 0; i < counts; i++)
                {
                    if (inrek != temps[i].norek)
                    {
                        ofs_history << left << setw(5) << no
                                    << setprecision(10) << setw(15) << temps[i].norek
                                    << setw(30) << temps[i].nama
                                    << setw(10) << temps[i].saldo
                                    << setw(12) << temp_log[i].trsaksi << setw(20) << replacespasi(temp_waktu[i])
                                    << endl;
                        no++;
                    }
                }
                ofs_history.close();
            }
            // Memperbarui file riwayat transaksi
            remove("History.txt");
            rename("temps.dat", "History.txt");
            // Menulis ulang file data nasabah
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
            cout << "Data berhasil dihapus\n";
            // Memperbarui file data nasabah
            remove("NasabahBD.txt");
            rename("temp.dat", "NasabahBD.txt");
            ulang = 0;
            break;
        }
    } while (ulang = 1);
    PressAnyKey();
}

void Search()
{
    int inrek;
    cout << "Masukkan no rekening : ";
    cin >> inrek;
    // Membaca file nasabah
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
    // Melakukan pengecekan no.rekening
    for (int i = 0; i <= count; i++)
    {
        index = ((inrek == temp[i].norek)) ? i : count;
        if (index != count)
            break;
    }

    if (index == count)
    {
        cout << "Data tidak ditemukan\n";
    }
    else
    { // Menampilkan data yang dicari
        cout << "\nData dengan no rekening '" << temp[index].norek << "' ditemukan"
             << "\nNo rekening          : " << temp[index].norek
             << "\nNama                 : " << replaceunderscore(temp[index].nama)
             << "\nSaldo                : " << temp[index].saldo << endl;
    }
    PressAnyKey();
}

void Transaksi()
{
    int optionTransaksi;
    do
    { // Menu Transaksi
        system("CLS");
        cout << "\n\n============================================================="
             << "\n                        Program BANK KRUD                      "
             << "\n_____________________________________________________________"
             << "\n                           Transaksi                           "
             << "\n============================================================="
             << "\n 1. Isi saldo"
             << "\n 2. Tarik tunai"
             << "\n 3. Transfer"
             << "\n 4. Back"
             << "\n\n Pilih : ";
        cin >> optionTransaksi;
        cout << "\n=============================================================\n";
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
    cout << "Masukkan no rekening : ";
    cin >> inrek;
    // Membaca file nasabah
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
    // Melakukan pengecekan no.rekening
    for (int i = 0; i <= count; i++)
    {
        index = ((inrek == temp[i].norek)) ? i : count;
        if (index != count)
            break;
    }

    if (index == count)
    {
        cout << "Data tidak ditemukan\n";
    }
    else
    {
        // Membaca file riwayat transaksi
        ifstream ifs(filehistory);
        int counts = 0;
        int indexs;
        if (ifs.is_open())
        {
            int j = counts;
            while (!ifs.eof())
            {
                ifs >> inno[j] >> temps[j].norek >> temps[j].nama >> temps[j].saldo >> temp_log[j].trsaksi >> temp_waktu[j];
                j++;
            }
            counts += j - 1;
            ifs.close();
        }
        // Menampilkan riwayat data yang dicari
        cout << "Nama                 : " << replaceunderscore(temp[index].nama)
             << "\nSaldo                : Rp " << temp[index].saldo
             << "\n\nRiwayat Transaksi\n";

        if (counts == 0)
        {
            cout << "Belum ada transaksi";
        }
        else
        {
            cout << "============================================================\n"
                 << left << setw(5) << "No" << setw(12) << "Transaksi" << setw(12) << "Ket" << setw(25) << "Waktu" << endl
                 << "============================================================\n";

            int n = 1;
            for (int i = 0; i < counts + 1; i++)
            {
                if (temps[i].norek == temp[index].norek)
                {
                    cout << setw(5) << n++ << setw(12) << temps[i].saldo
                         << setw(12) << temp_log[i].trsaksi << setw(25) << replaceunderscore(temp_waktu[i]) << "\n";
                }
            }
        }
    }
    PressAnyKey();
}

void Saldo(int option)
{
    int inrek, insal;
    cout << "Masukkan no rekening : ";
    cin >> inrek;
    // Membaca file nasabah
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
    // Melakukan pengecekan no.rekening
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
        // Membaca file riwayat transaksi
        ifstream ifs(filehistory);
        int a = 0;
        if (ifs.is_open())
        {
            int j = a;
            while (!ifs.eof())
            {
                ifs >> inno[j] >> temps[j].norek >> temps[j].nama >> temps[j].saldo >> temp_log[j].trsaksi >> temp_waktu[j];
                j++;
            }
            a += j - 1;
            ifs.close();
        }

        switch (option)
        {
        case 1: // Tambah saldo
        {
            temp[index].saldo += insal; // Menambahkan saldo sesuai jumlah nominal
            transaksi[a].waktu = time(0);
            transaksi[a].trsaksi = "Setoran";
            // Menulis riwayat setoran terbaru
            ofstream ofs(filehistory, ios::app);
            if (ofs.is_open())
            {
                ofs << left << setw(5) << inno[a]
                    << setprecision(10) << setw(15) << temp[index].norek
                    << setw(30) << temp[index].nama
                    << setw(1) << "+" << left << setw(10) << insal
                    << setw(12) << transaksi[a].trsaksi << setw(20) << replacespasi(ctime(&transaksi[a].waktu));
                ofs.close();
            }
            cout << "\nSuccess";
        }
        break;
        case 2: // Penarikan
        {
            if (temp[index].saldo >= insal)
            {
                temp[index].saldo -= insal; // Mengurangi saldo sesuai jumlah nominal
                transaksi[a].waktu = time(0);
                transaksi[a].trsaksi = "Penarikan";
                // Menulis riwayat penarikan terbaru
                ofstream ofs(filehistory, ios::app);
                if (ofs.is_open())
                {
                    ofs << left << setw(5) << inno[a]
                        << setprecision(10) << setw(15) << temp[index].norek
                        << setw(30) << temp[index].nama
                        << setw(1) << "-" << left << setw(10) << insal
                        << setw(12) << transaksi[a].trsaksi << setw(20) << replacespasi(ctime(&transaksi[a].waktu));
                    ofs.close();
                }
                cout << "\nSuccess";
            }
            else
            {
                cout << "\nMaaf, saldo anda tidak mencukupi!!";
            }
        }
        break;
        default:
            cout << "input tidak valid";
            break;
        }
        // Menulis ulang saldo ke file nasabah
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
        cout << "\nSaldo anda : Rp " << temp[index].saldo << endl;
        remove("NasabahBD.txt");
        rename("tempsal.dat", "NasabahBD.txt");
    }
    PressAnyKey();
}

void Transfer()
{
    int inrek, s_inrek, transfer;
    char opsi;
    cout << "Masukkan no rekening anda : ";
    cin >> inrek;
    // Membaca file nasabah
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
    // Melakukan pengecekan no.rekening
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
        cout << "Masukkan no rekening tujuan : ";
        cin >> s_inrek;
        // Melakukan pengecekan no.rekening tujuan
        int indexs;
        for (int i = 0; i <= count; i++)
        {
            indexs = ((s_inrek == temp[i].norek)) ? i : count;
            if (indexs != count)
                break;
        }

        if (indexs == count)
        {
            cout << "Data tidak ditemukan";
        }
        else
        {
            cout << "Masukkan nominal : Rp ";
            cin >> transfer;
            if (temp[index].saldo >= transfer)
            {
                cout << "\nApakah Anda yakin untuk melakukan transfer sebesar Rp. " << transfer << endl
                     << "ke rekening " << temp[indexs].norek << " atas nama '" << replaceunderscore(temp[indexs].nama) << "' ? [Y/N] ";
                cin >> opsi;
                if (opsi == 'y' || opsi == 'Y')
                {
                    // Membaca file riwayat
                    ifstream ifs(filehistory);
                    int a = 0;
                    if (ifs.is_open())
                    {
                        int j = a;
                        while (!ifs.eof())
                        {
                            ifs >> inno[j] >> temps[j].norek >> temps[j].nama >> temps[j].saldo >> temp_log[j].trsaksi >> temp_waktu[j];
                            j++;
                        }
                        a += j;
                        ifs.close();
                    }
                    temp[index].saldo -= transfer;  // Pengurangan saldo pengirim berdasarkan nominal yang ditentukan
                    temp[indexs].saldo += transfer; // Penambahan saldo penerima berdasarkan nominal yang ditentukan
                    transaksi[a].waktu = time(0);
                    transaksi[a].trsaksi = "Transfer";
                    transaksi[a + 1].waktu = transaksi[a].waktu;
                    transaksi[a + 1].trsaksi = transaksi[a].trsaksi;
                    // Menulis riwayat transfer ke file riwayat
                    ofstream ofs_history(filehistory, ios::app);
                    if (ofs_history.is_open())
                    { // riwayat transfer pengirim
                        ofs_history << left << setw(5) << inno[a - 1]
                                    << setprecision(10) << setw(15) << temp[index].norek
                                    << setw(30) << temp[index].nama
                                    << setw(1) << "-" << left << setw(10) << transfer
                                    << setw(12) << transaksi[a].trsaksi << setw(20) << replacespasi(ctime(&transaksi[a].waktu));
                        // riwayat transfer penerima
                        ofs_history << left << setw(5) << inno[a]
                                    << setprecision(10) << setw(15) << temp[indexs].norek
                                    << setw(30) << temp[indexs].nama
                                    << setw(1) << "+" << left << setw(10) << transfer
                                    << setw(12) << transaksi[a + 1].trsaksi << setw(20) << replacespasi(ctime(&transaksi[a + 1].waktu));
                        ofs_history.close();
                    }
                    cout << "\nSuccess\n"
                         << "Saldo anda : Rp " << temp[index].saldo << endl;
                    // Menulis ulang saldo file nasabah
                    ofstream ofs_temp("tempsal.dat", ios::app);
                    if (ofs_temp.is_open())
                    {
                        for (int i = 0; i < count; i++)
                        {

                            ofs_temp << left << setw(5) << tempno[i]
                                     << setprecision(10) << setw(15) << temp[i].norek
                                     << setw(30) << temp[i].nama
                                     << right << setw(10) << temp[i].saldo
                                     << endl;
                        }
                        ofs_temp.close();
                    }
                    remove("NasabahBD.txt");
                    rename("tempsal.dat", "NasabahBD.txt");
                }
                else if (opsi == 'n' || opsi == 'N')
                {
                    cout << "Transfer dibatalkan. \n";
                }
                else
                    cout << "Input tidak valid! \n";
            }
            else
            {
                cout << "\nMaaf, saldo anda tidak mencukupi!!\n";
            }
        }
    }
    PressAnyKey();
}

void PressAnyKey()
{
    cout << "\n"
         << "[Press any key to continue.]";
    getch();
    system("CLS");
}

void sorting1(int n)
{
    for (int i = 1; i < n; i++)
    {

        int j = i - 1;

        while (j >= 0 && temp[j + 1].nama < temp[j].nama)
        {

            temp_sort = temp[j];
            temp[j] = temp[j + 1];
            temp[j + 1] = temp_sort;
            j--;
        }
    }
}

void sorting2(int n)
{
    for (int i = 1; i < n; i++)
    {

        int j = i - 1;

        while (j >= 0 && temp[j + 1].saldo < temp[j].saldo)
        {

            temp_sort = temp[j];
            temp[j] = temp[j + 1];
            temp[j + 1] = temp_sort;
            j--;
        }
    }
}
