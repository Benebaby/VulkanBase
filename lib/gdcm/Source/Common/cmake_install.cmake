# Install script for directory: C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmCommon.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmCommon.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmCommon.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmCommon.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xApplicationsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmCommon.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmCommon.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmCommon.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmCommon.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDebugDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmCommon.pdb")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmCommon.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gdcm-3.0" TYPE FILE FILES
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmASN1.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmBase64.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmBoxRegion.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmByteSwap.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmByteSwap.txx"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCAPICryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCAPICryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCommand.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDataEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDeflateStream.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDirectory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDummyValueGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmException.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmFileNameEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmFilename.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmFilenameGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmLegacyMacro.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmMD5.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmObject.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLCryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLCryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLP7CryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLP7CryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmProgressEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmRegion.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSHA1.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSmartPointer.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmStaticAssert.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmString.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSubject.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSwapCode.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSwapper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSwapper.txx"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSystem.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTerminal.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTestDriver.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTesting.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTrace.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTypes.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmUnpacker12Bits.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmVersion.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmWin32.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/zipstreamimpl.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gdcm-3.0" TYPE FILE FILES
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmASN1.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmBase64.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmBoxRegion.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmByteSwap.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmByteSwap.txx"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCAPICryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCAPICryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCommand.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmCryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDataEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDeflateStream.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDirectory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmDummyValueGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmException.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmFileNameEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmFilename.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmFilenameGenerator.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmLegacyMacro.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmMD5.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmObject.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLCryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLCryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLP7CryptoFactory.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmOpenSSLP7CryptographicMessageSyntax.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmProgressEvent.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmRegion.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSHA1.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSmartPointer.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmStaticAssert.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmString.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSubject.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSwapCode.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSwapper.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSwapper.txx"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmSystem.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTerminal.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTestDriver.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTesting.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTrace.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmTypes.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmUnpacker12Bits.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmVersion.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/gdcmWin32.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/Common/zipstreamimpl.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Source/Common/gdcmConfigure.h"
    )
endif()

