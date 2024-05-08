#include "sirumahsakit.h"
#include "admin.h"
#include "pasien.h"
#include "ui_sirumahsakit.h"

SiRumahSakit::SiRumahSakit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SiRumahSakit)
{
    ui->setupUi(this);
}

SiRumahSakit::~SiRumahSakit()
{
    delete ui;
    delete adminWindow;
    delete pasienWindow;
}

void SiRumahSakit::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Check for admin login
    if (username == "admin" && password == "admin") {
        QMessageBox::information(this, "Login", "Login sebagai admin berhasil!");
        AdminWindow *adminWindow = new AdminWindow();
        adminWindow->show();
        this->close();
    }
    else if (username == "pasien" && password == "pasien") {
        QMessageBox::information(this, "Login", "Login sebagai user berhasil!");
        PasienWindow *pasienWindow = new PasienWindow();
        pasienWindow->show();
        this->close();
    }
    else {
        QMessageBox::warning(this, "Login", "Username atau password salah!");
    }
}
