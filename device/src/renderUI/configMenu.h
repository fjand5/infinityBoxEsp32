#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
void renderConfigMenu()
{
  renderButton("Config Box", "begin_config", "Begin", R"({
  })",
               [](String key, String val)
               {                 
                 setValue("timer_tgl", "false");
                 box.beginConfigMode();

               });
  renderButton("Config Box", "done_config", "Done", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.endConfigMode();
               });
  // Mặt trước
  renderInputText("Config Box", "seg_font_1", "Font 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_font_1_rev", "false") == "true";
                    int segNum = getValue("seg_font_1", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_font_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_font_1_rev", "false") == "true";
                 int segNum = getValue("seg_font_1", "0").toInt();

                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_font_2", "Font 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_font_2_rev", "false") == "true";
                    int segNum = getValue("seg_font_2", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_font_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_font_2_rev", "false") == "true";
                 int segNum = getValue("seg_font_2", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_font_3", "Font 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_font_3_rev", "false") == "true";
                    int segNum = getValue("seg_font_3", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_font_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_font_3_rev", "false") == "true";
                 int segNum = getValue("seg_font_3", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_font_4", "Font 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_font_4_rev", "false") == "true";
                    int segNum = getValue("seg_font_4", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_font_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_font_4_rev", "false") == "true";
                 int segNum = getValue("seg_font_4", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });
  renderButton("Config Box", "done_config_face_font", "View Font Face", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.currentConfigFace("seg_font");
               });
  // Mặt sau
  renderInputText("Config Box", "seg_back_1", "Back 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_back_1_rev", "false") == "true";
                    int segNum = getValue("seg_back_1", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_back_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_back_1_rev", "false") == "true";
                 int segNum = getValue("seg_back_1", "0").toInt();

                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_back_2", "Back 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_back_2_rev", "false") == "true";
                    int segNum = getValue("seg_back_2", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_back_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_back_2_rev", "false") == "true";
                 int segNum = getValue("seg_back_2", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_back_3", "Back 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_back_3_rev", "false") == "true";
                    int segNum = getValue("seg_back_3", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_back_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_back_3_rev", "false") == "true";
                 int segNum = getValue("seg_back_3", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_back_4", "Back 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_back_4_rev", "false") == "true";
                    int segNum = getValue("seg_back_4", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_back_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_back_4_rev", "false") == "true";
                 int segNum = getValue("seg_back_4", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });
    renderButton("Config Box", "done_config_face_back", "View Back Face", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.currentConfigFace("seg_back");
               });

  // Mặt trên
  renderInputText("Config Box", "seg_top_1", "top 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_top_1_rev", "false") == "true";
                    int segNum = getValue("seg_top_1", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_top_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_top_1_rev", "false") == "true";
                 int segNum = getValue("seg_top_1", "0").toInt();

                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_top_2", "top 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_top_2_rev", "false") == "true";
                    int segNum = getValue("seg_top_2", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_top_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_top_2_rev", "false") == "true";
                 int segNum = getValue("seg_top_2", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_top_3", "top 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_top_3_rev", "false") == "true";
                    int segNum = getValue("seg_top_3", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_top_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_top_3_rev", "false") == "true";
                 int segNum = getValue("seg_top_3", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_top_4", "top 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_top_4_rev", "false") == "true";
                    int segNum = getValue("seg_top_4", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_top_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_top_4_rev", "false") == "true";
                 int segNum = getValue("seg_top_4", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });
    renderButton("Config Box", "done_config_face_top", "View Top Face", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.currentConfigFace("seg_top");
               });
 // Mặt dưới
  renderInputText("Config Box", "seg_bottom_1", "bottom 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_bottom_1_rev", "false") == "true";
                    int segNum = getValue("seg_bottom_1", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_bottom_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_bottom_1_rev", "false") == "true";
                 int segNum = getValue("seg_bottom_1", "0").toInt();

                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_bottom_2", "bottom 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_bottom_2_rev", "false") == "true";
                    int segNum = getValue("seg_bottom_2", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_bottom_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_bottom_2_rev", "false") == "true";
                 int segNum = getValue("seg_bottom_2", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_bottom_3", "bottom 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_bottom_3_rev", "false") == "true";
                    int segNum = getValue("seg_bottom_3", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_bottom_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_bottom_3_rev", "false") == "true";
                 int segNum = getValue("seg_bottom_3", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_bottom_4", "bottom 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_bottom_4_rev", "false") == "true";
                    int segNum = getValue("seg_bottom_4", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_bottom_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_bottom_4_rev", "false") == "true";
                 int segNum = getValue("seg_bottom_4", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });
    renderButton("Config Box", "done_config_face_bottom", "View Bottom Face", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.currentConfigFace("seg_bottom");
               });
 // Mặt trái
  renderInputText("Config Box", "seg_left_1", "left 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_left_1_rev", "false") == "true";
                    int segNum = getValue("seg_left_1", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_left_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_left_1_rev", "false") == "true";
                 int segNum = getValue("seg_left_1", "0").toInt();

                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_left_2", "left 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_left_2_rev", "false") == "true";
                    int segNum = getValue("seg_left_2", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_left_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_left_2_rev", "false") == "true";
                 int segNum = getValue("seg_left_2", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_left_3", "left 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_left_3_rev", "false") == "true";
                    int segNum = getValue("seg_left_3", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_left_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_left_3_rev", "false") == "true";
                 int segNum = getValue("seg_left_3", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_left_4", "left 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_left_4_rev", "false") == "true";
                    int segNum = getValue("seg_left_4", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_left_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_left_4_rev", "false") == "true";
                 int segNum = getValue("seg_left_4", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });
    renderButton("Config Box", "done_config_face_left", "View Left Face", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.currentConfigFace("seg_left");
               });
  // Mặt phải
  renderInputText("Config Box", "seg_right_1", "right 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_right_1_rev", "false") == "true";
                    int segNum = getValue("seg_right_1", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_right_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_right_1_rev", "false") == "true";
                 int segNum = getValue("seg_right_1", "0").toInt();

                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_right_2", "right 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_right_2_rev", "false") == "true";
                    int segNum = getValue("seg_right_2", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_right_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_right_2_rev", "false") == "true";
                 int segNum = getValue("seg_right_2", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_right_3", "right 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_right_3_rev", "false") == "true";
                    int segNum = getValue("seg_right_3", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_right_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_right_3_rev", "false") == "true";
                 int segNum = getValue("seg_right_3", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });

  renderInputText("Config Box", "seg_right_4", "right 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                    bool isRev = getValue("seg_right_4_rev", "false") == "true";
                    int segNum = getValue("seg_right_4", "0").toInt();
                    box.currentConfigSegment(segNum, isRev);
                  });
  renderToggle("Config Box", "seg_right_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 bool isRev = getValue("seg_right_4_rev", "false") == "true";
                 int segNum = getValue("seg_right_4", "0").toInt();
                 box.currentConfigSegment(segNum, isRev);
               });
    renderButton("Config Box", "done_config_face_right", "View Right Face", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.currentConfigFace("seg_right");
               });
}