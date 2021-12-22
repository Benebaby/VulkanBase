# Install script for directory: C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/GDCM")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDebugDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmMSFF.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmMSFF.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmMSFF.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmMSFF.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xApplicationsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmMSFF.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmMSFF.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmMSFF.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmMSFF.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDebugDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmMSFF.pdb")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmMSFF.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gdcm-3.0" TYPE FILE FILES
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmAnonymizeEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmAnonymizer.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmApplicationEntity.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmAudioCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmBitmap.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmBitmapToBitmapFilter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmCoder.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmConstCharWrapper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmCurve.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDICOMDIR.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDICOMDIRGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDataSetHelper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDecoder.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDeltaEncodingCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDictPrinter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDirectionCosines.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDirectoryHelper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmDumper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmEmptyMaskGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmEncapsulatedDocument.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmEquipmentManufacturer.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmFiducials.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmFileAnonymizer.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmFileChangeTransferSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmFileDecompressLookupTable.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmFileDerivation.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmFileExplicitFilter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmFileStreamer.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmIPPSorter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmIconImage.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmIconImageFilter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmIconImageGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImage.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageApplyLookupTable.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageChangePhotometricInterpretation.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageChangePlanarConfiguration.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageChangeTransferSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageConverter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageFragmentSplitter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageHelper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageRegionReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageToImageFilter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmImageWriter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmJPEG12Codec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmJPEG16Codec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmJPEG2000Codec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmJPEG8Codec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmJPEGCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmJPEGLSCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmJSON.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmKAKADUCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmLookupTable.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmMeshPrimitive.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmOrientation.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmOverlay.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPDFCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPGXCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPNMCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPVRGCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPersonName.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPhotometricInterpretation.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPixelFormat.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPixmap.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPixmapReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPixmapToPixmapFilter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPixmapWriter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmPrinter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmRAWCodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmRLECodec.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmRescaler.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmScanner.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSegment.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSegmentHelper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSegmentReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSegmentWriter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSegmentedPaletteColorLookupTable.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSerieHelper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSimpleSubjectWatcher.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSorter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSpacing.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSpectroscopy.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSplitMosaicFilter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmStreamImageReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmStreamImageWriter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmStrictScanner.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmStringFilter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSurface.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSurfaceHelper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSurfaceReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmSurfaceWriter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmTagPath.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmUIDGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmUUIDGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmValidate.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmWaveform.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcmXMLPrinter.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcm_j2k.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/MediaStorageAndFileFormat/gdcm_jp2.h"
    )
endif()

