#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

/**
 * @brief Calculator function
 *
 * @param op operator '+' for sum, '/' for div
 * @param a first operand
 * @param b second operand
 * @param[out] result Reference to the result
 * @retval 0 if success
 * @retval negative if failed */
int calc(char op, int a, int b, int *result);

#endif /* !_CALCULATOR_H_ */
