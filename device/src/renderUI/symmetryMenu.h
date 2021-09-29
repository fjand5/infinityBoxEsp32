#include "../lib/webserver/render.h"
#include "../lib/box/handleBox.h"
#include "../lib/webserver/config.h"

void renderSymmetryMenu()
{
  renderInputText("Symmetry", "cur_sym", "Current Symmetry", R"({
    "newLine":true
  })",
                  [](String key, String val) {
                  });

  box.setSymmetry(box.getSymmetricNumber(getValue("cur_sym")));
  renderButton("Symmetry", "sym_no_sym_btn", "No Symmetry", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.setSymmetry(SYM_NO_SYM);
                 setValue("cur_sym", box.getSymmetricString(SYM_NO_SYM));
               });

  renderButton("Symmetry", "sym_vertex_btn", "Vertex", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.setSymmetry(SYM_VERTEX);
                 setValue("cur_sym", box.getSymmetricString(SYM_VERTEX));
               });

  renderButton("Symmetry", "sym_surface_btn", "Surface", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.setSymmetry(SYM_SURFACE);
                 setValue("cur_sym", box.getSymmetricString(SYM_SURFACE));
               });
  renderButton("Symmetry", "sym_test_btn", "Test", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.setSymmetry(SYM_TEST);
                 setValue("cur_sym", box.getSymmetricString(SYM_TEST));
               });
               box.setSymmetry(box.getSymmetricNumber(getValue("cur_sym","11")));
}