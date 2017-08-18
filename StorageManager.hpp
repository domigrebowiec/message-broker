#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <cstdint>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

uint64_t now(){
    return 123;
}

class Device {
    friend class StorageManager;
    private:
        string name;
        uint16_t shortAddress;
        uint64_t extendedAddress;

        uint16_t firmwareHash;
        uint64_t firmwareStartTime;

        bool discoveryState;
        bool connectedToBase;
        bool on;

        uint64_t lastUpdateTime;
};

class UpdateRequest {
    friend class StorageManager;
    private:
        uint16_t targetShortAddress;
        uint64_t updateStartTime;
        uint64_t updateEndTime;
};
class FirmwareUpdateRequest : public UpdateRequest {
    friend class StorageManager;
    private:
        uint16_t currFirmwareHash;
        uint16_t newFirmwareHash;
        
};
class StateUpdateRequest : public UpdateRequest {
    friend class StorageManager;
    private:
        bool updateToDiscovery;
        bool updateToConnected;
};

class StorageManager {
    public:
        bool addFirmwareUpdateRequest(uint16_t shortAddress, uint16_t curr, uint16_t newF, uint64_t updateTime=now());
        bool finishFirmwareUpdateRequest(uint16_t shortAddress, uint64_t updateTime=now());

        bool addStateUpdateRequest(uint16_t shortAddress, bool toDiscovery, bool toConnected, uint64_t updateTime=now());
        bool finishStateUpdateRequest(uint16_t shortAddress, uint64_t updateTime=now());

        void saveToJSON();

    private:
        map<uint16_t, Device> devices;
        map<uint16_t, FirmwareUpdateRequest> firmUpdateRequests;
        map<uint16_t, StateUpdateRequest> stateUpdateRequests;

        void addToDevices(uint16_t shortAddress);

        bool updateFirmwareInDevice(uint16_t shortAddress, uint16_t newF, uint64_t updateTime=now());
        bool updateStateInDevice(uint16_t shortAddress, bool toDiscovery, bool toConnected, uint64_t updateTime=now());

        void printDevices(ofstream &jsonFile);
        void printFirmwareUpdateRequests(ofstream &jsonFile);
        void printStateUpdateRequests(ofstream &jsonFile);
};

#endif
