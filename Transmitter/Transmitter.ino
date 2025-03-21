#define TRANSMIT_LED 8   // Define LED pin

#define START_END_DELAY 150    // 2000ms LED ON at start & end
#define ELEMENT_DELAY 10      // 1000ms OFF between bits
#define BIT_ON_TIME 60         // 1000ms ON/OFF time for each bit

void setup() {
    pinMode(TRANSMIT_LED, OUTPUT);
    Serial.begin(9600);
    Serial.println("Enter a message (spaces will be ignored):");
}

void loop() {
    if (Serial.available() > 0) {
        String message = Serial.readStringUntil('\n'); // Read user input
        message.trim(); // Remove spaces or newline characters

        // Remove spaces
        message.replace(" ", "");

        if (message.length() == 0) {
            Serial.println("Invalid input! Enter a valid message.");
            return;
        }

        // Append '#' as a terminator
        message += "#";

        Serial.println("Starting Transmission...");
        
        // Turn LED ON for 2000ms at the start
        digitalWrite(TRANSMIT_LED, HIGH);
        delay(START_END_DELAY);

        // Turn LED OFF for 1000ms before transmission starts
        digitalWrite(TRANSMIT_LED, LOW);
        delay(ELEMENT_DELAY);

        // Send Binary Data for each character
        for (char c : message) {
            Serial.print("Sending: ");
            Serial.println(c);

            for (int i = 7; i >= 0; i--) {
                bool bitState = (c >> i) & 1;
                
                digitalWrite(TRANSMIT_LED, bitState); // LED ON for '1', OFF for '0'
                delay(BIT_ON_TIME); // Hold state for 1000ms

                digitalWrite(TRANSMIT_LED, LOW); // Ensure OFF state between bits
                delay(ELEMENT_DELAY); // 1000ms delay before next bit
            }
        }

        Serial.println("Transmission Completed.");
        Serial.println("Enter next message:");
    }
}
