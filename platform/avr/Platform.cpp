/**
 ******************************************************************************
 * @file    Platform.cpp
 * @authors Matthew McGowan
 * @date    22 February 2015
 ******************************************************************************
  Copyright (c) 2015 Brewpi/Matthew McGowan, Inc.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

#include "DeviceManager.h"
#include "Pins.h"

int8_t  DeviceManager::enumerateActuatorPins(uint8_t offset)
{
#if BREWPI_STATIC_CONFIG<=BREWPI_SHIELD_REV_A
    switch (offset) {
        case 0: return heatingPin;
        case 1: return coolingPin;
        default:
            return -1;
    }
#elif BREWPI_STATIC_CONFIG>=BREWPI_SHIELD_REV_C
    switch (offset) {
        case 0: return actuatorPin1;
        case 1: return actuatorPin2;
        case 2: return actuatorPin3;
        case 3: return actuatorPin4;
        default: return -1;
    }
#endif			
    return -1;
}

int8_t DeviceManager::enumerateSensorPins(uint8_t offset) 
{
    if (offset==0)
        return doorPin;
    return -1;
}
	
/* 
 * Enumerates the 1-wire pins.
 */
int8_t DeviceManager::enumOneWirePins(uint8_t offset)
{		
#if BREWPI_STATIC_CONFIG<=BREWPI_SHIELD_REV_A
    if (offset==0)
        return beerSensorPin;
    if (offset==1)
        return fridgeSensorPin;
#endif
#if BREWPI_STATIC_CONFIG>=BREWPI_SHIELD_REV_C
    if (offset==0)
        return oneWirePin;
#endif
    return -1;								
}