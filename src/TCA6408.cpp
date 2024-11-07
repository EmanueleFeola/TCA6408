#include "TCA6408.h"

void TCA_Begin(int8_t sda_pin, int8_t scl_pin, uint32_t wire_freq, uint16_t wire_timeout_ms)
{
    Wire.setTimeOut(wire_timeout_ms);
    Wire.begin(sda_pin, scl_pin, wire_freq);
}

uint8_t TCA_Read(uint8_t tca_addr, uint8_t reg)
{
    // return the requested byte
    Wire.beginTransmission(tca_addr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(tca_addr, 1);
    return Wire.read();
}

uint8_t TCA_Write(uint8_t tca_addr, uint8_t reg, uint8_t data)
{
    // return 0 if write success
    Wire.beginTransmission(tca_addr);
    Wire.write(reg);
    Wire.write(data);
    return Wire.endTransmission();
}

uint8_t TCA_Read_Input(uint8_t tca_addr)
{
    return (TCA_Read(tca_addr, TCA6408_INPUT));
}

uint8_t TCA_Read_Output(uint8_t tca_addr)
{
    return (TCA_Read(tca_addr, TCA6408_OUTPUT));
}

uint8_t TCA_Read_Inversion(uint8_t tca_addr)
{
    return (TCA_Read(tca_addr, TCA6408_POLARITY_INVERSION));
}

uint8_t TCA_Read_Direction(uint8_t tca_addr)
{
    return (TCA_Read(tca_addr, TCA6408_CONFIGURATION));
}

uint8_t TCA_Write_Output(uint8_t tca_addr, uint8_t data)
{
    return (TCA_Write(tca_addr, TCA6408_OUTPUT, data));
}

uint8_t TCA_Write_Inversion(uint8_t tca_addr, uint8_t data)
{
    return (TCA_Write(tca_addr, TCA6408_POLARITY_INVERSION, data));
}

uint8_t TCA_Write_Direction(uint8_t tca_addr, uint8_t data)
{
    return (TCA_Write(tca_addr, TCA6408_CONFIGURATION, data));
}

bool TCA_Set_Out_Pin(uint8_t tca_addr, uint8_t pin_index, bool state)
{
    /*
    non posso settare il valore di un singolo pin alla volta. devo settare lo stato di tutti i pin.
    ritorna 1 se la scrittura è successful
    pin_index from 0 to 7
    state either 0 or 1
    */

    uint8_t currentState = TCA_Read_Output(tca_addr); // current state of all pins

    // Modify the state of the specified pin
    if (state)
    {
        currentState |= (1 << pin_index); // Set pin to HIGH
    }
    else
    {
        currentState &= ~(1 << pin_index); // Set pin to LOW
    }

    bool write_success = TCA_Write_Output(tca_addr, currentState);
    return write_success;
}

bool TCA_Get_Input_Pin(uint8_t tca_addr, uint8_t pin_index)
{
    /*
    non posso leggere il valore di un singolo pin alla volta. devo leggere lo stato di tutti i pin.
    ritorna il valore del pin richiesto
    pin_index from 0 to 7
    */
    uint8_t currentState = TCA_Read_Input(tca_addr); // current state of all pins
    return currentState & (1 << pin_index);
    // return (currentState >> pin_index) & 0x01; // alternativa
}