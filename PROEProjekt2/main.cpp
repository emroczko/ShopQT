#include "mainwindow2.h"
#include <QApplication>
#include "car.h"
#include "mainobjectshop.h"
#include "addvehicle.h"

int main(int argc, char *argv[])
{

    Shop sklep(4);

    QApplication a(argc, argv);
   //Shop salon;
   //cout<<salon;
    /*
    vector<Vehicle*> vehicles;
    vehicles.emplace_back(Vehicle::makeVehicle(1, "dsjcns", 7597494, 43287529, condition::USED, engine::GASOLINE ));       // Taki test czy to działa jakoś sensownie
    vehicles.emplace_back(Vehicle::makeVehicle(1,"mkfdvnf", 500000, 439327, condition::NEW, engine::DIESEL));


    cout<<vehicles.at(1)->Get_Model()<<endl<<vehicles.at(1)->Get_Price()<<endl<<vehicles.at(1)->Get_ID()<<endl<<endl;
    */
    //a z tąd można wziąć operator <<

   // salon+=

    //salon+=car2;

    a.setQuitOnLastWindowClosed(false);
    MainWindow2 w;
    w.show();
<<<<<<< Updated upstream
    a.exec();



    return 0;
=======



    //Car car2 = add.getVehicle();

    //cout<<car2;



    return a.exec();;
>>>>>>> Stashed changes
}
