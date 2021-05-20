#ifndef CARS_H
#define CARS_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Node;

class CarModel
{
public:
    int model_id;
    bool sort_by_rate;
    int type_id;
    int num_of_sales;
    int rate;
    CarModel(int model_id, bool sort_by_rate, int type_id, int num_of_sales=0, int rate=0);
    ~CarModel() = default;
    bool operator>(CarModel &model2);
};

CarModel::CarModel(int model_id, bool sort_by_rate, int type_id, int num_of_sales, int rate) : model_id(model_id), sort_by_rate(sort_by_rate), type_id(type_id),
                                                                                               num_of_sales(num_of_sales), rate(rate)
{
}


bool CarModel::operator>(CarModel &model2)
{
    assert(sort_by_rate == model2.sort_by_rate);
    //check by rate//
    if (sort_by_rate == true)
    {
        if (rate > model2.rate)
        {
            return true;
        }
        else if (rate < model2.rate)
        {
            return false;
        }
        else
        {
            if (type_id > model2.type_id)
            {
                return true;
            }
            else if (type_id < model2.type_id)
            {
                return false;
            }
            else
            {
                if (model_id > model2.model_id)
                {
                    return true;
                }
                else if (model_id < model2.model_id)
                {
                    return false;
                }
            }
        }
    }
    //check by sells//
    else
    {
        if (num_of_sales > model2.num_of_sales)
        {
            return true;
        }
        else if (num_of_sales < model2.num_of_sales)
        {
            return false;
        }
        else
        {
            if (type_id > model2.type_id)
            {
                return false;
            }
            else if (type_id < model2.type_id)
            {
                return true;
            }
            else
            {
                if (model_id > model2.model_id)
                {
                    return false;
                }
                else if (model_id < model2.model_id)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

class CarModelList : public CarModel{
    public:
    CarModelList* next;
    CarModelList* previous;
    CarModelList(int model_id, bool sort_by_rate, int type_id, int num_of_sales=0, int rate=0);
    ~CarModelList()=default;
};

CarModelList::CarModelList(int model_id, bool sort_by_rate, int type_id, int num_of_sales, int rate) : 
                                    CarModel(model_id,sort_by_rate,type_id,num_of_sales,rate),next(NULL),previous(NULL)
{}

class CarType{
public:
    int type_id;
    int num_of_models;
    int best_seller;
    int best_seller_sales;
    int** statistics;
    CarModelList **pointers;
    CarType(int type_id, int num_of_models=0,int best_seller=0, int best_seller_sales=0);
    ~CarType();
    bool operator>(CarType &model2);
};

int** creatArrey(int num_of_models){
    int** temp = new int*[2];
    temp[0] = new int[num_of_models];
    temp[1] = new int[num_of_models];
    for(int i=0;i<num_of_models;i++){
        temp[0][i]=0;
        temp[1][i]=0;    
    }
    return temp;
}

CarType::CarType(int type_id, int num_of_models,int best_seller, int best_seller_sales) : type_id(type_id), num_of_models(num_of_models),
                                                    best_seller(best_seller),best_seller_sales(best_seller_sales),
                                                    statistics(creatArrey(num_of_models)),pointers(new CarModelList*[num_of_models])
{

}

CarType::~CarType()
{
    delete[] pointers;
    delete[] statistics[0];
    delete[] statistics[1];
    delete[] statistics;
}

bool CarType::operator>(CarType &type2)
{
    if (type_id > type2.type_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class NewCarType : public CarType{
    public:
        CarModelList* new_list;
        NewCarType(int type_id, int num_of_models=0,int best_seller=0, int best_seller_sales=0);
        ~NewCarType()=default;
};

NewCarType::NewCarType(int type_id, int num_of_models,int best_seller, int best_seller_sales) :
                CarType(type_id,num_of_models,best_seller,best_seller_sales),new_list(NULL){}
                                                  


int max_int(int a, int b) {
  return (a > b) ? a : b;
}


#endif