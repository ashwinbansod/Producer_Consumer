/******************************************************************************/
/*! File Name: Receiver.h
 *  Description: This header file contains the class definition for Receiver
 *                class
 *
 *  Creation Date: 05-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

#ifndef PRODUCER_CONSUMER_RECEIVER_H
#define PRODUCER_CONSUMER_RECEIVER_H
/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
/* Standard C++ includes */

// Project header files
#include "Data.h"

/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************/

#define SET_RECEIVER_STATUS_RUNNING() (this->status = RUNNING)

#define SET_RECEIVER_STATUS_FINISHED() (this->status = FINISHED)

/******************************************************************************/
/*                C.L.A.S.S  D.E.F.I.N.I.T.I.O.N                              */
/******************************************************************************/



class Receiver {
private:
    Data *buffer_;
    int status;
public:
    // Constructor
    Receiver(Data* buffer);

    // Thread execution point
    void run();

    // Function to receive packet.
    int receive_pkt(int num);

    int get_status();
};


/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.F.I.N.I.T.I.O.N                        */
/******************************************************************************/

#endif //PRODUCER_CONSUMER_RECEIVER_H
