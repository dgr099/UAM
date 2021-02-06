#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KCYN  "\x1B[36m"
#define RESET "\033[0m"
#else
#define KRED
#define KGRN
#define KYEL
#define KCYN
#define RESET
#endif

#define PRINT_TEST_RESULT(x) do{\
    __test_counter++;\
    __pass = (x);\
    __test_passed = (__pass)? __test_passed + 1 : __test_passed;\
    printf(KYEL "%s" RESET " line "  "%d " KCYN "%s" RESET ": %s\n", \
	   __FILE__, __LINE__ , __FUNCTION__, \
	   ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET));	\
  } while (0)

#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter))
      
static int __test_counter = 0;
static int __test_passed  = 0;
static int __pass = 0;

#endif
