# UDP Password Generator - Client/Server Application

This project is a UDP client/server application where the server acts as a password generator, responding to client requests with passwords generated according to specified criteria.

## Features

- The client communicates with the server via UDP sockets.
- The server listens for incoming datagrams and logs the client’s IP address and port (e.g., `New request from xxx.xxx.xxx.xxx:yyyyy`).
- The client supports the following commands:
  - `n LENGTH`: Generate a numeric password (digits only).
  - `a LENGTH`: Generate an alphabetic password (lowercase letters only).
  - `m LENGTH`: Generate a mixed password (lowercase letters and digits).
  - `s LENGTH`: Generate a secure password (uppercase, lowercase, digits, and symbols).
  - `u LENGTH`: Generate an unambiguous secure password (no similar-looking characters).
  - `h`: Display a help menu with details about available commands.
  - `q`: Quit the application.
- Password length must be between 6 and 32 characters.
- The server generates the password based on the client request and sends it back as a UDP datagram.
- The client displays the received password and can make subsequent requests until terminated with the `q` command.

### Help Menu Example
```
Password Generator Help Menu
Commands:
h        : show this help menu
n LENGTH : generate numeric password (digits only)
a LENGTH : generate alphabetic password (lowercase letters)
m LENGTH : generate mixed password (lowercase letters and numbers)
s LENGTH : generate secure password (uppercase, lowercase, numbers, symbols)
u LENGTH : generate unambiguous secure password (no similar-looking characters)
q        : quit application

LENGTH must be between 6 and 32 characters

Ambiguous characters excluded in 'u' option:
0 O o (zero and letters O)
1 l I i (one and letters l, I)
2 Z z (two and letter Z)
5 S s (five and letter S)
8 B (eight and letter B)
```

## Requirements

- The shared application protocol is defined in a `.h` header file.
- Password generation functions:
  - `generate_numeric()`
  - `generate_alpha()`
  - `generate_mixed()`
  - `generate_secure()`
  - `generate_unambiguous()`
- Input for password requests must be entered as a single line (e.g., `n 8`).
- Default IP address, server name (`passwdgen.uniba.it`), and port are preconfigured.
- The code is portable and does not rely on platform-specific libraries.
- The project is divided into two separate Eclipse projects: one for the client and one for the server.

## How to Run

1. Compile and launch the server from its Eclipse project:
   ```cmd
   server.exe
   ```
2. Compile and launch the client from its Eclipse project:
   ```cmd
   client.exe
   ```
3. Follow the client prompts to request passwords or view the help menu.

## Example Interaction

1. The client connects to the server and sends a request:
   ```
   Input: n 8
   ```
2. The server logs the request:
   ```
   New request from xxx.xxx.xxx.xxx:yyyyy
   ```
3. The server generates the requested password and sends it back to the client:
   ```
   Password: 45237891
   ```
4. The client can continue making requests or quit using `q`:
   ```
   Input: q
   Disconnected from the server.
   ```

This program was developed using **Eclipse** and tested on a Windows environment.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing

Contributions are welcome! If you have suggestions for improvements or find bugs, please open an issue or submit a pull request on GitHub.

## Author

- C4rbo (https://github.com/C4rbo)
