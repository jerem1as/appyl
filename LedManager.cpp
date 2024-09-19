#include "LedManager.h"

LedManager::LedManager(uint8_t pin1, uint8_t pin2, uint8_t pin3)
    : _pin1(pin1), _pin2(pin2), _pin3(pin3), _titilando(false), _hit(false), _salteando(false), _currentLight(1) {
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    pinMode(_pin3, OUTPUT);
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    digitalWrite(_pin3, LOW);
}

void LedManager::hit(uint8_t luz, unsigned long time) {
    _hit = true;
    _hitTime = millis() + time;

    if (luz == 1) digitalWrite(_pin1, HIGH);
    else if (luz == 2) digitalWrite(_pin2, HIGH);
    else if (luz == 3) digitalWrite(_pin3, HIGH);
}

void LedManager::titilar(uint8_t luz, int cantidad_de_titileos, unsigned long tiempo) {
    if (_titilando){return;}
    _titilarLuz = luz;
    _titilarTime = tiempo;
    _cantidad_de_titileos = cantidad_de_titileos * 2;  // Cada ciclo incluye ON y OFF
    _titilando = true;
    _lastTime = millis();
}

void LedManager::pararDeTitilar() {
    _titilando = false;
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    digitalWrite(_pin3, LOW);
}

void LedManager::saltear(unsigned long time) {
    _saltearTime = time;
    _salteando = true;
    _lastTime = millis();
}

void LedManager::pararDeSaltear() {
    _salteando = false;
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
}

void LedManager::encender(uint8_t luz) {
    if (luz == 1) digitalWrite(_pin1, HIGH);
    else if (luz == 2) digitalWrite(_pin2, HIGH);
    else if (luz == 3) digitalWrite(_pin3, HIGH);
}

void LedManager::apagar(uint8_t luz) {
    if (luz == 1) digitalWrite(_pin1, LOW);
    else if (luz == 2) digitalWrite(_pin2, LOW);
    else if (luz == 3) digitalWrite(_pin3, LOW);
}

void LedManager::loop() {
    handleHit();
    handleTitilar();
    handleSaltear();
}

void LedManager::handleHit() {
    if (_hit && millis() > _hitTime) {
        digitalWrite(_pin1, LOW);
        digitalWrite(_pin2, LOW);
        digitalWrite(_pin3, LOW);
        _hit = false;
    }
}

void LedManager::handleTitilar() {
    if (_titilando && millis() - _lastTime >= _titilarTime) {
        uint8_t pin;
        if (_titilarLuz == 1) pin = _pin1;
        else if (_titilarLuz == 2) pin = _pin2;
        else if (_titilarLuz == 3) pin = _pin3;
        else return;

        digitalWrite(pin, !digitalRead(pin));
        _lastTime = millis();

        if (_cantidad_de_titileos > 0) {
            _cantidad_de_titileos--;
            if (_cantidad_de_titileos == 0) {
                pararDeTitilar();
            }
        }
    }
}

void LedManager::handleSaltear() {
    if (_salteando && millis() - _lastTime >= _saltearTime) {
        if (_currentLight == 1) {
            digitalWrite(_pin1, HIGH);
            digitalWrite(_pin2, LOW);
            _currentLight = 2;
        } else {
            digitalWrite(_pin1, LOW);
            digitalWrite(_pin2, HIGH);
            _currentLight = 1;
        }
        _lastTime = millis();
    }
}
