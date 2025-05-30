# TideSculpt: A 2D Environmental Puzzle Game

## Overview
TideSculpt is a unique 2D environmental puzzle game built in C++ using the SFML library. Players sculpt tidal currents on a grid to guide drifting artifacts to ancient shrines, navigating around whirlpools and barriers. The game blends fluid dynamics with strategic puzzle-solving, offering a fresh experience distinct from traditional puzzle or exploration games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, environmental mechanics, and physics-based puzzles. By sponsoring TideSculpt via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Tidal Current Sculpting**: Place current tiles to guide artifact movement.
- **Dynamic Hazards**: Avoid whirlpools and barriers that disrupt artifact paths.
- **Minimalist Visuals Clean 2D graphics with flowing water effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/tidesculpt.git
   cd tidesculpt
   ```
3. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
4. Configure with CMake:
   ```bash
   cmake ..
   ```
5. Build the project:
   ```bash
   cmake --build .
   ```
6. Run the game:
   ```bash
   ./TideSculpt
   ```

## Gameplay
- **Objective**: Guide all artifacts to the shrine by sculpting tidal currents while avoiding hazards.
- **Controls**:
  - **Arrow Keys**: Move the cursor on the grid.
  - **Space**: Place a current tile (cycles through directions).
  - **R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Current tiles direct artifact movement. Place tiles strategically to navigate artifacts around whirlpools and barriers to reach the shrine.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (artifacts, currents, hazards, shrine).
- `src/Game.hpp`: Core game logic, current simulation, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support TideSculpt’s development through [GitHub Sponsors](https://github.com/sponsors/samdshaba)! Your contributions fund:
- New hazard types and level designs.
- Enhanced current mechanics and visual effects.
- Tutorials for C++ and fluid dynamics in games.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by fluid dynamics and environmental puzzles.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor TideSculpt to shape the flow of innovative puzzle gaming!**
