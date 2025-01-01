#include "client.h"

// Function to display the help menu with command options
void print_help() {
    printf("\n Password Generator Help Menu\n");
    printf("\nCommands:\n");
    printf("  h        : Show help menu\n");
    printf("  n LENGTH : Generate numeric password (digits only)\n");
    printf("  a LENGTH : Generate alphabetic password (lowercase letters)\n");
    printf("  m LENGTH : Generate mixed password (letters and digits)\n");
    printf("  s LENGTH : Generate secure password (letters, digits, symbols)\n");
    printf("  u LENGTH : Generate unambiguous password (no similar-looking characters)\n");
    printf("  q        : Quit the application\n\n");
    printf("LENGTH must be between 6 and 32 characters.\n\n");
    printf("Ambiguous characters excluded in 'u' option:\n0 O o (zero and letters O)\n1 l I i (one and letters l, I)\n2 Z z (two and letter Z)\n5 S s (five and letter S)\n8 B (eight and letter B)\n");
}

int main() {
#if defined WIN32
    // Initialize Winsock on Windows
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);
#endif

    // Create a UDP socket for communication
    int client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Structure to store server details
    struct sockaddr_in server_address;
    char buffer[BUFFMAX], response[BUFFMAX];
    int server_address_length = sizeof(server_address);

    // Resolve the server's hostname to an IP address
    struct hostent *host_entry = gethostbyname(SERVER_NAME);
    if (!host_entry) {
        fprintf(stderr, "Error: Unable to resolve hostname.\n");
#if defined WIN32
        WSACleanup();
#endif
        return 1;
    }

    // Convert the resolved hostname to a string representation of the IP address
    char *server_ip = inet_ntoa(*(struct in_addr *)host_entry->h_addr_list[0]);

    // Initialize the server address structure
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(server_ip);

    // Display help menu to the user
    print_help();

    // Main loop to handle user commands
    while (1) {
        printf("\nInsert the command to generate a password: ");
        fflush(stdout);

        // Read the user input from stdin
        fgets(buffer, BUFFMAX, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        // Check for empty input
        if (strlen(buffer) == 0) {
            printf("Error: Empty command.\n");
            continue;
        }

        // Display help menu if the user enters 'h'
        if (buffer[0] == 'h') {
            print_help();
            continue;
        }

        // Exit the application if the user enters 'q'
        if (buffer[0] == 'q') {
            printf("Exiting...\n");
            break;
        }

        // Send the command to the server
        sendto(client_socket, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_address, sizeof(server_address));

        // Wait for the server's response
        memset(response, 0, BUFFMAX);
        recvfrom(client_socket, response, BUFFMAX, 0,
                 (struct sockaddr *)&server_address, &server_address_length);

        // Print the server's response to the standard output
        printf("Response: %s\n", response);
    }

    // Close the socket and clean up resources
    close(client_socket);
#if defined WIN32
    WSACleanup();
#endif
    return 0;
}
