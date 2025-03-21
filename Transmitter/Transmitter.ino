#define TRANSMIT_LED 8   // Define LED pin

#define START_END_DELAY 150    // 2000ms LED ON at start & end
#define ELEMENT_DELAY  30  // 1000ms OFF between bits
#define BIT_ON_TIME 60        // 1000ms ON/OFF time for each bit

const char* encodingTable[52] = {
    "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001", "001010", // A-J
    "001011", "001100", "001101", "001110", "001111", "010000", "010001", "010010", "010011", "010100", // K-T
    "010101", "010110", "010111", "011000", "011001", "011010", // U-Z 26
    "011011", "011100", "011101", "011110", "011111", "100000", "100001", "100010", "100011", "100100", // a-j 27
    "100101", "100110", "100111", "101000", "101001", "101010", "101011", "101100", "101101", "101110", // k-t
    "101111", "110000", "110001", "110010", "110011", "110100"  // u-z 52
};

// Special character encoding (6-bit)
const char* specialCharTable[11] = {
    "110101", "110110", "110111", "111000", "111001", "111010", "111011", "111100", "111101", "111110", "111111" // 53 - 63
};
const char specialChars[11] = {' ', '#', '.', '?', '!', ':', '@', '_', '\'', '-', ';'};

void setup() {
    pinMode(TRANSMIT_LED, OUTPUT);
    Serial.begin(9600);
    Serial.println("Enter a message:");
}

void loop() {
    if (Serial.available() > 0) {
        String message = Serial.readStringUntil('\n'); // Read user input
        message.trim(); // Remove newline characters

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

            String binaryCode = "";

            if (c >= 'A' && c <= 'Z') {
                binaryCode = encodingTable[c - 'A'];
            } else if (c >= 'a' && c <= 'z') {
                binaryCode = encodingTable[26 + (c - 'a')];
            } else {
                for (int i = 0; i < 11; i++) {
                    if (specialChars[i] == c) {
                        binaryCode = specialCharTable[52 + i - 52];
                        break;
                    }
                }
            }

            if (binaryCode == "") {
                Serial.println("Invalid character detected! Skipping.");
                continue;
            }

            for (char bit : binaryCode) {
                bool bitState = (bit == '1');
                
                digitalWrite(TRANSMIT_LED, bitState); // LED ON for '1', OFF for '0'
                delay(BIT_ON_TIME);
                
                digitalWrite(TRANSMIT_LED, LOW); // Ensure OFF state between bits
                delay(ELEMENT_DELAY);
            }
        }

        Serial.println("Transmission Completed.");
        Serial.println("Enter next message:");
    }
}
