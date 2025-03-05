#include "src/game.hpp"
#include <cstdio>
#include <raylib.h>
#include <string>

std::string FormatWithLeadingZeros(int number, int width) {
  std::string numberText = std::to_string(number);
  int leadingZeros = width - numberText.length();
  return numberText = std::string(leadingZeros, '0') + numberText;
}

int main(int argc, char *argv[]) {

  Color grey = {29, 29, 27, 255};
  Color yellow = {243, 216, 63, 255};
  int offset = 50;

  int windowWidth = 750;
  int windowHeight = 700;
  // create a window
  InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space invaders");
  InitAudioDevice();

  Font font = LoadFontEx("assets/fonts/Doto/Doto.ttf", 64, 0, 0);

  Texture2D spaceshipImage = LoadTexture("assets/ship.png");

  SetTargetFPS(60);
  Game game;

  while (WindowShouldClose() == false) {

    SetMusicVolume(game.music, 1.0f); // 1.0 is max volume
    UpdateMusicStream(game.music);
    game.HandleInput();
    game.Update();
    BeginDrawing();

    ClearBackground(grey);
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
    DrawLineEx({25, 730}, {775, 730}, 3, yellow);
    if (game.run) {
      DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
    } else {
      DrawTextEx(font, "Game Over!", {570, 740}, 34, 2, yellow);
    }
    float x = 50.0;

    for (int i = 0; i < game.GetLives(); i++) {
      DrawTextureV(spaceshipImage, {x, 745}, WHITE);
      x += 50;
    }

    DrawTextEx(font, "Score", {50, 15}, 34, 2, yellow);

    std::string scoreText = FormatWithLeadingZeros(game.score, 5);
    DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

    DrawTextEx(font, "High Score", {570, 15}, 34, 2, yellow);

    std::string highScoreText = FormatWithLeadingZeros(game.highScore, 5);
    DrawTextEx(font, highScoreText.c_str(), {655, 40}, 34, 2, yellow);

    game.Draw();
    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
