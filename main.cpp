#include <stdio>

#include "StorageManager.h"

int main(){

    cout << "Hej!" << endl;

    StorageManager storageManager;
    storageManager.addFirmwareUpdateRequest(123, 10, 11);
    storageManager.addFirmwareUpdateRequest(124, 20, 21);
    storageManager.addStateUpdateRequest(125, true, false);

    storageManager.saveToJSON();

}