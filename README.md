# CAN-UDS-Parser

## 📜 Project Overview
**CAN-UDS-Parser** is a C++ simulator for automotive diagnostic communication over CAN (Controller Area Network) using UDS (Unified Diagnostic Services, ISO 15765-2).  
It parses both **single-frame** and **multi-frame** (ISO-TP) messages, extracts service IDs and DIDs (Data Identifiers), and decodes payloads—e.g. reconstructs and displays a 17-character VIN in ASCII.

---

## 🛠️ Features
- **Single-Frame Parsing**  
  - Detect and decode standard UDS requests (e.g. ReadDataByIdentifier `0x22`)
  - Extract CAN ID, DLC, service byte, and DID
- **Multi-Frame (ISO-TP) Support**  
  - Identify First Frames (`0x1X`) and Consecutive Frames (`0x2X`)
  - Reassemble payloads longer than 7 bytes
- **Service & DID Lookup**  
  - Map common services (`0x22`, `0x2E`, etc.) to human-readable names  
  - Map DIDs (`0xF190`, `0xF187`, etc.) to data definitions
- **Response Simulation**  
  - Provide fake ECU responses (e.g. sample VINs, software versions)
  - Decode hex payloads to ASCII for display
- **Modular, Embedded-Style Design**  
  - Clear separation of concerns: parsing, decoding, response generation, utilities

---