#include <ctype.h>  /* NOLINT */
#include <stdio.h>  /* NOLINT */
#include <stdlib.h> /* NOLINT */
#include <string.h> /* NOLINT */

#if defined(_MSC_VER)
#pragma warning(disable : 4996) /* deprecation */
#endif

#include "gdcmTestDriver.h"


/* Forward declare test functions. */
int TestAttribute(int, char*[]);
int TestCodeString(int, char*[]);
int TestAttribute1(int, char*[]);
int TestAttribute7(int, char*[]);
int TestLO(int, char*[]);
int TestCSAElement(int, char*[]);
int TestPreamble(int, char*[]);
int TestReader(int, char*[]);
int TestReaderUpToTag1(int, char*[]);
int TestReaderUpToTag2(int, char*[]);
int TestReaderSelectedTags(int, char*[]);
int TestReaderSelectedPrivateGroups(int, char*[]);
int TestReaderCanRead(int, char*[]);
int TestWriter(int, char*[]);
int TestWriter2(int, char*[]);
int TestCSAHeader(int, char*[]);
int TestByteSwapFilter(int, char*[]);
int TestBasicOffsetTable(int, char*[]);
int TestComposite(int, char*[]);
int TestDataElement(int, char*[]);
int TestDataSet(int, char*[]);
int TestDS(int, char*[]);
int TestVRLT(int, char*[]);
int TestVRUI(int, char*[]);
int TestElement1(int, char*[]);
int TestFile(int, char*[]);
int TestFileSet(int, char*[]);
int TestFragment(int, char*[]);
int TestItem(int, char*[]);
int TestSequenceOfFragments(int, char*[]);
int TestSequenceOfItems(int, char*[]);
int TestTag(int, char*[]);
int TestPrivateTag(int, char*[]);
int TestTransferSyntax(int, char*[]);
int TestMediaStorage(int, char*[]);
int TestVL(int, char*[]);
int TestVM(int, char*[]);
int TestVR(int, char*[]);
int TestElement2(int, char*[]);
int TestElement4(int, char*[]);
int TestElement5(int, char*[]);
int TestElement6(int, char*[]);


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
    "TestAttribute",
    TestAttribute
  },
  {
    "TestCodeString",
    TestCodeString
  },
  {
    "TestAttribute1",
    TestAttribute1
  },
  {
    "TestAttribute7",
    TestAttribute7
  },
  {
    "TestLO",
    TestLO
  },
  {
    "TestCSAElement",
    TestCSAElement
  },
  {
    "TestPreamble",
    TestPreamble
  },
  {
    "TestReader",
    TestReader
  },
  {
    "TestReaderUpToTag1",
    TestReaderUpToTag1
  },
  {
    "TestReaderUpToTag2",
    TestReaderUpToTag2
  },
  {
    "TestReaderSelectedTags",
    TestReaderSelectedTags
  },
  {
    "TestReaderSelectedPrivateGroups",
    TestReaderSelectedPrivateGroups
  },
  {
    "TestReaderCanRead",
    TestReaderCanRead
  },
  {
    "TestWriter",
    TestWriter
  },
  {
    "TestWriter2",
    TestWriter2
  },
  {
    "TestCSAHeader",
    TestCSAHeader
  },
  {
    "TestByteSwapFilter",
    TestByteSwapFilter
  },
  {
    "TestBasicOffsetTable",
    TestBasicOffsetTable
  },
  {
    "TestComposite",
    TestComposite
  },
  {
    "TestDataElement",
    TestDataElement
  },
  {
    "TestDataSet",
    TestDataSet
  },
  {
    "TestDS",
    TestDS
  },
  {
    "TestVRLT",
    TestVRLT
  },
  {
    "TestVRUI",
    TestVRUI
  },
  {
    "TestElement1",
    TestElement1
  },
  {
    "TestFile",
    TestFile
  },
  {
    "TestFileSet",
    TestFileSet
  },
  {
    "TestFragment",
    TestFragment
  },
  {
    "TestItem",
    TestItem
  },
  {
    "TestSequenceOfFragments",
    TestSequenceOfFragments
  },
  {
    "TestSequenceOfItems",
    TestSequenceOfItems
  },
  {
    "TestTag",
    TestTag
  },
  {
    "TestPrivateTag",
    TestPrivateTag
  },
  {
    "TestTransferSyntax",
    TestTransferSyntax
  },
  {
    "TestMediaStorage",
    TestMediaStorage
  },
  {
    "TestVL",
    TestVL
  },
  {
    "TestVM",
    TestVM
  },
  {
    "TestVR",
    TestVR
  },
  {
    "TestElement2",
    TestElement2
  },
  {
    "TestElement4",
    TestElement4
  },
  {
    "TestElement5",
    TestElement5
  },
  {
    "TestElement6",
    TestElement6
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
