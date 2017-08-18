#include "StorageManager.hpp"

bool StorageManager::addFirmwareUpdateRequest(uint16_t shortAddress, uint16_t curr, uint16_t newF, uint64_t updateTime){

    auto firmwareIter = firmUpdateRequests.find(shortAddress);
    if (firmwareIter == firmUpdateRequests.end()){
        cout << "ERROR Firmware update request is already stored. We can not add another one." << endl;
        return false;
    }

    FirmwareUpdateRequest fur;
    fur.targetShortAddress = shortAddress;
    fur.currFirmwareHash = curr;
    fur.newFirmwareHash = newF;
    fur.updateStartTime = updateTime;
    fur.updateEndTime = 0;

    firmUpdateRequests.emplace(shortAddress, fur);

    addToDevices(shortAddress);

    return true;
}

bool StorageManager::finishFirmwareUpdateRequest(uint16_t shortAddress, uint64_t updateTime){

    auto firmwareIter = firmUpdateRequests.find(shortAddress);
    if (firmwareIter == firmUpdateRequests.end()){
        cout << "ERROR No firmware update request found for " << shortAddress << endl;
        return false;
    }
    firmwareIter->second.updateEndTime = updateTime;
    
    if (updateFirmwareInDevice(shortAddress, firmwareIter->second.newFirmwareHash, updateTime)){
        firmUpdateRequests.erase(firmwareIter);
        return true;
    }
    return false;
}

bool StorageManager::addStateUpdateRequest(uint16_t shortAddress, bool toDiscovery, bool toConnected, uint64_t updateTime){

    auto stateIter = stateUpdateRequests.find(shortAddress);
    if (stateIter == stateUpdateRequests.end()){
        cout << "INFO State update request is already stored. It will be replaced with new one." << endl;
        stateUpdateRequests.erase(stateIter);
    }

    StateUpdateRequest sur;
    sur.targetShortAddress = shortAddress;
    sur.updateToDiscovery = toDiscovery;
    sur.updateToConnected = toConnected;
    sur.updateStartTime = updateTime;
    sur.updateEndTime = 0;

    stateUpdateRequests.emplace(shortAddress, sur);

    addToDevices(shortAddress);

    return true;
}

bool StorageManager::finishStateUpdateRequest(uint16_t shortAddress, uint64_t updateTime){
    
    auto stateIter = stateUpdateRequests.find(shortAddress);
    if (stateIter == stateUpdateRequests.end()){
        cout << "ERROR No state update request found for " << shortAddress << endl;
        return false;
    }
    stateIter->second.updateEndTime = updateTime;
    
    if (updateStateInDevice(shortAddress, stateIter->second.updateToDiscovery, stateIter->second.updateToConnected, updateTime)){
        stateUpdateRequests.erase(stateIter);
        return true;
    }
    return false;
}

void StorageManager::saveToJSON(){

    string file = "devices.json";
    ofstream jsonFile(file, ios::out);
    if (jsonFile.is_open()){

        printDevices(jsonFile);
        printFirmwareUpdateRequests(jsonFile);
        printStateUpdateRequests(jsonFile);

        jsonFile.close();
    } else {
        cout << "ERROR Can not open file " << file << endl;
    }
}

//private
void StorageManager::addToDevices(uint16_t shortAddress){
    auto deviceIter = devices.find(shortAddress);
    if (deviceIter == devices.end()){
        Device device;
        device.shortAddress = shortAddress;
        device.lastUpdateTime = now();
        devices.emplace(shortAddress, device);
    }
}

//private
bool StorageManager::updateFirmwareInDevice(uint16_t shortAddress, uint16_t newF, uint64_t updateTime) {
    auto deviceIter = devices.find(shortAddress);
    if (deviceIter == devices.end()){
        cout << "ERROR No device found with shortAddress " << shortAddress;
        return false;
    }
    deviceIter->second.firmwareHash = newF;
    deviceIter->second.firmwareStartTime = updateTime;
    deviceIter->second.lastUpdateTime = updateTime;

    return true;
}

//private
bool StorageManager::updateStateInDevice(uint16_t shortAddress, bool toDiscovery, bool toConnected, uint64_t updateTime) {
    auto deviceIter = devices.find(shortAddress);
    if (deviceIter == devices.end()){
        cout << "ERROR No device found with shortAddress " << shortAddress;
        return false;
    }
    deviceIter->second.discoveryState = toDiscovery;
    deviceIter->second.connectedToBase = toConnected;
    deviceIter->second.lastUpdateTime = updateTime;

    return true;
}

/*
{"devices":[
    { "shortAddress":"123", "extendedAddress":"123456789" },
    { "shortAddress":"124", "extendedAddress":"222222222" }
]}
*/
void StorageManager::printDevices(ofstream &jsonFile){

    size_t size = devices.size();

    jsonFile << "{\"devices\":[" << endl;
    for (auto &device : devices){
        jsonFile << "{ \"shortAddress\":\""<< device.second.shortAddress << "\",";
        jsonFile << "\"extendedAddress\":\"" << device.second.extendedAddress << "\",";
        jsonFile << "\"firmwareHash\":\"" << device.second.firmwareHash << "\",";
        jsonFile << "\"firmwareStartTime\":\"" << device.second.firmwareStartTime << "\",";
        jsonFile << "\"discoveryState\":\"" << device.second.discoveryState << "\",";
        jsonFile << "\"connectedToBase\":\"" << device.second.connectedToBase << "\",";
        jsonFile << "\"on\":\"" << device.second.on << "\",";
        jsonFile << "\"lastUpdateTime\":\"" << device.second.lastUpdateTime << "\",";
        jsonFile << "}";
        if (--size > 0){
            jsonFile << ",";
        }
    }
    jsonFile << "]}";
}

void StorageManager::printFirmwareUpdateRequests(ofstream &jsonFile) {

    size_t size = firmUpdateRequests.size();

    jsonFile << "{\"firmwareUpdateRequests\":[" << endl;
    for (auto &firm : firmUpdateRequests){
        jsonFile << "{ \"targetShortAddress\":\""<< firm.second.targetShortAddress << "\",";
        jsonFile << "\"currFirmwareHash\":\"" << firm.second.currFirmwareHash << "\",";
        jsonFile << "\"newFirmwareHash\":\"" << firm.second.newFirmwareHash << "\",";
        jsonFile << "\"updateStartTime\":\"" << firm.second.updateStartTime << "\",";
        jsonFile << "\"updateEndTime\":\"" << firm.second.updateEndTime << "\",";
        jsonFile << "}";
        if (--size > 0){
            jsonFile << ",";
        }
    }
    jsonFile << "]}";
}

void StorageManager::printStateUpdateRequests(ofstream &jsonFile){

    size_t size = stateUpdateRequests.size();

    jsonFile << "{\"stateUpdateRequests\":[" << endl;
    for (auto &state : stateUpdateRequests){
        jsonFile << "{ \"targetShortAddress\":\""<< state.second.targetShortAddress << "\",";
        jsonFile << "\"updateToDiscovery\":\"" << state.second.updateToDiscovery << "\",";
        jsonFile << "\"updateToConnected\":\"" << state.second.updateToConnected << "\",";
        jsonFile << "\"updateStartTime\":\"" << state.second.updateStartTime << "\",";
        jsonFile << "\"updateEndTime\":\"" << state.second.updateEndTime << "\",";
        jsonFile << "}";
        if (--size > 0){
            jsonFile << ",";
        }
    }
    jsonFile << "]}";
}
