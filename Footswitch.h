#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

#include <Arduino.h>
#include "Preference_Manager.h"
#include "LedManager.h"
#include <BleKeyboard.h>

class Footswitch {
private:
  int button1Pin, button2Pin;
  bool inverseMode1, inverseMode2;
  unsigned long button1PressedTime, button2PressedTime;
  unsigned long longPressThreshold;
  bool button1Handled, button2Handled;

  // Instancia del Preference_Manager, LedManager y del teclado BLE
  Preference_Manager* preferences;
  LedManager* ledManager;
  BleKeyboard* bleKeyboard;

public:
  Footswitch(int btn1Pin, int btn2Pin, Preference_Manager* prefs, BleKeyboard* keyboard, LedManager* ledManager, unsigned long threshold = 3000);

  void loop();
  int getStatus();  // Devuelve el estado de los botones
  bool isInverseMode(int buttonNumber);  // Verifica si un botón está en modo inverso

private:
  void handleButton(int buttonPin, bool &inverseMode, unsigned long &pressedTime, bool &handled, int buttonNumber);
  void executeAction(int buttonNumber);  // Ejecuta la acción basada en el número de botón
};

#endif
