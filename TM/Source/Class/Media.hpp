#ifndef MEDIA_HPP
#define MEDIA_HPP
/************************************************** Description *******************************************************/
/*
    File : Media.hpp
    Programmer : Mohammad Lotfi
    Used : Use header
    Design Pattern : Virtual
    Types of memory : Nothing
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2023/8/5
*/
/************************************************** Warnings **********************************************************/
/*
    Nothing
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include "defines.h"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/* Media is interface with virtual functions to use other media for example (UART,LAN,RS485,USB,...) and all things that follows this structure */
class Media {    

    public: 
        /* This function open media */
        virtual bool Open() = 0;
        /* This function set setting media */
        virtual bool Update(uint32_t Speed) = 0;
        /* This function for send data*/
        virtual bool Send(uint8_t *Message, uint32_t Length) = 0;
        /* This function for receive data*/
        virtual bool Receive(uint8_t *Message, uint32_t *Length) = 0;
        /* This function clear ring buffer media */
        virtual bool Clear() = 0;
        /* This function reset means close and then open for reinit media */
        virtual bool Reset() = 0;
        /* This function close media */
        virtual bool Close() = 0;
};
/************************************************** Functions *********************************************************/
/*
    Nothing
*/
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
#endif
