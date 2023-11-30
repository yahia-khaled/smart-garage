/*
 * HC_SR04_interface.h
 *
 *  Created on: Feb 6, 2023
 *      Author: abdal
 */

#ifndef HAL_HC_SR04_HC_SR04_INTERFACE_H_
#define HAL_HC_SR04_HC_SR04_INTERFACE_H_

#include "HC_SR04_config.h"

void H_HC_SR04_Init();
void H_HC_SR04_SendTriggerPulse();
float H_HC_SR04_GetDistance();

#endif /* HAL_HC_SR04_HC_SR04_INTERFACE_H_ */
