#define LDR_PIN A0          // LDR connected to Analog Pin A0
#define THRESHOLD 500       // Light threshold (adjust as per your setup)
#define FIRST_SAMPLE_DELAY 60 // Delay before first sample (in ms)
#define START_TIME 150      // TIME FOR DETECTING START OF TRANSMISSION
#define SAMPLE_DELAY 90  // Delay between consecutive samples (in ms)

String binaryData = "";     // Store received binary string
bool receiving = false;     // Flag to check if receiving data
unsigned long startTime;    // Timer for checking start/end signals

// 6-bit encoding table for letters (A-Z, a-z)
const char letterTable[53] = {
    '\0','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'
};

// 6-bit encoding table for special characters
const char specialChars[11] = {' ', '#', '.', '?', '!', ':', '@', '_', '\'', '-', '\0'};

void setup() {
    Serial.begin(115200);
    Serial.println("Rx Ready");
}

void loop() {
    int ldrValue = analogRead(LDR_PIN);  // Read LDR sensor value

    if (!receiving) {
        if (ldrValue < THRESHOLD) {  
            startTime = millis();
            
            while (analogRead(LDR_PIN) < THRESHOLD) {  
                if (millis() - startTime >= START_TIME) {  // Detecting Start Transmission
                    Serial.println("Transmission Start Detected");
                    receiving = true;
                    binaryData = "";  
                    // Serial.println("Waiting for first bit...");
                    delay(FIRST_SAMPLE_DELAY);  
                    break;
                }
            }
        }
    } else {
        while (receiving) {
            ldrValue = analogRead(LDR_PIN);  
            int bitValue = (ldrValue > THRESHOLD) ? 0 : 1;  
            binaryData += String(bitValue);  

            //Check for correct bit

            // Serial.print(bitValue);  
            // Serial.print(" ");  
            delay(SAMPLE_DELAY);  

            // Process binary in real-time (every 6 bits)
            if (binaryData.length() >= 6) {
                String bitChunk = binaryData.substring(0, 6);  // Extract first 6 bits
                char receivedChar = binaryToChar(bitChunk);  // Convert to character
                // Serial.print(" -> ");  
                if(receivedChar!='#') Serial.print(receivedChar);  // Print decoded character 
                binaryData = binaryData.substring(6);  // Remove processed bits
                
                // Check for end of communication ('#' character)
                if (receivedChar == '#' || receivedChar == '\0') {
                    if (receivedChar == '#') Serial.println("\nEnd Signal Detected!");
                    if (receivedChar == '\0') Serial.println("\nError: Invalid character received.");
                    receiving = false;
                    Serial.println("Transmission Complete");
                    binaryData = "";  
                    break;
                }
            }
        }
    }
}

// Function to convert a 6-bit binary string to a character
char binaryToChar(String binary) {
    int index = 0;
    for (int i = 0; i < 6; i++) {
        if (binary[i] == '1') {
            index += (1 << (5 - i));  // Convert binary to decimal (6-bit index)
        }
    }
    
    if (index < 53) return letterTable[index]; // Letters A-Z, a-z
    if (index >= 53 && index < 64) return specialChars[index - 53]; // Special characters
    return '\0';  // Invalid index
}
