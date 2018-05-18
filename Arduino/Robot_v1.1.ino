//constant for ultrasound sensor
#define left_trig  2
#define left_echo  3

#define right_trig  4
#define right_echo  5

//motor control
int left_1 = 10;
int left_2 = 9;

int right_1 = 8;
int right_2 = 7;

//ultrasound variable
float distance;
float duration;
float cm_left;
float cm_right;


// proximiti sensor
int proximite = A7;

//proxi variable
float volts;
int distance_front;

void setup() {

  Serial.begin(9600);

  //motor setup
  pinMode(left_1, OUTPUT);
  pinMode(left_2, OUTPUT);
  pinMode(right_1, OUTPUT);
  pinMode(right_2, OUTPUT);

  //ultrasound setup
  pinMode(left_trig, OUTPUT);
  pinMode(left_echo, INPUT);
  pinMode(right_trig, OUTPUT);
  pinMode(right_echo, INPUT);

}


void Go()
{
  //gauche
  digitalWrite(left_1, HIGH);
  digitalWrite(left_2, LOW);

  //droite
  digitalWrite(right_1, HIGH);
  digitalWrite(right_2, LOW);
}

void Back()
{
  //gauche
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, HIGH);

  //droite
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, HIGH);

  delay(500);
}

void Stop()
{
  //gauche
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, LOW);

  //droite
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, LOW);

  delay(500);
}

void Go_left()
{
  //gauche
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, HIGH);

  //droite
  digitalWrite(right_1, HIGH);
  digitalWrite(right_2, LOW);

  delay(500);
}

void Go_right()
{
  //gauche
  digitalWrite(left_1, HIGH);
  digitalWrite(left_2, LOW);

  //droite
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, HIGH);

  delay(500);
}

void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

}

void loop() {
  //Read ultrasound sensors
  SonarSensor(left_trig, left_echo);
  cm_left = distance;
  SonarSensor(right_trig, right_echo);
  cm_right = distance;

  //read IR distance
  volts = analogRead(proximite) * 0.0048828125;
  distance_front = 17 * pow(volts, -1);

  //debug test sensor
  Serial.print("distance left:  ");
  Serial.print(cm_left);
  Serial.print("  distance right:   ");
  Serial.print(cm_right);
  Serial.print("   distance front:  ");
  Serial.println(distance_front);
  //delay(100);

  //Moving
  if ((distance_front > 14) and (cm_left > 5) and (cm_right > 5))
  {
    //avancer
    Go();
  }

  else
  {
    // si il ya plus d'espace a gauche que a droite
    if (cm_left > cm_right)
    {
      //Stop//
      Stop();

      //reculer//
      Back();

      //deplacer gauche//
      Go_left();
    }

    // si il ya plus d'espace à droite qu'à gauche
    if (cm_right > cm_left)
    {
      //stop//
      Stop();

      //reculer//
      Back();

      //deplacer droite//
      Go_right();
    }


  }

}

