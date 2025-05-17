#include <iostream>
using namespace std;

// Struktur node
struct node
{
    string nama;
    int antrian;
    string penyakit;
    node *next;
    node *prev;
};

void tambah(node *&awal, string new_nama, int new_antrian, string new_penyakit)
{
    node *new_node = new node;
    new_node->nama = new_nama;
    new_node->antrian = new_antrian;
    new_node->penyakit = new_penyakit;
    new_node->next = nullptr;
    // Jika linked list kosong, node baru menjadi awal
    if (awal == nullptr)
    {
        awal = new_node;
        return;
    }
    node *bantu = awal;
    while (bantu->next != nullptr)
    {
        bantu = bantu->next;
    }
    // Menambahkan node baru di akhir linked list
    bantu->next = new_node;
    new_node->prev = bantu;
    cout << "====Pasien berhasil ditambahkan!====" << endl;
}

void hapus(node *&awal, int cari)
{
    if (awal == nullptr)
    {
        cout << "====Daftar pasien kosong!====" << endl;
        return;
    }
    if (awal->antrian == cari)
    {
        node *hapus = awal;
        awal = awal->next;
        if (awal != nullptr)
            awal->prev = nullptr;
        delete hapus;
        cout << "====Pasien berhasil dihapus!====" << endl;
        return;
    }
    node *bantu = awal;
    // Mencari node yang ingin dihapus
    while (bantu != nullptr)
    {
        if (bantu->antrian == cari)
        {
            // Update pointer next dan prev agar linked list tetap terhubung
            if (bantu->next != nullptr)
            {
                bantu->next->prev = bantu->prev;
            }
            if (bantu->prev != nullptr)
            {
                bantu->prev->next = bantu->next;
            }
            delete bantu;
            cout << "====Pasien berhasil dihapus!====" << endl;
            return;
        }
        bantu = bantu->next;
    }
    cout << "====Pasien tidak ditemukan!====" << endl;
}

void tampil_awal(node *&awal)
{
    node *bantu = awal;
    if (bantu == nullptr)
    {
        cout << "====Daftar pasien kosong!====" << endl;
        return;
    }
    // Hitung jumlah node
    int jumlah = 0;
    bantu = awal;
    while (bantu != nullptr)
    {
        jumlah++;
        bantu = bantu->next;
    }

    // Tandai node yang sudah ditampilkan
    bool *sudah = new bool[jumlah];
    for (int i = 0; i < jumlah; i++)
        sudah[i] = false;

    cout << "====Daftar Pasien====" << endl;
    for (int i = 0; i < jumlah; i++)
    {
        node *minNode = nullptr;
        int minAntrian = 9999999;
        int idx = 0, idxMin = -1;
        bantu = awal;
        while (bantu != nullptr)
        {
            if (!sudah[idx] && bantu->antrian < minAntrian)
            {
                minAntrian = bantu->antrian;
                minNode = bantu;
                idxMin = idx;
            }
            bantu = bantu->next;
            idx++;
        }
        if (minNode != nullptr)
        {
            cout << "No Antrian: " << minNode->antrian << endl;
            cout << "Nama pasien : " << minNode->nama << endl;
            cout << "Keluhan : " << minNode->penyakit << endl;
            cout << "====================" << endl;
            sudah[idxMin] = true;
        }
    }
    delete[] sudah;
}

void tampil_akhir(node *&awal)
{
    if (awal == nullptr)
    {
        cout << "====Daftar pasien kosong!====" << endl;
        return;
    }
    // Hitung jumlah node
    int jumlah = 0;
    node *bantu = awal;
    while (bantu != nullptr)
    {
        jumlah++;
        bantu = bantu->next;
    }

    // Tandai node yang sudah ditampilkan
    bool *sudah = new bool[jumlah];
    for (int i = 0; i < jumlah; i++)
        sudah[i] = false;

    cout << "====Daftar Pasien====" << endl;
    for (int i = 0; i < jumlah; i++)
    {
        node *maxNode = nullptr;
        int maxAntrian = -1;
        int idx = 0, idxMax = -1;
        bantu = awal;
        while (bantu != nullptr)
        {
            if (!sudah[idx] && bantu->antrian > maxAntrian)
            {
                maxAntrian = bantu->antrian;
                maxNode = bantu;
                idxMax = idx;
            }
            bantu = bantu->next;
            idx++;
        }
        if (maxNode != nullptr)
        {
            cout << "No Antrian: " << maxNode->antrian << endl;
            cout << "Nama pasien : " << maxNode->nama << endl;
            cout << "Keluhan : " << maxNode->penyakit << endl;
            cout << "====================" << endl;
            sudah[idxMax] = true;
        }
    }
    delete[] sudah;
}

void cari_pasien(node *awal, int no_antrian)
{
    node *bantu = awal;
    while (bantu != nullptr)
    {
        if (bantu->antrian == no_antrian)
        {
            cout << "====Pasien ditemukan!====" << endl;
            cout << "No Antrian: " << bantu->antrian << endl;
            cout << "Nama pasien : " << bantu->nama << endl;
            cout << "Keluhan : " << bantu->penyakit << endl;
            return;
        }
        bantu = bantu->next;
    }
    cout << "====Pasien dengan no antrian " << no_antrian << " tidak ditemukan!====" << endl;
}

int main()
{
    node *awal = nullptr;
    int menu;
    string nama, penyakit;
    int antrian;

    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Tambah Pasien" << endl;
        cout << "2. Tampilkan Daftar Pasien dari Awal" << endl;
        cout << "3. Tampilkan Daftar Pasien dari Akhir" << endl;
        cout << "4. Hapus Pasien" << endl;
        cout << "5. Cari Pasien" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> menu;
        cin.ignore();

        switch (menu)
        {
        case 1:
            cout << "Masukkan nama pasien: ";
            getline(cin, nama);
            cout << "Masukkan no antrian: ";
            cin >> antrian;
            cin.ignore();
            cout << "Masukkan keluhan: ";
            getline(cin, penyakit);
            tambah(awal, nama, antrian, penyakit);
            break;
        case 2:
            tampil_awal(awal);
            break;
        case 3:
            tampil_akhir(awal);
            break;
        case 4:
            // Jika linked list kosong
            if (awal == nullptr)
            {
                cout << "====Daftar pasien kosong!====" << endl;
                break;
            }
            cout << "Masukkan no antrian yang ingin dihapus: ";
            cin >> antrian;
            hapus(awal, antrian);
            break;
        case 5:
            // Jika linked list kosong
            if (awal == nullptr)
            {
                cout << "====Daftar pasien kosong!====" << endl;
                break;
            }
            cout << "Masukkan no antrian yang ingin dicari: ";
            cin >> antrian;
            cari_pasien(awal, antrian);
            break;
        case 6:
            cout << "====Terima kasih!====" << endl;
            break;
        }

    } while (menu != 6);
}