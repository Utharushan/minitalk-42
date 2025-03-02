# minitalk

## Overview

`minitalk` is a project that implements a simple communication protocol between a client and a server using UNIX signals. The client sends a message to the server, which then prints the message to the standard output.

## Project Structure

### Description of Key Files

- **client.c**: Contains the implementation of the client program that sends messages to the server.
- **server.c**: Contains the implementation of the server program that receives messages from the client and prints them.
- **inc/minitalk.h**: Header file containing function prototypes and necessary includes for the project.
- **minitalk_utils.c**: Utility function to convert a string to binary and send it to the server.
- **Makefile**: Script to compile the project.
- **normi**: Configuration file for the norminette code linter.

## Installation
## Project Structure

├── Makefile\
├── README.md\
├── inc/minitalk.h\
├── libftprintf\
├── client.c\
├── server.c\
├── minitalk_utils.c\
└── normi

### Prerequisites

To compile and use this project, you will need:
- **A C compiler** (e.g., `cc`).
- **Make** utility to compile the project.

### Compilation

1. Clone this repository:

	```bash
	git clone https://github.com/Utharushan/minitalk-42.git
	cd minitalk-42
	```

2. Build the project:

	```bash
	make
	```

## Usage

1. Start the server:

	```bash
	./server
	```

	The server will print its process ID (PID).

2. In another terminal, send a message using the client:

	```bash
	./client <server_pid> "Your message here"
	```

Replace `<server_pid>` with the PID printed by the server and `"Your message here"` with the message you want to send.
