#include <garretlab_ArduinoGraphics.h>

// Constructor.
garretlab_ArduinoGraphics::garretlab_ArduinoGraphics(int width, int height)
    : ArduinoGraphics(width, height) {
  canvasWidth = width;
  canvasHeight = height;
}

// Display text.
void garretlab_ArduinoGraphics::text(const String &str, int x, int y) {
  byte fontData[textFontHeight()];
  char *ptr = (char *)str.c_str();

  switch (font.fontType) {
    case ASCII:
      ArduinoGraphics::text(str, x, y);
      break;
    case Misaki:
      while (*ptr) {
        ptr = getFontData(fontData, ptr, true);
        bitmap(fontData, x, y, textFontWidth(), textFontHeight());
        x += font.font->width;
      }
      break;
    default:
      break;
  }
}

// Set text font.
void garretlab_ArduinoGraphics::textFont(const Font &which) {
  font.font = (Font *)&which;
  font.fontType = ASCII;

  ArduinoGraphics::textFont(which);
}

// Set text font.
void garretlab_ArduinoGraphics::textFont(const garretlab_Font &which) {
  font = which;

  ArduinoGraphics::textFont(*(font.font));
}

// Write for Print class.
size_t garretlab_ArduinoGraphics::write(uint8_t c) {
  static int skip = 0;

  if ((c != 0x0a) && (c != 0x0d)) {  // Skip cr/lf.
    textBuffer += (char)c;
    ArduinoGraphics::write(c);
    if (skip == 0) {
      textBufferLength++;
      if ((c & 0x80) == 0) {
        skip = 0;
      } else if ((c & 0xe0) == 0xc0) {
        skip = 1;
      } else if ((c & 0xf0) == 0xe0) {
        skip = 2;
      }
    } else {
      skip--;
    }
  }

  return 1;
}

// Begin text.
void garretlab_ArduinoGraphics::beginText(int x, int y) {
  textBuffer = "";
  textBufferLength = 0;
  textX = x;
  textY = y;

  ArduinoGraphics::beginText(x, y);
}

// Begin text.
void garretlab_ArduinoGraphics::beginText(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  beginText(x, y);
  ArduinoGraphics::beginText(x, y, r, g, b);
}

// Begin text.
void garretlab_ArduinoGraphics::beginText(int x, int y, uint32_t color) {
  beginText(x, y, COLOR_R(color), COLOR_G(color), COLOR_B(color));
}

// Display text.
void garretlab_ArduinoGraphics::endText(int scrollDirection) {
  int scrollLength;

  if (font.fontType == ASCII) {
    ArduinoGraphics::endText(scrollDirection);
    return;
  }

  switch (scrollDirection) {
    case SCROLL_LEFT:
      scrollLength = textBufferLength * textFontWidth();

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX - i, textY);
        endDraw();

        delay(scrollSpeed);
      }
      break;
    case SCROLL_RIGHT:
      scrollLength = textBufferLength * textFontWidth();

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX - (scrollLength - i - 1), textY);
        endDraw();

        delay(scrollSpeed);
      }
      break;
    case SCROLL_UP:
      scrollLength = textFontHeight() + textY;

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX, textY - i);
        endDraw();

        delay(scrollSpeed);
      }
      break;
    case SCROLL_DOWN:
      scrollLength = textFontHeight() + textY;

      for (int i = 0; i < scrollLength; i++) {
        beginDraw();
        text(textBuffer, textX, textY - (scrollLength - i - 1));
        endDraw();

        delay(scrollSpeed);
      }
      break;
    default:
      beginDraw();
      text(textBuffer, textX, textY);
      endDraw();
      break;
  }
}

// Set text scroll speed.
void garretlab_ArduinoGraphics::textScrollSpeed(unsigned long scrollSpeed) {
  this->scrollSpeed = scrollSpeed;

  ArduinoGraphics::textScrollSpeed(scrollSpeed);
}

// Font structure for Misaki font.
const struct garretlab_Font Font_Misaki {
  new Font{8, 8, NULL}, Misaki
};