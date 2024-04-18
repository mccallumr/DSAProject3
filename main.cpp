#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ProvinceMap.h"
using namespace std;

int main() {

    vector<CarNode*> cars;
    ifstream carFile;
    carFile.open("Car_sale_ads.csv");

    string line = "";
    getline(carFile, line);
    line = "";
    while(getline(carFile, line))
    {
        CarNode* newCar = new CarNode;

        int index;
        int price;
        string currency;
        bool used = false;
        string brand;
        string model;
        string version;
        string generation;
        int year;
        int mileage;
        int horsepower;
        int displacement;
        string fuel_type;
        int emissions;
        string drive;
        bool manual = false;
        string type;
        int num_doors;
        string color;
        string country;
        bool first_owner = false;
        string register_date;
        string offer_date;
        string location;
        string features;
        //vector<string> features;

        string temp = "";
        stringstream inputString(line);

        getline(inputString, temp, ',');
        index = atoi(temp.c_str());
        newCar->index = index;
        temp = "";
        getline(inputString, temp, ',');
        price = atoi(temp.c_str());
        temp = "";
        newCar->price = price;
        getline(inputString, currency, ',');
        newCar->currency = currency;
        getline(inputString, temp, ',');
        if(temp == "Used")
        {
            used = true;
        }
        newCar->used = used;
        temp = "";
        getline(inputString, brand, ',');
        newCar->brand = brand;
        getline(inputString, model, ',');
        newCar->model = model;
        getline(inputString, version, ',');
        newCar->version = version;
        getline(inputString, generation, ',');
        newCar->generation = generation;
        getline(inputString, temp, ',');
        year = atoi(temp.c_str());
        newCar->year = year;
        temp = "";
        getline(inputString, temp, ',');
        mileage = atoi(temp.c_str());
        newCar->mileage = mileage;
        temp = "";
        getline(inputString, temp, ',');
        horsepower = atoi(temp.c_str());
        newCar->horsepower = horsepower;
        temp = "";
        getline(inputString, temp, ',');
        displacement = atoi(temp.c_str());
        newCar->displacement = displacement;
        temp = "";
        getline(inputString, fuel_type, ',');
        newCar->fuel_type = fuel_type;
        getline(inputString, temp, ',');
        emissions = atoi(temp.c_str());
        newCar->emissions = emissions;
        temp = "";
        getline(inputString, drive, ',');
        newCar->drive = drive;
        getline(inputString, temp, ',');
        if(temp == "Manual")
        {
            manual = true;
        }
        newCar->manual = manual;
        temp = "";
        getline(inputString, type, ',');
        newCar->type = type;
        getline(inputString, temp, ',');
        num_doors = atoi(temp.c_str());
        newCar->num_doors = num_doors;
        temp = "";
        getline(inputString, color, ',');
        newCar->color = color;
        getline(inputString, country, ',');
        newCar->country = country;
        getline(inputString, temp, ',');
        if(temp == "Yes")
        {
            first_owner = true;
        }
        newCar->first_owner = first_owner;
        temp = "";
        getline(inputString, register_date, ',');
        newCar->register_date = register_date;
        getline(inputString, offer_date, ',');
        newCar->offer_date = offer_date;
        getline(inputString, location, '[');
        newCar->location = location;
        getline(inputString, features, ']');
        newCar->features = features;

        line = "";

        cars.push_back(newCar);
    }


    // print out some of the features!
    auto test = cars[9];
    cout << "index: " << test->index << endl;
    cout << "price: " << test->price << endl;
    cout << "location: " << test->location << endl;
    cout << "features: " <<test->features << endl;



    return 0;
}