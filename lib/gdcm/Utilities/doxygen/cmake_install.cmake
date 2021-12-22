# Install script for directory: C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm-3.0.10/Utilities/doxygen

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcm2pnm.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcm2vtk.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmanon.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmconv.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmdiff.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmdump.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmgendir.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmimg.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcminfo.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmpap3.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmpdf.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmraw.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmscanner.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmscu.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmtar.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmviewer.1"
    "C:/Users/lukas/Documents/Bachelorarbeit/VulkanBase/lib/gdcm/Utilities/doxygen/gdcmxml.1"
    )
endif()

