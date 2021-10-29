#ifndef INPUT_H
#define INPUT_H

//---------------------------------------
//!
//! Enum to log errors while opening file
//!
//---------------------------------------

enum FileStatus {
    OK = 0,
    DOESNT_EXIST = 1,
    EMPTY_FILE = 2,
    WRITING_ERROR = 3
};

//---------------------------------------
//!
//! Asks user to enter files' names to
//! read from and write to and checks 
//! either they are available or not
//!
//! @param[out] <input_file> name of
//!                          input file
//! @param[out] <output_file> name of
//!                          output file
//! @param[out] <buffer> pointer to the
//!                      allocated memory
//!                      to write input
//! @param[out] <symbols_amount> amount
//!           of symbols in file included
//!
//! @note: allocates memory
//!
//!--------------------------------------
    
enum FileStatus Input(char* input_file, char** buffer);

#endif // INPUT_H
