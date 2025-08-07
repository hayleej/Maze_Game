/*
 * File Name: terminal.c
 * Author: Haylee Jackson
 * Purpose: functions related to disabling/enabling Echo and Canonical feature on Linux terminal
 * Last Modified: 13/09/2021
 * Comments: disableBuffer() and enableBuffer() were functions given as part of UCP Assignment 1
*/

#include<stdio.h>
#include<termios.h>
#include"terminal.h"

/**
 * @brief  disables Echo and Canonical feature on Linux terminal
 * @note   From UCP Assignment 1 (was given as part of assignment 1)
 * @retval None
 */
void disableBuffer(void)
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}






/**
 * @brief  enables Echo and Canonical feature on Linux terminal
 * @note   From UCP Assignment 1 (was given as part of assignment 1)
 * @retval None
 */
void enableBuffer(void)
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}
