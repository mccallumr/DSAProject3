#include <vector>
#include <string>
using namespace std;

struct CarNode
{
    int price;
    string currency;
    bool used;
    string brand;
    string model;
    int year;
    string type;
    string color;
    CarNode(int price, string currency, bool used, string brand, string model, int year, string type, string color)
    {
        this->price = price;
        this->currency = currency;
        this->used = used;
        this->brand = brand;
        this->model = model;
        this->year = year;
        this->type = type;
        this->color = color;
    }
};


class CarHash {
    int buckets;
    int* BrandLibrary;
public:
    CarHash() {};

    void insert() {};
    void rehash() {};
};
