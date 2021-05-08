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
    TypeNode *type_tree;
    NewNode *new_tree;
    ModelNode *rate_tree;
    SalesNode *sales_tree;
    ModelNode *WorstRate;
    ModelNode *WorstRateNew;
    ModelNode *WorstSecondRate;
    ModelNode *WorstSecondRateNew;
    int NumOfModels;
    SalesNode *MaxSales;
    Dealership();
    ~Dealership();
};

Dealership::Dealership() : type_tree(NULL), new_tree(NULL), rate_tree(NULL), sales_tree(NULL), WorstRate(NULL),
                           WorstRateNew(NULL), WorstSecondRate(NULL), WorstSecondRateNew(NULL), NumOfModels(0),
                           MaxSales(NULL)
{
}

Dealership::~Dealership() {}
#endif