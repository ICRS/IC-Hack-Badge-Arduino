#include "ICHack.h"
#include <string>

// Create the frame buffer. The first 24 bits of each uint32_t
// represent one column of the LED matrix. You can write to this
// buffer directly and patters will appear on the display.
volatile uint32_t fb[FRAME_BUFFER_WIDTH];


int playerHeight = 0;
bool goingUp = false;
bool goingDown = false;
bool hoveredThree = false;
bool hoveredFour = false;
bool bigJump = false;
int pole1Y = 0;
int pole1Height = 3;

int pole2Y = -14;
int pole2Height = 2;
int score;
int birdY;

int timeSincePassed;

bool gameover = false;


void setup() {

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(LOGO_I, OUTPUT);
  pinMode(LOGO_C, OUTPUT);
  pinMode(LOGO_H, OUTPUT);
  digitalWrite(LOGO_I, LOW);
  digitalWrite(LOGO_C, LOW);
  digitalWrite(LOGO_H, LOW);
  pole1Y = 0;
  pole1Height = 3;
  timeSincePassed = 3;

  pole2Y = -14;
  pole2Height = 2;

  score = 0;

  birdY = -300;

  // Initialise the display by passing it the frame buffer. This
  // will create a thread that continuously renders the frame
  // buffer to the matrix.
  display_init(fb);
  delay(1000);
}

void drawpixel(int x, int y) {
  fb[x] |= 1 << y;
}

// these other three functions are unused but nice to have
void togglepixel(int x, int y) {
  fb[x] ^= 1 << y;
}

void undrawpixel(int x, int y) {
  fb[x] &= (((1 << 24) - 1) ^ (1 << y));
}

void fillrow(int row) {
  fb[row] = (1 << 24) - 1;
}


void handleJump() {
  if (goingUp) {
    if (playerHeight == 2) {
      // long press for high jump
      if (digitalRead(BUTTON_A) == LOW) {
        playerHeight++;
      }
      else {
        goingUp = false;
        goingDown = true;
      }
    }
    else if (playerHeight == 3) {
      if (!hoveredThree) {
        hoveredThree = true;
      }
      else {
        hoveredThree = false;
        playerHeight++;
      }
    }
    else if (playerHeight == 4) {
      if (!hoveredFour) {
        hoveredFour = true;
      }
      else {
        hoveredFour = false;
        goingUp = false;
        goingDown = true;
        playerHeight--;
      }
    }
    else {
      playerHeight++;
    }
  }

  else if (goingDown) {
    if (playerHeight > 0) {
      if (playerHeight == 3) {
        if (!hoveredThree) {
          hoveredThree = true;
        }
        else {
          hoveredThree = false;
          playerHeight--;
        }
      }
      else {
        playerHeight--;
      } 
    }
    else {
      goingDown = false;
    }
  }

  // jump input
  else if (digitalRead(BUTTON_A) == LOW) {
    if (playerHeight == 0) {
      if (!goingUp) {
        goingDown = false;
        goingUp = true;
      }
      playerHeight++;
    }
  }
}

void drawPole1(int y) {
  for (int i = 0; i < pole1Height; ++i) {
    drawpixel(4 - i, y);
  }
}

void drawPole2(int y) {
  for (int i = 0; i < pole2Height; ++i) {
    drawpixel(4 - i, y);
  }
}

void drawBird() {
  if (birdY >= 0) {
    drawpixel(0, birdY);
  }
}

void loop() {
  if (!gameover) {
    display_clear();
    handleJump();
  
    drawpixel(4 - playerHeight, 22);
    drawPole1(pole1Y);
    drawPole2(pole2Y);

    drawBird();

    if (pole1Y == 22 && playerHeight < pole1Height)
      gameover = true;
    if (pole2Y == 22 && playerHeight < pole2Height)
      gameover = true;

    // update obstacle 1 position
    if (pole1Y > 23) {
      pole1Y = random(-4, 1);
      pole1Height = random(1, 4);
    }
    else {
      pole1Y++;
    }

    // update obstacle 2 position
    if (pole2Y > 23) {
      pole2Y = random(min(-2, pole1Y - 10), min(1, pole1Y - 13));
      pole2Height = random(2, 4);
    }
    else {
      pole2Y++;
    }

    // update bird position
    if (birdY > 23) {
      birdY = random(-300, -500);
    }
    else {
      birdY += 3;
    }

    score++;
    timeSincePassed++;
  }

  // light up ic hack logo after jumping over obstacle
  if (pole1Y == 22 || pole2Y == 22) {
    timeSincePassed = 0;
  }

  if (timeSincePassed < 3) {
    digitalWrite(LOGO_I, HIGH);
    digitalWrite(LOGO_C, HIGH);
    digitalWrite(LOGO_H, HIGH);
  }
  else {
    digitalWrite(LOGO_I, LOW);
    digitalWrite(LOGO_C, LOW);
    digitalWrite(LOGO_H, LOW);
  }

  // speed up as game progresses
  delay(100000 / (score + 1000));

  if (gameover) {
    display_clear();
    static char score_message[] = "SCORE";
    display_draw_string(score_message, 5, 23);
    delay(1000);
    display_clear();
    display_draw_string((char*)(std::to_string(score).c_str()), std::to_string(score).length(), 23);
    delay(3000);
    gameover = false;
    setup();
  }
}
