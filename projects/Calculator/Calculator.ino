#include "LiquidCrystal_I2C.h"
#include "Keypad.h"

//////////
// KeyPad :
//
//                 ===========
//                 | 1 2 3 A |
//                 | 4 5 6 B |
//                 | 7 8 9 C |
//                 | * 0 # D |
//  =========================================
//    |   |   |   |   |   |   |   |   |   |       <= Keyboard pin
//   N/A  5   6   7   8   9   10  11  12 N/A      <= Arduino digital pin
//////////

char keypadKeys[4][4] = {{'1','2','3','A'},
                         {'4','5','6','B'},
                         {'7','8','9','C'},
                         {'*','0','#','D'}};
 
byte keypadRowPin[4] = {9,10,11,12};
byte keypadColPin[4] = {5,6,7,8};
 
Keypad keypad(makeKeymap(keypadKeys), keypadRowPin, keypadColPin, 4, 4);

//////////
// Screen :
//   GND => GND
//   VCC => +5V
//   SDA => SDA
//   SDL => SDL
//////////

LiquidCrystal_I2C lcd(0x27,16,2);


//////////
// Setup
//////////
void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(0));
    
    lcd.init();
    lcd.clear();
    lcd.backlight();
}

//////////
// Play the success animation
//////////
void playQuestionAnimation(const String& question, int questionLength)
{
    lcd.clear();
    for (int i=0; i<16; i++)
    {
      lcd.setCursor(i, 0);
      lcd.print('?');
      lcd.setCursor(i, 1);
      lcd.print('?');
      delay(25);
    }
    
    for (int i=0; i<16; i++)
    {
      lcd.setCursor(i, 0);
      if (i < questionLength) lcd.print(question.charAt(i));
      else                    lcd.print(' ');
      lcd.setCursor(i, 1);
      lcd.print(' ');
      delay(25);
    }
    
    lcd.setCursor(0, 0);
    lcd.print(question);
}

//////////
// Play the result animation
//////////
void playResultAnimation(const String& result)
{
    int resultLength = result.length();

    for (int i=0; i<resultLength; i++)
    {
      char currentChar = result.charAt(i);
      for (int j=15; j>=i; j--)
      {
        lcd.setCursor(j, 1);
        lcd.print(currentChar);
        if (j < 15) lcd.print(' ');
        delay(25);
      }
    }
}

//////////
// Play the clear answer animation
//////////
void playClearAnswerAnimation(int questionLength)
{
    for (int i=15; i>questionLength-2; i--)
    {
      lcd.setCursor(i, 0);
      lcd.print('?');
      delay(25);
    }
    
    for (int i=questionLength; i<16; i++)
    {
      lcd.setCursor(i, 0);
      lcd.print(' ');
      delay(25);
    }
}

//////////
// Play the answer animation
//////////
void playAnswerAnimation(int questionLength, int answer)
{
    for (int i=15; i>questionLength-2; i--)
    {
      lcd.setCursor(i, 0);
      lcd.print('!');
      delay(25);
    }

    String answerString(answer);
    int answerLength = answerString.length();
    for (int i=questionLength-1; i<16; i++)
    {
      lcd.setCursor(i, 0);
      int index = i-(questionLength-1);
      if (index < answerLength) lcd.print(answerString.charAt(index));
      else                      lcd.print(' ');
      delay(25);
    }
}

//////////
// Get the answer from the user
//////////
int getUserAnswer(int questionLength)
{
	// Wait for input
	int answer = 0;

	bool inputDone = false;
	while (inputDone == false)
	{
		char pressed = keypad.getKey();

		if (pressed != 0)
		{
			if (pressed == 'A')       answer = 9999;
      else if (pressed == '0')  answer = answer*10;
      else if (pressed == '1')  answer = 1 + answer*10;
			else if (pressed == '2')  answer = 2 + answer*10;
			else if (pressed == '3')  answer = 3 + answer*10;
			else if (pressed == '4')  answer = 4 + answer*10;
			else if (pressed == '5')  answer = 5 + answer*10;
			else if (pressed == '6')  answer = 6 + answer*10;
			else if (pressed == '7')  answer = 7 + answer*10;
			else if (pressed == '8')  answer = 8 + answer*10;
			else if (pressed == '9')  answer = 9 + answer*10;
			else if (pressed == '*')  inputDone = true;

			if (answer > 1000)
			{
				answer = 0;
        playClearAnswerAnimation(questionLength);
			}

      if (answer > 0)
      {
        lcd.setCursor(questionLength - 1, 0);
        lcd.print(answer);
      }
		}
	}
	
	return answer;
}

//////////
// Loop
//////////
void loop()
{
  // Pick numbers, build question and answer
  int A               = random(5, 20);
  int B               = random(5, 20);
  int answer          = A + B;
  String question     = String(A) + String(" + ") + String(B) + String(" = ?");
  int questionLength  = question.length();

  // Display the question
  playQuestionAnimation(question, questionLength);

  // Get user answer
	int userAnswer = getUserAnswer(questionLength);

  // Display success or failure
	if (userAnswer == answer)
	{
		playResultAnimation("Bravo!");
	}
	else
	{
    playResultAnimation("Perdu!");
    playAnswerAnimation(questionLength, answer);
	}
 
  while (keypad.getKey() == 0)
  {
    delay(10);
  }
}
