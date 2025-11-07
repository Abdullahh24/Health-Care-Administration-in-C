#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define MAGENTA "\033[1;35m"

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

void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    Patient p;
    printf(WHITE "Enter Patient ID: " RESET);
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender: ");
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
    while(fread(&p, sizeof(Patient), 1, fp))
        printf("ID: %d | Name: %s | Age: %d | Gender: %s\n", p.id, p.name, p.age, p.gender);
    fclose(fp);
}

void addAppointment() {
    FILE *fp = fopen("appointments.dat", "ab");
    Appointment a;
    printf(WHITE "Enter Appointment ID: " RESET);
    scanf("%d", &a.id);
    printf("Enter Patient ID: ");
    scanf("%d", &a.patientId);
    printf("Enter Date (dd/mm/yyyy): ");
    scanf("%s", a.date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", a.time);
    printf("Enter Doctor Name: ");
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
    while(fread(&a, sizeof(Appointment), 1, fp))
        printf("ID: %d | Patient ID: %d | Date: %s | Time: %s | Doctor: %s\n",
                a.id, a.patientId, a.date, a.time, a.doctor);
    fclose(fp);
}

void addStaff() {
    FILE *fp = fopen("staff.dat", "ab");
    Staff s;
    printf(WHITE "Enter Staff ID: " RESET);
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Role: ");
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
    while(fread(&s, sizeof(Staff), 1, fp))
        printf("ID: %d | Name: %s | Role: %s\n", s.id, s.name, s.role);
    fclose(fp);
}

void generateBill() {
    int patientId;
    float amount;
    printf(WHITE "Enter Patient ID: " RESET);
    scanf("%d", &patientId);
    printf("Enter Bill Amount: ");
    scanf("%f", &amount);
    FILE *fp = fopen("bills.dat", "a");
    fprintf(fp, "Patient ID: %d | Amount: %.2f\n", patientId, amount);
    fclose(fp);
    printf(MAGENTA "Bill generated successfully!\n" RESET);
}
