#include "Preference_Manager.h"

// Constructor: No necesitamos abrir el namespace aquí, lo haremos en cada operación
Preference_Manager::Preference_Manager() {}

Preference_Manager::~Preference_Manager() {}

// Setters
void Preference_Manager::setAction(int index, uint8_t value) {
    if (index >= 0 && index < 3) {
        char key[10];
        snprintf(key, sizeof(key), "action%d", index);  // Genera la clave "action0", "action1", "action2"
        preferences.begin(namespaceName, false);  // Abre el namespace de Preferences
        preferences.putUInt(key, value);  // Guarda el valor en Preferences
        preferences.end();  // Cierra el namespace
        Serial.print("Guardado action "); Serial.print(index); Serial.print(": "); Serial.println(value);
    } else {
        Serial.println("Índice de acción inválido");
    }
}

void Preference_Manager::setIsReseted(bool value) {
    preferences.begin(namespaceName, false);  // Abre el namespace
    preferences.putBool("is_reseted", value);  // Guarda el valor
    preferences.end();  // Cierra el namespace
}

void Preference_Manager::setResetCount(uint16_t value) {
    preferences.begin(namespaceName, false);  // Abre el namespace
    preferences.putUShort("reset_count", value);  // Guarda el valor
    preferences.end();  // Cierra el namespace
}

void Preference_Manager::setDeviceName(const char* name) {
    preferences.begin(namespaceName, false);  // Abre el namespace
    preferences.putString("device_name", name);  // Guarda el valor
    preferences.end();  // Cierra el namespace
}

// Getters
uint8_t Preference_Manager::getAction(int index) {
    if (index >= 0 && index < 3) {
        char key[10];
        snprintf(key, sizeof(key), "action%d", index);  // Genera la clave "action0", "action1", "action2"
        preferences.begin(namespaceName, true);  // Abre el namespace en modo solo lectura
        uint32_t action = preferences.getUInt(key, 255);  // Lee el valor, por defecto devuelve 255 si no existe
        preferences.end();  // Cierra el namespace

        if (action == 255) {
            Serial.print("Error al leer action "); Serial.println(index);
        } else {
            Serial.print("Leído action "); Serial.print(index); Serial.print(": "); Serial.println(action);
        }
        return action;
    } else {
        Serial.println("Índice de acción inválido");
        return 0;
    }
}

bool Preference_Manager::getIsReseted() {
    preferences.begin(namespaceName, true);  // Abre el namespace
    bool isReseted = preferences.getBool("is_reseted", false);  // Lee el valor
    preferences.end();  // Cierra el namespace
    return isReseted;
}

uint16_t Preference_Manager::getResetCount() {
    preferences.begin(namespaceName, true);  // Abre el namespace
    uint16_t resetCount = preferences.getUShort("reset_count", 0);  // Lee el valor
    preferences.end();  // Cierra el namespace
    return resetCount;
}

String Preference_Manager::getDeviceName() {
    preferences.begin(namespaceName, true);  // Abre el namespace
    String deviceName = preferences.getString("device_name", "ESP32");  // Lee el valor
    preferences.end();  // Cierra el namespace
    return deviceName;
}
