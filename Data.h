/******************************************************************************/
/*! File Name: Data.h
 *  Description: This header file contains the class definition for Data class
 *
 *  Creation Date: 05-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

#ifndef PRODUCER_CONSUMER_DATA_H
#define PRODUCER_CONSUMER_DATA_H
/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
/* Standard C++ includes */

// Project header files
#include "Common.h"

/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************

/******************************************************************************/
/*                C.L.A.S.S  D.E.F.I.N.I.T.I.O.N                              */
/******************************************************************************/




class Data
{
private:
    // Add them as member variables here
    std::mutex mutex_data_var;
    std::condition_variable cond_data_var;

    // Your normal variables here
    std::deque<int> buff;
    const unsigned int max_size = 10;

    // Start and end values
    int start;
    int orig_start;
    int end;

public:
    Data();

    int add_element(int num);

    int remove_element(int num);

    int check_n_get_element_pos(int num);

    int parse_input(char *input);

    int get_element_count();

    int get_start_element();

    void increment_start_val();

    int write_to_file(std::string input_str);

    std::string read_from_file();

    void print_range();

    void print_buffer();
};

/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.F.I.N.I.T.I.O.N                        */
/******************************************************************************/



#endif //PRODUCER_CONSUMER_DATA_H
