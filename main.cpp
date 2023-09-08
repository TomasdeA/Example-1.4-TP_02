/**
 * @brief Al ejemplo de ARM https://github.com/armBookCodeExamples/example_1-3
 *  
 * @arg none
 * @param gasDetector El pin al que se conecta el sensor de gas (ahora un switch a 3v3)
 * @param overTempDetector El pin al que se conecta el sensor de temperatura (ahora un switch a 3v3)
 * @param alarmLed El LED el cual se usa como alarma.
 * @param alarmOffButton El pin al que se conecta el botón para apagar la alarma (ahora un switch a 3v3)
 * 
 * @note Asegúrese de que esté el button/switch conectado a 3v3 y a los pines D2 y D3.
 * @note Se utiliza un pull down por ende se debe conectar a 3v3. 
 * Si se pone Pull up, conectar a GND
 * 
 * @retval none.
 * Ventajas de esta modificación:
 *
 * 1-El código es más legible y organizado al utilizar BusIn y BusOut para agrupar las
 * entradas y salidas digitales.
 * 2-Facilita la expansión del código para agregar más entradas/salidas en el futuro
 * sin modificar significativamente la lógica existente.
 * 3-Las líneas de printf proporcionan una visión clara del estado de las entradas y 
 * salidas digitales en cada iteración, lo que facilita la depuración.
 *
 * Desventajas de esta modificación:
 *
 * El código puede parecer un poco más largo debido a las declaraciones adicionales
 * para configurar BusIn y BusOut, pero esta desventaja es mínima en comparación con
 * las ventajas en términos de legibilidad y escalabilidad.
 */
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include "mbed.h"
#include "arm_book_lib.h"

int main()
{  
    BusIn sensors(D2, D3); // Sensores de gas (D2) y temperatura (D3)
    BusIn buttons(D4, D5, D6, D7); // Botones A (D4), B (D5), C (D6), D (D7)
    BusOut alarmLed(LED1); // LED de alarma

    sensors.mode(PullDown);
    buttons.mode(PullDown);

    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {
        //Reminder: sensors[i] con i siendo la posición relativa de la lista y no el nombre del pin (Di)
        // Leer sensores y reflejar su estado
        bool gasDetectorState = sensors[0]; //D2
        bool overTempDetectorState = sensors[1];//D3
        bool aButtonState = buttons[0];//D4
        bool bButtonState = buttons[1];//D5
        bool cButtonState = buttons[2];//D6
        bool dButtonState = buttons[3];//D7
    
    
        printf("Gas Detector: %d, Over Temp Detector: %d, A Button: %d, B Button: %d, C Button: %d, D Button: %d, Alarm LED: %d\n",
               gasDetectorState, overTempDetectorState, aButtonState, bButtonState, cButtonState, dButtonState, alarmState);

        if (gasDetectorState || overTempDetectorState) {
            if (alarmState == OFF) {
                if (gasDetectorState) printf("Gas detected\n");
                if (overTempDetectorState) printf("Over Temperature detected\n");
                printf("Alarm Led ON\n");
            }
            alarmState = ON;
        }

        alarmLed = alarmState;

        if (aButtonState && bButtonState && !cButtonState && !dButtonState) {
            if (alarmState == ON) printf("Alarm Led OFF\n");
            alarmState = OFF;
        }
    }
}