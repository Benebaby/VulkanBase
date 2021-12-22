#include <ctype.h>  /* NOLINT */
#include <stdio.h>  /* NOLINT */
#include <stdlib.h> /* NOLINT */
#include <string.h> /* NOLINT */

#if defined(_MSC_VER)
#pragma warning(disable : 4996) /* deprecation */
#endif

#include "gdcmTestDriver.h"


/* Forward declare test functions. */
int TestVersion(int, char*[]);
int TestCommand(int, char*[]);
int TestCryptographicMessageSyntax(int, char*[]);
int TestDummyValueGenerator(int, char*[]);
int TestASN1(int, char*[]);
int TestTesting(int, char*[]);
int TestSystem3(int, char*[]);
int TestSwapper(int, char*[]);
int TestByteSwap(int, char*[]);
int TestString1(int, char*[]);
int TestString2(int, char*[]);
int TestTerminal(int, char*[]);
int TestFilenameGenerator(int, char*[]);
int TestObject(int, char*[]);
int TestSmartPointer(int, char*[]);
int TestSwapCode(int, char*[]);
int TestSystem1(int, char*[]);
int TestSystem2(int, char*[]);
int TestTrace(int, char*[]);
int TestTypes(int, char*[]);
int TestUnpacker12Bits(int, char*[]);
int TestBase64(int, char*[]);
int TestLog2(int, char*[]);


#ifdef __cplusplus
#  define CM_CAST(TYPE, EXPR) static_cast<TYPE>(EXPR)
#  if __cplusplus >= 201103L
#    define CM_NULL nullptr
#  else
#    define CM_NULL NULL
#  endif
#else
#  define CM_CAST(TYPE, EXPR) (TYPE)(EXPR)
#  define CM_NULL NULL
#endif

/* Create map.  */

typedef int (*MainFuncPointer)(int, char* []); /* NOLINT */
typedef struct /* NOLINT */
{
  const char* name;
  MainFuncPointer func;
} functionMapEntry;

static functionMapEntry cmakeGeneratedFunctionMapEntries[] = {
    {
    "TestVersion",
    TestVersion
  },
  {
    "TestCommand",
    TestCommand
  },
  {
    "TestCryptographicMessageSyntax",
    TestCryptographicMessageSyntax
  },
  {
    "TestDummyValueGenerator",
    TestDummyValueGenerator
  },
  {
    "TestASN1",
    TestASN1
  },
  {
    "TestTesting",
    TestTesting
  },
  {
    "TestSystem3",
    TestSystem3
  },
  {
    "TestSwapper",
    TestSwapper
  },
  {
    "TestByteSwap",
    TestByteSwap
  },
  {
    "TestString1",
    TestString1
  },
  {
    "TestString2",
    TestString2
  },
  {
    "TestTerminal",
    TestTerminal
  },
  {
    "TestFilenameGenerator",
    TestFilenameGenerator
  },
  {
    "TestObject",
    TestObject
  },
  {
    "TestSmartPointer",
    TestSmartPointer
  },
  {
    "TestSwapCode",
    TestSwapCode
  },
  {
    "TestSystem1",
    TestSystem1
  },
  {
    "TestSystem2",
    TestSystem2
  },
  {
    "TestTrace",
    TestTrace
  },
  {
    "TestTypes",
    TestTypes
  },
  {
    "TestUnpacker12Bits",
    TestUnpacker12Bits
  },
  {
    "TestBase64",
    TestBase64
  },
  {
    "TestLog2",
    TestLog2
  },

  { CM_NULL, CM_NULL } /* NOLINT */
};

static const int NumTests = CM_CAST(int,
  sizeof(cmakeGeneratedFunctionMapEntries) / sizeof(functionMapEntry)) - 1;

/* Allocate and create a lowercased copy of string
   (note that it has to be free'd manually) */
static char* lowercase(const char* string)
{
  char *new_string;
  char *p;
  size_t stringSize;

  stringSize = CM_CAST(size_t, strlen(string) + 1);
  new_string = CM_CAST(char*, malloc(sizeof(char) * stringSize));

  if (new_string == CM_NULL) { /* NOLINT */
    return CM_NULL;            /* NOLINT */
  }
  strcpy(new_string, string);  /* NOLINT */
  for (p = new_string; *p != 0; ++p) {
    *p = CM_CAST(char, tolower(*p));
  }
  return new_string;
}

int main(int ac, char* av[])
{
  int i;
  int testNum = 0;
  int partial_match;
  char *arg;
  int testToRun = -1;

  

  /* If no test name was given */
  /* process command line with user function.  */
  if (ac < 2) {
    /* Ask for a test.  */
    printf("Available tests:\n");
    for (i = 0; i < NumTests; ++i) {
      printf("%3d. %s\n", i, cmakeGeneratedFunctionMapEntries[i].name);
    }
    printf("To run a test, enter the test number: ");
    fflush(stdout);
    if (scanf("%d", &testNum) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
    if (testNum >= NumTests) {
      printf("%3d is an invalid test number.\n", testNum);
      return -1;
    }
    testToRun = testNum;
    ac--;
    av++;
  }
  partial_match = 0;
  arg = CM_NULL; /* NOLINT */
  /* If partial match is requested.  */
  if (testToRun == -1 && ac > 1) {
    partial_match = (strcmp(av[1], "-R") == 0) ? 1 : 0;
  }
  if (partial_match != 0 && ac < 3) {
    printf("-R needs an additional parameter.\n");
    return -1;
  }
  if (testToRun == -1) {
    arg = lowercase(av[1 + partial_match]);
  }
  for (i = 0; i < NumTests && testToRun == -1; ++i) {
    char *test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);
    if (partial_match != 0 && strstr(test_name, arg) != CM_NULL) { /* NOLINT */
      testToRun = i;
      ac -= 2;
      av += 2;
    } else if (partial_match == 0 && strcmp(test_name, arg) == 0) {
      testToRun = i;
      ac--;
      av++;
    }
    free(test_name);
  }
  free(arg);
  if (testToRun != -1) {
    int result;

    if (testToRun < 0 || testToRun >= NumTests) {
      printf("testToRun was modified by TestDriver code to an invalid value: "
             "%3d.\n",
             testNum);
      return -1;
    }
    result = (*cmakeGeneratedFunctionMapEntries[testToRun].func)(ac, av);

    return result;
  }

  /* Nothing was run, display the test names.  */
  printf("Available tests:\n");
  for (i = 0; i < NumTests; ++i) {
    printf("%3d. %s\n", i, cmakeGeneratedFunctionMapEntries[i].name);
  }
  printf("Failed: %s is an invalid test name.\n", av[1]);

  return -1;
}
