#ifndef GARRETLAB_ARDUINO_GRAPHICS_H
#define GARRETLAB_ARDUINO_GRAPHICS_H

#include <ArduinoGraphics.h>
#include <garretlab_Font.h>
#include <misakiUTF16.h>

#define COLOR_R(color) (uint8_t(color >> 16))
#define COLOR_G(color) (uint8_t(color >> 8))
#define COLOR_B(color) (uint8_t(color >> 0))

class garretlab_ArduinoGraphics : public ArduinoGraphics {
 public:
  garretlab_ArduinoGraphics(int width, int height);                       // Constructor.
  virtual int begin();                                                    // Begin matrix.
  virtual void endDraw();                                                 // End draw.
  virtual void clear();                                                   // Clear display.
  virtual void text(const String& str, int x = 0, int y = 0);             // Display text.
  virtual void textFont(const Font& which);                               // Set text font.
  virtual void textFont(const garretlab_Font& which);                     // Set text font.
  virtual void set(int x, int y, uint8_t r, uint8_t g, uint8_t b) = 0;    // Set pixel.
  virtual size_t write(uint8_t c);                                        // Write for Print class.
  virtual void beginText(int x = 0, int y = 0);                           // Begin text.
  virtual void beginText(int x, int y, uint8_t r, uint8_t g, uint8_t b);  // Begin text.
  virtual void beginText(int x, int y, uint32_t color);                   // Begin text.
  virtual void endText(int scrollDirection = NO_SCROLL);                  // Display text.
  virtual void textScrollSpeed(unsigned long scrollSpeed);                // Set text scroll speed.

 protected:
  String textBuffer;                // Buffer to hold text.
  int textBufferLength;             // Text buffer length, not the memory size.
  int textX;                        // X position of text.
  int textY;                        // Y position of text.
  struct garretlab_Font* font;      // Font name.
  int canvasWidth;                  // Canvas width.
  int canvasHeight;                 // Canvas height.
  unsigned long scrollSpeed = 150;  // Text scroll speed.
};

// Font structure for Misaki font.
extern const struct garretlab_Font Font_Misaki;

#endif /* GARRETLAB_ARDUINO_GRAPHICS_H */