#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

#define SSID "⚡"
#define PASSPHRASE "UPHUzN%*^7u"

void ConnectToWiFi()
{
    wifiMulti.addAP(SSID, PASSPHRASE);
    while (wifiMulti.run() != WL_CONNECTED)
    {
        delay(500);
    }
}