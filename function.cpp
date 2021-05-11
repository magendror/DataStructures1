
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

void* Init(){
    Dealership* ds=new Dealership();
    return ds;
}

void updatePointers(Dealership* DS){
    DS->MaxSales=SalesNodeWithMaxValue(DS->sales_tree);
    DS->WorstRate=RateNodeWithMimumValue(DS->rate_tree);
    DS->WorstSecondRate=RateNodeWithMimumValue(DS->rate_tree->right);
    DS->WorstRateNew=NewNodeWithMimumValue(DS->new_tree);
    DS->WorstSecondRateNew=NewNodeWithMimumValue(DS->new_tree->right);
}

void updatePointersMinimalistic(Dealership* DS){
    DS->WorstRateNew=NewNodeWithMimumValue(DS->new_tree);
    DS->WorstSecondRateNew=NewNodeWithMimumValue(DS->new_tree->right);
}

StatusType RemoveCarType(void *DS, int typeID){
    Dealership* DS_convert = (Dealership*)DS;
    if(DS==NULL || typeID<=0){
        return INVALID_INPUT;
    }
    TypeNode *type_node=findTypeNode(DS_convert->type_tree,typeID);
    if(type_node==NULL){
        return FAILURE;
    }
    //delete from rate and sales tree
    int num_of_models=type_node->key->num_of_models;
    int rate,sales;
    for(int i=0;i< num_of_models;i++){
        rate=type_node->key->statistics[0][i];
        sales=type_node->key->statistics[1][i];
        if(sales!=0){
            RateNode* model_node_rate = findRateNodeByRate(DS_convert->rate_tree,rate,i,typeID);
            CarModel* temp = model_node_rate->key;
            DS_convert->rate_tree=deleteRateNode(DS_convert->rate_tree,temp);
            delete temp;
            SalesNode* model_node_sales=findSalesNodeBySales(DS_convert->sales_tree,sales,i,typeID);
            temp = model_node_sales->key;
            DS_convert->sales_tree=deleteSalesNode(DS_convert->sales_tree,temp);
            delete temp;
        }
    }
    //delete list from new tree
    for(int i=0;i<type_node->key->num_of_models;i++){
        if (type_node->key->pointers[i]!=NULL){
                delete type_node->key->pointers[i];
                (DS_convert->NumOfNewModels)--;
        } 
    }
    NewNode *new_node=findNewNode(DS_convert->new_tree,typeID);
    CarType* temp_type = new_node->key;
    DS_convert->new_tree = deleteNewNode(DS_convert->new_tree,temp_type);
    delete temp_type;
    //delete from new tree
    temp_type = type_node->key;
    DS_convert->type_tree=deleteTypeNode(DS_convert->type_tree,temp_type);
    (DS_convert->NumOfModels)-=temp_type->num_of_models;
    delete temp_type;
    updatePointers(DS_convert);
    return SUCCESS;
}

StatusType MakeComplaint(void *DS, int typeID, int modelID, int t){
    Dealership* DS_convert = (Dealership*)DS;
    if(DS==NULL || typeID<=0 ||modelID<0){
         return INVALID_INPUT;
    }
    TypeNode *type_node=findTypeNode(DS_convert->type_tree,typeID);
    if(type_node==NULL){
        return FAILURE;
    }
    if(type_node->key->num_of_models<modelID){
        return FAILURE;
    }
    int newrate=100/t;
    int rate=type_node->key->statistics[0][modelID];
    RateNode* model_node=findRateNodeByRate(DS_convert->rate_tree,rate,modelID,typeID);
    //CarModel* temp = model_node->key;
    DS_convert->rate_tree = deleteRateNode(DS_convert->rate_tree,model_node->key);
    model_node->key->rate=model_node->key->rate-newrate;
    type_node->key->statistics[0][modelID]-=newrate;
    DS_convert->rate_tree=insertRateNode(DS_convert->rate_tree,model_node->key);
    updatePointers(DS_convert);
    return SUCCESS;
}

static void rateInorder(RateNode* rate_tree,int *types, int *models,int len,int *rate, int index=0){
    if(index>=len||rate_tree==NULL){
        return;
    }
    rateInorder(rate_tree->left,types,models,len,rate,index);
    if(index<len){
        types[index]=rate_tree->key->type_id;
        models[index]=rate_tree->key->model_id;
        rate[index]=rate_tree->key->rate;
        index++;
    }
    rateInorder(rate_tree->right,types,models,len,rate,index);
}

static void newInorder(NewNode* new_tree,int *types, int *models,int len,int index=0){
    if(index>=len||new_tree==NULL){
        return;
    }
    newInorder(new_tree->left,types,models,len,index);
    if(index<len){
        CarModelList* current = new_tree->newlist;
        while(index<len && current!=NULL){
            types[index]=new_tree->key->type_id;
            models[index]=current->model_id;
            index++;
            current=current->next;
        }
    }
    newInorder(new_tree->right,types,models,len,index);
}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models){
    if(DS==NULL || numOfModels<=0){
        return INVALID_INPUT;
    }
    Dealership* DS_convert = (Dealership*)DS;
    if(numOfModels>DS_convert->NumOfModels){
        return FAILURE;
    }
    int index=0;
    int index_rate=0;
    int index_new=0;
    int max_rate = numOfModels>(DS_convert->NumOfModels-DS_convert->NumOfNewModels)? DS_convert->NumOfModels-DS_convert->NumOfNewModels:numOfModels;
    int max_new = numOfModels>(DS_convert->NumOfNewModels)? DS_convert->NumOfNewModels:numOfModels;
    int rate_types[max_rate];
    int rate_model[max_rate];
    int rate[max_rate];
    int new_types[max_new];
    int new_model[max_new];
    rateInorder(DS_convert->rate_tree,rate_types,rate_model,max_rate,rate);
    newInorder(DS_convert->new_tree,new_types,new_model,numOfModels);
    //writing all negative rate

    while(index<numOfModels&&index_rate<max_rate&&index_new<max_new){
        if(rate[index_rate]<0){
            types[index]=rate_types[index_rate];
            models[index]=rate_model[index_rate];
            index++;
            index_rate++; 
        }
        else if(rate[index_rate]>0){
            types[index]=new_types[index_new];
            models[index]=new_model[index_new];
            index++;
            index_new++; 
        }
        else{
            if(rate_types[index_rate]<new_types[index_new]){
                types[index]=rate_types[index_rate];
                models[index]=rate_model[index_rate];
                index++;
                index_rate++; 
            }
            else if(rate_types[index_rate]>new_types[index_new]){
                types[index]=new_types[index_new];
                models[index]=new_model[index_new];
                index++;
                index_new++; 
            }
            else{
                if(rate_model[index_rate]<new_model[index_new]){
                    types[index]=rate_types[index_rate];
                    models[index]=rate_model[index_rate];
                    index++;
                    index_rate++; 
                }
                else{
                    types[index]=new_types[index_new];
                    models[index]=new_model[index_new];
                    index++;
                    index_new++;   
                }
            }
        }
    }

    if(index>=numOfModels){
        return SUCCESS;
    }
    while(index<numOfModels&&index_rate<max_rate){
        types[index]=rate_types[index_rate];
        models[index]=rate_model[index_rate];
        index++;
        index_rate++; 
    }
    while(index<numOfModels&&index_new<max_new){
        types[index]=new_types[index_new];
        models[index]=new_model[index_new];
        index++;
        index_new++; 
    }
    return SUCCESS;
}
/*
    while (rate[index]<0 && index<numOfModels && index<(DS_convert->NumOfModels-DS_convert->NumOfNewModels)){
        types[index]=rate_types[index];
        models[index]=rate_model[index];
        index++;
    }
    if(index==numOfModels){
        return SUCCESS;
    }
    if(rate[index]>0){
        /// need to add Num of new//
        for(int i=0;i<DS_convert->NumOfNewModels && index<numOfModels;i++){
            if(index+i<numOfModels)
            types[index]=new_types[i];
            models[index]=new_model[i];
            index++;
        }
        while(index<numOfModels){
            types[index]=rate_types[index];
            models[index]=rate_model[index];
            index++;
        }
        return SUCCESS; 
    }
    ///rate[index]==0
    else {
        while(index<numOfModels){
            while(rate_types[index]<new_types[index] && index<numOfModels){
                types[index]=rate_types[index];
                models[index]=rate_model[index];
                index++;
            }
            while(rate_model[index]<new_model[index] && index<numOfModels){
                types[index]=rate_types[index];
                models[index]=rate_model[index];
                index++;
            }
            if(index<numOfModels){
                types[index]=new_types[index];
                models[index]=new_model[index];
                index++;
            }
        }
    }
}
*/
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
    DS_convert->type_tree = insertTypeNode(DS_convert->type_tree,type);
    DS_convert->new_tree = insertNewNode(DS_convert->new_tree,new_type);
    NewNode* in_new_tree = findNewNode(DS_convert->new_tree,typeID);
    in_type_tree = findTypeNode(DS_convert->type_tree,typeID);
    for (int i=0;i<numOfModels;i++){
        CarModelList* model = new CarModelList(i,true,typeID);
        in_type_tree->key->pointers[i]=model;
        if (i==0){
            in_new_tree->newlist=model;
        }
        else if(i==numOfModels-1){
            in_type_tree->key->pointers[i]->previous=in_type_tree->key->pointers[i-1];   
        }
        else{
            in_type_tree->key->pointers[i]->previous=in_type_tree->key->pointers[i-1];
            in_type_tree->key->pointers[i-1]->next=in_type_tree->key->pointers[i];
        }
    }
    DS_convert->NumOfModels+=numOfModels;
    DS_convert->NumOfNewModels+=numOfModels;
    updatePointersMinimalistic(DS_convert);
    return SUCCESS;
}

void SellCarForFirstTime(void *DS, int typeID, int modelID){
    Dealership* DS_convert = (Dealership*)DS;
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
            DS_convert->new_tree=deleteNewNode(DS_convert->new_tree,temp);
            delete temp;    
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
    (DS_convert->NumOfNewModels)--;
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
    //if was sold already
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
        DS_convert->rate_tree=deleteRateNode(DS_convert->rate_tree,old_rate_model);
        DS_convert->sales_tree=deleteSalesNode(DS_convert->sales_tree,old_sales_model);
        delete old_rate_model;
        delete old_sales_model;
    }
    //type best seller update
    if(in_type_tree->key->statistics[1][modelID]>in_type_tree->key->best_seller_sales){
        in_type_tree->key->best_seller_sales=in_type_tree->key->statistics[1][modelID];
        in_type_tree->key->best_seller=modelID;
    }
    else if(in_type_tree->key->statistics[1][modelID]==in_type_tree->key->best_seller_sales&&
            modelID<in_type_tree->key->best_seller){
        in_type_tree->key->best_seller=modelID;
    }
    DS_convert->rate_tree=insertRateNode(DS_convert->rate_tree,rate);
    DS_convert->sales_tree=insertSalesNode(DS_convert->sales_tree,sales);
    updatePointers(DS_convert);
    return SUCCESS;
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int *modelID){
    Dealership* DS_convert = (Dealership*)DS;
    if(DS==NULL||typeID<0){
        return INVALID_INPUT;
    }
    if(DS_convert->MaxSales==NULL&&DS_convert->NumOfModels>0){
        *modelID=0;
        return SUCCESS;
    }
    if(DS_convert->NumOfModels==0){
        return FAILURE;
    }
    if (typeID==0){
        *modelID=DS_convert->MaxSales->key->model_id;
        return SUCCESS;
    }
    else{
        TypeNode* in_type_tree = findTypeNode(DS_convert->type_tree,typeID);
        if (in_type_tree==NULL){
            return FAILURE;
        }
        *modelID=in_type_tree->key->best_seller;
        return SUCCESS;
    }
}

void clearSalesNode(SalesNode* current){
    if (current==NULL){
        return;
    }
    clearSalesNode(current->left);
    clearSalesNode(current->right);
    delete current->key;
    delete current;
}

void clearRateNode(RateNode* current){
    if (current==NULL){
        return;
    }
    clearRateNode(current->left);
    clearRateNode(current->right);
    delete current->key;
    delete current;
}

void clearTypeNode(TypeNode* current){
    if (current==NULL){
        return;
    }
    clearTypeNode(current->left);
    clearTypeNode(current->right);
    delete current->key;
    delete current;
}

void clearNewNode(NewNode* current){
    if (current==NULL){
        return;
    }
    clearNewNode(current->left);
    clearNewNode(current->right);
    while(current->newlist!=NULL){
        CarModelList* temp = current->newlist->next;
        delete current->newlist;
        current->newlist=temp;
    }
    delete current->key;
    delete current;
}

void Quit(void **DS){
    Dealership* DS_convert = (Dealership*)*DS;
    clearSalesNode(DS_convert->sales_tree);
    clearNewNode(DS_convert->new_tree);
    clearTypeNode(DS_convert->type_tree);
    clearRateNode(DS_convert->rate_tree);
    delete DS_convert;
}




