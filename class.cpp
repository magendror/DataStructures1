#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CarModel
{
public:
    int model_id;
    int type_id;
    int num_of_sales;
    int rate;
    CarModel* father;
    CarModel* small_son;
    CarModel* big_son;
    int BF;
    int hight;
    int* statistics;
    CarModel(int type_id,int model_id);
    ~CarModel()=default;
};

CarModel::CarModel(int type_id,int model_id):type_id(type_id),model_id(model_id)
{
}

CarModel::~CarModel()
{
}


class CarType
{
public:
    int type_id;
    int num_of_models;
    int best_seller;
    int best_seller_sales;
    CarType* father;
    CarType* small_son;
    CarType* big_son;
    int BF;
    int hight;
    int* statistics;
    CarModel* pointers;
    CarType(int type_id);
    ~CarType()=default;
};

CarType::CarType(int type_id):type_id(type_id)
{
}

CarType::~CarType()
{
}

class Dealership
{
public:
    CarType* type_tree;
    CarType* new_tree;
    CarModel* rate_tree;
    CarType* sales_tree;
    CarModel* WorstRate;
    CarType* WorstRateNew;
    CarModel* WorstSecondRate;
    CarType* WorstSecondRateNew;
    int NumOfModels;
    CarModel* MaxSales;
    Dealership();
    ~Dealership();
};

Dealership::Dealership():type_tree(NULL),new_tree(NULL),rate_tree(NULL),sales_tree(NULL), WorstRate(NULL),
                        WorstRateNew(NULL),WorstSecondRate(NULL),WorstSecondRateNew(NULL),NumOfModels(0),
                        MaxSales(NULL)
{
}

Dealership::~Dealership()
{
}
