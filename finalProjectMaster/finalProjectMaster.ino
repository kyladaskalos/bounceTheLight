#include <Adafruit_CircuitPlayground.h>

int buttonPlay = 5;
volatile bool buttonFlag = 0;
int buttonStart = 4;
volatile bool startFlag = 0;
int switchPin = 7;
volatile bool switchFlag = 0;
int switchState = 0;
int switcher = 0;
int ledTracker = 0;
int totalPoints = 0;
bool continueGame = 1;
bool gameWin = 0;
bool gameLoss = 0;
int roundCounter = 0;
bool hardMode = 0;
int ballSpeed = 0;
bool playSparkle = 0;

float midi[127];
int A_four = 440;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPlay), ButtonBISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonStart), StartISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(switchPin), SwitchISR, CHANGE);
  generateMIDI();
}

void loop() {

  if(switchFlag == 1){ //dertimines  and prints mode
    switchState = digitalRead(switchPin);

    if(switchState == 0){
      hardMode = 0;
      ballSpeed = 300;
      Serial.println("Easy Mode");
    } else if(switchState == 1){
      hardMode = 1;
      ballSpeed = 200;
      Serial.println("Hard Mode");
    }

    switchFlag = 0;
  }

  while(startFlag == 1){

    //Detemine the 'bounce zone'
    if(totalPoints < 4){
      roundOne();
    } else if(totalPoints > 3 && totalPoints < 6){
      roundTwo();
    } else if(totalPoints > 5 && totalPoints < 9){
      roundThree();
    } else if(totalPoints > 8 && totalPoints < 14){
      finalRound();
    }

    while(switcher % 2 == 0 && continueGame == 1){
      for(ledTracker; ledTracker < 10; ledTracker++){ // iterates through, adding 1 to ledTracker each time
        if(totalPoints < 4){
          roundOne();
        }else if(totalPoints > 3 && totalPoints < 6){
          roundTwo();
        }else if(totalPoints > 5 && totalPoints < 9){
          roundThree();
        }else if(totalPoints > 8 && totalPoints < 14){
          finalRound();
        }

        CircuitPlayground.setPixelColor(ledTracker, 255, 255, 255);
        delay(ballSpeed);
        CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
        delay(ballSpeed);

        if(buttonFlag == 1){ // checking to see if bounced
          if(roundCounter == 1){ // checks when button is pressed and adds point if bounced in the correct zone
            if(ledTracker == 1 || ledTracker == 2 || ledTracker == 3 || ledTracker == 4){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          } else if(roundCounter == 2){
            if(ledTracker == 2 || ledTracker == 3 || ledTracker == 4){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          } else if(roundCounter == 3){
            if(ledTracker == 3 || ledTracker == 4){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          } else if(roundCounter == 4){
            if(ledTracker == 4){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          }
          CircuitPlayground.playTone(midi[70], 50);
          ledTracker--;
          switcher++;
          buttonFlag = 0;
          break;
        }
        if(ledTracker == 9){ // circles around
          ledTracker = -1;
        }
        if(totalPoints == 13){ // checks for win
          gameWin = 1;
          continueGame = 0;
          break;
        }
        if(ledTracker == 4){ // check for loss
          gameLoss = 1;
          continueGame = 0;
          break;
        }
      }
    } 
    while(switcher % 2 != 0 && continueGame == 1){
      for(ledTracker; ledTracker > -1; ledTracker--){ // iterates through, subtracting 1 from ledTracker
        if(totalPoints < 4){
          roundOne();
        }else if(totalPoints > 3 && totalPoints < 6){
          roundTwo();
        }else if(totalPoints > 5 && totalPoints < 9){
          roundThree();
        }else if(totalPoints > 8 && totalPoints < 14){
          finalRound();
        }

        CircuitPlayground.setPixelColor(ledTracker, 255, 255, 255);
        delay(ballSpeed);
        CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
        delay(ballSpeed);

        if(buttonFlag == 1){ //check if bounced
          if(roundCounter == 1){ // checks when button is pressed and adds point if bounced in the correct zone
            if(ledTracker == 8 || ledTracker == 7 || ledTracker == 6 || ledTracker == 5){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          } else if(roundCounter == 2){
            if(ledTracker == 7 || ledTracker == 6 || ledTracker == 5){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          } else if(roundCounter == 3){
            if(ledTracker == 6 || ledTracker == 5){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          } else if(roundCounter == 4){
            if(ledTracker == 5){
              totalPoints++;
              Serial.print("Points: ");
              Serial.println(totalPoints);
            }
          }
          CircuitPlayground.playTone(midi[70], 50);
          ledTracker++;
          switcher++;
          buttonFlag = 0;
          break;
        }
        if(ledTracker == 0){ // circles around
          ledTracker = 10;
        }
        if(totalPoints == 13){ //checks for win
          gameWin = 1;
          continueGame = 0;
          break;
        }
        if(ledTracker == 5){ // check for loss
          gameLoss = 1;
          continueGame = 0;
          break;
        }
      } 
    }

    if(gameLoss == 1){ // prints loss if led is not pressed in time
      Serial.println("You lose.");
      startFlag = 0;
      break;
    }
    if(gameWin == 1){ // prints win if 13 points
      Serial.println("You win!");
      startFlag = 0;
      playSparkle = 1;
      break;
    }
  }

  if(playSparkle == 1){
    victoryFlash();
  }
}

void ButtonBISR(){
  buttonFlag = 1;
}

void SwitchISR(){ // dertermins hard or easy mode
  switchFlag = 1;
}

void StartISR(){ // will start the game
  startFlag = 1;
}

void roundOne(){
  CircuitPlayground.clearPixels();

  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(3, 0, 0, 255);
  CircuitPlayground.setPixelColor(2, 0, 0, 255);
  CircuitPlayground.setPixelColor(1, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);
  CircuitPlayground.setPixelColor(6, 0, 0, 255);
  CircuitPlayground.setPixelColor(7, 0, 0, 255);
  CircuitPlayground.setPixelColor(8, 0, 0, 255);

  roundCounter = 1;
}

void roundTwo(){
  CircuitPlayground.clearPixels();

  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(3, 0, 0, 255);
  CircuitPlayground.setPixelColor(2, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);
  CircuitPlayground.setPixelColor(6, 0, 0, 255);
  CircuitPlayground.setPixelColor(7, 0, 0, 255);

  roundCounter = 2;
}

void roundThree(){
  CircuitPlayground.clearPixels();

  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(3, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);
  CircuitPlayground.setPixelColor(6, 0, 0, 255);

  roundCounter = 3;
}

void finalRound(){
  CircuitPlayground.clearPixels();

  CircuitPlayground.setPixelColor(4, 0, 0, 255);
  CircuitPlayground.setPixelColor(5, 0, 0, 255);

  roundCounter = 4;
}

void victoryFlash(){ // plays upon victory
  int randNum = random(10);
  delay(300);

  if(randNum == 0){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 0, 0);
    }
  } else if(randNum == 1){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 0, 255, 0);
    }
  } else if(randNum == 2){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 0, 0, 255);
    }
  } else if(randNum == 3){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 128, 0, 128);
    }
  } else if(randNum == 4){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 165, 0);
    }
  } else if(randNum == 5){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 0, 255);
    }
  } else if(randNum == 6){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 192, 203);
    }
  } else if(randNum == 7){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 128, 0, 128);
    }
  } else if(randNum == 8){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 0, 128, 128);
    }
  } else if(randNum == 9){
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 0, 255, 255);
    }
  }
}

// adapted from https://subsynth.sourceforge.net/midinote2freq.html
void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}
