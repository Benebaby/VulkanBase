# Install script for directory: C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Utilities/gdcmjpeg/16

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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmjpeg16.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmjpeg16.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmjpeg16.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmjpeg16.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xApplicationsx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Debug/gdcmjpeg16.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/Release/gdcmjpeg16.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/MinSizeRel/gdcmjpeg16.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/bin/RelWithDebInfo/gdcmjpeg16.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDebugDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gdcm-3.0/gdcmjpeg/16" TYPE FILE FILES
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/gdcmjpeg/16/jconfig.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/gdcmjpeg/16/jerror.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/gdcmjpeg/16/jinclude.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/gdcmjpeg/16/jmorecfg.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/gdcmjpeg/16/jpegcmake.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/gdcmjpeg/16/jpeglib.h"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/gdcmjpeg/16/mangle_jpeg16bits.h"
    )
endif()

