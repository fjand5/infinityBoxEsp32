#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/configBox.h"
void renderConfigMenu()
{
  renderButton("Config Box", "begin_config", "Begin", R"({
  })",
               [](String key, String val)
               {
               });
  renderButton("Config Box", "done_config", "Done", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
               });
  // Mặt trước
  renderInputText("Config Box", "seg_font_1", "Font 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_font_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_font_2", "Font 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_font_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_font_3", "Font 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_font_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_font_4", "Font 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_font_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });
  // Mặt sau
  renderInputText("Config Box", "seg_back_1", "Back 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_back_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_back_2", "Back 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_back_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_back_3", "Back 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_back_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_back_4", "Back 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_back_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });
  
   // Mặt trên
  renderInputText("Config Box", "seg_top_1", "Top 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_top_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_top_2", "Top 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_top_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_top_3", "Top 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_top_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_top_4", "Top 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_top_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });
               
   // Mặt dưới
  renderInputText("Config Box", "seg_bottom_1", "Bottom 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_bottom_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_bottom_2", "Bottom 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_bottom_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_bottom_3", "Bottom 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_bottom_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_bottom_4", "Bottom 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_bottom_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });
  // Mặt trái
  renderInputText("Config Box", "seg_left_1", "Left 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_left_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_left_2", "Left 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_left_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_left_3", "Left 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_left_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_left_4", "Left 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_left_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });


          // Mặt phải
  renderInputText("Config Box", "seg_right_1", "Right 1", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_right_1_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_right_2", "Right 2", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_right_2_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_right_3", "Right 3", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_right_3_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });

    renderInputText("Config Box", "seg_right_4", "Right 4", R"({
  })",
                  [](String key, String val)
                  {
                    setValue(key, val);
                  });
  renderToggle("Config Box", "seg_right_4_rev", "Đảo chiều", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
               });
}