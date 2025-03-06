
#include "splashScreen.hpp"
#include <chrono>
#include <thread>

SplashScreen::SplashScreen(Font font, Color color) {
  this->font = font;
  this->color = color;
}

void SplashScreen::Show() {
  int windowWidth = 750;
  int windowHeight = 700;
  int offset = 50;

  float alpha = 0.0f; // Transparency value (0 = invisible, 255 = fully visible)
  bool fadingIn = true; // Determines whether we are fading in or out
  int fadeSpeed = 3;    // Speed of fade effect

  for (int frame = 0; frame < 300;
       frame++) { // Show splash screen for a set time
    BeginDrawing();
    ClearBackground(BLACK);

    // Adjust alpha for fade-in and fade-out effect
    if (fadingIn) {
      alpha += fadeSpeed; // Increase alpha (fade in)
      if (alpha >= 255) {
        alpha = 255;
        fadingIn = false; // Switch to fade-out
      }
    } else {
      alpha -= fadeSpeed; // Decrease alpha (fade out)
      if (alpha <= 0) {
        alpha = 0;
        fadingIn = true; // Switch back to fade-in
      }
    }

    // Draw text with the current alpha value
    std::string text = "made by PRESS-X";
    Vector2 textSize = MeasureTextEx(font, text.c_str(), 40, 2);
    Vector2 textPos = {(windowWidth + offset - textSize.x) / 2,
                       (windowHeight + offset - textSize.y) / 2};

    Color fadeColor = {color.r, color.g, color.b,
                       (unsigned char)alpha}; // Set alpha transparency
    DrawTextEx(font, text.c_str(), textPos, 40, 2, fadeColor);

    EndDrawing();

    // Small delay to control speed of fade effect
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
