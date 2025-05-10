#  Li-Fi Based Communication System

This project demonstrates a low-cost, Arduino-based **Li-Fi (Light Fidelity)** communication system that transmits data wirelessly using visible light. By blinking an LED to represent binary data and detecting it with an LDR (Light Dependent Resistor), this setup allows one-way data transfer without using radio waves. It explores basic to advanced encoding techniques like Huffman-style encoding, RLE, and LZW to optimize transmission efficiency.

##  Components
- 2× Arduino Uno/Nano
- 1× White LED
- 1× LDR (Light Dependent Resistor)
- 1× 10kΩ Resistor
- Breadboard, jumper wires

##  How It Works
- **Sender Arduino**: Converts a message into binary using encoding (Huffman-like / RLE / LZW) and transmits it via LED blinks.
- **Receiver Arduino**: Uses LDR to detect light pulses, decodes the binary stream, and prints the message to Serial Monitor.

##  Encoding Supported
- Custom 6-bit Huffman-like encoding
- Run-Length Encoding (RLE)
- Basic LZW Compression

##  Files
- `lifi_sender.ino` – Transmits encoded message via LED
- `lifi_receiver.ino` – Receives and decodes message via LDR

##  Features
- Custom encoding support
- Serial-based message input/output
- Fully hardware-based light communication

##  Future Improvements
- Add error detection
- Enable bidirectional communication
- Build user interface for easy use

##  Author
**Harsh Maliya**  
B.Tech EEE, IIT Patna
