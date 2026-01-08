# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
# Daisy Seed Platform Configuration

set (PLATFORM_SHARED_DIR ${CMAKE_CURRENT_LIST_DIR})

add_definitions(-DBH_PLATFORM_DAISY)

include_directories(${PLATFORM_SHARED_DIR})
include_directories(${PLATFORM_SHARED_DIR}/../include)

# Math library support for bare metal
include (${CMAKE_CURRENT_LIST_DIR}/../common/math/platform_api_math.cmake)

# Collect all platform source files
file (GLOB source_all ${PLATFORM_SHARED_DIR}/*.c)

set (PLATFORM_SHARED_SOURCE ${source_all} ${PLATFORM_COMMON_MATH_SOURCE})
