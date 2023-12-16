#include "wifi.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define LOCKER_ID 1
#define BACKEND "https://remote-locker-api.azurewebsites.net"

struct State
{
    int user_id;
    String username;
    String password;
    String name;
    bool locked;
    bool blocked;
    String status;
};

bool SignIn(State state)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connection was lost");
        return false;
    }
    HTTPClient http;

    http.begin(BACKEND + (String) "/signin");

    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST("{\"name\":\"" + state.username + "\",\"password\":\"" + state.password + "\"}");
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        http.end();
        // file found at server
        return httpCode == HTTP_CODE_OK;
        // JSONVar data = JSON.parse(http.getString());
        // Serial.println(data["locker_id"]);
    }
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    // Free resources
    http.end();
    return false;
}

void UpdateState(State &state)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        return;
    }
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(BACKEND + String("/lockers/") + String(LOCKER_ID));

    int httpCode = http.GET();

    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        // file found at server
        JSONVar data = JSON.parse(http.getString());
        state.locked = data["locked"];
        state.blocked = data["blocked"];
        state.name = (const char *)data["name"];
        state.status = (const char *)data["status"];
    }
    else
    {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    // Free resources
    http.end();
}

bool ChangeState(State state)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connection was lost");
        return false;
    }
    HTTPClient http;

    http.begin(BACKEND + (String) "/lockers/" + String(LOCKER_ID));

    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(
        "{\"username\":\"" + state.username + "\",\"password\":\"" + state.password + "\",\"locked\":\"" + state.locked + "\",\"blocked\":\"" + state.blocked + "\",\"status\":\"" + state.status + "\",\"name\":\"" + state.name + "\"}");
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        http.end();
        // file found at server
        return httpCode == HTTP_CODE_OK;
        // JSONVar data = JSON.parse(http.getString());
        // Serial.println(data["locker_id"]);
    }
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    // Free resources
    http.end();
    return false;
}