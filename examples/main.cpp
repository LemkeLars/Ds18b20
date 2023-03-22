#include "mbed.h"
#include "Ds18b20.h"

// Sensor an Pin PC_0 anschließen
Ds18b20 ds18b20(PC_0);

int main() {
    float temp;
    while(1) {
        // Temperatur auslesen
        ds18b20.start();
        // 750ms warten, bis die Temperatur ausgelesen wurde
        wait_ms(750);
        // Temperatur auslesen
        temp = ds18b20.readTemperature();
        // Temperatur auf der Konsole ausgeben
        printf("Temperatur: %.2f Grad Celsius\n", temp);
        // Eine Sekunde warten
        wait(1);
    }
}