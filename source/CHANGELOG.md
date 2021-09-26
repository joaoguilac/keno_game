# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/) 
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]

# [0.2.1] - 2021-09-25
### Added
- A new welcome message
### Changed
- Architecture (functions and organization)
- Game states
- The old welcome message has become a summary message
- Compiling and running on the `README.md` file

# [0.2.0] - 2021-07-05
### Added
- We can use CMake now
### Changed
- `payout_table` type (const float, now)


# [0.1.2] - 2021-07-05
### Added
- Sorting of sport
- Removing of spots repetitions
### Removed
- Binary file from `bin` directory to do not make the repository large

# [0.1.1] - 2021-07-03
### Added
- Payout table
- STL algorithm header
### Changed
- Fix stringstream
- Try to remove repetitions
### Removed
- `core` directory.

# [0.1.0] - 2021-07-03
### Added
- Make the bet input code
- New files: `keno_common.cpp`, `game_manager.cpp`, and `game_manager.h`.
- `keno_common.cpp` is a file of implementations of the `main.cpp`'s functions.
- New `game_manager.*` files for our new class GameManager (responsible to manager the game).
- New `bin` directory for binary files.
- New `include` directory for header files.
- New `src` directory for implementation files.
### Changed
- Move files from `core` directory to `include` and `src` directories.
