/*
 * IOT_TEMP_SENSOR for Raspberry Pi Pico
 *
 * @version     1.0.0
 * @author     Justin Berkshire
 * @copyright   2023
 * @licence     MIT
 *
 */
#include "main.h"
using namespace std;

int main() {

    AdcController variableInputs;
    SpiInterface communication;

    while (true) {
        printf("Compiling Data");
        string message = variableInputs.constructJsonOfOutput();
        communication.transferBytes(&message);
    }

    return 0;
}
