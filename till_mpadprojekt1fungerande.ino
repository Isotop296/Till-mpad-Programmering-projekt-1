#include <Wire.h>
#include <Servo.h>


Servo myservo1;// säger bara till arduinon att det finns en servo som kallas myservo1
Servo myservo2;// säger bara till arduinon att det finns en servo som kallas myservo2
//Servo myservo3; kanske skulle användas för att ha den vertikala axeln, men behövdes inte. säger bara till arduinon att det finns en servo som kallas myservo3

int i = 0; //skapar en variabel(i) och ger den värdet 0
//int j = i; används inte men kanske skulle använts för att den skulle kunna fortsätta om i var mindre än 180 eller störe än 0. Skapar variabeln j som är lika med i
const int trigPin = 10;//skapar att sensorns trigpin eller den som skickar ut är kopplad till 10  echopin.
const int echoPin = 11;//echopin, sen som tar emot är kopplad till 11
long duration;//definerar variabler
int distance;//definerar variabler

void setup() {
  pinMode(4, OUTPUT);//är för lasern så jag kan stänga av den och sätta på den
  //pinMode(2, INPUT);användes inte men skulle varit om jag använt en knapp

  myservo1.attach(9);//sätter att servo 1 är kopplad till pin 9
  myservo2.attach(6);//sätter att servo 2 är kopplad till pin 6

  pinMode(trigPin, OUTPUT); //  sätter trigPin som en Output
  pinMode(echoPin, INPUT); // sätterechoPin som en Input
  Serial.begin(9600); // startar serial monitern om jag skulle till exempel kolla värderna från sensorn

}

void loop() {
  
  for (i = 0; i < 180; i = i + 10) {
    delay(50);//gör så att den väntar i 50 ms
    checkDist();//kollar funktionen checkDist
    if (distance < 10) {
      setLazer();//startar funktionen setLazer
        delay(2000);//stannar allt i 2s
          ( i=i-10);//tar minus så i inte blir störe och då så att servo1 inte ökar i grader tills distancen blir över 10
    }
    //if sats som kollar om distancen är mindre än 10
    else{
    myservo1.write(i);//sätter servo1 på i grader, sätter att servons grader blir lika med i
     digitalWrite(4, LOW);//stänger av lasern
    }
    //else sats som sätts på om distancen är mer än 10,
  }
  //for lop som ökar i om den är mindre än 180 och gör allt i loppen medans det stämmer,  första påståndet säger bara att i blir lika med 0, deta sker om det andra påstondet stämmer vilket är att i ska vara mindre än 180,det sista påståndets gör att varje gång den går in i for loopen lägger den till tio till i

  for (i = 180; i > 0; i = i - 10) {
     delay(50);
    checkDist();//kollar funktionen checkDist
    if (distance < 10) {
      setLazer();//startar funktionen setLazer
      delay(2000);//stannar allt i 2s
      ( i=i+10);//tar plus så i inte blir mindre och då så att servo1 inte minskar i grader tills distancen blir över 10
    }
     //if sats som kollar om distancen är mindre än 10
    else{
     myservo1.write(i);//sätter servo1 på i grader, sätter att servons grader blir lika med i
      digitalWrite(4, LOW);//stänger av lasern
    }
     //else sats som sätts på om distancen är mer än 10,
  }
  //for lop som minskar i om den är större än 0 och gör allt i loppen medans det stämmer, Alla påstånde fungera lika dana fast nu kollar den så att i är större än noll och den tar minus 10 på i
}


void checkDist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
   // sätter trigPin på hög lägge i 10 micro sekunder
  digitalWrite(trigPin, LOW);
  // läser av echoPin, retunerar sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);//kollar hur länge det varade mellan impulsen från trigpin till echopin
  distance = duration * 0.034 / 2;// räknar ut distance
  // Serial.print("Distance: "); Kan använda denna kod om jag vill se vad jag får ut
  // Serial.println(distance); Kan använda denna kod om jag vill se vad jag får ut
}
//funktion som kollar en distans på ett föremål framför sensorn
void setLazer() {
  
  myservo2.write(i);//sätter servo2 på i grader, sätter att servons grader blir lika med i
   delay(20);//gör så att den väntar i 20 ms
  digitalWrite(4, HIGH);//sätter på lasern, ger pin 4 hög elektrisitet
  delay(50);//gör så att den väntar i 50 ms
  
}
