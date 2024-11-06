# Simple Database Server in C++

This project is a minimal, yet functional **SQL database server** written in C++ designed to handle basic SQL queries like `SELECT`, `INSERT`, `UPDATE`, and `DELETE`. The server accepts client requests, parses SQL queries, manipulates data, and stores it in files. The project aims to provide an educational, lightweight example of how a relational database system operates.

## Features

* **Basic SQL Command Support**: Handles common SQL commands such as `SELECT`, `INSERT`, `UPDATE`, and `DELETE`.
* **Client-Server Architecture**: The server listens for incoming connections from clients and processes SQL queries in real-time.
* **Data Storage**: Stores database tables and data on disk in a minimal format.
* **Query Parsing**: Simple SQL query parsing to break down and interpret commands.
* **Modular Design**: The project is organized into separate modules for networking, parsing, storage, and query execution.

## Project Structure

``` bash
/simple-db/
│
├── /src/                  # All source code files
│   ├── /core/             # Core database logic (e.g., query parsing, storage, indexing)
│   ├── /network/          # Network-related code (e.g., server-client communication)
│   ├── /parser/           # SQL query parser
│   ├── /storage/          # Data storage and file management
│   ├── /utils/            # Utility code (e.g., logging, error handling)
│   ├── /commands/         # Specific SQL command implementations (SELECT, INSERT, etc.)
│   ├── /tests/            # Unit tests for your components
│   └── main.cpp           # Entry point for your application (server initialization)
│
├── /docs/                 # Project documentation (e.g., architecture, design decisions)
├── /build/                # Build directory (generated when you build your project)
│
├── CMakeLists.txt         # CMake build configuration
├── Makefile               # If you're using Makefile for build (optional)
└── README.md              # Project description and setup guide
```

## Getting Started

### Prerequisites

Before you begin, ensure you have the following installed:

* **C++ Compiler**: A C++ compiler like GCC or Clang.
* **CMake** (optional but recommended): A build system to manage the compilation process.

To check if you have `g++` installed, run:

``` bash
g++ --version
```

To check if you have `CMake` installed, run:

``` bash
cmake --version
```

### Building the Project

1. Clone the repository:

    ``` bash
    git clone https://github.com/your-username/simple-db.git cd simple-db
    ```

2. **Option 1: Using CMake**

    Create a build directory and run CMake:

    ``` bash
    mkdir build cd build cmake .. make
    ```

3. **Option 2: Using Makefile** If you prefer using a Makefile, simply run:

    ``` bash
    make
    ```

4. The compiled executable will be in the `build/` directory.

### Running the Server

Once the server is built, you can run it using the following command:

``` bash
./simple-db
```

The server will start and listen for client connections on a predefined port (you can configure this in the code).

## How to Use

### SQL Queries

The database server supports the following basic SQL commands:

* **SELECT**: Retrieve data from the database.

    Example:

    ``` sql
    SELECT * FROM users;
    ```

* **INSERT**: Add new records to a table.

    Example:

    ``` sql
    INSERT INTO users (id, name) VALUES (1, 'Luca');
    ```

* **UPDATE**: Modify existing records.

    Example:

    ``` sql
    UPDATE users SET name = 'Jaz' WHERE id = 2;
    ```

* **DELETE**: Remove records from a table.

    Example:

    ``` sql
    DELETE FROM users WHERE id = 3;
    ```

### Connecting to the Server

To connect to the server, you can use a **client program** or a **telnet session** to manually send SQL queries. The server listens for connections and processes queries from any client that connects.

## Architecture

### Core Components

1. **Server**:

    * The server is responsible for accepting client connections and managing their requests.
    * It processes incoming queries and forwards them to the relevant components (like the parser, storage manager, etc.).
2. **SQL Parser**:

    * The parser takes the raw SQL query and breaks it down into structured components that can be understood and executed by the server.
    * Example: A `SELECT` query is parsed into the table name and field list.
3. **Storage Manager**:

    * The storage manager is responsible for reading and writing data to disk. It handles the physical storage of tables and rows.
    * Data is stored in simple text or binary files, with basic indexing for performance.
4. **Command Handlers**:

    * Each SQL command (e.g., `SELECT`, `INSERT`, `UPDATE`, `DELETE`) has a corresponding handler that knows how to execute it.
    * The command handlers are responsible for interacting with the storage manager to manipulate data.

## Testing

Unit tests are included in the `/tests` folder. You can run the tests to ensure that the components work as expected.

### Running Tests

1. Navigate to the `/tests` directory.
2. Compile the test files.
3. Run the test executable to verify that all components function correctly.

## Contributing

If you would like to contribute to this project, please fork the repository and submit a pull request with your proposed changes. Ensure that your changes are well-tested, and feel free to add new features or improve existing ones.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

* This project is built as part of an educational initiative to understand the internals of database systems.
