# Install script for directory: C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmIOD.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmIOD.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmIOD.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmIOD.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xApplicationsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmIOD.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmIOD.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmIOD.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmIOD.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDebugDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmIOD.pdb")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmIOD.pdb")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gdcm-3.0" TYPE FILE FILES
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmDefinedTerms.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmDefs.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmEnumeratedValues.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmIOD.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmIODEntry.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmIODs.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmMacro.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmMacroEntry.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmMacros.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmModule.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmModuleEntry.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmModules.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmNestedModuleEntries.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmPatient.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmSeries.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmStudy.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmTable.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmTableEntry.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmTableReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmType.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmUsage.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmXMLDictReader.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/gdcmXMLPrivateDictReader.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xLibrariesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gdcm-3.0/XML" TYPE FILE FILES
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/Part3.xml"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Source/InformationObjectDefinition/Part4.xml"
    )
endif()

