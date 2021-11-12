#pragma once
#define APSSID "infinity box"
#define APPSK "78787878"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPUpdateServer.h>
#include "./ws/WebSocketsServer.h"
#include "config.h"
#include "render.h"
#include "event.h"
#include "dist.h"
#include "utils.h"

DynamicJsonDocument webDoc(512);
void (*onClientCommit)(uint8_t num, String);
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
bool isConnect = false;

HTTPUpdateServer httpUpdater;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    break;
  case WStype_CONNECTED:
    break;
  case WStype_TEXT:
    String data;
    for (unsigned int i = 0; i < length; i++)
    {
      data += (char)payload[i];
    }

    if (data == "ping")
    {
      webSocket.sendTXT(num, "pong");
      return;
    }
    if (onClientCommit != NULL)
      onClientCommit(num, data);
    break;
  }
}
void addComonHeader()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.sendHeader("Access-Control-Expose-Headers", "*");
}
void renderSystem()
{
  renderInputText("system", "sta_id", "Station wifi", R"({
    "label":"Wifi"
    }))",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderPassword("system", "sta_pass", "Station Password", R"({
        "newLine":true,
        "label":"Password",
        })",
                 [](String key, String val)
                 {
                   setValue(key, val);
                 });
  renderButton("system", "try_conn", "Thử kết nối", R"({
        "newLine":true,
        "showSplit":true
    }))",
               [](String key, String val)
               {
                 Serial.println("Thử kết nối");
                 uint32_t preTime = millis();
                 if (checkKey("sta_id") && checkKey("sta_pass"))
                 {
                   Serial.println("Dang Thử kết nối");
                   setValue("sta_ip", "");
                   WiFi.begin(getValue("sta_id").c_str(), getValue("sta_pass").c_str());
                   while (WiFi.status() != WL_CONNECTED && (millis() - preTime) < 30000)
                   {
                     delay(100);
                     Serial.print(".");
                   }
                   if (WiFi.status() == WL_CONNECTED)
                   {
                     Serial.println("");
                     Serial.println("WiFi connected");
                     Serial.println("IP address: ");
                     Serial.println(WiFi.localIP());
                     setValue("sta_ip", IpAddress2String(WiFi.localIP()));
                     isConnect = true;
                   }
                 }
                 else
                 {
                   Serial.println("Not found station info!!");
                 }
               });

  renderInputText("system", "ap_id", "Access point wifi", R"({
    "label":"Wifi"
    }))",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderPassword("system", "ap_pass", "Access point Password", R"({
        "newLine":true,
        "label":"Password",
        "showSplit":true
        })",
                 [](String key, String val)
                 {
                   setValue(key, val);
                 });

  renderButton("system", "reset", "Reset hệ thống", R"({
    }))",
               [](String key, String val)
               {
                 ESP.restart();
               });
  renderButton("system", "restart", "Restart hệ thống", R"({
    }))",
               [](String key, String val)
               {
                 ESP.restart();
               });
}
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  if (checkKey("sta_id") && checkKey("sta_pass"))
  {
    WiFi.begin(getValueByCStr("sta_id"), getValueByCStr("sta_pass"));

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
      delay(500);
      Serial.print(".");
    }
  }
}
void setupWebserver()
{
  renderSystem();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(getValueByCStr("sta_id", "Vong Cat-Hide"), getValueByCStr("sta_pass", "78787878"));

  while (WiFi.status() != WL_CONNECTED && millis() < 30000)
  {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    setValue("sta_ip", IpAddress2String(WiFi.localIP()));
    WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);

    isConnect = true;
  }
  if (checkKey("ap_id") && checkKey("ap_pass"))
  {

    WiFi.softAP(getValueByCStr("ap_id", "vocauiu2"), getValueByCStr("ap_pass", "12345678"));
  }
  else
  {
    WiFi.softAP(APSSID, APPSK);
  }

  // client truyền dữ liệu cho server
  onClientCommit = [](uint8_t num, String data)
  {
    DeserializationError err = deserializeJson(webDoc, data);
    if (!err)
    {
      JsonObject obj = webDoc.as<JsonObject>();
      String cmd = obj["cmd"];
      serializeJsonPretty(obj, Serial);
      if (cmd == "gut")
      {
        // String key = obj["key"];
        String res = String(millis());
        webSocket.sendTXT(num, res.c_str());
      }
      if (cmd == "get")
      {
        String key = obj["key"];
        String res = "{\"key\":\"" + key + "\",\"val\":\"" + getValue(key) + "\"}";
        webSocket.sendTXT(num, res.c_str());
      }
      if (cmd == "gal")
      {
        webSocket.sendTXT(num, getValuesByString().c_str());
      }
      if (cmd == "exe")
      {
        String key = obj["key"];
        String val = obj["val"];
        execEvent(key, val);
      }
    }
  };

  // Server truyền dữ liệu cho client
  setOnConfigChange([](String key, String val)
                    {
                      // String res = "{\"" + key +"\":\""+getValue(key)+"\"}";
                      webSocket.broadcastTXT(getValuesByString().c_str());
                    });

  server.on("/", HTTP_GET, []()
            {
              addComonHeader();
              server.sendHeader("Content-Encoding", "gzip");
              server.send_P(200, "text/html", index_html, index_html_length);
            });
  server.on("/css/chunk-vendors.css", []()
            {
              addComonHeader();
              server.sendHeader("Content-Encoding", "gzip");
              server.send_P(200, "text/css", vendor_css, vendor_css_length);
            });
  server.on("/css/app.css", []()
            {
              addComonHeader();
              server.sendHeader("Content-Encoding", "gzip");
              server.send_P(200, "text/css", app_css, app_css_length);
            });
  server.on("/js/chunk-vendors.js", []()
            {
              addComonHeader();
              server.sendHeader("Content-Encoding", "gzip");
              server.send_P(200, "application/javascript", vendor_js, vendor_js_length);
            });
  server.on("/js/app.js", []()
            {
              addComonHeader();
              server.sendHeader("Content-Encoding", "gzip");
              server.send_P(200, "application/javascript", app_js, app_js_length);
            });
  server.on("/favicon.ico", []()
            {
              addComonHeader();
              server.sendHeader("Content-Encoding", "gzip");
              server.send_P(200, "image/x-icon", favicon_ico, favicon_ico_length);
            });
  server.on("/render", []()
            {
              addComonHeader();
              server.send_P(200, "application/json", getRender().c_str());
            });
  server.onNotFound([]()
                    {
                      addComonHeader();
                      server.send(200, "text/plain", "");
                      Serial.println("isAccessNotFound = true;");
                    });

  const char *headerkeys[] = {"Version-Content-Client"};
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
  server.collectHeaders(headerkeys, headerkeyssize);

  httpUpdater.setup(&server);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
void loopWebserver()
{
  webSocket.loop();
  delay(10);
  server.handleClient();

}
