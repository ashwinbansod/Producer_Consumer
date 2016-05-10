/******************************************************************************/
/*! File Name: Sender.cpp
 *  Description: This header file includes the declarations for function
 *               defined in Sender.h
 *
 *  Creation Date: 05-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
#include "Sender.h"
#include "main.h"

/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************/


/******************************************************************************/
/*                C.L.A.S.S  D.E.F.I.N.I.T.I.O.N                              */
/******************************************************************************/

/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.C.L.A.R.A.T.I.O.N                      */
/******************************************************************************/


Sender::Sender(Data* buffer)
{
    this->buffer_ = buffer;
}

void Sender::run() {
    SET_SENDER_STATUS_RUNNING();

    int num;
    int count = 0;
    int max_elements = buffer_->get_element_count();

    while (FOREVER)
    {
        num = send_pkt();
        count++;

        cout_mu.lock();
        std::cout << "Sent: " << num << "\n";
        cout_mu.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        if (count == max_elements)
            break;
    }

    cout_mu.lock();
    std::cout << "Exiting sender thread. All elements sent." << "\n";
    cout_mu.unlock();

    SET_SENDER_STATUS_FINISHED();
    return;
}

int Sender::send_pkt() {
    int num_exist = EXIST;
    int num = 0;

    while (num_exist == EXIST) {
        num = std::rand() % (MAX_VALUE + 1);

        //std::cout << "waiting to send pkt [" << num << "]\n" ;
        num_exist = buffer_->add_element(num);;
    }

    return num;
}

int Sender::get_status()
{
    return this->status;
}