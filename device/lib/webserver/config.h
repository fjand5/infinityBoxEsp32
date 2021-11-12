#pragma once
#define CONFIG_FILE "/config.txt"
#include "./json/ArduinoJson.h"
#include "SPIFFS.h"
#include <map>
#include <list>

void setValue(String key, String value, bool save);
std::map<String, String> ConfigContent;
typedef void (*configChangeCallback)(String, String);
std::list<configChangeCallback> onConfigChanges;
void setOnConfigChange(void (*func)(String key, String value))
{
  onConfigChanges.push_front(func);
}
// Mỗi dòng là một phần tử (một cặp key value) (key):(value)\n
void loadFileIntoConfig(String content)
{
  Serial.println(content);
  while (content.indexOf("\n") >= 0)
  {
    String curLine = content.substring(0, content.indexOf("\n"));
    String key = curLine.substring(0, content.indexOf(":"));
    String value = curLine.substring(content.indexOf(":") + 1);
    ConfigContent[key] = value;
    content.remove(0, curLine.length() + 1);
  }
}
// Kiểm tra key có tồn tại không
bool checkKey(String key)
{
  if (ConfigContent.find(key) != ConfigContent.end())
  {
    return true;
  }
  return false;
}

// Lấy giá trị của Key
String getValue(String key, String def = "", bool setDefaultTokey = true)
{
  if (checkKey(key))
    return ConfigContent[key];
  else
  {
    if (setDefaultTokey)
    {
      setValue(key, def, true);
    }
    return def;
  }
}
char* getValueByCStr(String key, String def = "", bool setDefaultTokey = true)
{
  char *ret;

  if (checkKey(key)){
    String tmp =  ConfigContent[key];
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
    String tmp =  def;
    ret = new char[tmp.length() + 1];
    strcpy(ret, tmp.c_str());
    return ret;
  }
}
// Lấy toàn bộ file content
String getValuesByString()
{
  String ret = "";
  for (std::pair<String, String> e : ConfigContent)
  {
    String k = e.first;
    String v = e.second;
    ret += k + ":" + v + "\n";
  }
  return ret;
}
String getValuesByJson()
{
  DynamicJsonDocument doc(8192);
  JsonObject obj = doc.to<JsonObject>();
  String ret;
  for (std::pair<String, String> e : ConfigContent)
  {
    String k = e.first;
    String v = e.second;
    obj[k] = v;
  }
  serializeJson(obj, ret);
  return ret;
}
// Gán giá trị cho key
void setValue(String key, String value, bool save = true)
{
  ConfigContent[key] = value;
  
  for (auto onConfigChange = onConfigChanges.begin();
       onConfigChange != onConfigChanges.end();
       ++onConfigChange)
  {
    if ((*onConfigChange) != NULL)
    {
      (*onConfigChange)(key, value);
    }
  }
  // nếu không yêu cầu lưu vào flash
  if (!save)
    return;

  File cfg_file = SPIFFS.open(CONFIG_FILE, "w");
  if (!cfg_file)
  {
    cfg_file.close();
    return;
  }

  for (std::pair<String, String> e : ConfigContent)
  {
    String k = e.first;
    String v = e.second;
    cfg_file.print(k + ":" + v + "\n");
  }

  cfg_file.close();
}

// Khởi tạo
void setupConfig()
{
  if (!SPIFFS.begin())
  {
    Serial.println("Can't mount SPIFFS, Try format");

    SPIFFS.format();
    if (!SPIFFS.begin())
    {
      Serial.println("SPIFFS mounted ");
    }
    else
    {
      Serial.println("Can't mount SPIFFS");
      return;
    }
  }
  else
  {
    Serial.println("SPIFFS mounted ");
  }

  File cfg_file = SPIFFS.open(CONFIG_FILE, "r");
  if (cfg_file)
  {
    String tmp = cfg_file.readString();
    loadFileIntoConfig(tmp);
  }
  cfg_file.close();
}

void loopConfig()
{
}
