#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int buttonPlay = 5;
volatile bool buttonFlag = 0;
int switcher = 0;
int ledTracker = 0;
int totalPoints = 0;
bool continueGame = 1;
bool gameWin = 0;
bool gameLoss = 0;
int roundCounter = 0;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPlay), ButtonBISR, FALLING);
}

void loop() {

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
      delay(300);
      CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
      delay(300);

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
      delay(300);
      CircuitPlayground.setPixelColor(ledTracker, 0, 0, 0);
      delay(300);

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
    gameLoss = 0; // prevents infint printing
  }
  if(gameWin == 1){ // prints win if 13 points
    Serial.println("You win!");
    gameWin = 0; // prevents infint printing
  }
}

void ButtonBISR(){
  buttonFlag = 1;
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




