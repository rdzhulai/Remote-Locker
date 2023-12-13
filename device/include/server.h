#include "wifi.h"
#include <HTTPClient.h>

#define BACKEND "http://example.com/index.html"

bool server_confirm_pin(String pin)
{
    if ((wifiMulti.run() != WL_CONNECTED))
        return false;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    http.begin(BACKEND);

    Serial.print("[HTTP] GET...\n");

    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            Serial.println(payload);
            return true;
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

    return false;
}