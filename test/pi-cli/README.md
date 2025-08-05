# pi-cli

`pi-cli` is a simple command-line interface application written in C++. It supports multithreaded command execution and provides a set of sample commands for demonstration purposes.

---

## Supported Commands

Here are the commands supported by `pi-cli`:

- **`exit`**: Exit the program. Ensures that the worker thread is stopped cleanly before exiting.
- **`help`**: Display a list of available commands and their descriptions.
- **`echo [parameters...]`**: Echoes the provided parameters back to the console.

---

## Building the Application

Follow these steps to build `pi-cli` on macOS or Linux:

### Prerequisites

Make sure you have the following installed:
- `CMake` (version 3.10 or higher)
- A C++ compiler with support for C++17 (e.g., `clang` or `g++`)

### Steps to Build

1. Open a terminal.

2. Navigate to the directory containing the `CMakeLists.txt` file:
   ```bash
   cd /path/to/project
   ```

3. Create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

4. Generate the build files using CMake:
   ```bash
   cmake ..
   ```

5. Build the project:
   ```bash
   make
   ```

6. The compiled executable will be located in the `bin` directory inside the `build` folder. You can run it as follows:
   ```bash
   ./bin/pi-cli
   ```

---

## Running the Application

Once built, run the `pi-cli` executable. You will see a prompt where you can enter supported commands.

### Example Usage

```bash
$ ./bin/pi-cli
Please enter a command (type 'help' for available commands): help
Available commands:
- exit: Exit the program.
- help: Display this help message.
- echo: Echoes the provided parameters.
```

To exit the program, type:
```bash
exit
```

---

## Notes

- For Linux builds, the `-pthread` flag is automatically applied to ensure multithreading compatibility.
- If you encounter any issues, ensure that your development environment meets the prerequisites.

```bash
# To install CMake on macOS using Homebrew:
brew install cmake
```

---

Enjoy using `pi-cli`!