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
        int price;
        string currency;
        bool used = false;
        string brand;
        string model;
        int year;
        string type;
        string color;

        string temp = "";
        string skip = "";
        stringstream inputString(line);

        getline(inputString, skip, ','); // skip index

        getline(inputString, temp, ',');
        price = atoi(temp.c_str());
        temp = "";
        getline(inputString, currency, ',');
        //newCar->currency = currency;
        getline(inputString, temp, ',');
        if(temp == "Used")
        {
            used = true;
        }
        temp = "";
        getline(inputString, brand, ',');
        getline(inputString, model, ',');

        getline(inputString, skip, ','); // skip version
        getline(inputString, skip, ','); // skip generation

        getline(inputString, temp, ',');
        year = atoi(temp.c_str());
        temp = "";

        getline(inputString, skip, ','); // skip mileage
        getline(inputString, skip, ','); // skip horsepower
        getline(inputString, skip, ','); //skip displacement
        getline(inputString, skip, ','); // skip fuel type
        getline(inputString, skip, ','); // skip emissions
        getline(inputString, skip, ','); // skip drive
        getline(inputString, skip, ','); // skip manual


        getline(inputString, type, ',');

        getline(inputString, skip, ','); // skip num doors

        getline(inputString, color, ',');

        getline(inputString, skip, ','); // skip country
        getline(inputString, skip, ','); // skip first owner

        getline(inputString, skip, ','); // skip register date
        getline(inputString, skip, ','); // skip offer date
        getline(inputString, skip, '['); // skip location
        getline(inputString, skip, ']'); // skip features

        line = "";

        CarNode* newCar = new CarNode(price, currency, used, brand, model, year, type, color);
        cars.push_back(newCar);
    }


    // print out some of the features!
    auto test = cars[75760];
    cout << "price: " << test->price << endl;
    cout << "currency: " << test->currency << endl;
    cout << "used: " << test->used << endl;
    cout << "brand: " << test->brand << endl;
    cout << "model: " << test->model << endl;
    cout << "year: " << test->year << endl;
    cout << "type: " << test->type << endl;
    cout << "color: " << test->color << endl;

    return 0;
}