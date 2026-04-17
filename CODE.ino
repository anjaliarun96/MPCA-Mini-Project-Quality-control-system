int irPin = 2;
int ldrPin = 3;

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define OUT 8

int red, green, blue;

void setup() {
  pinMode(irPin, INPUT);
  pinMode(ldrPin, INPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {

  // STEP 1: Detect object
  if (digitalRead(irPin) == LOW) {

    Serial.println("Object detected");

    // STEP 2: Check lighting
    if (digitalRead(ldrPin) == LOW) {

      Serial.println("Good lighting");

      // STEP 3: Read color
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      red = pulseIn(OUT, LOW);

      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      blue = pulseIn(OUT, LOW);

      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      green = pulseIn(OUT, LOW);

      Serial.print("R:");
      Serial.print(red);
      Serial.print(" G:");
      Serial.print(green);
      Serial.print(" B:");
      Serial.println(blue);

      // STEP 4: DECISION
      if (red + 40 < green && red + 40 < blue) {
        Serial.println("ACCEPTED (Valid product - RED)");
      } else {
        Serial.println("REJECTED (Defective product)");
      }

      Serial.println("----------------------");

    } else {
      Serial.println("Bad lighting - Cannot analyze");
    }
  }
  else
  {
    Serial.println("No object detected");
  }

  delay(1500);
}