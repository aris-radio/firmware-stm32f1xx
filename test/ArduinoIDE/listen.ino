/**
 *  @attention
 *  Copyright (C) 2025 - ARIS Alliance
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ******************************************************************************
 * @file    listen.ino
 * @brief   Tester to listen infinitely for incoming data from ARISR module
 * @author  ARIS Alliance
 *
 ******************************************************************************
 */

#include <SPI.h>

// Define SPI pins for different boards
#if defined(ESP32)
    #define SPI_MOSI 23 // MOSI pin for ESP32
    #define SPI_MISO 19 // MISO pin for ESP32
    #define SPI_SCK 18  // SCK pin for ESP32
    #define SPI_CS 5    // CS (Chip Select) pin for ESP32
    #define INT_PIN 4   // Interrupt pin for ESP32

#elif defined(ESP8266)
    #define SPI_MOSI D7 // MOSI pin for ESP8266
    #define SPI_MISO D6 // MISO pin for ESP8266
    #define SPI_SCK D5  // SCK pin for ESP8266
    #define SPI_CS D8   // CS (Chip Select) pin for ESP8266
    #define INT_PIN D2  // Interrupt pin for ESP8266

#else               // Default for Arduino (Uno, Mega, etc.)
    #define SPI_MOSI 11 // MOSI pin for Arduino
    #define SPI_MISO 12 // MISO pin for Arduino
    #define SPI_SCK 13  // SCK pin for Arduino
    #define SPI_CS 10   // CS (Chip Select) pin for Arduino
    #define INT_PIN 2   // Interrupt pin for Arduino (must be an interrupt-capable pin)
#endif

volatile bool interruptReceived = false; // Flag to indicate interrupt received
uint8_t receivedData = 0;                // Variable to store received data

// Interrupt Service Routine (ISR)
void IRAM_ATTR handleInterrupt()
{
    interruptReceived = false; // Reset flag

    digitalWrite(SPI_CS, LOW); // Enable SPI (select slave)
    delayMicroseconds(5);      // Small delay for stability

    receivedData = SPI.transfer(0x00); // Read data from SPI slave

    digitalWrite(SPI_CS, HIGH); // Disable SPI (deselect slave)

    // Print received data
    Serial.print("Received via SPI: 0x");
    Serial.println(receivedData, HEX);
}

void setup()
{
    Serial.begin(115200); // Initialize serial communication
    SPI.begin();          // Start SPI communication

    pinMode(SPI_CS, OUTPUT);
    digitalWrite(SPI_CS, HIGH); // Disable SPI at startup

    pinMode(INT_PIN, INPUT_PULLUP); // Configure interrupt pin as input

    // Attach interrupt to INT_PIN (triggers on FALLING edge)
    attachInterrupt(digitalPinToInterrupt(INT_PIN), handleInterrupt, FALLING);
}

void loop()
{
    // Nothing
}
