// #define LDR_PIN A0          // LDR connected to Analog Pin A0
// #define THRESHOLD 500       // Light threshold (adjust as per your setup)
// #define FIRST_SAMPLE_DELAY 1500  // Delay before first sample (in ms)
// #define SAMPLE_DELAY 2000   // Delay between consecutive samples (in ms)

// String binaryData = "";     // Store received binary string
// bool receiving = false;     // Flag to check if receiving data
// unsigned long startTime;    // Timer for checking start/end signals

// void setup() {
//     Serial.begin(9600);
//     // Serial.println("RX");
// }

// void loop() {
    
//     int ldrValue = analogRead(LDR_PIN);  // Read LDR sensor value

//     if (!receiving) {
//     // If light is detected (LDR value LOW), start the timer
//     if (ldrValue < THRESHOLD) {  
//         startTime = millis();
        
//         while (analogRead(LDR_PIN) < THRESHOLD) {  
//             if (millis() - startTime >=10000 ) {  // Check for continuous HIGH signal for 2000ms
//                 Serial.println("Transmission Start Detected");
//                 receiving = true;
//                 binaryData = "";  // Clear previous data
//                 // delay(500);  // Short delay before sampling
//                 Serial.println("Waiting 1500ms for first bit...");
//                 delay(FIRST_SAMPLE_DELAY);  // Wait before the first sample
//                 break;
//             }
//         }
//     }
// } else {
//         // Read binary bits at defined intervals
//         while (receiving) {
//             ldrValue = analogRead(LDR_PIN);  // Read LDR value
//             int bitValue = (ldrValue > THRESHOLD) ? 0 : 1;  // Convert to binary
//             binaryData += String(bitValue);  // Store bit
//             Serial.print(bitValue);  // Print received bit
//             Serial.print(" ");  
//             delay(SAMPLE_DELAY);  // Wait 2000ms before next bit
            
//             // Check for 6000ms HIGH light signal to mark the end
//             // if (analogRead(LDR_PIN) < THRESHOLD) {
//             //     startTime = millis();
//             //     while (analogRead(LDR_PIN) < THRESHOLD) {  
//             //         if (millis() - startTime >= 6000) {  
//             //             Serial.println("\nEnd Signal Detected");
//             //             Serial.println("Received Binary Data: " + binaryData);
//             //             receiving = false;
//             //             delay(6000);  // Ensure end signal completes
//             //             break;
//             //         }
//             //     }
//             // }
//         }
//     }
// }



// #define LDR_PIN A0          // LDR connected to Analog Pin A0
// #define THRESHOLD 500      // Light threshold (adjust as per your setup)
// #define FIRST_SAMPLE_DELAY 40 // Delay before first sample (in ms)
// #define START_TIME 150     // TIME FOR DETECTING START OF TRANSMISSION
// #define SAMPLE_DELAY 70   // Delay between consecutive samples (in ms)
// #define END_PATTERN "00100011"  // '#' in binary

// String binaryData = "";     // Store received binary string
// bool receiving = false;     // Flag to check if receiving data
// unsigned long startTime;    // Timer for checking start/end signals

// void setup() {
//     Serial.begin(9600);
//     Serial.println("Rx");
// }

// void loop() {
//     int ldrValue = analogRead(LDR_PIN);  // Read LDR sensor value

//     if (!receiving) {
//         if (ldrValue < THRESHOLD) {  
//             startTime = millis();
            
//             while (analogRead(LDR_PIN) < THRESHOLD) {  
//                 if (millis() - startTime >= START_TIME) {  // Check for continuous HIGH signal for 10 sec
//                     Serial.println("Transmission Start Detected");
//                     receiving = true;
//                     binaryData = "";  
//                     Serial.println("Waiting 15ms for first bit...");
//                     delay(FIRST_SAMPLE_DELAY);  
//                     break;
//                 }
//             }
//         }
//     } else {
//         while (receiving) {
//             ldrValue = analogRead(LDR_PIN);  
//             int bitValue = (ldrValue > THRESHOLD) ? 0 : 1;  
//             binaryData += String(bitValue);  
//             Serial.print(bitValue);  
//             Serial.print(" ");  
//             delay(SAMPLE_DELAY);  

//             // Process binary in real-time (every 8 bits)
//             if (binaryData.length() >= 8) {
//                 String byteString = binaryData.substring(0, 8);  // Extract first 8 bits
//                 char receivedChar = binaryToChar(byteString);  // Convert to character
//                 Serial.print(" -> ");  
//                 Serial.println(receivedChar);  // Print decoded character
                
//                 binaryData = binaryData.substring(8);  // Remove processed bits
                
//                 // Check for end of communication ('#' character)
//                 if (receivedChar == '#' || receivedChar == '\0') {
//                       if (receivedChar == '#') Serial.println("\nEnd Signal Detected!");
//                       if (receivedChar == '\0') Serial.println("\nSome error occurred during transmission (NUL received).");
//                       receiving = false;
//                       Serial.println("Transmission Complete");
//                       binaryData = "";  
//                       break;
//                 }

//             }
//         }
//     }
// }

// // Function to convert binary string (8 bits) to ASCII character
// char binaryToChar(String binary) {
//     int value = 0;
//     for (int i = 0; i < 8; i++) {
//         if (binary[i] == '1') {
//             value += (1 << (7 - i));  // Convert binary to decimal
//         }
//     }
//     return (char)value;  // Return ASCII character
// }



#define LDR_PIN A0          // LDR connected to Analog Pin A0
#define THRESHOLD 500       // Light threshold (adjust as per your setup)
#define FIRST_SAMPLE_DELAY 60 // Delay before first sample (in ms)
#define START_TIME 150      // TIME FOR DETECTING START OF TRANSMISSION
#define SAMPLE_DELAY 90    // Delay between consecutive samples (in ms)

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
    Serial.begin(9600);
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
