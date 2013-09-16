#ifndef IP_H
#define IP_H

void ip_init(void);
void ip_setipmac(char *ip, char *subnet, char *mac);
int ip_socket(void);
int ip_recvfrom(int socket, char *head, char *buf, int len);
int ip_sendto(int socket, char *head, char *buf, int len);

#endif
