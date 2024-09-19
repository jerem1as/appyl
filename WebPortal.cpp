#include "WebPortal.h"
#include "KeyMap.h"  
#include <ESPmDNS.h>

WebPortal::WebPortal(Preference_Manager* preferences)
  : server(80) {
  this->preferences = preferences;
}

void WebPortal::begin() {
  WiFi.softAP("ESP32_Config");

  server.on("/", std::bind(&WebPortal::handleRoot, this));
  server.on("/save", std::bind(&WebPortal::handleSave, this));
  server.begin();
  Serial.println("WebPortal iniciado, puedes conectarte a la red Wi-Fi 'ESP32_Config'");
  // Iniciar mDNS para que el dominio sea esp32.local
  if (!MDNS.begin("esp32")) {
    Serial.println("Error al iniciar mDNS");
  } else {
    Serial.println("mDNS iniciado con el dominio esp32.local");
  }
}

void WebPortal::handleClient() {
  server.handleClient();
}

void WebPortal::handleRoot() {
  String html = generateHTML();
  server.send(200, "text/html", html);
}

void WebPortal::handleSave() {
  for (int i = 0; i < 3; i++) {
    if (server.hasArg("action" + String(i))) {
      uint8_t action = server.arg("action" + String(i)).toInt();
      preferences->setAction(i, action);
      Serial.print("Action ");
      Serial.print(i);
      Serial.print(" guardada con valor: ");
      Serial.println(action);
    }
  }
  // Redirige automáticamente a la página principal después de guardar
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");  // Redirección HTTP
}

String WebPortal::generateHTML() {
  String html = "<html><head>";
  html += "<style>" + generateStyle() + "</style>";  // Agregar estilo
  html += "</head><body>";
  html += "<h1>Configuraci&oacute;n APPYL</h1>";  // Aseguramos que la tilde se vea bien
  html += "<form action='/save' method='POST'>";

  for (int i = 0; i < 3; i++) {
    html += "<div><label>Action " + String(i + 1) + ": </label>";
    html += "<select name='action" + String(i) + "'>";

    uint8_t currentAction = preferences->getAction(i);
    Serial.print("Generando combo box para Action ");
    Serial.print(i);
    Serial.print(" con valor almacenado: ");
    Serial.println(currentAction);

    // Iterar sobre el mapa keyMap para generar las opciones del combo box
    for (const auto& keyPair : keyMap) {
      uint8_t keyCode = keyPair.first;
      String keyName = keyPair.second;
      html += "<option value='" + String(keyCode) + "'";
      if (keyCode == currentAction) {
        html += " selected";  // Selecciona la opción si es la que está almacenada
      }
      html += ">" + keyName + "</option>";
    }
    html += "</select></div>";
  }

  html += "<button type='submit' class='button'>Guardar</button>";
  html += "</form></body></html>";

  return html;
}

String WebPortal::generateStyle() {
  String style = F(
    "html { font-family: monospace; display: inline-block; }"
    "body { display: flex; flex-direction: column; align-items: center; background-color: black; color: white; padding: 16px; font-size: 18px; }"
    "div { margin-bottom: 16px; }"
    "h1 { text-align: center; font-size: 32px; color: white; border: 2px solid blue; padding: 10px; border-radius: 8px; }"
    "select { padding: 4px; border-radius: 8px; font-size: 16px; }"
    "button { padding: 8px; width: 200px; font-size: 18px; }");
  return style;
}
