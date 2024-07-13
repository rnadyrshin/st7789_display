# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/ruslan/esp/v5.2.1/esp-idf/components/bootloader/subproject"
  "/Users/ruslan/next.module/st7789_display/build/bootloader"
  "/Users/ruslan/next.module/st7789_display/build/bootloader-prefix"
  "/Users/ruslan/next.module/st7789_display/build/bootloader-prefix/tmp"
  "/Users/ruslan/next.module/st7789_display/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/ruslan/next.module/st7789_display/build/bootloader-prefix/src"
  "/Users/ruslan/next.module/st7789_display/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/ruslan/next.module/st7789_display/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/ruslan/next.module/st7789_display/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
