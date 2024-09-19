#include <Arduino.h>
#include "Preference_Manager.h"
#include "WebPortal.h"
#include <WiFi.h>
#include "Footswitch.h"
#include "LedManager.h"
#include <BleKeyboard.h>


// Crear instancias de las clases
BleKeyboard bleKeyboard("ESP32 Keyboard", "Jeremias", 100);
Preference_Manager preferences;
LedManager ledManager(22, 23, 16);  // Pines: luz1=22, luz2=23, luz3=16
WebPortal portal(&preferences);
Footswitch footswitch(19, 21, &preferences, &bleKeyboard, &ledManager);  // Pines para los pulsadores, con preferencias y BLE

unsigned long previousMillis = 0;  // Para el temporizador de 3 segundos
unsigned long bootTime = 0;  // Tiempo en el que el ESP32 arrancó
const long interval = 3000;  // Intervalo de 3 segundos para logs
const long resetTimeout = 3000;  // Tiempo límite para considerar reinicio rápido

void setup() {
    Serial.begin(115200);
    bleKeyboard.begin();  // Iniciar el teclado BLE
    bootTime = millis();  // Guardar el tiempo de arranque

    // Leer el contador de reinicios y aumentarlo
    uint16_t resetCount = preferences.getResetCount();
    resetCount++;
    preferences.setResetCount(resetCount);

    // Verificar si hemos reiniciado más de 3 veces
    if (resetCount > 3) {
        // Entrar en modo configuración
        const char* ssid = "ESP32_Config";
        const char* password = "12345678";

        WiFi.softAP(ssid, password);  // Levantar la red Wi-Fi
        portal.begin();  // Inicia el portal web
        Serial.println("Entrando en modo configuración: WiFi iniciado.");
        ledManager.saltear(500);
    } else {
        Serial.println("Modo normal: no se levantó WiFi.");
    }
}

void loop() {
    unsigned long currentMillis = millis();

    // Verificar si han pasado más de 3 segundos desde el arranque
    if (currentMillis - bootTime > resetTimeout) {
        // Si han pasado más de 3 segundos, reseteamos el contador
        preferences.setResetCount(0);
    }

    // Si estamos en modo configuración (WiFi levantado), manejamos el portal
    if (WiFi.softAPgetStationNum() > 0) {
        portal.handleClient();  // Maneja las solicitudes de los clientes web
    }

    footswitch.loop();  // Controla los pulsadores
    ledManager.loop();  // Controla los leds

    // Lógica adicional cada 3 segundos
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Logs o dump de valores cada 3 segundos
        //preferences.dumpValues();
    }
    
    delay(50);  // Pequeño retardo para evitar sobrecargar el ESP32
}
