
link_directories(/home/sun/openwrt-git/openwrt/staging_dir/target-mipsel_24kc_musl/root-ramips/usr/lib/)
include_directories(http/)
add_library(http http.cpp)
target_link_libraries(http curl)

