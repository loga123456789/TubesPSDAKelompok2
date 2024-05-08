#include "pasien.h"
#include "ui_pasien.h"
#include <QMessageBox>
#include <QDebug>

PasienWindow::PasienWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasienWindow)
{
    ui->setupUi(this);

    // Inisialisasi model untuk tabel
    model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels(QStringList() << "Nama Pasien" << "Umur Pasien" << "Tanggal Masuk" << "Status Pasien");

    // Set model untuk QTableView
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setVisible(false);
}

PasienWindow::~PasienWindow()
{
    delete ui;
}

void PasienWindow::on_pushButtonTambah_clicked()
{
    qDebug() << "Tombol Tambah diklik";

    if (jumlahPasien < MAX_PATIENTS) {
        // Ambil data dari inputan
        Pasient pasien;
        pasien.nama = ui->namaLineEdit->text();
        pasien.umur = ui->umurSpinBox->value();
        pasien.tanggalMasuk = ui->tanggalMasukDateEdit->date();
        pasien.status = ui->statusComboBox->currentText();

        // Simpan data ke dalam array dataPasien
        dataPasien[jumlahPasien] = pasien;

        // Tambahkan jumlahPasien
        jumlahPasien++;

        // Perbarui model dan tampilkan data
        tampilkanData();
    }
}

void PasienWindow::on_pushButtonUpdate_clicked()
{
    // Dapatkan indeks baris yang dipilih
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int index = selectedIndexes.at(0).row();

        // Ambil data dari input teks yang ingin diupdate
        QString nama = ui->namaLineEdit->text();
        int umur = ui->umurSpinBox->value();
        QDate tanggalMasuk = ui->tanggalMasukDateEdit->date();
        QString status = ui->statusComboBox->currentText();

        // Update data di dalam array dataPasien
        if (index >= 0 && index < jumlahPasien) {
            Pasient pasien;
            pasien.nama = nama;
            pasien.umur = umur;
            pasien.tanggalMasuk = tanggalMasuk;
            pasien.status = status;
            dataPasien[index] = pasien;

            // Tampilkan data yang telah diupdate di dalam QTableView
            tampilkanData();
        }
    }
}

void PasienWindow::tampilkanData()
{
    // Bersihkan model sebelum menambahkan data baru
    model->clear();

    // Set header untuk tabel
    model->setHorizontalHeaderLabels(QStringList() << "Nama Pasien" << "Umur Pasien" << "Tanggal Masuk" << "Status Pasien");

    // Tampilkan data ke dalam QTableView
    for (int i = 0; i < jumlahPasien; ++i) {
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(dataPasien[i].nama)
                 << new QStandardItem(QString::number(dataPasien[i].umur))
                 << new QStandardItem(dataPasien[i].tanggalMasuk.toString("dd-MM-yyyy"))
                 << new QStandardItem(dataPasien[i].status);
        model->appendRow(rowItems);
    }
}

int PasienWindow::sequentialSearch(const QString& namaCari)
{
    for (int i = 0; i < jumlahPasien; ++i) {
        if (dataPasien[i].nama == namaCari) {
            return i; // Return the index if the name is found
        }
    }
    return -1; // Return -1 if the name is not found
}

void PasienWindow::on_pushButtonCari_clicked()
{
    // Ambil nama pasien yang akan dicari dari QLineEdit
    QString namaCari = ui->namaLineEdit->text();

    // Lakukan pencarian sekuensial
    int index = sequentialSearch(namaCari);

    // Periksa apakah nama pasien ditemukan atau tidak
    if (index != -1) {
        // Jika ditemukan, tampilkan pesan informasi
        QMessageBox::information(this, "Pencarian Berhasil", QString("Nama pasien '%1' ditemukan di indeks %2").arg(namaCari).arg(index));

        // Pilih baris yang sesuai dengan hasil pencarian di QTableView
        ui->tableView->selectRow(index);
    } else {
        // Jika tidak ditemukan, tampilkan pesan peringatan
        QMessageBox::warning(this, "Pencarian Gagal", QString("Nama pasien '%1' tidak ditemukan.").arg(namaCari));
    }
}
