
int proximPolice = 0;
int contactPolice = 0;
int lampDetect = 0;
int Mode_1 = 0;
int Mode_2 = 0;
int Mode_3 = 0;
int Mode_4 = 0;
int Automatic = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(2, INPUT);   // photo resistor Analog
    pinMode(A3, INPUT);  // photo resistor Analog
    pinMode(13, OUTPUT); // alarm sur arduino Digital
    pinMode(6, OUTPUT);  // LED rouge sur plaque Digital
    pinMode(7, INPUT);   // manual/ auto toggle switch Digital
    pinMode(12, OUTPUT); // works like 13 & 6 in auto but not manual Digital
    pinMode(3, INPUT);   // contact relay Digital
    pinMode(A5, INPUT);  // contact - touche Analog
    pinMode(4, INPUT);   // proximity sensor digital
    pinMode(A4, INPUT);  // proximity sensor Analog
    pinMode(5, INPUT);   // rgb led
    pinMode(11, OUTPUT); //
    pinMode(10, OUTPUT); //
    pinMode(9, OUTPUT);  //
}

void loop()
{

    static uint8_t counter = 0;  // casser le compteur de boucle
    static uint8_t counter2 = 0; // casser le compteur de boucle

    lampDetect = analogRead(A3);    // Lire la sortie du capteur de photorésistance
    proximPolice = analogRead(A4);  // Lire la sortie du capteur de proximitie
    contactPolice = analogRead(A5); // lire la capteur Touche

    Automatic = digitalRead(7);

    Mode_1 = digitalRead(2);
    Mode_3 = digitalRead(4);
    Mode_4 = digitalRead(5); // State de feux Rouge

    if (Mode_1 == 0)
    {
        Serial.println("in mode 1");

        {
            // si la photorésistance est supérieure à 600, allumez la LED rouge.
            if (lampDetect < 800)
            {
                digitalWrite(13, HIGH); // Mettez la led rouge en marche
                digitalWrite(6, HIGH);  // Mettez la led rouge en marche
                Serial.println("on");
                Serial.print(lampDetect);
                if (Automatic == 0)
                {
                    digitalWrite(12, HIGH);
                }
            }
        }
    }
    if (Mode_3 == 0)
    {
        Serial.println("in mode 3");
        if (proximPolice < 239)
        {
            digitalWrite(13, HIGH); // Mettez la led rouge en marche
            digitalWrite(6, HIGH);  // Mettez la led rouge en marche
            Serial.println("on");
        }
    }

    if (Mode_4 == 0)
    {
        for (counter = 0; counter < 30; ++counter)
        {
            analogWrite(11, 255);
            analogWrite(10, 0);
            analogWrite(9, 0);
            if (lampDetect < 800 || (proximPolice < 239 || contactPolice < 300))
            {
                analogWrite(11, 0);
                analogWrite(10, 0);
                analogWrite(9, 0);
                digitalWrite(12, HIGH);
                digitalWrite(13, HIGH);
                delay(10000); // Wait for 10000 millisecond(s)
                digitalWrite(12, LOW);
                digitalWrite(13, LOW);
            }
            delay(200); // Wait for 200 millisecond(s)
        }
        analogWrite(11, 155);
        analogWrite(10, 153);
        analogWrite(9, 0);
        delay(4000); // Wait for 4000 millisecond(s)
        analogWrite(11, 0);
        analogWrite(10, 255);
        analogWrite(9, 0);
        delay(6000); // Wait for 6000 millisecond(s)
    }
    else
    {
        if (Mode_4 == 0)
        {
            analogWrite(11, 0);
            analogWrite(10, 0);
            analogWrite(9, 0);
            lampDetect = analogRead(A3);
            proximPolice = analogRead(A4);
            contactPolice = analogRead(A5);
            if (lampDetect < 800 || (proximPolice < 239 || contactPolice < 300))
            {
                digitalWrite(12, HIGH);
                digitalWrite(13, HIGH);
                for (counter2 = 0; counter2 < 5; ++counter2)
                {
                    analogWrite(11, 255);
                    analogWrite(10, 0);
                    analogWrite(9, 0);
                    delay(300); // Wait for 300 millisecond(s)
                    analogWrite(11, 0);
                    analogWrite(10, 0);
                    analogWrite(9, 0);
                    delay(500); // Wait for 500 millisecond(s)
                }
            }
        }
    }
}
