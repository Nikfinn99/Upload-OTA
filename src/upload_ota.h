#pragma once

/**
 * @brief Setup the ArduinoOTA with usefull default callbacks and parameters
 * 
 * @param pw (optional) password for OTA upload
 * @param name (optional) mDNS hostname
 */
void setupOTA(const char *pw = nullptr, const char *name = nullptr);

/**
 * @brief internal loop for ota upload
 */
void loopOTA();
