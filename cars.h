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
    return true;
}

class CarType
{
public:
    int type_id;
    int num_of_models;
    int best_seller;
    int best_seller_sales;
    int *statistics;
    CarModel **pointers;
    CarType(int type_id, int num_of_models,int best_seller=0, int best_seller_sales=0);
    ~CarType();
    bool operator>(CarType &model2);
};

CarType::CarType(int type_id, int num_of_models,int best_seller, int best_seller_sales) : type_id(type_id), num_of_models(num_of_models),
                                                    best_seller(best_seller),best_seller_sales(best_seller_sales),
                                                    statistics(new int[2 * num_of_models]),pointers(new CarModel *[num_of_models])
{
}

CarType::~CarType()
{
    delete[] pointers;
    delete[] statistics;
}
bool CarType::operator>(CarType &type2)
{
    assert(type_id == type2.type_id);
    if (type_id > type2.type_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}


#endif