# Password Manager

This is a password manager written in C. It uses SQLite3 for database management and OpenSSL for cryptographic operations.

## Project Structure

The project is organized as follows:

- [``include/``](https://github.com/vaibhavsijaria/PasswordManager/tree/main/include): Contains all the header files.
- [``src/``](https://github.com/vaibhavsijaria/PasswordManager/tree/main/src): Contains the source files.

- [``.vscode/``](https://github.com/vaibhavsijaria/PasswordManager/tree/main/.vscode): Contains configuration files for Visual Studio Code.

## Building the Project

This project uses CMake for building. Here are the steps to build the project:

1. Navigate to the project directory.
2. Create a build directory and navigate into it:

```sh
mkdir build
cd build
```

3. Run CMake to generate the build files:

```sh
cmake ..
```

4. Build the project:

```sh
make
```

The executable `passwordManager` will be created in the ``build``directory.

## Dependencies

This project depends on SQLite3 and OpenSSL. Make sure these are installed on your system before building the project.

## Development

The project is set up for development in Visual Studio Code. The [``.vscode/c_cpp_properties.json``](https://github.com/vaibhavsijaria/PasswordManager/blob/main/.vscode/c_cpp_properties.json) file is configured for a Linux environment with the C17 standard. Adjust this file as needed for your development environment.

## Contributing

Contributions are welcome. Please make sure to test your changes thoroughly before submitting a pull request.
