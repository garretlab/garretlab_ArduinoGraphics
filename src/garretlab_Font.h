#ifndef GARRETLAB_FONT_H
#define GARRETLAB_FONT_H
#include <Font.h>

enum struct eFont {
  ASCII,
  Misaki,
  FontX
};

struct garretlab_Font : Font {
  eFont fontType;
  garretlab_Font(const Font& font) : Font(font) {
  }
  garretlab_Font(const Font& font, eFont f) : Font(font) {
    fontType = eFont::Misaki;
  }
};
#endif /* GARRETLAB_FONT_H */