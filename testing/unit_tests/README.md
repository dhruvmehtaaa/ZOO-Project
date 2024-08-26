# Installation Guide

## Development Environment

- **Distributor ID:** Ubuntu
- **Description:** Ubuntu 24.04 LTS
- **Release:** 24.04
- **Codename:** noble


## 1. Install CUnit

CUnit is a unit testing framework for C. To install CUnit, you can use the package manager for your system.

### On Ubuntu/Debian-based Systems:

```bash
sudo apt update
sudo apt install -y libcunit1-dev
```

## 2. Install Additional System Dependencies

You will also need other libraries required by the unit tests. Use the following commands to install them:

### On Ubuntu/Debian-based Systems:

```bash
sudo apt update
sudo apt install -y \
    libjson-c-dev \
    libcurl4-openssl-dev \
    libssh2-1-dev \
    libgdal-dev \
    libyaml-dev \
    python3.12-dev \
    libxml2-dev \
    libperl-dev \
    libr-dev
```

## After Installing run the below commands to execute the tests

```
chmod +x run_tests.py
python3 run_tests.py
```

## The various components tested as part of GSoC are:

* caching.c: This section includes unit tests developed using the CUnit framework to validate the caching mechanism's functionality. The tests cover key operations such as generating filenames from requests, caching these filenames, checking for their presence in the cache, and managing input configurations. These tests ensure the reliability and correctness of the caching system within the broader application.

* map_functions.c: Provides a set of functions for managing key-value pairs within a dynamic map structure. It includes functionalities to create maps, add and retrieve key-value pairs, resize the map when necessary, and safely free allocated memory. Additional functions handle errors and parse input data, including HTTP requests and cookies, storing the results in the map structure.

* meta_sql.c: Provides a series of functions for handling SQL-related operations in the context of a meta SQL framework. These operations include retrieving I/O types, filling parameters and metadata, processing literal and complex data, extracting inputs, and managing SQL queries. The unit tests validate each function's behavior, ensuring that they handle various inputs correctly and maintain robustness against NULL pointers and improper configurations.

* request_parser.c: Contains unit tests designed to validate the correctness of request parsing operations. It ensures that the functionality related to handling errors, processing cookies, and managing HTTP request inputs operates as expected. The tests, created using the CUnit framework, confirm that the parsing and map management functionalities handle different scenarios effectively and maintain proper memory management.

* response_print.c: Contains unit tests for functions related to XML document handling and map management. The tests verify the correctness of operations such as printing raw data outputs, bounding box documents, and status information, as well as the creation and modification of sample map structures. The functionality is validated by ensuring that the XML document structures are correctly managed and that map operations behave as expected, even with empty inputs.

* server_intefnal.c: Provides unit tests for functions handling various server operations. It includes tests for checking the server status, removing subdirectories, handling dismissal scenarios, reading service configuration files, creating registries, producing error messages based on error codes, and retrieving map data in key-value pair format. The tests ensure that each function performs as expected, verifying correct return values and error handling in different scenarios.

* service.c: Includes unit tests designed to verify the functionality of inheritance and memory management for various data structures used in the service module. The tests cover operations such as copying data from one map to another, transferring I/O types and elements, and ensuring that these operations correctly initialize and manage memory. Additional tests validate the overall inheritance functionality and resource cleanup for the service and registry structures, ensuring robust handling of these components.

* service_internal.c: The tests ensure correct behavior for operations like obtaining and releasing shared memory locks, locking and unlocking mechanisms, and generating status messages for process IDs. Each function is tested to confirm it handles various input values appropriately, including edge cases, and produces the expected results. This helps ensure the robustness and reliability of the shared memory management and status reporting functionalities in the service module.

* service_internal_java.c: Contains tests for the core functionalities of a service system. It verifies successful service initialization and cleanup, checks request handling, and ensures proper execution of response printing. Each test validates that the components perform as expected under different scenarios.

* service_internal_perl.c: Includes tests for converting between Perl hashes and internal data structures. It verifies that Perl hash objects are created correctly and ensures that the conversion processes work as expected. The tests involve setting up a Perl interpreter, creating Perl hash objects, and cleaning up properly.

* service_internal_python.c: Provides tests for functions handling Python integration in the service. It includes tests for supporting Python interaction with internal data structures and reporting functionality. The tests check both valid and invalid inputs, ensuring correct behavior and error handling.

* service_internal_r.c: Includes a series of tests designed to validate the integration with R language functionality. It ensures that structures are correctly initialized, handles scenarios involving empty and null values, and verifies proper memory management. The tests cover creating and managing data with varying content and check for robustness in handling different edge cases. 

* service_json.c: Includes a series of unit tests to verify JSON processing functionalities. It tests various functions for converting JSON strings into internal representations and vice versa. This includes generating JSON from internal data structures, formatting literal values as JSON, and handling request parsing. Each test validates that the function outputs are correct and that memory management is handled properly. The goal is to ensure that the JSON handling code performs as expected and produces accurate results.

* service_loader.c: Contains a set of unit tests designed to verify various functionalities related to configuration and service management. It includes tests for reading configuration files, retrieving specific settings based on keys, handling service execution, and supporting Python integration. Key functionalities tested include ensuring correct retrieval of configuration values, validating memory allocation for service structures, and simulating service execution and Python support scenarios. Each test checks for proper execution, accurate results, and appropriate error handling, ensuring the robustness of the configuration and service management system.

* service_yaml.c: Focuses on handling Service structures with YAML data representation. It includes functionality for creating Service objects, converting them into YAML format, and parsing YAML strings back into Service objects. The tests validate the correctness of each operation, ensuring that Service objects are properly instantiated, correctly formatted into YAML strings, and accurately reconstructed from YAML data. These checks confirm that data integrity and conversion processes are functioning as intended.

* sqlapi.c: Tests the functionality of the fetchSql function from the sqlapi module. It verifies various scenarios, such as fetching layers from a configuration based on valid and invalid indices, handling cases with empty layer lists, and dealing with NULL SQL strings. The tests also cover situations with multiple layers, large indices, and different SQL queries to ensure that the function behaves correctly across a range of conditions. The setup and teardown functions are used to initialize and clean up resources before and after the tests.

* sshapi.c: This code is designed to validate the functionality of the sshapi module, focusing on SSH connection management and configuration handling. It ensures that the module correctly initializes an SSH connection, retrieves session counts from the configuration, and manages file uploads. The tests confirm that the SSH connection object is created properly, the session count is accurately reported, and files are correctly added to the upload queue, even though the specifics of the upload process are not detailed. The setup and teardown procedures are used to manage resources for each test, ensuring clean and effective testing.

* ulinet.c:  The tests cover the storage of data in memory, writing data to a file, and handling HTTP headers. Specifically, it checks whether data is correctly copied into memory buffers, written to temporary files, and managed when dealing with HTTP headers. The code ensures that the functions behave as expected, such as accurately storing and retrieving data, and correctly managing memory allocations and file operations.

* zoo_loader_fpm.c: The tests focus on verifying that the cgiMain and cgiInit functions return the expected results, which are simply zero in this case. The test suite sets up the necessary environment for these tests and then runs them to ensure that the functions behave as intended. After executing the tests, it cleans up the testing registry to maintain a clean state.
