/******************************************************************************/
/*! File Name: main.cpp
 *  Description: This header file includes the main function for the project
 *
 *  Creation Date: 05-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

#define _MODULE_MAIN_

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
/* Standard C++ includes */

// Project header files
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


int main() {
    int iRetVal = SUCCESS;

    Data datapkt;

    // Read previous ranges from input file.
    std::string input_str = datapkt.read_from_file();

    std::cout << " Program takes input as the range of numbers (for ex 1,5) \n\n" ;

    // If there are no input ranges, then directly take user defined input ranges.
    if (input_str.length() == 0)
    {
        std::cout << "Enter the user defined range between (" << MIN_VALUE << "," << MAX_VALUE << "): ";
        std::getline(std::cin, input_str);
    }
    else
    {
        /*! */
        char ch;

        std::cout << "1. Press '1' to use previous input value which is [" << input_str << "]\n";
        std::cout << "0. Press '0' to enter new user defined values.\n";
        std::cout << "Enter your choice: ";
        std::cin >> ch;
        getchar();

        if (! isdigit(ch) || (ch != '0' && ch != '1'))
        {
            std::cout << "Improper command\n";
            std::cout << "Kindly enter correct value. \n";

            return FAILURE;
        }

        if (ch == '0')
        {
            std::cout << "Enter the user defined range between (" << MIN_VALUE << "," << MAX_VALUE << "): ";
            std::getline(std::cin, input_str);
        }
        /*! else use the same input_str value as  read from input file. */
    }

    char caInputStr[256];
    strcpy(caInputStr, input_str.c_str());

    iRetVal = datapkt.parse_input(caInputStr);
    if (iRetVal != SUCCESS)
    {
        std::cout << "\nERROR: Improper entry [" << input_str << "]\n";
        std::cout << "Correct format should be [start_num,end_num]\n";
        std::cout << "MIN VALUE: [" << MIN_VALUE << "]     MAX VALUE: [" << MAX_VALUE << "]\n";

        return FAILURE;
    }

    datapkt.write_to_file(input_str);
    datapkt.print_range();

    /*! Create Receiver and Sender objects and pass their run method as
     *  as callback function while creating a new thread.
     *  Join the newly created threads to main thread.
     */
    Receiver rcvr_obj(&datapkt);
    Sender sndr_obj(&datapkt);

    std::thread sender_thread(&Receiver::run, &rcvr_obj);
    std::thread receiver_thread(&Sender::run, &sndr_obj);

    sender_thread.join();
    receiver_thread.join();

    /*! Busy loop while the sender and receiver threads are running. */
    while (rcvr_obj.get_status() || sndr_obj.get_status())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return iRetVal;
}

//End of _MODULE_MAIN_