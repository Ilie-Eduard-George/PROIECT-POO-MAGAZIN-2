cmake_minimum_required(VERSION 3.16)
project(MagazinElectronicePOO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(magazin_lib
    src/Product.cpp
    src/Phone.cpp
    src/Tablet.cpp
    src/Laptop.cpp
    src/MarketSimulator.cpp
    src/PricingEngine.cpp
    src/ProductFactory.cpp
    src/Store.cpp
)

target_include_directories(magazin_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(magazin main.cpp)
target_link_libraries(magazin PRIVATE magazin_lib)

if (MSVC)
  target_compile_options(magazin_lib PRIVATE /W4)
  target_compile_options(magazin PRIVATE /W4)
else()
  target_compile_options(magazin_lib PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(magazin PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Install rules for GitHub Actions packaging
install(TARGETS magazin RUNTIME DESTINATION bin)
install(FILES launcher.command DESTINATION bin)
