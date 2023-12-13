#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

#define WIFI_TRIES_TO_CONNECT 4
#define WIFI_MILIS_BETWEEN_TRIES_TO_CONNECT 1000
#define SSID "⚡"
#define PASSPHRASE "UPHUzN%*^7u"

void wifi_connect()
{
    for (uint8_t t = WIFI_TRIES_TO_CONNECT; t > 0; t--)
    {
        Serial.printf("[WIFI] WAIT %d/%u...\n", t, WIFI_TRIES_TO_CONNECT);
        Serial.flush();
        delay(WIFI_MILIS_BETWEEN_TRIES_TO_CONNECT);
    }

    wifiMulti.addAP(SSID, PASSPHRASE);
}