#ifndef GARRETLAB_FONT_H
#define GARRETLAB_FONT_H
#include <Font.h>

enum {
  ASCII,
  Misaki,
  FontX
};

struct garretlab_Font {
  Font *font;
  int fontType;
};
#endif /* GARRETLAB_FONT_H */