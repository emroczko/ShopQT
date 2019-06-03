#include "mainobjectshop.h"



using namespace std;

Shop::Shop():income_(1000) {}
void Shop::Set_income(int val) {income_=val;}
Shop::Shop(int income): income_(income)
{


    Personnel_.emplace_back(Person::makeSalesman("Jan", "Jankowski", 4000, 6));
    Personnel_.emplace_back(Person::makeSalesman("Anna", "Bratkowska", 3000, 3));
    Personnel_.emplace_back(Person::makeMechanic("Adam", "Mazowiecki", 4200, "Mechanik"));
    Personnel_.emplace_back(Person::makeMechanic("Juliusz", "Marski", 3500, "Wulkanizator"));
    Personnel_.emplace_back(Person::makeSalesman("Dariusz", "Markowski", 5000, 5));
    Vehicles_.emplace_back(Vehicle::makeCar("BMW 340i", 320000, 1, "Nowy", "Benzyna", "Manualna"));
    Vehicles_.emplace_back(Vehicle::makeCar("BMW 550i", 440000, 2, "Używany", "Diesel", "Automatyczna hydrauliczna"));
    Vehicles_.emplace_back(Vehicle::makeCar("BMW 730d", 370000, 3, "Używany", "Diesel", "Automatyczna bezstopniowa"));
    Vehicles_.emplace_back(Vehicle::makeCar("BMW 428i", 190000, 4, "Nowy", "Benzyna", "Manualna"));
    Vehicles_.emplace_back(Vehicle::makeCar("BMW 316d", 142000, 5, "Nowy", "Diesel", "Manualna"));
    Vehicles_.emplace_back(Vehicle::makeMotorcycle("BMW R 1250 RS", 23000, 1, "Benzyna", "Używany", "Dwusuwowy"));
}

Shop::Shop(int income, vector < shared_ptr<Vehicle> > assortment, vector <shared_ptr<Person>> Personnel): income_(income)
 {
    for(auto x: assortment)
        Vehicles_.emplace_back(x);
    for(auto i: Personnel)
        Personnel_.emplace_back(i);
}

Shop::Shop(const Shop& shop):income_(shop.income_),Vehicles_(shop.Vehicles_) ,Personnel_(shop.Personnel_)
{
}

Shop & Shop::operator += (shared_ptr<Person> employee)
{
    Personnel_.emplace_back(employee);
    return *this;
}
Shop & Shop::operator += (const shared_ptr<Vehicle> vehicle)
{
    Vehicles_.emplace_back(vehicle);
    return *this;
}
Shop & Shop::operator -= (int i)
{
    Vehicles_.erase(Vehicles_.begin()+i);
    return *this;
}

vector < shared_ptr<Vehicle> > Shop::getVehicles() const {return Vehicles_;}
vector < shared_ptr<Person> > Shop::getPersonnel() const {return Personnel_;}

ostream& operator<<(ostream& os,const Shop& S)
{

    if(S.Vehicles_.size()!= 0)
    {
    os << "Samochody: " <<endl;
        for(auto &p : S.Vehicles_){
            if (typeid(*p) == typeid(Car)){
            os << *p<<endl;
            }
        }
    os<< "Motocykle: " <<endl;
        for(auto &p : S.Vehicles_){
            if (typeid(*p) == typeid(Motorcycle)){
            os << *p << endl;
            }
        }
    }
    if(S.Personnel_.size()!=0)
    {
        os << "Sprzedawcy:"<< endl;
        for(auto &p : S.Personnel_){
            if (typeid(*p) == typeid(Salesman)){
            os << *p << endl;
            }
        }
        os << "Mechanicy:"<< endl;
        for(auto &p : S.Personnel_){
            if (typeid(*p) == typeid(Mechanic)){
            os << *p << endl;
            }
        }
    }
    os<<endl;
    return os;
}
istream & operator >> (istream &in, Shop &shop)
{
    string model, condition, transmission,transmission2, engine, temp_;
    int id, exp;
    double money, price;
    string name, surname,  spec;

    in>>temp_;

    while (!in.eof())
    {

    //in>>"BMW" >>model>>"Cena:">>price>>"zł">>"ID:">>id>>"Stan:">>condition>>"Silnik:">>engine>>"Skrzynia biegów:">>transmission;

    in>>temp_;
    if(temp_=="Motocykle:")
        break;

    in>>model>>temp_>>price>>temp_>>temp_>>id>>temp_>>condition>>temp_>>engine>>temp_>>temp_>>transmission;
    if(transmission!="Manualna")
    {
        in>>transmission2;
        shop+=Vehicle::makeCar("BMW "+model, price, id, condition, engine, transmission+transmission2);
    }
    else
    shop+=Vehicle::makeCar("BMW "+model, price, id, condition, engine, transmission);
    }


    while (!in.eof())
    {

    in>>temp_;
    if(temp_=="Sprzedawcy:")
        break;
    in>>model>>temp_>>price>>temp_>>temp_>>id>>temp_>>condition>>temp_>>engine>>temp_>>temp_>>transmission;


    shop+=Vehicle::makeMotorcycle("BMW "+model, price, id, condition, engine, transmission);
    }

    while (!in.eof())
    {
    in>>temp_;
    if(temp_=="Mechanicy:")
    break;

    in>>name>>temp_>>surname>>temp_>>money>>temp_>>exp;

    shop+=Person::makeSalesman(name, surname, money, exp);
    }
    while (!in.eof())
    {
    in>>temp_>>name;
    if(name=="")
    break;

    in>>temp_>>surname>>temp_>>money>>temp_>>spec;

    shop+=Person::makeMechanic(name, surname, money, spec);
    }
    return in;
}

Shop & Shop::operator = (Shop &shop)
{
    income_ = shop.income_;

    Personnel_.clear();
    Vehicles_.clear();

    for(int i = 0; i< shop.Personnel_.size(); ++i)
        Personnel_.emplace_back(shop.Personnel_[i]);

    for(int i = 0; i< shop.Vehicles_.size(); ++i)
        Vehicles_.emplace_back(shop.Vehicles_[i]);

    return *this;
}

int Shop::getIncome()const {
   return income_;
}
Shop::~Shop()
{

}
