/*
 * Interrupt_handle.h
 *
 *  Created on: 2020年7月3日
 *      Author: IFpop
 */

#ifndef SRC_APPSW_TRICORE_USER_AFTER_INTERRUPT_H_
#define SRC_APPSW_TRICORE_USER_AFTER_INTERRUPT_H_

// 相关参数

#define Const 0
#define Obstacle_Cam  600
#define Cam_k 1.0

void After_bluetoothIRQ(uint8_t, uint8_t*);
void After_Receive_Cam(uint8_t*);

#endif /* SRC_APPSW_TRICORE_USER_AFTER_INTERRUPT_H_ */
