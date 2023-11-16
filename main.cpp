const int buttonPin = 2;
const int ledPin = 13;
int led = 0;

unsigned long currentMillis;
unsigned long previousMillis = 0, previousMillisFade = 0;
unsigned long interval = 1000;
unsigned long clickInterval = 250;
int clickCounter = 0;

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
	Serial.begin(9600);
}

void loop()
{
    if (digitalRead(buttonPin) == HIGH)
    {
		Serial.print("\n light on");
        digitalWrite(ledPin, false);
        led = 0;

        if (checkDoubleClick())
        {
            changeInterval();
        }
        else
        {
            togleLED();
        }
    }
}

void togleLED()
{
    while (true)
    {

        if (digitalRead(buttonPin) == HIGH)
        {
                break;
        }
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            if (led == 0)
            {
                digitalWrite(ledPin, true);
                led = 1;
            }
            else
            {
                digitalWrite(ledPin, false);
                led = 0;
            }
        }
    }
}

bool checkDoubleClick()
{
    unsigned long clickTime = millis();
    if (clickTime - previousMillisFade > clickInterval)
    {
        clickCounter = 0;
    }

    clickCounter++;

    if (clickCounter == 2)
    {
        clickCounter = 0;
        previousMillisFade = clickTime;
        return true;
    }

    previousMillisFade = clickTime;
    return false;
}

void changeInterval()
{
    if (interval <= 500)
    {
        interval = 1000;
    }
    else
    {
        interval -= 250;
    }
}
