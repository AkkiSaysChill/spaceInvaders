#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include <raylib.h>
#include <string>

class SplashScreen {
public:
  SplashScreen(Font font, Color color);
  void Show();

private:
  Font font;
  Color color;
};

#endif
