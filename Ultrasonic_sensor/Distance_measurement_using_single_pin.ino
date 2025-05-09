#define TRIG_ECHO_PIN  PA0  // Using PA0 for both Trigger and Echo

void setup() {
  Serial.begin(9600);  // Start serial communication
  pinMode(TRIG_ECHO_PIN, OUTPUT);  // Set TRIG_ECHO_PIN as output (initially for trigger)
  digitalWrite(TRIG_ECHO_PIN, LOW); // Ensure it's low to start
}

void loop() {
  long duration, distance;

  // Send the trigger pulse (start measurement)
  pinMode(TRIG_ECHO_PIN, OUTPUT);  // Set as output for trigger
  digitalWrite(TRIG_ECHO_PIN, LOW);  // Ensure LOW
  delayMicroseconds(2);
  digitalWrite(TRIG_ECHO_PIN, HIGH);  // Send HIGH pulse to start measurement
  delayMicroseconds(10);  // Pulse duration
  digitalWrite(TRIG_ECHO_PIN, LOW);  // End the pulse

  // Switch to input to read the Echo pulse
  pinMode(TRIG_ECHO_PIN, INPUT);  // Set as input to read Echo pulse
  duration = pulseIn(TRIG_ECHO_PIN, HIGH);  // Measure pulse duration

  // Calculate the distance (cm)
  distance = duration * 0.034 / 2;  // Duration * speed of sound (0.034 cm/µs), divide by 2 for round trip

  // Output distance
  if (distance > 0) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Out of range or no echo");
  }

  delay(500);  // Delay between readings
}
