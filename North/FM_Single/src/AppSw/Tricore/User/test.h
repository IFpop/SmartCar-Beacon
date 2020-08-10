/*
 * test.h
 *
 *  Created on: 2020Äê7ÔÂ17ÈÕ
 *      Author: pengs
 */

#ifndef SRC_APPSW_TRICORE_USER_TEST_H_
#define SRC_APPSW_TRICORE_USER_TEST_H_

#define Change_ob  0.5
#define Change_cut 5
#define Change_kp  0.2
#define Change_speed 0.1

#define Button1 P02_0
#define Button2 P02_2
#define Button3 P02_6
#define Button4 P00_0


void test_bluetooth(void);
void test_motor(void);
void test_DQ(void);
void Test_terminal(void);
#endif /* SRC_APPSW_TRICORE_USER_TEST_H_ */
