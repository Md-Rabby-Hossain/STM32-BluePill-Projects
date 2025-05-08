#define SENSOR_PIN PA5

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT_ANALOG);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Reverse the condition logic
  if (sensorValue > 2500) {
    Serial.println("Object Detected");
  } else {
    Serial.println("No Object");
  }

  delay(500);
}
