#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include <QMessageBox>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent), salon(1000000),
    ui(new Ui::MainWindow2)
{
    this->hide();
    ui->setupUi(this);
    welcomeScreen welcome;
    welcome.setModal(true);
    welcome.exec();
    if(welcome.on_zacznijOdNowa_clicked()==false)
        {
           Shop tempsalon = welcome.pass_the_shop();
           salon = tempsalon;
        }
    MainWindow2::Income();
    this->showFullScreen();
    this->show();
}

MainWindow2::~MainWindow2()
{
    delete ui;
}
void MainWindow2::Income()
{
    int kasa = salon.getIncome();
    string kasa1 = std::to_string(kasa);
    string stan = "Stan konta: ";
    QString konto = QString::fromStdString(stan+kasa1);
    MainWindow2::on_stanKontsa_windowIconTextChanged(konto);
    MainWindow2::on_stanKontsa_2_windowIconTextChanged(konto);
    MainWindow2::on_stanKontsa_3_windowIconTextChanged(konto);
}
void MainWindow2::Add_car()
{
    AddVehicle addCar;
    addCar.setModal(true);
    addCar.exec();
    if(addCar.on_Anuluj_clicked()==false)
    {
        shared_ptr<Vehicle> tmp = addCar.on_Akceptuj_clicked();
        if(tmp->Get_Price()<=0 || tmp->Get_ID()<0)
        {
            QMessageBox::StandardButton resBtn = QMessageBox::question( this, " ", "Podana cena lub ID moga być nieprawidłowe. Czy jesteś pewien że chcesz dodać samochód?", QMessageBox::No | QMessageBox::Yes);
            if(resBtn==QMessageBox::No)  {addCar.reject();}
            else
            {
                addCar.accept();
                salon += tmp;
            }
        }
        else{ add(tmp); }

     }
    MainWindow2::Income();
}

void MainWindow2::Add_motorcycle()
{
    AddMotorcycle addMotor;
    addMotor.setModal(true);
    addMotor.exec();
    if(addMotor.on_Anuluj_clicked()==false)
    {
        shared_ptr<Vehicle> tmp = addMotor.on_Akceptuj_clicked();
        if(tmp->Get_Price()<=0 || tmp->Get_ID()<0)
        {
            QMessageBox::StandardButton resBtn = QMessageBox::question( this, " ", "Podana cena lub ID mogą być nieprawidłowe. Czy jesteś pewien że chcesz dodać samochód?", QMessageBox::No | QMessageBox::Yes);
            if(resBtn==QMessageBox::No)
            {
                addMotor.reject();
            }
            else
            {
                addMotor.accept();
                salon += tmp;
            }
        }
        else{ add(tmp); }

    }
    MainWindow2::Income();

}
void MainWindow2::add(shared_ptr<Vehicle> tmp)
{
    if(salon.getIncome()-tmp->Get_Price()>=0)
    {
        salon.Set_income(salon.getIncome()-tmp->Get_Price());
        salon += tmp;
    }
    else
    {
        QMessageBox::warning(this, "", "Nie wystarczające środki");
    }

}

void MainWindow2::Add_employee()
{
    AddPersonnel addperson;
    addperson.setModal(true);
    addperson.exec();
    if(addperson.on_Anuluj_mechanik_clicked()==false)
    {
        salon+=addperson.on_Akceptuj_mechanik_clicked();
    }
}

void MainWindow2::Motorcycles_owned()
{
   Vehicles_owned(false);
}

void MainWindow2::Cars_owned()
{
   Vehicles_owned(true);
}

void MainWindow2::Vehicles_owned(bool which)
{
    std::vector<shared_ptr<Vehicle>> Vehicles_;
    for(auto p : salon.getVehicles())
    if (which==0 && typeid (*p) == typeid(Motorcycle)) Vehicles_.push_back((p));
    else if(which==1 && typeid (*p) == typeid(Car)) Vehicles_.push_back((p));

    Dialog1 dial(Vehicles_);
    dial.setModal(true);
    dial.exec();
}
void MainWindow2::Sell_car()
{
    sell(true);
}
void MainWindow2::Sell_motorcycle()
{
    sell(false);
}
void MainWindow2::sell(bool whichVehicle)
{
    std::vector<shared_ptr<Vehicle>> vehicles_;
    for(auto p : salon.getVehicles())
    if (whichVehicle==0 && typeid (*p) == typeid(Motorcycle)) vehicles_.push_back((p));
    else if(whichVehicle==1 && typeid (*p) == typeid(Car)) vehicles_.push_back((p));

    deleteWindow deleteVehicle_(vehicles_);
    deleteVehicle_.setModal(true);
    if(vehicles_.size()>0)
    {
        deleteVehicle_.exec();
        std::stringstream buffer;

            for(unsigned int i=0; i<salon.getVehicles().size(); i++)
            {
                buffer << *salon.getVehicles()[i];
                if(buffer.str()==deleteVehicle_.on_Usun_clicked())
                {
                deleteHelper(i);
                }
                buffer.str(std::string());
            }
    }
    else
    {
        QMessageBox::warning(this, tr("Błąd"), tr("Brak motocykli do usunięcia."));   //(*this, tr("Problem"), tr("Nie ma pojazdów do usunięcia"));
    }
    MainWindow2::Income();
}

void MainWindow2::deleteHelper(int i)
{
    shared_ptr<Vehicle> tmp =salon.getVehicles()[i];
    int val =salon.getIncome()+tmp->Get_Price()*1.2;
    salon.Set_income(val);
    salon-=i;
}

void MainWindow2::Salon_info()
{
    Dialog1 dial(salon.getVehicles());
    dial.setModal(true);
    dial.exec();
}

void MainWindow2::on_Dodaj_samochod_clicked() {Add_car();}
void MainWindow2::on_Posiadane_samochodu_clicked() {Cars_owned();}
void MainWindow2::on_pushButton_clicked() {Add_motorcycle();}
void MainWindow2::on_Sprzedaj_Auto_clicked() {Sell_car();}
void MainWindow2::on_Posiadane_motocykle_clicked() {Motorcycles_owned();}
void MainWindow2::on_stanKontsa_windowIconTextChanged(const QString &iconText) {ui->stanKontsa->setText(iconText);}
void MainWindow2::on_stanKontsa_2_windowIconTextChanged(const QString &iconText) {ui->stanKontsa_2->setText(iconText);}
void MainWindow2::on_stanKontsa_3_windowIconTextChanged(const QString &iconText) {ui->stanKontsa_3->setText(iconText);}

void MainWindow2::on_Savetofile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Zapisz stan"), "",
            tr("Obecny_stan (*.txt);;All Files (*)"));

        if (fileName.isEmpty())
            return;

            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
            std::stringstream buffer;
            buffer << salon;
            string auta = buffer.str();
            QTextStream out(&file);
            QString qstr = QString::fromStdString(auta);
            out << qstr;

}

void MainWindow2::on_SprzedajMotocykl_clicked() {Sell_motorcycle();}
void MainWindow2::on_SalonInfo_clicked() {Salon_info();}
void MainWindow2::on_Zatrudnij_nowego_clicked() {Add_employee();}

void MainWindow2::on_Zatrudnieni_pracownicy_clicked()
{
    std::vector<shared_ptr<Person>> people;
    for(auto p : salon.getPersonnel()) {people.push_back((p));}
    ShowPersonnelWindow showpersonnel(people);
    showpersonnel.setModal(true);
    showpersonnel.exec();
    showpersonnel.showMethod(people);

}

void MainWindow2::on_Wyjscie_clicked() {MainWindow2::close();}
