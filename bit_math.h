#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(x,n) x=x|(1<<n)
#define CLR_BIT(x,n) x=x&(~(1<<n))
#define TOGGEL_BIT(x,n) x=x^(1<<n)
#define GET_BIT(x,n) ((x>>n)&1)

#endif
