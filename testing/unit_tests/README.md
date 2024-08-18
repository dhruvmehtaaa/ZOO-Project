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
    libxml2-dev
```

## After Installing run the below commands to execute the tests

```
chmod +x run_tests.py
python3 run_tests.py
```

