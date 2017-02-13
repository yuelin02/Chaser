#include <SevenSeg.h>
//https://www.arduino.cc/en/Tutorial/ForLoopIteration

//Timer
unsigned long Watch, _micro, time = millis();
unsigned int Clock = 0, R_clock;
boolean Reset = false, Stop = false, Paused = false;
volatile boolean timeFlag = false;



//led pins and button pins
int leds[] = {5, 6, 7, 8, 9, 10, 11, 12};
//int newled = 4;
int buttons[] =          {22, 24, 26, 28, 30, 32, 34, 36};
int buttonsState[] =     {0,  0,  0,  0,  0,  0,  0, 0};
int buttonsLastState[] = {0,  0,  0,  0,  0,  0,  0, 0};

//score
int score = 0;

//delay
unsigned long previousMillis = 0;
const long interval = 1500;

//led random
int ledState = 0;
int lastledState = 0;
int target = random(0, 8);

//start button
int startButton = 3;
int buttonPushCounter = 0;
int startButtonState = 0;
int startButtonLastState = 0;
boolean gameStarted = false;
boolean lose = false;
boolean win = false;

//int seconds =0;
unsigned long currentTime;
int previousTime = 0;
int gameTime = 10000;
int countDown;
int secondsTimer;


void setup() {
  Serial.begin(9600);
  Serial.println("hello");

  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode (buttons[i], INPUT_PULLUP);
  }
  pinMode(3, INPUT_PULLUP);
  Serial.println("ready");
//  SetTimer(10); // 30 seconds
}

void checkStartButton() {
  startButtonState = digitalRead(startButton);
  
  if (startButtonState != startButtonLastState) {
//    Serial.println("ready");
    if (startButtonState == LOW) {
      currentTime = millis();
      previousTime = currentTime;
      gameStarted = true;
      Serial.println("s");
      Serial.println("s");
      Serial.println("s");
    }
  }
  startButtonLastState = startButtonState;
}

void setsNewLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  
    int temp = target;
    while (temp == target) {
      target = random(0, 8);
    }

    for (int i = 0; i < 8; i++) {
      digitalWrite(leds[i], LOW);
    }
    digitalWrite(leds[target], HIGH);
  }
}

void checkButtonInput() {
  for (int i = 0; i < (sizeof(buttons) / sizeof(int)); i++) {
    buttonsState[i] = digitalRead(buttons[i]);

    if (target == i) {
      if (buttonsState[i] != buttonsLastState[i]) {
        if (buttonsState[i] == LOW) {
          score++;
          Serial.println(score);
          if (score >= 4) {
            Serial.println("w");
            Serial.println("w");
            Serial.println("w");
            resetGame();
            gameStarted = false;
          }
        }
      }
    }
    buttonsLastState[i] = buttonsState[i];
  }
}

void resetGame() {
  for (int i = 0; i < (sizeof(buttonsState) / sizeof(int)); i++) {
    buttonsState[i] = 0;
    buttonsLastState[i] = 0;
    digitalWrite(leds[i], LOW);
  }
  currentTime = millis();
  previousTime = currentTime;
  Serial.println("r");
  Serial.println("r");
  Serial.println("r");
  score = 0;
}

void loop() {
  //check to see if start button is pushed - if it is pushed, turn game start on.
  if (!gameStarted) {
    checkStartButton();
  } else {
    //if the game is running:
    setsNewLED();
    checkButtonInput();
    timer(); // run the timer
    if((score<4)&&(secondsTimer>0)){
      Serial.print(secondsTimer);
      Serial.print(",");
      Serial.println(score);
    }else{
      Serial.println("l");
      Serial.println("l");
      Serial.println("l");
      gameStarted = false;
//      delay(6000);
      resetGame();
    }
   
//    if (Stop == true) {
//      Serial.println("o");
//      resetGame();
//      gameStarted = false;
//      ResetTimer();
//    }
  }
}





void timer(){
  currentTime = millis();
  if (currentTime - previousTime >= gameTime) {
    previousTime = currentTime;
    
  }
  countDown = gameTime - (currentTime - previousTime);
  secondsTimer = ceil(countDown/1000);
    //Serial.println(secondsTimer);
  
}













//Timer
boolean CountDownTimer()
{
  static unsigned long duration = 1000; // 1 second
  timeFlag = false;

  if (!Stop && !Paused) // if not Stopped or Paused, run timer
  {
    // check the time difference and see if 1 second has elapsed
    if ((_micro = millis()) - time > duration )
    {
      Clock--;
      timeFlag = true;
      Serial.println(Clock);
      if (Clock == 0) // check to see if the clock is 0
        Stop = true; // If so, stop the timer

      _micro < time ? time = _micro : time += duration;
    }
  }
  return !Stop; // return the state of the timer
}


void ResetTimer() {
  SetTimer(R_clock);
  Stop = false;
}

void StartTimer() {
  Watch = millis(); // get the initial milliseconds at the start of the timer
//  Serial.println(micros());
  Stop = false;
  Paused = false;
}

void StopTimer() {
  Stop = true;
}

void StopTimerAt(unsigned int seconds) {
  if (TimeCheck(seconds) )
    Stop = true;
}

void SetTimer(unsigned int seconds) {
  // StartTimer(seconds / 3600, (seconds / 3600) / 60, seconds % 60);
  Clock = seconds;
  R_clock = Clock;
  Stop = false;
}

int ShowSeconds() {
  return Clock % 60;
}

boolean TimeHasChanged() {
  return timeFlag;
}

// output true if timer equals requested time
boolean TimeCheck(unsigned int seconds) {
  return (seconds == ShowSeconds());
}


