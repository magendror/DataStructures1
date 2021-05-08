
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

void updatingmax(Dealership* ds){
    ds->WorstRate=NodeWithMimumValue(ds->rate_tree);
    // ModelNode* WorstRateNew;
    // ModelNode* WorstSecondRate;
    // ModelNode* WorstSecondRateNew;
    ds->MaxSales=SalesnodeWithMimumValue(ds->sales_tree)->key.num_of_sales;

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
        ModelNode *modelnode=findNodeByRate(DS.rate_tree,rate,i,typeID);
        DS.rate_tree=deleteNode(DS.rate_tree,modelnode->key);
        modelnode=findNodeBySales(DS.sales_tree,sales,i,typeID);
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
    ModelNode *modelnode=findNodeByRate(DS.ratetree,rate,modelID,typeID);
    DS.ratetree=deleteNode(DS.ratetree,modelnode->key);
    modelnode->key.rate=modelnode->key.rate-newrate;
    DS.ratetree=insertNode(DS.ratetree,modelnode->key);
    updatingmax(DS);
    return SUCCESS;
}

void inorder(ModelNode*ratetree,Node *newtree,int *types, int *models){
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
    ModelNode *rate_node=NodeWithMimumValue(DS.rate_tree);
    while(counter<numOfModels){
    }
}

StatusType AddCarType(void *DS, int typeID, int numOfModels){
    Dealership* DS_convert = (Dealership*)DS;
    if(DS==NULL||typeID<=0||numOfModels<0){
        return INVALID_INPUT;
    }
    CarType* type = new CarType(typeID,numOfModels);
    CarType* new_type = new CarType(typeID,numOfModels);
    insertTypeNode(DS_convert->type_tree,type);
    insertNode(DS_convert->new_tree,new_type);
    ();
    return SUCCESS;
}


