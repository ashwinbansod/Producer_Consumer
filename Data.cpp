/******************************************************************************/
/*! File Name: Data.cpp
 *  Description: This header file includes the declarations for function
 *               defined in Data.h
 *
 *  Creation Date: 05-09-2016
 *  Author: Ashwin
 */
/******************************************************************************/

/******************************************************************************/
/*                   H.E.A.D.E.R  F.I.L.E.S                                   */
/******************************************************************************/
#include "Data.h"

/******************************************************************************/
/*                              M.A.C.R.O.S                                   */
/******************************************************************************/


/******************************************************************************/
/*                C.L.A.S.S  D.E.F.I.N.I.T.I.O.N                              */
/******************************************************************************/

/******************************************************************************/
/*                F.U.N.C.T.I.O.N  D.E.C.L.A.R.A.T.I.O.N                      */
/******************************************************************************/



Data::Data() {}

int Data::add_element(int num) {

    std::unique_lock<std::mutex> lck(mutex_data_var);
    cond_data_var.wait(lck, [this](){return buff.size() < max_size;});

    int pos = check_n_get_element_pos(num);
    if (pos == EXIST) {
        return pos;
    }

    buff.push_back(num);

    int qsize = buff.size();
    for (int cntr = qsize-2; cntr >= pos; cntr--)
    {
        buff[cntr + 1] = buff[cntr];
    }

    buff[pos] = num;

    //print_buffer();

    lck.unlock();
    cond_data_var.notify_all();

    return SUCCESS;
}


int Data::remove_element(int num) {

    std::unique_lock<std::mutex> lck(mutex_data_var);

    cond_data_var.wait(lck, [this](){return buff.size() > 0;});

    int back = buff.back();
    if (back == num) {
        buff.pop_back();
        increment_start_val();
    }
    else
        back = NOT_EXIST;

    lck.unlock();
    cond_data_var.notify_all();

    return back;
}

int Data::check_n_get_element_pos(int num) {

    int pos = EXIST;

    if (num < start || num > end)
    {
        return pos;
    }

    int qsize = buff.size();
    if (qsize == 0)
    {
        pos = 0;
    }
    else {
        for (int cntr = 0; cntr < qsize; cntr++) {
            if (num == buff[cntr]) {
                pos = EXIST;
                break;
            }
            else if (num > buff[cntr]) {
                pos = cntr;
                break;
            }
            else {
                pos = cntr + 1;
            }
        }
    }

    return pos;
}


int Data::parse_input(char *input)
{
    char buffer[256];
    char * pch;

    memset(buffer, NULL_CHAR, sizeof(buffer));

    // Get next value from input
    pch = strtok (input,DELIMITER);

    if(pch != NULL)
    {
        if (isdigit(*pch)) {
            start = atoi(pch);
            orig_start = start;

            // Validate range of numbers.
            if ((start < MIN_VALUE) || (start > MAX_VALUE))
            {
                return FAILURE;
            }
        }
    }
    else {
        // Return Failure if no start value is specified.
        return FAILURE;
    }

    // Get next value from input
    pch = strtok (NULL, DELIMITER);

    if(pch != NULL)
    {
        // NOTE: Add trim if necessary

        if (isdigit(*pch)) {
            end = atoi(pch);

            // Validate range of numbers.
            if ((end <= start) || (end > MAX_VALUE))
            {
                return FAILURE;
            }
        }
    }
    else {
        // Return Failure if no end value is specified.
        return FAILURE;
    }

    // Check if input is empty.
    // If input is not empty return failure.
    pch = strtok (NULL, DELIMITER);
    if (pch != NULL)
    {
        return FAILURE;
    }

    return SUCCESS;
}

int Data::get_element_count()
{
    return (end - start + 1);
}

int Data::get_start_element()
{
    return start;
}

void Data::increment_start_val()
{
    start++;
}

void Data::print_range()
{
    std::cout << "Start Value : " << start << "\n" ;
    std::cout << "End Value : " << end << "\n" ;
}

void Data::print_buffer() {

    for (int cntr = 0; cntr < buff.size(); cntr++)
    {
        std::cout << buff[cntr] << ", ";
    }

    return;
}

std::string Data::read_from_file() {
    std::ifstream input_file;
    input_file.open (IP_FILE_NAME);

    std::string input_str;
    getline(input_file, input_str);

    return input_str;
}

int Data::write_to_file(std::string input_str) {
    std::ofstream input_file;
    input_file.open (IP_FILE_NAME, std::ofstream::out | std::ofstream::trunc);

    input_file << input_str;

    input_file.close();

    return SUCCESS;
}