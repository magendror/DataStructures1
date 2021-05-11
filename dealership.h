#ifndef DEALERSHIP_H
#define DEALERSHIP_H
#include "salestree.h"
#include "newtree.h"
#include "typetree.h"
#include "ratetree.h"
#include "cars.h"

class Dealership
{
public:
    TypeNode* type_tree;
    NewNode* new_tree;
    RateNode* rate_tree;
    SalesNode* sales_tree;
    RateNode* WorstRate;
    NewNode* WorstRateNew;
    RateNode* WorstSecondRate;
    NewNode* WorstSecondRateNew;
    int NumOfModels;
    int NumOfNewModels;
    SalesNode* MaxSales;
    Dealership();
    ~Dealership();
};

Dealership::Dealership() : type_tree(NULL), new_tree(NULL), rate_tree(NULL), sales_tree(NULL), WorstRate(NULL),
                           WorstRateNew(NULL), WorstSecondRate(NULL), WorstSecondRateNew(NULL), NumOfModels(0),
                           NumOfNewModels(0), MaxSales(NULL)
{
}

Dealership::~Dealership() {}
#endif