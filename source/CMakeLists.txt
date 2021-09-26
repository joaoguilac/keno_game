cmake_minimum_required(VERSION 3.2)
project (KenoGame VERSION 1.0.0 LANGUAGES CXX )

#=== Main App ===

include_directories("include"
                    "src")

add_executable(keno
               src/main.cpp
               src/keno_bet.cpp
               src/game_manager.cpp
               include/keno_bet.h
               include/keno_common.h
               include/game_manager.h)

target_compile_features( keno PUBLIC cxx_std_17 )
