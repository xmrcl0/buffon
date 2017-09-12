/** @file     utils.h
 *  @brief    Function prototypes for utils.
 *  @author   Marcelo Pinto (xmrcl0@gmail.com)
 *  @date     09/12/2017
 */

#include <regex.h>
#include <stdio.h>

/** @brief Verify if a string is a valid integer.
 *
 *  @param[in] n  Number to be validated
 *  @return Validation status 
 *
 *  @retval  0 Success
 *  @retval  1 Failure
 *  @retval -1 Internal error
 */
int is_integer(char *n);


/** @brief Verify if a string is a valid number.
 *
 *  @param[in] number Number to be validated
 *  @return Validation status 
 *
 *  @retval  0 Success
 *  @retval  1 Failure
 *  @retval -1 Internal error
 */
int is_positive_number(char *n);
