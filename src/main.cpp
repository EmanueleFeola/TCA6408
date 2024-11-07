/**
 * test read/write multiple TCA devices
 */

#include <Arduino.h>
#include "TCA6408.h"

#define I2C_SDA 26
#define I2C_SCL 27

#define TCA_ADDR_1 32
#define TCA_ADDR_2 33

// define input (1) output (0) of the 8 available pins
#define TCA_IO_ARR_TCA1 0b11111111 // all pins are input
#define TCA_IO_ARR_TCA2 0b11111100 // only last 2 pins are output

void setup()
{
  Serial.begin(115200);

  TCA_Begin(I2C_SDA, I2C_SCL, 100000, 100);
  TCA_Write_Direction(TCA_ADDR_1, TCA_IO_ARR_TCA1); // set input/output pins
  TCA_Write_Direction(TCA_ADDR_2, TCA_IO_ARR_TCA2); // set input/output pins

  bool pin_state = false;
  while (1)
  {
    // test tca2 by toggling pins
    pin_state = !pin_state;
    TCA_Set_Out_Pin(TCA_ADDR_2, 6, pin_state); // write/set 7th pin
    TCA_Set_Out_Pin(TCA_ADDR_2, 7, pin_state); // write/set 8th pin

    // test tca1 and tca2 by reading pins
    bool pin0_read_val_tca_1 = TCA_Get_Input_Pin(TCA_ADDR_1, 0); // read 1st pin
    Serial.printf("pin0_read_val_tca_1: %d\n", pin0_read_val_tca_1);

    bool pin0_read_val_tca_2 = TCA_Get_Input_Pin(TCA_ADDR_2, 0); // read 1st pin
    Serial.printf("pin0_read_val_tca_2: %d\n", pin0_read_val_tca_2);

    vTaskDelay(100);
  }
}

void loop()
{
  vTaskDelete(NULL);
}