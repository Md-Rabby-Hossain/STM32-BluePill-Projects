#define TRIG_PIN PA1
#define ECHO_PIN PA0

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration;
  float distance_cm;

  // Send a 10us HIGH pulse to trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the length of echo pulse in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance: sound speed = 0.0343 cm/us
  distance_cm = (duration * 0.0343) / 2;

  // Print distance
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500); // Wait before next reading
}
