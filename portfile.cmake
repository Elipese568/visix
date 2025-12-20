cmake_minimum_required(VERSION 4.2)

vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO MicrosoftDocs/vcpkg-docs
    REF "${VERSION}"
    SHA512 3f206cc2fe61d9c97c82b30852e1e4e6df299d93f6159edd1e56c644fa03ccc4670f7681e356d0e3db898a74e099a1ec531821df5430a7b14d61c743c5aa8c30
    HEAD_REF visix
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(PACKAGE_NAME "visix")

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")