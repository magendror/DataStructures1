
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typetree.h"
#include "ratetree.h"
#include "salestree.h"
#include "newtree.h"
#include "library.h"
#include "cars.h"
#include "dealership.h"

void *init(){
    Dealership* ds=new Dealership();
    return ds;

}

void updatePointers(Dealership* DS){
    DS->MaxSales=SalesNodeWithMaxValue(DS->sales_tree);
    DS->WorstRate=RateNodeWithMimumValue(DS->rate_tree);
    DS->WorstSecondRate=RateNodeWithMimumValue(DS->rate_tree->right);
    DS->WorstRateNew=NewNodeWithMimumValue(DS->new_tree);
    DS->WorstRateNew=NewNodeWithMimumValue(DS->new_tree);
}

StatusType RemoveCarType(void *DS, int typeID){
    DS=(Dealership*) DS;
    if(DS==NULL || typeID<=0){
        return INVALID_INPUT;
    }
    TypeNode *typenode=findTypeNode(DS.type_tree,typeID);
    if(typenode==NULL){
        return FAILURE;
    }
    int numofmodels=typenode->key->num_of_models;
    int rate,sales;
    for(int i=0;i< numofmodels;i++){
        rate=typenode->key->statistics[0][i];
        sales=typenode->key->statistics[1][i];
        RateNode* modelnode = findNodeByRate(DS.rate_tree,rate,i,typeID);
        DS.rate_tree=deleteNode(DS.rate_tree,modelnode->key);
        SalesNode=findNodeBySales(DS.sales_tree,sales,i,typeID);
        DS.sales_tree=deleteSalesNode(DS.sales_tree,modelnode->key);
        DS.NumOfModels--;
        while(typenode->key.pointers!=NULL){ ////list delete
            CarModel *nextcar=*(typenode->key.pointers++);
            delete(typenode->key.pointers);
            *(typenode->key.pointers)=nextcar;
            DS.NumOfModels--;
        }
        DS.typetree=deleteTypeNode(DS.typetree,typenode->key);
        updatingmax(DS);
        return SUCCESS;
    }
    //////

}


StatusType makeComplaint(void *DS, int typeID, int modelID, int t){
    DS=(Dealership*)DS;
    if(DS==NULL || typeID<=0 || DS.numofmodel<modelID||modelID<0){
         return INVALID_INPUT;
    }
    TypeNode *typenode=findTypeNode(DS.typetree,typeID);
    if(typenode==NULL){
        return FAILURE;
    }
    int newrate=100/t;
    int rate=typenode->key.statistics[0][modelID];
    RateNode *modelnode=findNodeByRate(DS.ratetree,rate,modelID,typeID);
    DS.ratetree = deleteNode(DS.ratetree,modelnode->key);
    modelnode->key.rate=modelnode->key.rate-newrate;
    DS.ratetree=insertNode(DS.ratetree,modelnode->key);
    updatePointers(DS);
    return SUCCESS;
}

void inorder(RateNode* ratetree,NewNode *newtree,int *types, int *models){
    if(ratetree==NULL){
        return;
    }
    inorder(ratetree->left,newtree,types,models);
    if(ratetree->key.rate==0){

    }

}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models){
    if(DS==NULL || numOfModels<=0){
        return INVALID_INPUT;
    }
    DS=(Dealership*)DS;
    if(numOfModels>DS.NumOfModels){
        return FAILURE;
    }
    int counter=0;
    RateNode* rate_node = NodeWithMimumValue(DS.rate_tree);
    while(counter<numOfModels){
    }
}

StatusType AddCarType(void *DS, int typeID, int numOfModels){
    Dealership* DS_convert = (Dealership*)DS;
    if(DS==NULL||typeID<=0||numOfModels<0){
        return INVALID_INPUT;
    }
    TypeNode* in_type_tree = findTypeNode(DS_convert->type_tree,typeID);
    if(in_type_tree!=NULL){
        return FAILURE;
    }
    CarType* type = new CarType(typeID,numOfModels);
    CarType* new_type = new CarType(typeID,numOfModels);
    insertTypeNode(DS_convert->type_tree,type);
    insertNewNode(DS_convert->new_tree,new_type);
    NewNode* in_new_tree = findNewNode(DS_convert->new_tree,typeID);
    in_type_tree = findTypeNode(DS_convert->type_tree,typeID);
    for (int i=0;i<numOfModels;i++){
        CarModelList* model = new CarModelList(i,true,typeID);
        in_type_tree->key->pointers[i]=model;
        if (i==0){
            in_new_tree->newlist=model;
        }
        else{
            in_type_tree->key->pointers[i]->previous=in_type_tree->key->pointers[i-1];   
        }
    }
    DS_convert->NumOfModels+=numOfModels;
    return SUCCESS;
}

StatusType SellCarForFirstTime(void *DS, int typeID, int modelID){
    Dealership* DS_convert = (Dealership*)DS;
    //if wasent sold yet
    NewNode* in_new_tree = findNewNode(DS_convert->new_tree,typeID);
    TypeNode* in_type_tree = findTypeNode(DS_convert->type_tree,typeID);
    //if first in list
    if(in_new_tree->newlist->model_id==modelID){
        in_new_tree->newlist=in_type_tree->key->pointers[modelID]->next;
        if(((in_type_tree->key->pointers[modelID])->next)!=NULL){
            ((in_type_tree->key->pointers[modelID])->next)->previous=NULL;
        }
        delete in_type_tree->key->pointers[modelID];
        in_type_tree->key->pointers[modelID]=NULL;
        //if also last in list - now list empty
        if(in_new_tree->newlist==NULL){
            CarType* temp = new CarType(typeID);
            deleteNewNode(DS_convert->new_tree,temp);    
        }
    }
    //if not first in list
    else{
        if(((in_type_tree->key->pointers[modelID])->next)!=NULL){
            ((in_type_tree->key->pointers[modelID])->next)->previous=(in_type_tree->key->pointers[modelID])->previous;
        }
        ((in_type_tree->key->pointers[modelID])->previous)->next=(in_type_tree->key->pointers[modelID])->next;
        delete in_type_tree->key->pointers[modelID];
        in_type_tree->key->pointers[modelID]=NULL;
    }
    return SUCCESS; 
}

StatusType SellCar(void *DS, int typeID, int modelID){
    Dealership* DS_convert = (Dealership*)DS;
    if(DS==NULL||typeID<=0||modelID<0){
        return INVALID_INPUT;
    }
    TypeNode* in_type_tree = findTypeNode(DS_convert->type_tree,typeID);
    if (in_type_tree==NULL){
        return FAILURE;
    }
    if (in_type_tree->key->num_of_models<modelID){
        return INVALID_INPUT;    
    }
    CarModel* rate = new CarModel(modelID,true,typeID);
    CarModel* sales = new CarModel(modelID,false,typeID);
    //if wasent sold yet
    if(in_type_tree->key->pointers[modelID]!=NULL){
        SellCarForFirstTime(DS,typeID,modelID);
        rate->rate=10;
        sales->num_of_sales=1;
        (in_type_tree->key->statistics[1][modelID])++;
        (in_type_tree->key->statistics[0][modelID])+=10;
    }
    else{
        RateNode* old_rate = findRateNodeByRate(DS_convert->rate_tree,in_type_tree->key->statistics[0][modelID],
                                                modelID,typeID);
        SalesNode* old_sales = findSalesNodeBySales(DS_convert->sales_tree,in_type_tree->key->statistics[1][modelID],
                                                modelID,typeID);
        (in_type_tree->key->statistics[1][modelID])++;
        (in_type_tree->key->statistics[0][modelID])+=10;
        rate->rate=in_type_tree->key->statistics[0][modelID];
        sales->num_of_sales=in_type_tree->key->statistics[1][modelID];
        CarModel* old_rate_model = old_rate->key;
        CarModel* old_sales_model = old_sales->key;
        deleteRateNode(DS_convert->rate_tree,old_rate_model);
        deleteSalesNode(DS_convert->sales_tree,old_sales_model);
        delete old_rate_model;
        delete old_sales_model;
    }
    insertRateNode(DS_convert->rate_tree,rate);
    insertSalesNode(DS_convert->sales_tree,sales);
    updatePointers(DS_convert);
    return SUCCESS;
}


