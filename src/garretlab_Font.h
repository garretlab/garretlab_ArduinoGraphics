#ifndef GARRETLAB_FONT_H
#define GARRETLAB_FONT_H
#include <Font.h>

enum struct eFont {
  ASCII,
  Misaki,
  FontX
};

struct garretlab_Font {
  Font *font;
  eFont fontType;
};
#endif /* GARRETLAB_FONT_H */