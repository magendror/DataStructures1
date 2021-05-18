#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "library.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
    int main(){
        void* DS;
        void** ptr = &DS;
        DS=Init();
        StatusType res = AddCarType(DS, 1, 7);
        res = AddCarType(DS, 10, 3);
        res = AddCarType(DS, 100, 5);
        res = SellCar(DS, 10,1);
        res = SellCar(DS, 10,2);
        res = SellCar(DS, 10,1);
        res = SellCar(DS, 100,0);
        res = MakeComplaint(DS, 100,0,8);
        res = SellCar(DS, 100,0);
        res = MakeComplaint(DS, 10,2,6);
        res = SellCar(DS, 100,6);
        res = MakeComplaint(DS, 100,1,7);
        res = MakeComplaint(DS, 100,1,4);
        int* types = new int[3];
        int* models = new int[3];
        //res = GetWorstModels(DS,3,types,models);
        Quit(ptr);
        return 0;
    }
#ifdef __cplusplus
}
#endif