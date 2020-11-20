/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string>
#include <iostream>
#ifndef __BLE_BUTTON_SERVICE_H__
#define __BLE_BUTTON_SERVICE_H__
using namespace std;
class ButtonService {
public:
    const static uint16_t BUTTON_SERVICE_UUID              = 0xA000;
    const static uint16_t BUTTON_STATE_CHARACTERISTIC_UUID = 0xA001;
    const static uint16_t BUTTON_STATE_CHARACTERISTIC_UUID2 = 0xA002;

    ButtonService(BLE &_ble, bool buttonPressedInitial,string initialid="123456789") :
        ble(_ble), buttonState(BUTTON_STATE_CHARACTERISTIC_UUID, &buttonPressedInitial, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY),
        buttonStrState(BUTTON_STATE_CHARACTERISTIC_UUID2, &initialid, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        GattCharacteristic *charTable[] = {&buttonState,&buttonStrState};
        GattService         buttonService(ButtonService::BUTTON_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
        ble.gattServer().addService(buttonService);
    }
    int number = 0;
    void updateButtonState1(bool newState) {
        string id = "b07901031";
        // ble.gattServer().write(buttonState.getValueHandle(), (uint8_t *)&newState, sizeof(bool));
        ble.gattServer().write(buttonStrState.getValueHandle(), (uint8_t *)&id, sizeof(id));
    }
    void updateButtonState2(bool newState) {
        // ble.gattServer().write(buttonState.getValueHandle(), (uint8_t *)&newState, sizeof(bool));
    }
    
private:
    BLE                              &ble;
    ReadWriteGattCharacteristic<bool>  buttonState;
    ReadWriteGattCharacteristic<string> buttonStrState;
};

#endif /* #ifndef __BLE_BUTTON_SERVICE_H__ */
