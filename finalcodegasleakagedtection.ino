// === Pin Definitions ===
#define GREEN_LED 2
#define RED_LED 3
#define BUZZER 4             // Passive buzzer
#define RELAY_VALVE 5        // Relay controlling solenoid valve
#define GAS_SENSOR A0        // Analog input from MQ2 gas sensor

int threshold = 104;         // Adjust based on normal vs. leak readings

void setup() {
  // Set all pin modes
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY_VALVE, OUTPUT);

  // Set initial device states
  digitalWrite(GREEN_LED, HIGH);      // Green LED ON initially
  digitalWrite(RED_LED, LOW);         // Red LED OFF
  digitalWrite(RELAY_VALVE, HIGH);    // Relay OFF (Active LOW logic)

  // Start Serial Monitor
  Serial.begin(9600);
  Serial.println("Gas Leakage Monitoring System Started...");
}

void loop() {
  // Read analog gas value
  int gasValue = analogRead(GAS_SENSOR);

  // Print gas reading to Serial Monitor
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Check for gas leakage
  if (gasValue > threshold) {
    // GAS LEAKAGE DETECTED
    digitalWrite(GREEN_LED, LOW);       // Green LED OFF
    digitalWrite(RED_LED, HIGH);        // Red LED ON
    tone(BUZZER, 1000);                 // Passive buzzer on (1kHz)
    digitalWrite(RELAY_VALVE, LOW);     // Activate relay → solenoid valve ON
  } else {
    // NORMAL CONDITION
    digitalWrite(GREEN_LED, HIGH);      // Green LED ON
    digitalWrite(RED_LED, LOW);         // Red LED OFF
    noTone(BUZZER);                     // Stop buzzer
    digitalWrite(RELAY_VALVE, HIGH);    // Deactivate relay → solenoid valve OFF
  }

  delay(500); // 0.5 second delay before next check
}

