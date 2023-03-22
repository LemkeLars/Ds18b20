#include "mbed.h"
#include "Ds18b20.h"

Ds18b20::Ds18b20(PinName pinname) : pin(pinname) {
}

// Funktion zum Senden eines Reset-Signals an den Sensor und Prüfen der Antwort
int Ds18b20::reset() {
    int presence;
    
    // Bus auf Low ziehen für mindestens 480 Mikrosekunden
    pin.output();
    pin = 0;
    wait_us(480);
    
    // Bus freigeben und warten bis der Sensor antwortet (60 Mikrosekunden)
    pin.input();
    wait_us(60);
    
    // Bus lesen und Antwort speichern
    presence = !pin;
    
     // Warten bis das Reset-Signal beendet ist (420 Mikrosekunden)
     wait_us(420);
     
     // Antwort zurückgeben (1 wenn Sensor vorhanden, 0 sonst)
     return presence;
}

// Funktion zum Senden eines Bits an den Sensor
void Ds18b20::writeBit(int bit) {
    // Bus auf Low ziehen für mindestens 1 Mikrosekunde
    pin.output();
    pin = 0;
    wait_us(1);
    
    // Bus auf High setzen wenn Bit 1 ist, sonst auf Low lassen
    if (bit) {
        pin.input();
    }
    
    // Warten bis das Bit gesendet ist (60 Mikrosekunden)
    wait_us(60);
    
    // Bus wieder freigeben
    pin.input();
}

// Funktion zum Empfangen eines Bits vom Sensor
int Ds18b20::readBit() {
    int bit;
    
    // Bus auf Low ziehen für mindestens 1 Mikrosekunde
    pin.output();
    pin = 0;
    wait_us(1);
    
    // Bus freigeben und warten bis der Sensor antwortet (15 Mikrosekunden)
    pin.input();
    wait_us(15);
    
    // Bus lesen und Bit speichern
    bit = pin;
    
     // Warten bis das Bit gelesen ist (45 Mikrosekunden)
     wait_us(45);
     
     // Bit zurückgeben
     return bit;
}

// Funktion zum Senden eines Bytes an den Sensor
void Ds18b20::writeByte(int byte) {
   int i;
   
   // Jedes Bit einzeln senden, beginnend mit dem LSB
   for (i = 0; i < 8; i++) {
       writeBit(byte & 0x01);
       byte >>= 1;
   }
}

// Funktion zum Empfangen eines Bytes vom Sensor
int Ds18b20::readByte() {
   int i;
   int byte = 0;
   
   // Jedes Bit einzeln empfangen, beginnend mit dem LSB
   for (i = 0; i < 8; i++) {
       byte >>= 1;
       byte |= (readBit() << 7);
   }
   
   // Byte zurückgeben 
   return byte;
}

// Funktion zum Starten einer Temperaturmessung beim Sensor 
void Ds18b20::start() {
     // Reset-Signal senden und Antwort prüfen 
     if (!reset()) {
         printf("Kein Sensor gefunden!\n");
         return;
     }
     
     // SKIP_ROM-Befehl senden um alle Sensoren anzusprechen 
     writeByte(SKIP_ROM);
     
     // CONVERT_T-Befehl senden um eine Messung zu starten 
     writeByte(CONVERT_T);  
}

// Funktion zum Auslesen der Temperatur vom Sensor 
float Ds18b20::readTemperature() {
      int tempLSB, tempMSB;
      float temp;
      
      // Reset-Signal senden und Antwort prüfen 
      if (!reset()) {
          printf("Kein Sensor gefunden!\n");
          return -999.9f;  
      }
      
      // SKIP_ROM-Befehl senden um alle Sensoren anzusprechen 
      writeByte(SKIP_ROM);
      
      // READ_SCRATCHPAD-Befehl senden um die Daten auszulesen 
      writeByte(READ_SCRATCHPAD);  
      
      // Die ersten zwei Bytes enthalten die Temperatur als vorzeichenbehaftete Ganzzahl 
      tempLSB = readByte();  
      tempMSB = readByte();  
      
      // Die restlichen Bytes ignorieren 
      reset();  
      
      // Die beiden Bytes zu einer Ganzzahl zusammenfügen 
      temp = ((tempMSB << 8) | tempLSB);  
      
       /* Die Ganzzahl durch sechzehn teilen um die Temperatur in Grad Celsius zu erhalten. Der Faktor kommt daher,
         dass der Sensor die Temperatur mit einer Auflösung von einem Sechzehntel Grad misst */
         
       temp /=16.0f;  
       
       /* Wenn Sie eine andere Auflösung eingestellt haben, müssen Sie den Faktor entsprechend anpassen. Zum Beispiel,
         bei einer Auflösung von einem Viertel Grad ist der Faktor vier */
         
       //temp /= 4.0f;  
       
       // Temperatur zurückgeben
       return temp;   
}