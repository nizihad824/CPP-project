/**********************************************************************
Matr.-Nr:                     3086815
Nachname/Surname:             Islam
Vorname/Given name:           Md Nurul
Uni-Email:                    md.islam.97@stud.uni-due.de
Studiengang/Course of studis: Computer Engeeniring ISÉ.spec in Software.
**********************************************************************/

#include<bits/stdc++.h>
using namespace std;

class DayOfYear
{

private:
    unsigned short dayOfYear;
    unsigned short year;
    static const short days[];

public:
    DayOfYear(unsigned short day = 1, unsigned short year= 365)
    {
        dayOfYear = day;
        this->year = year;
    }

    DayOfYear(unsigned short day, unsigned short month, unsigned short years)
    {
        year= years;
        dayOfYear = day;
        for (unsigned short i = 0; i < month - 1; i++)
        {
            dayOfYear += days[i];
        }
    }

    unsigned short get_dayOfYears()
    {
        return dayOfYear;
    }

    void operator++(int)
    {
        if (this->dayOfYear + 1 > 365)
        {
            dayOfYear = 1;
            year += 1;
        }
        else
        {
            this->dayOfYear += 1;
        }

    }
    friend ostream &operator<<(ostream &o, DayOfYear dy);
    friend istream &operator>>(istream &in, DayOfYear &dy);
};

//Implement friend input output operator

istream &operator>>(istream &in, DayOfYear &dy)
{
    string st;
    in >> st;
    int i = st.find("-");
    string years = st.substr(0, i);
    string month = st.substr(i + 1, st.find("-", i + 1) - i - 1);
    string day = st.substr(st.find("-", i + 1) + 1, -1);
    unsigned short y = stoi(years);
    unsigned short m = stoi(month);
    unsigned short dd = stoi(day);
    DayOfYear dt(dd, m, y);
    dy.dayOfYear = dt.get_dayOfYears();
    dy.year = y;

    return in;
}

ostream &operator<<(ostream &o, DayOfYear dy)
{
    unsigned short m = 0;
    unsigned short d = 0;
    unsigned short t = 0;
    int counter = 0;
    while (t < dy.get_dayOfYears())
    {
        t += DayOfYear::days[counter++];
        m++;
    }
    d = dy.get_dayOfYears() - t + DayOfYear::days[counter - 1];
    o << dy.year<< "-" << ((m >= 10) ? to_string(m) : "0" + to_string(m)) << "-" << ((d >= 10) ? to_string(d) : "0" + to_string(d));
    return o;
}

const short DayOfYear::days[12] = {31,59,90,120,151,181,212,243,273,304,334,365};


//Start class Rental

class Rental
{
private:
    const int no;
    DayOfYear from;
    int days;
    string customer;
    static int last_no;

public:
    Rental(string customer1, DayOfYear fromm, int days1 = 1) : no(last_no)
    {
        last_no++;
        from=fromm;
        days = days1;
        customer = customer1;
    }

    int get_days()
    {
        return days;
    }

    DayOfYear get_from()
    {
        return from;
    }

    DayOfYear get_until(){
        DayOfYear dd;int ds;
        dd=from;ds=days;
        while(ds!=0)
        {
            dd++;

        };
        return dd;
    };
    virtual void print();

};

int Rental::last_no = 1;
void Rental :: print() {cout<<"VEHICLE RENTAL"<<endl;
    cout<<"rental no:       "<<(no+1)<<endl;
    cout<<"from:            "<<from<<endl;DayOfYear n;n=get_until();
    cout<<"until:           ";cout<<n;cout<<endl;
    cout<<"for:            "<<customer<<endl;

}
//Start class Vehicle
class Vehicle
{
private:
    const int no;
    string model;
    float price24h;
public:
    Vehicle(int no,string model,float price24h=9.99):no(no),model(model),price24h(price24h){};

    virtual  ~Vehicle(){};

    string get_model(){return model;};

    int get_no()
    {
        return no;
    }
    float get_price(int a){return a*price24h;}

    void set_price24h(int a){price24h=a;};
    void virtual print()=0;
};

//Start Class Bike
class Bike:public Vehicle
{
public:
    Bike(int a,string b):Vehicle(a,b,9.99){};
    void print(){
        cout<<"Bike "<<Vehicle::get_model()<<"("<<Vehicle::get_no()<<")";
    }
};

//start class EMotorVehicle
class EMotorVehicle: public Vehicle
{
public:
    EMotorVehicle( int a, string b, float c) : Vehicle(a, b, c) {}

    virtual bool is_streetLegal()=0;

    void print()
    {
        if(!is_streetLegal()) cout<<"(not street legal)"<<endl;
        else cout<<"no : "<<Vehicle::get_no()<<", model : "<<Vehicle::get_model()<<endl;
    }
};

// start class EBike
class EBike : public EMotorVehicle
{
public:
    EBike(int number, string model,float p=29.99) : EMotorVehicle(number, model, 29.99) {}
    virtual bool is_streetLegal()
    {
        return true;
    }
    virtual void print()
    {

        cout << Vehicle::get_no() << " : " << Vehicle::get_model() << " " << (this->is_streetLegal() ? "" : "(not street legal)") << " (EBike)" << endl;

    }
};
class EScooter : public EMotorVehicle
{
private:
    bool streetLegal;

public:
    EScooter(int number, string model, bool streetLegal = false) : EMotorVehicle(number, model, 19.99)
    {
        this->streetLegal = streetLegal;
    }
    virtual bool is_streetLegal()
    {
        return streetLegal;
    }
    virtual void print()
    {

        cout << Vehicle::get_no()<< " : " << Vehicle::get_model() << " " << (this->is_streetLegal() ? "" : "(not street legal)") << " (EScooter)" << endl;
    }
};


//Start Class Schedule
class Schedule
{
private:
    Vehicle *vehicle;
    Rental *years[365];
    Schedule *next;

public:
    Schedule(Vehicle *vehicle) : years{nullptr}
    {
        this->vehicle = vehicle;
        next = nullptr;
    }

    Vehicle *get_vehicle()
    {
        return vehicle;
    }

    Schedule *get_next()
    {
        return next;
    }

    void set_next(Schedule *nxt)
    {
        next = nxt;
    }

    bool isFree(DayOfYear d, int ds)
    {
        int i,j=0;
        bool k=true;
        for(i=d.get_dayOfYears();i<=(ds+(d.get_dayOfYears()));i++)
        {
            if(i>365){i=i-365;j=1;}
            if(years[i]!=nullptr){k=false;}
            if(j==1&&i==((ds+(d.get_dayOfYears()))-365)){break;}
        }
        return k;

    }
    float  book(string cu,DayOfYear srtTime,int numberOfDays=1)
    {
        Rental* r1=new Rental(cu,srtTime,numberOfDays);

        int i = srtTime.get_dayOfYears() - 1;
        years[i] = r1;

        return vehicle->get_price(numberOfDays);
    };

    void print(DayOfYear d)
    {
        vehicle->print();

        int ml,jump=0,firstBook=0;
        {
            for(ml=jump;ml<365;ml++)
            {if(years[ml]!=nullptr)
                {years[ml]->print();
                    ml=ml+years[ml]->get_days();
                    if(ml>365){jump=ml-365+1;}
                    firstBook=1;
                }

            }}
        if(firstBook==0)
        {
            cout<<"not booked yet!"<<endl;
        }

    };

    void print(){

        cout<<"SCHEDULE"<<endl;
        vehicle->print();
        for (int m = 0; m < 365; m++)
        {
            if (years[m])
            {
                cout << vehicle->get_price(years[m]->get_days()) << " EUR" << endl;
            }
        }
    }

    void priceOfVehicle();


    void printVehicle()
    {

        vehicle->print();
    }


};
void Schedule::priceOfVehicle()  {
    cout << " Already Booked, Price : ";
    for (int k = 0; k < 365; k++)
    {
        if (years[k])
        {
            cout << vehicle->get_price(years[k]->get_days()) << " EURO" << endl;
        }
    }
}


class Agency{
private:
    float profitPercent;
    float profit;
    Schedule *head;
    Schedule *last;
public:
    //a public standard constructor initialising the percentage of the profit to 20%,
// the profit to 0.00 EUR and the two pointers to null pointers

    Agency(float pp=20,float p=0.00){
        profitPercent=pp;
        profit=p;
        head= nullptr;
        last= nullptr;

    }


    float get_profit(){
        return profit;
    }
    void set_profitPercentage( float q)
    {
        this->profitPercent=q;
    }


    void add(Vehicle* vehicle) {
        Schedule* nSch = new Schedule(vehicle);

        if (this->head == nullptr) {
            head = nSch;
            last = nSch;
        }
        else {
            last->set_next(nSch);
            last = nSch;
        }
    }

    bool isFree(int vehicleNo, DayOfYear d, int ds) {

        Rental* years[365];
        int i;
        bool k=true;
        for(i=d.get_dayOfYears();i<=(ds+(d.get_dayOfYears()));i++)
        {

            if(years[i]!=nullptr){k=false;}
            Schedule* schedule = this->searchFor(vehicleNo);
            if (schedule != nullptr) {
                return schedule->isFree(d, ds);
            }
            return k;
        };



    }
    void ppv(int i);


    bool book(int i, string customer, DayOfYear srtD, int days)
    {
        if (!isFree(i, srtD, days))
        {
            cout << "Sorry vehicle already booked" << endl;
            return false;
        }
        profit += searchFor(i)->book(customer, srtD, days) * profitPercent / 100;
        return true;
    }

    int chooseVehicle()
    {
        if (!head)
            return 0;
        Schedule *t = head;
        int c = 1;
        while (t->get_next())
        {
            t->printVehicle();
            t = t->get_next();
            c++;
        }
        t->printVehicle();
        cout << "Choose vehicle no : ";
        int choose;
        cin >> choose;
        return choose;
    }
    void print(DayOfYear dd)
    {
        cout << "SCHEDULE FOR :" << dd << endl;
        if (!head)
            return;
        Schedule *t = head;
        while (t->get_next())
        {
            t->print(dd);
            t = t->get_next();
        }
        t->print(dd);
    }


    void print();


protected:
    Schedule* searchFor(int searchNo) {
        Schedule* t = head;
        while (t != nullptr) {
            if (t->get_vehicle()->get_no() == searchNo) {
                return t;
            }
            t = t->get_next();
        }

        return nullptr;
    }

protected:
    Schedule *searchForPrice(int i)
    {
        Schedule *t =head;
        while (t->get_next())
        {
            if (t->get_vehicle()->get_no() == i)
            {
                break;
                return t;
            }
            t = t->get_next();
        }
        if (t->get_vehicle()->get_no() == i)
        {
            t->priceOfVehicle();
            return t;
        }
        return nullptr;
    }
};
void Agency:: print() {

    if (!head)
    {
        cout << "profit: " << fixed << setprecision(2) << profit << " EUR" << endl;
        return;
    }
    Schedule *t = head;
    while (t->get_next())
    {
        t->print();
        t = t->get_next();
    }
    t->print();
    cout << "profit: " << fixed << setprecision(2) << profit << " EUR" << endl;
}
void Agency::ppv(int i)

{
    if (searchForPrice(i));

}


int main()
{


    Agency agency;
    int vehicleNumber = 1;


    time_t t1 = time(0);   // get time now
    struct tm * now = localtime( & t1 );

    DayOfYear today(now->tm_mday, 1 + now->tm_mon, 1900 + now->tm_year);
    DayOfYear tomorrow = today;

    tomorrow++;
    DayOfYear dayOfRentel(now->tm_mday, 1 + now->tm_mon, 1900 + now->tm_year);


    cout << "SIMPLIFIED SIMULATION OF A RENTAL AGENCY" << endl;
    cout << "========================================" << endl;

    while (1)
    {
        cout << "____________________________" << endl;
        cout << "MENUE" << endl;
        cout << "A end of simulation" << endl;
        cout << "B set new simulation date" << endl;
        cout << "C new rental manually" << endl;
        cout << "D print rental of today " << today  << endl;
        cout << "E print rental of tomorrow " << tomorrow << endl;
        cout << "F print all rentals" << endl;
        cout << "G print agency profit" << endl;
        cout << "H set agency profit percent" << endl;
        cout << "I add bikes" << endl;
        cout << "J add E - bikes" << endl;
        cout << "K add E - scooters" << endl;
        cout << "L new rental simulation" << endl;
        cout << "your choice : ";

        char choose;
        cin >>choose;

        if (choose == 'a' || choose == 'A')
        {

            exit(0);
        }
        else if (choose == 'b' || choose == 'B')
        {
            string v;
            cout << "input date of today: ";
            cin >> today;
            tomorrow=today;
            tomorrow++;;

        }
        else if (choose == 'c' || choose == 'C')
        {
            int index = agency.chooseVehicle();
            if (index != 0)
            {

                cout << "Day of rental:";
                cin >> dayOfRentel;
                cout << "Number of days : ";
                int days;
                cin >> days;
                if (!agency.isFree(index, dayOfRentel, days))
                {
                    cout << "sorry vehicle already booked" << endl;
                }
                else
                {
                    cout << "input data vehicle renter name:";
                    string name;
                    cin >> name;
                    agency.book(index, name, dayOfRentel, days);
                    agency.ppv(index);
                }
            }
        }
        else if (choose == 'd' || choose == 'D')
        {
            agency.print(today);
        }
        else if (choose == 'e' || choose == 'E')
        {
            agency.print(today);
        }
        else if (choose == 'f' || choose == 'F')
        {
            agency.print();
        }
        else if (choose == 'g' || choose == 'G')
        {
            cout << "agency profit: " << agency.get_profit() << " EUR" << endl;
        }
        else if (choose == 'h' || choose == 'H')
        {
            cout << "agency profit percent : ";
            float p;
            cin >> p;
            agency.set_profitPercentage(p);
        }
        else if (choose == 'i' || choose == 'I')
        {
            cout << "How many Bikes in this simulation? ";
            int c;
            cin >> c;
            for (int i = 0; i < c; i++)
            {

                vehicleNumber++;
                string model = "City";
                Bike *b = new Bike(vehicleNumber, model);
                agency.add(b);
            }
        }
        else if (choose == 'j' || choose == 'J')
        {
            cout << "How many EBikes in this simulation? ";
            int c;
            cin >> c;
            for (int i = 0; i < c; i++)
            {
                vehicleNumber++;
                string model1 ="Trekky";

                EBike *e = new EBike(vehicleNumber, model1);
                agency.add(e);
                vehicleNumber++;
            }
        }
        else if (choose == 'k' || choose == 'K')
        {
            cout << "How many EScooters in this simulation? ";
            int c;
            cin >> c;
            for (int i = 0; i < c; i++)
            {

                vehicleNumber++;
                string model = "Scooty";
                bool streetLegal = false;
                EScooter *e = new EScooter(vehicleNumber, model, streetLegal);
                agency.add(e);
            }
        }
        else if (choose == 'l' || choose == 'L')
        {
            cout << "how many reservations to simulate? ";
            int l;
            cin >> l;
            if (l > 0)
            {
                for (int j = 0; j < l; j++)
                {
                    int vehicleRandom = (rand() %
                                         (l - 0)) +
                                        1;
                    int dateRandom = (rand() %
                                      (365 - 0)) +
                                     1;
                    int dysRandom = (rand() %
                                     (7 - 0)) +
                                    1;



                    DayOfYear randomD;
                    if (agency.isFree(vehicleRandom, randomD, dysRandom))
                    {
                        string cuName = "customer" + to_string(j + 1);
                        agency.book(vehicleRandom, cuName, randomD, dysRandom);

                        cout << "rental vehicle :" << vehicleRandom << " from " << randomD << " for " << dysRandom << " days" << endl;
                    }
                    else
                    {
                        cout << "rental vehicle :" << vehicleRandom << " from " << randomD << " for " << dysRandom << " days"
                             << " sorry vehicle already booked" << endl;
                    }
                }
            }
        }
        else
        {
        }
    }

    return 0;
}

