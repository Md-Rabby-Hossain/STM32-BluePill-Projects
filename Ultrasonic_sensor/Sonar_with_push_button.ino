#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG_ECHO_PIN  PA0
#define BUTTON_PIN     PA1

int currentIndex = 0;
String names[] = {"Rabby", "Kamal", "Sanjid", "Saif"};
int totalNames = 4;
bool buttonPressed = false;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Press button to");
  display.println("show names & distance");
  display.display();

  pinMode(TRIG_ECHO_PIN, OUTPUT);
  digitalWrite(TRIG_ECHO_PIN, LOW);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
    buttonPressed = true;
    delay(50); // simple debounce

    if (currentIndex < totalNames) {
      showName(names[currentIndex]);
      currentIndex++;
    } else {
      float distance = measureDistance();
      showDistance(distance);
      currentIndex = 0;  // Reset index to cycle again
    }

    delay(500);
  }

  if (digitalRead(BUTTON_PIN) == HIGH) {
    buttonPressed = false;
  }
}

float measureDistance() {
  long duration;
  float distance;

  pinMode(TRIG_ECHO_PIN, OUTPUT);
  digitalWrite(TRIG_ECHO_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_ECHO_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_ECHO_PIN, LOW);

  pinMode(TRIG_ECHO_PIN, INPUT);
  duration = pulseIn(TRIG_ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void showName(String name) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println(name);
  display.display();
}

void showDistance(float distance) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Distance:");

  display.setTextSize(2);
  display.setCursor(0, 20);

  if (distance > 0 && distance < 400) {
    display.print(distance, 1);
    display.println(" cm");
  } else {
    display.setTextSize(1);
    display.setCursor(0, 30);
    display.println("Out of range");
  }

  display.display();
}
