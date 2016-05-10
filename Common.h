/******************************************************************************/
/*! File Name: Common.h
 *  Description: This header file contains the all the common header files and
 *               macros required by the project
 *
 *  Creation Date: 05-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

#ifndef PRODUCER_CONSUMER_COMMON_H
#define PRODUCER_CONSUMER_COMMON_H
/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
/* Standard C++ includes */
#include <iostream>
#include <thread>
#include <deque>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <sstream>
#include <string.h>
#include <cstring>
#include <fstream>

// Project header files

/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************/

#define FAILURE                         1
#define SUCCESS                         0

#define FOREVER                         1

#define MIN_VALUE                       1
#define MAX_VALUE                       9

#define DELIMITER                       ","
#define NULL_CHAR                       '\0'

#define EXIST                           -1
#define NOT_EXIST                       -1

#define RUNNING                         1
#define FINISHED                        0

#define IP_FILE_NAME                    "input_string.txt"

/******************************************************************************/
/*                C.L.A.S.S  D.E.F.I.N.I.T.I.O.N                              */
/******************************************************************************/


/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.F.I.N.I.T.I.O.N                        */
/******************************************************************************/

#endif //PRODUCER_CONSUMER_COMMON_H
