#include <ctype.h>  /* NOLINT */
#include <stdio.h>  /* NOLINT */
#include <stdlib.h> /* NOLINT */
#include <string.h> /* NOLINT */

#if defined(_MSC_VER)
#pragma warning(disable : 4996) /* deprecation */
#endif

#include "gdcmTestDriver.h"


/* Forward declare test functions. */
int TestAnonymizer(int, char*[]);
int TestDataSetHelper(int, char*[]);
int TestEquipmentManufacturer(int, char*[]);
int TestFileChangeTransferSyntax1(int, char*[]);
int TestFileChangeTransferSyntax2(int, char*[]);
int TestFileChangeTransferSyntax3(int, char*[]);
int TestFileChangeTransferSyntax4(int, char*[]);
int TestFileStreamer1(int, char*[]);
int TestFileStreamer2(int, char*[]);
int TestFileStreamer3(int, char*[]);
int TestFileStreamer4(int, char*[]);
int TestFileStreamer5(int, char*[]);
int TestFileStreamer6(int, char*[]);
int TestFileAnonymizer1(int, char*[]);
int TestFileAnonymizer2(int, char*[]);
int TestFileAnonymizer3(int, char*[]);
int TestFileAnonymizer4(int, char*[]);
int TestIconImageFilter(int, char*[]);
int TestParseXPATH(int, char*[]);
int TestValidate(int, char*[]);
int TestAnonymizeEvent(int, char*[]);
int TestFileDerivation(int, char*[]);
int TestSegmentedPaletteColorLookupTable(int, char*[]);
int TestPNMCodec(int, char*[]);
int TestSpacing(int, char*[]);
int TestSerieHelper(int, char*[]);
int TestFileExplicitFilter(int, char*[]);
int TestImageFragmentSplitter(int, char*[]);
int TestTagPath(int, char*[]);
int TestOrientation(int, char*[]);
int TestIconImage(int, char*[]);
int TestImageHelper(int, char*[]);
int TestImageToImageFilter(int, char*[]);
int TestImageChangeTransferSyntax1(int, char*[]);
int TestImageChangeTransferSyntax2(int, char*[]);
int TestImageChangeTransferSyntax3(int, char*[]);
int TestImageChangeTransferSyntax4(int, char*[]);
int TestImageChangeTransferSyntax6(int, char*[]);
int TestImageChangeTransferSyntax7(int, char*[]);
int TestImageApplyLookupTable(int, char*[]);
int TestFileDecompressLookupTable(int, char*[]);
int TestImageChangePlanarConfiguration(int, char*[]);
int TestCoder(int, char*[]);
int TestDecoder(int, char*[]);
int TestRescaler1(int, char*[]);
int TestRescaler2(int, char*[]);
int TestDumper(int, char*[]);
int TestDictPrinter(int, char*[]);
int TestApplicationEntity(int, char*[]);
int TestStringFilter1(int, char*[]);
int TestStringFilter2(int, char*[]);
int TestStringFilter3(int, char*[]);
int TestStringFilter4(int, char*[]);
int TestUIDGenerator(int, char*[]);
int TestUUIDGenerator(int, char*[]);
int TestXMLPrinter(int, char*[]);
int TestPrinter1(int, char*[]);
int TestPrint(int, char*[]);
int TestSorter(int, char*[]);
int TestImageReader(int, char*[]);
int TestStreamImageReader(int, char*[]);
int TestImageRegionReader1(int, char*[]);
int TestImageRegionReader2(int, char*[]);
int TestImageRegionReader3(int, char*[]);
int TestImageReaderRandomEmpty(int, char*[]);
int TestDirectionCosines(int, char*[]);
int TestImageWriter(int, char*[]);
int TestCodec(int, char*[]);
int TestPDFCodec(int, char*[]);
int TestRLECodec(int, char*[]);
int TestAudioCodec(int, char*[]);
int TestImage(int, char*[]);
int TestPhotometricInterpretation(int, char*[]);
int TestLookupTable(int, char*[]);
int TestOverlay(int, char*[]);
int TestOverlay3(int, char*[]);
int TestCurve(int, char*[]);
int TestCurve2(int, char*[]);
int TestPixelFormat(int, char*[]);
int TestPersonName(int, char*[]);
int TestImageCodec(int, char*[]);
int TestImageConverter(int, char*[]);
int TestJPEGCodec(int, char*[]);
int TestRAWCodec(int, char*[]);
int TestDICOMDIR(int, char*[]);
int TestWaveform(int, char*[]);
int TestFiducials(int, char*[]);
int TestEncapsulatedDocument(int, char*[]);
int TestSpectroscopy(int, char*[]);
int TestSurfaceWriter(int, char*[]);
int TestSurfaceWriter2(int, char*[]);
int TestImageChangeTransferSyntax5(int, char*[]);


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
    "TestAnonymizer",
    TestAnonymizer
  },
  {
    "TestDataSetHelper",
    TestDataSetHelper
  },
  {
    "TestEquipmentManufacturer",
    TestEquipmentManufacturer
  },
  {
    "TestFileChangeTransferSyntax1",
    TestFileChangeTransferSyntax1
  },
  {
    "TestFileChangeTransferSyntax2",
    TestFileChangeTransferSyntax2
  },
  {
    "TestFileChangeTransferSyntax3",
    TestFileChangeTransferSyntax3
  },
  {
    "TestFileChangeTransferSyntax4",
    TestFileChangeTransferSyntax4
  },
  {
    "TestFileStreamer1",
    TestFileStreamer1
  },
  {
    "TestFileStreamer2",
    TestFileStreamer2
  },
  {
    "TestFileStreamer3",
    TestFileStreamer3
  },
  {
    "TestFileStreamer4",
    TestFileStreamer4
  },
  {
    "TestFileStreamer5",
    TestFileStreamer5
  },
  {
    "TestFileStreamer6",
    TestFileStreamer6
  },
  {
    "TestFileAnonymizer1",
    TestFileAnonymizer1
  },
  {
    "TestFileAnonymizer2",
    TestFileAnonymizer2
  },
  {
    "TestFileAnonymizer3",
    TestFileAnonymizer3
  },
  {
    "TestFileAnonymizer4",
    TestFileAnonymizer4
  },
  {
    "TestIconImageFilter",
    TestIconImageFilter
  },
  {
    "TestParseXPATH",
    TestParseXPATH
  },
  {
    "TestValidate",
    TestValidate
  },
  {
    "TestAnonymizeEvent",
    TestAnonymizeEvent
  },
  {
    "TestFileDerivation",
    TestFileDerivation
  },
  {
    "TestSegmentedPaletteColorLookupTable",
    TestSegmentedPaletteColorLookupTable
  },
  {
    "TestPNMCodec",
    TestPNMCodec
  },
  {
    "TestSpacing",
    TestSpacing
  },
  {
    "TestSerieHelper",
    TestSerieHelper
  },
  {
    "TestFileExplicitFilter",
    TestFileExplicitFilter
  },
  {
    "TestImageFragmentSplitter",
    TestImageFragmentSplitter
  },
  {
    "TestTagPath",
    TestTagPath
  },
  {
    "TestOrientation",
    TestOrientation
  },
  {
    "TestIconImage",
    TestIconImage
  },
  {
    "TestImageHelper",
    TestImageHelper
  },
  {
    "TestImageToImageFilter",
    TestImageToImageFilter
  },
  {
    "TestImageChangeTransferSyntax1",
    TestImageChangeTransferSyntax1
  },
  {
    "TestImageChangeTransferSyntax2",
    TestImageChangeTransferSyntax2
  },
  {
    "TestImageChangeTransferSyntax3",
    TestImageChangeTransferSyntax3
  },
  {
    "TestImageChangeTransferSyntax4",
    TestImageChangeTransferSyntax4
  },
  {
    "TestImageChangeTransferSyntax6",
    TestImageChangeTransferSyntax6
  },
  {
    "TestImageChangeTransferSyntax7",
    TestImageChangeTransferSyntax7
  },
  {
    "TestImageApplyLookupTable",
    TestImageApplyLookupTable
  },
  {
    "TestFileDecompressLookupTable",
    TestFileDecompressLookupTable
  },
  {
    "TestImageChangePlanarConfiguration",
    TestImageChangePlanarConfiguration
  },
  {
    "TestCoder",
    TestCoder
  },
  {
    "TestDecoder",
    TestDecoder
  },
  {
    "TestRescaler1",
    TestRescaler1
  },
  {
    "TestRescaler2",
    TestRescaler2
  },
  {
    "TestDumper",
    TestDumper
  },
  {
    "TestDictPrinter",
    TestDictPrinter
  },
  {
    "TestApplicationEntity",
    TestApplicationEntity
  },
  {
    "TestStringFilter1",
    TestStringFilter1
  },
  {
    "TestStringFilter2",
    TestStringFilter2
  },
  {
    "TestStringFilter3",
    TestStringFilter3
  },
  {
    "TestStringFilter4",
    TestStringFilter4
  },
  {
    "TestUIDGenerator",
    TestUIDGenerator
  },
  {
    "TestUUIDGenerator",
    TestUUIDGenerator
  },
  {
    "TestXMLPrinter",
    TestXMLPrinter
  },
  {
    "TestPrinter1",
    TestPrinter1
  },
  {
    "TestPrint",
    TestPrint
  },
  {
    "TestSorter",
    TestSorter
  },
  {
    "TestImageReader",
    TestImageReader
  },
  {
    "TestStreamImageReader",
    TestStreamImageReader
  },
  {
    "TestImageRegionReader1",
    TestImageRegionReader1
  },
  {
    "TestImageRegionReader2",
    TestImageRegionReader2
  },
  {
    "TestImageRegionReader3",
    TestImageRegionReader3
  },
  {
    "TestImageReaderRandomEmpty",
    TestImageReaderRandomEmpty
  },
  {
    "TestDirectionCosines",
    TestDirectionCosines
  },
  {
    "TestImageWriter",
    TestImageWriter
  },
  {
    "TestCodec",
    TestCodec
  },
  {
    "TestPDFCodec",
    TestPDFCodec
  },
  {
    "TestRLECodec",
    TestRLECodec
  },
  {
    "TestAudioCodec",
    TestAudioCodec
  },
  {
    "TestImage",
    TestImage
  },
  {
    "TestPhotometricInterpretation",
    TestPhotometricInterpretation
  },
  {
    "TestLookupTable",
    TestLookupTable
  },
  {
    "TestOverlay",
    TestOverlay
  },
  {
    "TestOverlay3",
    TestOverlay3
  },
  {
    "TestCurve",
    TestCurve
  },
  {
    "TestCurve2",
    TestCurve2
  },
  {
    "TestPixelFormat",
    TestPixelFormat
  },
  {
    "TestPersonName",
    TestPersonName
  },
  {
    "TestImageCodec",
    TestImageCodec
  },
  {
    "TestImageConverter",
    TestImageConverter
  },
  {
    "TestJPEGCodec",
    TestJPEGCodec
  },
  {
    "TestRAWCodec",
    TestRAWCodec
  },
  {
    "TestDICOMDIR",
    TestDICOMDIR
  },
  {
    "TestWaveform",
    TestWaveform
  },
  {
    "TestFiducials",
    TestFiducials
  },
  {
    "TestEncapsulatedDocument",
    TestEncapsulatedDocument
  },
  {
    "TestSpectroscopy",
    TestSpectroscopy
  },
  {
    "TestSurfaceWriter",
    TestSurfaceWriter
  },
  {
    "TestSurfaceWriter2",
    TestSurfaceWriter2
  },
  {
    "TestImageChangeTransferSyntax5",
    TestImageChangeTransferSyntax5
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
