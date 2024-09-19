#ifndef WEBPORTAL_H
#define WEBPORTAL_H

#include <WiFi.h>
#include <WebServer.h>
#include "Preference_Manager.h"

class WebPortal {
private:
    WebServer server;
    Preference_Manager* preferences;

public:
    WebPortal(Preference_Manager* preferences);
    void begin();
    void handleClient();

private:
    void handleRoot();
    void handleSave();
    String generateHTML();
    String generateStyle(); 
};

#endif
