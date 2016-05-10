/******************************************************************************/
/*! File Name: Receiver.cpp
 *  Description: This header file includes the declarations for function
 *               defined in Receiver.h
 *
 *  Creation Date: 05-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
#include "Receiver.h"
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


Receiver::Receiver(Data* buffer)
{
    this->buffer_ = buffer;
}

void Receiver::run() {
    SET_RECEIVER_STATUS_RUNNING();

    int max_elements = buffer_->get_element_count();
    int count  = 0;
    int curr_element = buffer_->get_start_element();


    while (FOREVER)
    {
        if (receive_pkt(curr_element) == curr_element)
        {
            curr_element++;
            count++;

            if (count == max_elements)
                break;
        }
    }

    cout_mu.lock();
    std::cout << "Exiting receiver thread. All elements received." << "\n";
    cout_mu.unlock();

    SET_RECEIVER_STATUS_FINISHED();
    return;
}

int Receiver::receive_pkt(int num) {

    int rcvd_num = buffer_->remove_element(num);

    if (rcvd_num == num)
    {
        cout_mu.lock();
        std::cout << "Received: " << rcvd_num << "\n";
        cout_mu.unlock();
    }
    else
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return rcvd_num;
}

int Receiver::get_status()
{
    return this->status;
}