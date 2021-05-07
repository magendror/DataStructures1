#ifndef CLASS
#define CLASS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typetree.h"
#include "ratetree.h"
#include "salestree.h"
#include "newtree.h"
class CarModel
{
public:
    int model_id;
    bool sort_by_rate;
    int type_id;
    int num_of_sales;
    int rate;
    CarModel(int model_id,bool sort_by_rate,int type_id,int num_of_sales,int rate);
    ~CarModel()=default;
    bool operator>(CarModel& model2);
};

CarModel::CarModel(int model_id,bool sort_by_rate,int type_id,int num_of_sales,int rate):
                                    type_id(type_id),model_id(model_id),sort_by_rate(sort_by_rate),
                                    num_of_sales(num_of_sales),rate(rate)
{
}

CarModel::~CarModel()
{
}
bool CarModel::operator>(CarModel& model2){
    assert(sort_by_rate==model2.sort_by_rate);
    //check by rate//
    if(sort_by_rate==true){
        if(rate>model2.rate){
            return true;
        }
        else if(rate<model2.rate){
            return false;
        }
        else{
            if(type_id>model2.type_id){
                return true;
            }
            else if(type_id<model2.type_id){
                return false;
            }
            else{
                if(model_id>model2.model_id){
                    return true;
                }
            else if(model_id<model2.model_id){
                return false;
                }
            }
        }
    }
    //check by sells//
    else if(sort_by_rate==false){
        if(num_of_sales>model2.num_of_sales){
            return true;
        }
        else if(num_of_sales<model2.num_of_sales){
            return false;
        }
        else{
            if(type_id>model2.type_id){
                return false;
            }
            else if(type_id<model2.type_id){
                return true;
            }
            else{
                if(model_id>model2.model_id){
                    return false;
                }
            else if(model_id<model2.model_id){
                return true;
                }
            }
        }
    }
}

class CarType
{
public:
    int type_id;
    int num_of_models;
    int best_seller;
    int best_seller_sales;
    int* statistics;
    CarModel** pointers;
    CarModel* zero_list;
    CarType(int type_id,int num_of_models);
    ~CarType();
    bool operator>(CarType& model2);
};

CarType::CarType(int type_id,int num_of_models):
        type_id(type_id),num_of_models(num_of_models),pointers(new CarModel*[num_of_models]),
                statistics(new int[2*num_of_models])
                {}

CarType::~CarType()
{
    delete[] pointers;
    delete[] statistics;
}
bool CarType::operator>(CarType& type2){
    assert(type_id==type2.type_id);
    if(type_id>type2.type_id){
        return true;
    }
    else{
        return false;
    }
}
class Dealership
{
public:
    TypeNode* type_tree;
    Node* new_tree;
    ModelNode* rate_tree;
    SalesNode* sales_tree;
    ModelNode* WorstRate;
    ModelNode* WorstRateNew;
    ModelNode* WorstSecondRate;
    ModelNode* WorstSecondRateNew;
    int NumOfModels;
    SalesNode* MaxSales;
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
#endif