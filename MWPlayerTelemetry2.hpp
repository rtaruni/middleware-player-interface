/**
 * @file MWPlayerTelemetry2.hpp
 * @brief Supporting class to provide telemetry support to MWPlayer
 */

#ifndef __MWPLAYER_TELEMETRY_2_H__
#define __MWPLAYER_TELEMETRY_2_H__

#include <cjson/cJSON.h>
#include <iostream>
#include <string>
#include <map>
#include "PlayerLogManager.h"

// Note that RDK telemetry 2.0 support is per process basic, 
// this class is created to take care of un initialization of telemetry but having object as global variable 
// when process goes down, destructor of this class will be called and it will uninitialize the telemetry. 

class MWPlayer_TelemetryInitializer {
private:
    bool m_Initialized = false;
public:
    MWPlayer_TelemetryInitializer();
    void Init();
    bool isInitialized() const; 
    ~MWPlayer_TelemetryInitializer();
};


class MWPlayerTelemetry2 {
private:
    static MWPlayer_TelemetryInitializer mInitializer;
    std::string appName;
    
public:
    /**
     * @brief Constructor
     * @param[in] NONE
     */
    MWPlayerTelemetry2();
    
    /**
     * @brief Constructor
     * @param[in] appName - Name of the application
     */
    MWPlayerTelemetry2(const std::string &appName);
    
    /**
     *  
     * @brief send  - Send the telemetry data to the telemetry bus by converting input map to json string
     * @param[in] markerName - Name of the marker
     * @param[in] intData - Map of int data
     * @param[in] stringData - Map of string data
     * @param[in] floatData - Map of float data
     * @return bool - true if success, false otherwise
     */
    bool send(const std::string &markerName, const std::map<std::string, int>& intData, const std::map<std::string, std::string>& stringData, const std::map<std::string, float>& floatData);
    
    /**
     * @brief send  - Send the telemetry data to the telemetry bus
     * @param[in] markerName - Name of the marker
     * @param[in] data - Data to be sent
     */
    bool send(const std::string &markerName, const char *  data);
};

#endif // __MWPLAYER_TELEMETRY_2_H__
