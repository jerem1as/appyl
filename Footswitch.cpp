#include "Footswitch.h"

Footswitch::Footswitch(int btn1Pin, int btn2Pin, Preference_Manager* prefs, BleKeyboard* keyboard, LedManager* lm, unsigned long threshold)
  : button1Pin(btn1Pin), button2Pin(btn2Pin),
    inverseMode1(false), inverseMode2(false),
    button1PressedTime(0), button2PressedTime(0),
    longPressThreshold(threshold),
    button1Handled(false), button2Handled(false),
    preferences(prefs), bleKeyboard(keyboard),
    ledManager(lm) {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
}

void Footswitch::loop() {
  handleButton(button1Pin, inverseMode1, button1PressedTime, button1Handled, 1);
  handleButton(button2Pin, inverseMode2, button2PressedTime, button2Handled, 2);

  if (bleKeyboard->isConnected()) {
    ledManager->encender(3);
  } else {
    ledManager->titilar(3, 2, 100);
  };
}

int Footswitch::getStatus() {
  bool button1Pressed = digitalRead(button1Pin) == LOW;
  bool button2Pressed = digitalRead(button2Pin) == LOW;

  if (inverseMode1) button1Pressed = !button1Pressed;
  if (inverseMode2) button2Pressed = !button2Pressed;

  if (button1Pressed && button2Pressed) {
    return 3;  // Ambos pulsadores presionados
  } else if (button1Pressed) {
    return 1;  // Pulsador 1 presionado
  } else if (button2Pressed) {
    return 2;  // Pulsador 2 presionado
  }

  return 4;  // Ningún pulsador presionado
}

bool Footswitch::isInverseMode(int buttonNumber) {
  if (buttonNumber == 1) {
    return inverseMode1;
  } else if (buttonNumber == 2) {
    return inverseMode2;
  }
  return false;
}

void Footswitch::handleButton(int buttonPin, bool& inverseMode, unsigned long& pressedTime, bool& handled, int buttonNumber) {
  bool buttonPressed = digitalRead(buttonPin) == LOW;

  if (!inverseMode) {
    if (buttonPressed) {
      if (!handled) {
        executeAction(buttonNumber);  // Ejecutar la acción al presionar
        handled = true;               // Evitar la acción repetida hasta que se suelte
      }

      if (pressedTime == 0) {
        pressedTime = millis();  // Inicio del tiempo de pulsación
      } else if (millis() - pressedTime > longPressThreshold) {
        inverseMode = true;  // Cambiar a modo inverso
        pressedTime = 0;  // Resetear el temporizador
        ledManager->titilar(buttonNumber, 2, 200); //Doble titileo para indicar el paso a modo inverso
      }
    } else {
      pressedTime = 0;  // Resetear el temporizador cuando se suelta
      handled = false;  // Permitir la acción en la próxima pulsación
    }
  } else {
    if (!buttonPressed) {
      if (!handled) {
        executeAction(buttonNumber);  // Ejecutar la acción al soltar en modo inverso
        handled = true;               // Evitar la acción repetida hasta que se presione de nuevo
      }

      if (pressedTime == 0) {
        pressedTime = millis();  // Inicio del tiempo cuando se suelta el botón
      } else if (millis() - pressedTime > longPressThreshold) {
        inverseMode = false;  // Cambiar a modo normal
        pressedTime = 0;      // Resetear el temporizador
        ledManager->titilar(buttonNumber, 2, 200); //Doble titileo para indicar el paso a modo normal
      }
    } else {
      pressedTime = 0;  // Resetear el temporizador cuando se presiona nuevamente
      handled = false;  // Permitir la acción en la próxima soltada
    }
  }
}

void Footswitch::executeAction(int buttonNumber) {
  int action = preferences->getAction(buttonNumber);  // Obtener la acción configurada para el pulsador

  if (bleKeyboard->isConnected()) {
    bleKeyboard->write(action);  // Ejecutar la acción como un teclado BLE
  }
  ledManager->hit(buttonNumber, 100); // Prendo la luz para indicar que la acción fue ejecutada

}
