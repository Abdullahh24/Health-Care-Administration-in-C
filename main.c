#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"


typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
} Patient;

typedef struct {
    int id;
    int patientId;
    char date[20];
    char time[10];
    char doctor[50];
} Appointment;

typedef struct {
    int id;
    char name[50];
    char role[30];
} Staff;


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


void adminMenu() {
    int choice;
    do {
        printSlow(YELLOW "\n--- Admin Menu ---\n",40000);
        printf("1. Add Patient\n2. View Patients\n3. Add Appointment\n4. View Appointments\n");
        printf("5. Add Staff\n6. View Staff\n7. Generate Bill\n8. Exit\n");
        printf(WHITE "Choice: " RESET);
        scanf("%d", &choice);
        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: addAppointment(); break;
            case 4: viewAppointments(); break;
            case 5: addStaff(); break;
            case 6: viewStaff(); break;
            case 7: generateBill(); break;
            case 8: exit(0);
            default: printf(RED "Invalid choice!\n" RESET);
    loadingAnimation();
    sleep(1);
        }
    } while(1);
}


void staffMenu() {
    int choice;
    do {
        printf(YELLOW "\n--- Staff Menu ---\n" RESET);
        printf("1. Add Patient\n2. View Patients\n3. Add Appointment\n4. View Appointments\n5. Exit\n");
        printf(WHITE "Choice: " RESET);
        scanf("%d", &choice);
        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: addAppointment(); break;
            case 4: viewAppointments(); break;
            case 5: exit(0);
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while(1);
}


void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    Patient p;
    printf(WHITE "Enter Patient ID: " RESET);
    scanf("%d", &p.id);
    printf(WHITE "Enter Name: " RESET);
    scanf(" %[^\n]", p.name);
    printf(WHITE "Enter Age: " RESET);
    scanf("%d", &p.age);
    printf(WHITE "Enter Gender: " RESET);
    scanf("%s", p.gender);
    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);
    printf(GREEN "Patient added successfully!\n" RESET);
}


void viewPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) {
        printf(RED "No patient records found.\n" RESET);
        return;
    }
    Patient p;
    printf(CYAN "\n--- Patient List ---\n" RESET);
    while(fread(&p, sizeof(Patient), 1, fp)) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s\n", p.id, p.name, p.age, p.gender);
    }
    fclose(fp);
}


void addAppointment() {
    FILE *fp = fopen("appointments.dat", "ab");
    Appointment a;
    printf(WHITE "Enter Appointment ID: " RESET);
    scanf("%d", &a.id);
    printf(WHITE "Enter Patient ID: " RESET);
    scanf("%d", &a.patientId);
    printf(WHITE "Enter Date (dd/mm/yyyy): " RESET);
    scanf("%s", a.date);
    printf(WHITE "Enter Time (HH:MM): " RESET);
    scanf("%s", a.time);
    printf(WHITE "Enter Doctor Name: " RESET);
    scanf(" %[^\n]", a.doctor);
    fwrite(&a, sizeof(Appointment), 1, fp);
    fclose(fp);
    printf(GREEN "Appointment added successfully!\n" RESET);
}


void viewAppointments() {
    FILE *fp = fopen("appointments.dat", "rb");
    if (!fp) {
        printf(RED "No appointment records found.\n" RESET);
        return;
    }
    Appointment a;
    printf(CYAN "\n--- Appointment List ---\n" RESET);
    while(fread(&a, sizeof(Appointment), 1, fp)) {
        printf("ID: %d | Patient ID: %d | Date: %s | Time: %s | Doctor: %s\n",
                a.id, a.patientId, a.date, a.time, a.doctor);
    }
    fclose(fp);
}


void addStaff() {
    FILE *fp = fopen("staff.dat", "ab");
    Staff s;
    printf(WHITE "Enter Staff ID: " RESET);
    scanf("%d", &s.id);
    printf(WHITE "Enter Name: " RESET);
    scanf(" %[^\n]", s.name);
    printf(WHITE "Enter Role: " RESET);
    scanf("%s", s.role);
    fwrite(&s, sizeof(Staff), 1, fp);
    fclose(fp);
    printf(GREEN "Staff added successfully!\n" RESET);
}


void viewStaff() {
    FILE *fp = fopen("staff.dat", "rb");
    if (!fp) {
        printf(RED "No staff records found.\n" RESET);
        return;
    }
    Staff s;
    printf(CYAN "\n--- Staff List ---\n" RESET);
    while(fread(&s, sizeof(Staff), 1, fp)) {
        printf("ID: %d | Name: %s | Role: %s\n", s.id, s.name, s.role);
    }
    fclose(fp);
}


void generateBill() {
    int patientId;
    float amount;
    printf(WHITE "Enter Patient ID: " RESET);
    scanf("%d", &patientId);
    printf(WHITE "Enter Bill Amount: " RESET);
    scanf("%f", &amount);
    FILE *fp = fopen("bills.dat", "a");
    fprintf(fp, "Patient ID: %d | Amount: %.2f\n", patientId, amount);
    fclose(fp);
    printf(MAGENTA "Bill generated successfully!\n" RESET);
}
