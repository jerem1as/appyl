#ifndef PREFERENCE_MANAGER_H
#define PREFERENCE_MANAGER_H

#include <Preferences.h>

class Preference_Manager {
private:
    Preferences preferences;
    const char* namespaceName = "config";

public:
    Preference_Manager();
    ~Preference_Manager();

    // Setters
    void setAction(int index, uint8_t value);
    void setIsReseted(bool value);
    void setResetCount(uint16_t value);
    void setDeviceName(const char* name);

    // Getters
    uint8_t getAction(int index);
    bool getIsReseted();
    uint16_t getResetCount();
    String getDeviceName();

    // Helper functions
    void saveShort(const char* key, uint16_t value);
    uint16_t readShort(const char* key);
};

#endif