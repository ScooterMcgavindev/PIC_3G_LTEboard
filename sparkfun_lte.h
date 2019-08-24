/* 
 * File:   sparkfun_lte.h
 *
 * "Created in MPLAB Xpress"
 *
 *  Header file for the sparkfun LTE board
 *  Anytime line numbers referd to are in the git retpo
 *  See: https://github.com/sparkfun/SparkFun_LTE_Shield_Arduino_Library/blob/master/src/SparkFun_LTE_Shield_Arduino_Library.h
 *
 */

#ifndef SPARKFUN_LTE_H
#define	SPARKFUN_LTE_H

#include <string.h>
#include <stdbool.h>
#include <stdint.h> // some of the structs need this.  Don't remove
#include "testconfig.h"

#define LTE_SHIELD_POWER_PIN 5
#define LTE_SHIELD_RESET_PIN 6

// moble network operators from line 57
// pretty sure these are used to set things
#define MNO_INVALID -1
#define MNO_SW_DEFAULT 0
#define MNO_SIM_ICCD 1
#define MNO_ATT 2
#define MNO_VERIZON 3
#define MNO_TELSTRA 4
#define MNO_TMO 5
#define MNO_CT 6

// pin definitions
// right now I'm gonna just assume this is all on portA
#define POWERPIN 0
#define RESETPIN 1

// LTE error codes, see line 68 
typedef char LTE_Shield_error_t;
#define LTE_SHIELD_ERROR_INVALID -1
#define LTE_SHIELD_ERROR_SUCCESS 0
#define LTE_SHIELD_ERROR_OUT_OF_MEMORY 1
#define LTE_SHIELD_ERROR_TIMEOUT 2
#define LTE_SHIELD_ERROR_UNEXPECTED_PARAM 3
#define LTE_SHIELD_ERROR_UNEXPECTED_RESPONSE 4
#define LTE_SHIELD_ERROR_NO_RESPONSE 5
#define LTE_SHIELD_ERROR_DEREGISTERED 6

// LTE sheild registration status, see line 92
typedef char LTE_Shield_registration_status_t;
#define LTE_SHIELD_REGISTRATION_INVALID -1
#define LTE_SHIELD_REGISTRATION_NOT_REGISTERED 0
#define LTE_SHIELD_REGISTRATION_HOME 1
#define LTE_SHIELD_REGISTRATION_SEARCHING 2
#define LTE_SHIELD_REGISTRATION_DENIED 3
#define LTE_SHIELD_REGISTRATION_UNKNOWN 4
#define LTE_SHIELD_REGISTRATION_ROAMING 5
#define LTE_SHIELD_REGISTRATION_HOME_SMS_ONLY 6
#define LTE_SHIELD_REGISTRATION_ROAMING_SMS_ONLY 7
#define LTE_SHIELD_REGISTRATION_HOME_CSFB_NOT_PREFERRED 8
#define LTE_SHIELD_REGISTRATION_ROAMING_CSFB_NOT_PREFERRED 9

// LTE sheild codes 
//typedef char LTE_Shield_error_t;
#define LTE_SHIELD_STANDARD_RESPONSE_TIMEOUT 1000
#define LTE_SHIELD_SET_BAUD_TIMEOUT 500
#define LTE_SHIELD_POWER_PULSE_PERIOD 3200
#define LTE_RESET_PULSE_PERIOD 10000
#define LTE_SHIELD_IP_CONNECT_TIMEOUT 60000
#define LTE_SHIELD_POLL_DELAY 1
#define LTE_SHIELD_SOCKET_WRITE_TIMEOUT 10000

// macros for selecting the TCP/UDP network protocol
typedef char lte_shield_socket_protocol_t;
#define LTE_SHIELD_TCP 6
#define LTE_SHEILD_UDP 17

// LTE sheild message format
typedef char lte_shield_message_format_t;
#define LTE_SHIELD_MESSAGE_FORMAT_PDU 0
#define LTE_SHIELD_MESSAGE_FORMAT_TEXT 1

struct DateData {
    uint8_t day;
    uint8_t month;
    unsigned int year;
};

struct TimeData {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    unsigned int ms;
    uint8_t tzh;
    uint8_t tzm;
};

struct ClockData {
    struct DateData date;
    struct TimeData time;
};

struct PositionData {
    float utc;
    float lat;
    char latDir;
    float lon;
    char lonDir;
    float alt;
    char mode;
    char status;
};

struct SpeedData {
    float speed;
    float track;
    float magVar;
    char magVarDir;
};

struct operator_stats {
    uint8_t stat;
    char *shortOp;
    char *longOp;
    unsigned long numOp;
    uint8_t act;
};


typedef struct
{
    unsigned short baud; // baud rate
    unsigned char powerPin; //...
    unsigned char resetPin;
} LTE_sheild;

// headers for dev mode functions
#ifdef TESTMODE
// headers for the dummy functions
// prototypes for functions
void usart_setup(); // setup the registers to correct values 
void putch(char ch); // send a single char
void flush(); // flush out the input register
char getln(char *buffer,char length); // read a number of characters into buffer, length is the max number of chars to be read
char putln(char *str); // send a full string

// dummy variables for PIC IO registers 
char PORTA;
char PORTC;
char TRISA;
char TRISC;
// dummy of a delay function


#endif

// headers for LTE functions

// functions for starting the sheild and doing some basic boot stuff
LTE_Shield_error_t init(unsigned long baud); // init takes in a baud rate and dose some basic startup with the lte board
void powerOn(); // physically turns on the board, see section 2.3.1 on page 11
void hwReset(); // hardware reset of the board 2.3.3 on page 11

// sets the LTE sheild to reseive commands
// returns true if worked, false if it dosnt
bool begin(unsigned short baud_rate); 

// functions defined in line 160 of the gitrepo
// loop polling and polling setup
bool poll();
LTE_Shield_error_t at(); 
LTE_Shield_error_t sendCommandWithResponse(const char * command, const char * expectedResponse, char * responseDest, unsigned long commandTimeout, bool at);

// functions to start serial communication with the network
LTE_Shield_error_t init(unsigned long baud); // setup serial communication with the device

// LTE functions for connectiong to and qurreing information about the current network
char getOperators(struct operator_stats * opRet,unsigned char maxOps);

// getting and setting the APN of the network


#endif	/* SPARKFUN_LTE_H */
