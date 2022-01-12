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
DynamicJsonDocument webDoc(1024);
void (*onClientCommit)(uint8_t num, String);
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
bool isConnect = false;

HTTPUpdateServer httpUpdater;
SemaphoreHandle_t websocket_sem;
void sendTXT(uint8_t num, String data)
{
  if (xSemaphoreTake(websocket_sem, portMAX_DELAY) == pdTRUE)
  {
    log_w("sendTXT: %d", num);
    if (webSocket.clientIsConnected(num))
      webSocket.sendTXT(num, data.c_str());

    xSemaphoreGive(websocket_sem);
  }
}
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
      sendTXT(num, "pong");
      return;
    }

    if (onClientCommit != NULL)
    {
      onClientCommit(num, data);
    }
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
                 log_d("Thử kết nối");
                 uint32_t preTime = millis();
                 if (checkKey("sta_id") && checkKey("sta_pass"))
                 {
                   log_d("Dang Thử kết nối");
                   setValue("sta_ip", "");
                   WiFi.begin(getValue("sta_id").c_str(), getValue("sta_pass").c_str());
                   while (WiFi.status() != WL_CONNECTED && (millis() - preTime) < 30000)
                   {
                     delay(100);
                     log_d(".");
                   }
                   if (WiFi.status() == WL_CONNECTED)
                   {
                     log_d("WiFi connected");
                     log_d("IP address: %s", WiFi.localIP().toString().c_str());
                     setValue("sta_ip", IpAddress2String(WiFi.localIP()));
                     isConnect = true;
                   }
                 }
                 else
                 {
                   log_d("Not found station info!!");
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
  renderButton("system", "format", "Restart hệ thống", R"({
    }))",
               [](String key, String val)
               {
                 LITTLEFS.format();
               });

  renderInputText("system", "version", "Phiên bản", R"({
    "label":"Phiên bản firmware"
    }))",
                  [](String key, String val) {
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
      log_d("-");
    }
  }
}
void setupWebserver()
{
  renderSystem();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(getValueByCStr("sta_id", "Vong Cat-Hide"), getValueByCStr("sta_pass", "78787878"));

  while (WiFi.status() != WL_CONNECTED && millis() < 10000)
  {
    delay(1000);
    log_d(".");
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    log_d("WiFi connected");
    log_d("IP address: %s", WiFi.localIP().toString().c_str());
    setValue("sta_ip", IpAddress2String(WiFi.localIP()));
    WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);

    isConnect = true;
  }
  else
  {
    WiFi.mode(WIFI_AP);
  }
  // if (checkKey("ap_id") && checkKey("ap_pass"))
  // {
  // SPEX_xxx
  uint8_t tmp[6];
  char ap_id[18];
  ap_id[17] = 0;
  WiFi.macAddress(tmp);
  sprintf(ap_id, "SPEX_%X%X%X%X%X%X", tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
  WiFi.softAP(getValueByCStr("ap_id", ap_id), getValueByCStr("ap_pass", "12345678"));
  // }
  // else
  // {
  //   WiFi.softAP(APSSID, APPSK);
  // }

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
        log_w("millis");

        String res = String(millis());
        sendTXT(num, res.c_str());
        log_w("millis");
      }
      else if (cmd == "get")
      {
        log_w("getValue");

        String key = obj["key"];
        String res = "{\"key\":\"" + key + "\",\"val\":\"" + getValue(key) + "\"}";
        sendTXT(num, res.c_str());
        log_w("getValue");
      }
      else if (cmd == "gal")
      {
        log_w("getValuesByString");

        sendTXT(num, getValuesByString().c_str());
        log_w("getValuesByString");
      }

      else if (cmd == "exe")
      {
        log_w("execEvent");

        String key = obj["key"];
        String val = obj["val"];
        execEvent(key, val);
        log_w("execEvent");
      }

      else if (cmd == "save")
      {
        saveConfigFile();
        sendTXT(num, getValuesByString().c_str());
      }
    }
  };

  // Server truyền dữ liệu cho client
  setOnConfigChange([](String key, String val)
                    {
                      // String res = "{\"" + key +"\":\""+getValue(key)+"\"}";
                      if (xSemaphoreTake(websocket_sem, portMAX_DELAY) == pdTRUE)
                      {
                        webSocket.broadcastTXT(getValuesByString().c_str());
                        xSemaphoreGive(websocket_sem);
                      }
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
                    });

  const char *headerkeys[] = {"Version-Content-Client"};
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char *);
  server.collectHeaders(headerkeys, headerkeyssize);

  httpUpdater.setup(&server);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  log_d("webserver ready");
  websocket_sem = xSemaphoreCreateBinary();
  xSemaphoreGive(websocket_sem);
}
void loopWebserver()
{
  webSocket.loop();
  server.handleClient();
}
