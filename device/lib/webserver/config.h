#pragma once
#define CONFIG_FILE "/config.txt"
#include "./json/ArduinoJson.h"
#include "SPIFFS.h"
#include <map>
#include <list>
void saveConfigFile();
void setValue(String key, String value, bool save);
std::map<String, String> ConfigContent;
typedef void (*configChangeCallback)(String, String);
std::list<configChangeCallback> onConfigChanges;
std::list<String> ignoreSave;
SemaphoreHandle_t spiffs_sem;
SemaphoreHandle_t configContent_sem;
void setOnConfigChange(void (*func)(String key, String value))
{
  onConfigChanges.push_front(func);
}
// Mỗi dòng là một phần tử (một cặp key value) (key):(value)\n
void loadFileIntoConfig(String content)
{
  log_d("%s", content.c_str());
  configContent_sem = xSemaphoreCreateBinary();
  while (content.indexOf("\n") >= 0)
  {
    String curLine = content.substring(0, content.indexOf("\n"));
    String key = curLine.substring(0, content.indexOf(":"));
    String value = curLine.substring(content.indexOf(":") + 1);
    ConfigContent[key] = value;
    content.remove(0, curLine.length() + 1);
  }
  xSemaphoreGive(configContent_sem);
}
// Kiểm tra key có tồn tại không
bool checkKey(String key)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    bool ret = ConfigContent.find(key) != ConfigContent.end();
    xSemaphoreGive(configContent_sem);
    return ret;
  }
  return false;
}

// Lấy giá trị của Key
String getValue(String key, String def = "", bool setDefaultTokey = true)
{
  if (checkKey(key))
  {
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      String ret = ConfigContent[key];
      xSemaphoreGive(configContent_sem);
      return ret;
    }
  }
  else
  {
    if (setDefaultTokey)
    {
      setValue(key, def, true);
    }
    return def;
  }
}
char *getValueByCStr(String key, String def = "", bool setDefaultTokey = true)
{
  char *ret;

  if (checkKey(key))
  {
    String tmp;
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      tmp = ConfigContent[key];
      xSemaphoreGive(configContent_sem);
    }
    ret = new char[tmp.length() + 1];
    strcpy(ret, tmp.c_str());
    return ret;
  }
  else
  {
    if (setDefaultTokey)
    {
      setValue(key, def, true);
    }
    String tmp = def;
    ret = new char[tmp.length() + 1];
    strcpy(ret, tmp.c_str());
    return ret;
  }
}
// Lấy toàn bộ file content
String getValuesByString()
{
  String ret = "";
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    for (std::pair<String, String> e : ConfigContent)
    {
      String k = e.first;
      String v = e.second;
      ret += k + ":" + v + "\n";
    }
    xSemaphoreGive(configContent_sem);
  }
  return ret;
}
String getValuesByJson()
{
  DynamicJsonDocument doc(8192);
  JsonObject obj = doc.to<JsonObject>();
  String ret;

  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    for (std::pair<String, String> e : ConfigContent)
    {
      String k = e.first;
      String v = e.second;
      obj[k] = v;
    }
    xSemaphoreGive(configContent_sem);
  }
  serializeJson(obj, ret);
  return ret;
}
// Gán giá trị cho key
void setValue(String key, String value, bool save = true)
{
  log_d("key: %s; value: %s; save: %d", key.c_str(), value.c_str(), save);
  bool noChange = ConfigContent[key] == value;
  if (!noChange)
  {
    if (key.indexOf(":") >= 0 || key.indexOf("\n") >= 0 || value.indexOf(":") >= 0 || value.indexOf("\n") >= 0)
      return;
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      ConfigContent[key] = value;
      xSemaphoreGive(configContent_sem);
    }
  }

  for (auto onConfigChange = onConfigChanges.begin();
       onConfigChange != onConfigChanges.end();
       ++onConfigChange)
  {
    if ((*onConfigChange) != NULL)
    {
      (*onConfigChange)(key, value);
    }
  }
  // nếu không yêu cầu lưu vào flash hoặc giá trị như cũ
  if (!save || noChange)
  {
    ignoreSave.push_front(key);
    return;
  }
  ignoreSave.remove(key);

  saveConfigFile();
}
void saveConfigFile()
{
  if (xSemaphoreTake(spiffs_sem, portMAX_DELAY) == pdTRUE)
  {
  REOPEN:
    File cfg_file = SPIFFS.open(CONFIG_FILE, "w");
    if (!cfg_file)
    {
      cfg_file.close();
      delay(100);
      log_e("can't open file, reopening...");
      SPIFFS.end();
      SPIFFS.begin();
      goto REOPEN;
    }
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      for (std::pair<String, String> e : ConfigContent)
      {
        String k = e.first;
        String v = e.second;
        bool ignore = false;
        for (auto _key = ignoreSave.begin();
             _key != ignoreSave.end();
             ++_key)
        {
          if (*_key == k)
          {
            ignore = true;
            break;
          }
        }

        if (!ignore)
          cfg_file.print(k + ":" + v + "\n");
        else{
          log_d("egnore: %s", k.c_str());
        }
      }
      xSemaphoreGive(configContent_sem);
    }
    cfg_file.close();
    xSemaphoreGive(spiffs_sem);
  }
}
// Khởi tạo
void setupConfig()
{
  spiffs_sem = xSemaphoreCreateBinary();
  if (!SPIFFS.begin())
  {
    log_d("Can't mount SPIFFS, Try format");
    SPIFFS.format();
    if (!SPIFFS.begin())
    {
      log_d("Can't mount SPIFFS");
    }
    else
    {
      log_d("SPIFFS mounted");
      xSemaphoreGive(spiffs_sem);
      return;
    }
  }
  else
  {
    log_d("SPIFFS mounted ");
    xSemaphoreGive(spiffs_sem);
  }
  if (xSemaphoreTake(spiffs_sem, portMAX_DELAY) == pdTRUE)
  {
    File cfg_file = SPIFFS.open(CONFIG_FILE, "r");
    if (cfg_file)
    {
      String tmp = cfg_file.readString();
      loadFileIntoConfig(tmp);
    }
    cfg_file.close();
    xSemaphoreGive(spiffs_sem);
  }
}

void loopConfig()
{
}
