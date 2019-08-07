#
# project: fips-sx
#

if (NOT FIPS_IMPORT)
    cmake_minimum_required(VERSION 3.0)
    # include the fips main cmake file
    get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
    include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

    fips_setup(PROJECT fips-sx)
endif()

fips_add_subdirectory(sx)

if (NOT FIPS_IMPORT)
    fips_finish()
endif()
