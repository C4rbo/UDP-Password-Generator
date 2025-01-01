#include "server.h"

// Generate a numeric password (digits only)
void generate_numeric(char *password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = '0' + rand() % 10; // Generate a random digit
    }
    password[length] = '\0'; // Null-terminate the string
}

// Generate an alphabetic password (lowercase letters)
void generate_alpha(char *password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = 'a' + rand() % 26; // Generate a random lowercase letter
    }
    password[length] = '\0'; // Null-terminate the string
}

// Generate a mixed password (letters and digits)
void generate_mixed(char *password, int length) {
    for (int i = 0; i < length; i++) {
        if (rand() % 2) {
            password[i] = 'a' + rand() % 26; // Generate a random lowercase letter
        } else {
            password[i] = '0' + rand() % 10; // Generate a random digit
        }
    }
    password[length] = '\0'; // Null-terminate the string
}

// Generate a secure password (letters, digits, symbols)
void generate_secure(char *password, int length) {
    char symbols[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    int symbols_len = sizeof(symbols) - 1;
    for (int i = 0; i < length; i++) {
        password[i] = symbols[rand() % symbols_len]; // Generate a random character from the set
    }
    password[length] = '\0'; // Null-terminate the string
}

// Generate an unambiguous password (no similar-looking characters)
void generate_unambiguous(char *password, int length) {
    char symbols[] = "abcdefghjkmnpqrstuvwxyzABCDEFGHJKMNPQRSTUVWXYZ34679!@#$%^&*";
    int symbols_len = sizeof(symbols) - 1;
    for (int i = 0; i < length; i++) {
        password[i] = symbols[rand() % symbols_len]; // Generate a random character from the set
    }
    password[length] = '\0'; // Null-terminate the string
}

int main() {
#if defined WIN32
    // Initialize Winsock on Windows
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);
#endif

    // Create a UDP socket for communication
    int server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Structures to store server and client details
    struct sockaddr_in server_address, client_address;
    unsigned int client_address_length = sizeof(client_address);
    char buffer[BUFFMAX], password[33];
    int message_length;

    // Initialize the server address structure
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    printf("Waiting for connections...\n\n");
    fflush(stdout);

    // Main loop to handle incoming client requests
    while (1) {
        memset(buffer, 0, BUFFMAX);

        // Receive a message from a client
        message_length = recvfrom(server_socket, buffer, BUFFMAX, 0,
                                  (struct sockaddr *)&client_address, &client_address_length);

        if (message_length > 0) {
            // Log the client's address and port
            printf("New request from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
            fflush(stdout);

            // Parse the command and password length from the message
            char command = buffer[0];
            int length = atoi(buffer + 2);

            // Handle the command and generate the appropriate password
            if (length < 6 || length > 32) {
                strncpy(password, "Invalid length (must be between 6 and 32)", 41);
                password[41] = '\0'; // Ensure null-terminated string
            } else if (command == 'n') {
                generate_numeric(password, length);
            } else if (command == 'a') {
                generate_alpha(password, length);
            } else if (command == 'm') {
                generate_mixed(password, length);
            } else if (command == 's') {
                generate_secure(password, length);
            } else if (command == 'u') {
                generate_unambiguous(password, length);
            } else if (command == 'h') {
                strncpy(password, "Help: Use 'n', 'a', 'm', 's', or 'u' followed by length (6-32)", 62);
                password[62] = '\0'; // Ensure null-terminated string
            } else {
                strncpy(password, "Invalid command (use 'h' for help)", 34);
                password[34] = '\0'; // Ensure null-terminated string
            }

            // Send the generated password back to the client
            sendto(server_socket, password, strlen(password), 0,
                   (struct sockaddr *)&client_address, client_address_length);
        }
    }

    // Close the socket and clean up resources
    close(server_socket);
#if defined WIN32
    WSACleanup();
#endif
    return 0;
}
