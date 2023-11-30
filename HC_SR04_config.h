/*
 * HC_SR04_config.h
 *
 *  Created on: Feb 6, 2023
 *      Author: abdal
 */

#ifndef HAL_HC_SR04_HC_SR04_CONFIG_H_
#define HAL_HC_SR04_HC_SR04_CONFIG_H_

//Define Pins for Trigger and Echo
#define TRIGGER_PIN1 PD0_PIN     //Trigger pin of HC-SR04 connected to PD0 of Atmega 32
#define ECHO_PIN1    PD1_PIN     //Echo pin of HC-SR04 connected to    PD1 of Atmega 32

#define TRIGGER_PIN2 PA3_PIN     //Trigger pin of HC-SR04 connected to PD0 of Atmega 32
#define ECHO_PIN2    PA4_PIN     //Echo pin of HC-SR04 connected to    PD1 of Atmega 32

#endif /* HAL_HC_SR04_HC_SR04_CONFIG_H_ */
