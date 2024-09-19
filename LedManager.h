#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>

class LedManager {
public:
    LedManager(uint8_t pin1, uint8_t pin2, uint8_t pin3);
    
    void hit(uint8_t luz, unsigned long time);
    void titilar(uint8_t luz, int cantidad_de_titileos, unsigned long tiempo);
    void pararDeTitilar();
    void saltear(unsigned long time);
    void pararDeSaltear();
    void encender(uint8_t luz);     // Método para dejar la luz permanentemente prendida
    void apagar(uint8_t luz);       // Método para apagar la luz
    void loop();  // Método para ser llamado desde el loop principal

private:
    uint8_t _pin1, _pin2, _pin3;
    bool _titilando;
    unsigned long _lastTime;
    unsigned long _hitTime;
    int _cantidad_de_titileos;
    unsigned long _titilarTime;
    unsigned long _saltearTime;
    bool _salteando;
    bool _hit;
    int _currentLight;
    int _titilarLuz;
    void alternarLuces();
    void handleHit();
    void handleTitilar();
    void handleSaltear();
};

#endif
