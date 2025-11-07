#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

void startupAnimation();
void printSlow(const char *text, int delay);
void loadingAnimation();
void login();
void adminMenu();
void staffMenu();
void addPatient();
void viewPatients();
void addAppointment();
void viewAppointments();
void addStaff();
void viewStaff();
void generateBill();

int main() {
    startupAnimation();
    login();
    return 0;
}

void startupAnimation() {
    printf("\033[2J\033[H");
    printSlow(RED "*====================================*\n",3000);
    printf(CYAN "====================================\n" RESET);
    printSlow("   HEALTH CARE ADMINISTRATION SYSTEM\n", 40000);
    printf(CYAN "====================================\n\n" RESET);
    printSlow(RED "*====================================*\n",3000);
    loadingAnimation();
    sleep(1);
}

void printSlow(const char *text, int delay) {
    for (int i = 0; i < strlen(text); i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(delay);
    }
}

void loadingAnimation() {
    printf(YELLOW "Loading" RESET);
    for (int i = 0; i < 5; i++) {
        fflush(stdout);
        usleep(500000);
        printf(".");
    }
    printf("\n");
}

void login() {
    char uname[30], pass[30];
    printf(CYAN "\n=== Login ===\n" RESET);
    printf(BLUE "Username: " RESET);
    scanf("%s", uname);
    printf(RED "Password: " RESET);
    scanf("%s", pass);

    if(strcmp(uname, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        adminMenu();
    } else if(strcmp(uname, "staff") == 0 && strcmp(pass, "staff123") == 0) {
        staffMenu();
    } else {
        printf(RED "Invalid credentials!\n" RESET);
        exit(0);
    }
}
