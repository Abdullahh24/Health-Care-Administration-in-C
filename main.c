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

#define PATIENT_FILE "patients.txt"
#define APPOINT_FILE "appointments.txt"
#define STAFF_FILE   "staff.txt"
#define TEMP_FILE    "temp.txt"

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
void patientMenu();
void appointmentMenu();
void staffManageMenu();
void addPatient();
void viewPatients();
void modifyPatient();
void deletePatient();
void addAppointment();
void viewAppointments();
void modifyAppointment();
void deleteAppointment();
void addStaff();
void viewStaff();
void modifyStaff();
void deleteStaff();
void generateBill();
void viewBills();

int main() {
    startupAnimation();
    login();
    return 0;
}

void startupAnimation() {
    printf("\033[2J\033[H");
    printSlow(RED "*====================================*\n",3000);
    printf(CYAN "====================================\n" RESET);
    printSlow(BLUE "HEALTH CARE ADMINISTRATION SYSTEM\n", 40000);
    printf(CYAN "====================================\n\n" RESET);
    printSlow(RED "*====================================*\n",3000);
    loadingAnimation();
    sleep(1);
}

void printSlow(const char *text, int delay) {
    for (size_t i = 0; i < strlen(text); i++) {
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
    printf(BLUE "***** Username: " RESET);
    scanf("%29s", uname);
    printf(RED "***** Password: " RESET);
    scanf("%29s", pass);

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
        printSlow(YELLOW "\n--- Admin Menu ---\n" RESET,20000);
        printf("1. Patient Management\n");
        printf("2. Appointment Management\n");
        printf("3. Staff Management\n");
        printf("4. Generate Bill\n");
        printf("5. Exit\n");
        printf(WHITE "Choice: " RESET);
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf(RED "Invalid input!\n" RESET); continue; }

        switch(choice) {
            case 1: patientMenu(); break;
            case 2: appointmentMenu(); break;
            case 3: staffManageMenu(); break;
            case 4: generateBill(); break;
            case 5: exit(0);
            default: printf(RED "Invalid choice!\n" RESET);
        }
        loadingAnimation();
        sleep(1);
    } while(1);
}

void staffMenu() {
    int choice;
    do {
        printf(YELLOW "\n--- Staff Menu ---\n" RESET);
        printf("1. Patient Management\n");
        printf("2. Appointment Management\n");
        printf("3. Exit\n");
        printf(WHITE "Choice: " RESET);
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf(RED "Invalid input!\n" RESET); continue; }

        switch(choice) {
            case 1: patientMenu(); break;
            case 2: appointmentMenu(); break;
            case 3: exit(0);
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while(1);
}

void patientMenu() {
    int choice;
    do {
        printf(CYAN "\n--- Patient Management ---\n" RESET);
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Modify Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Back\n");
        printf(WHITE "Choice: " RESET);
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf(RED "Invalid input!\n" RESET); continue; }
        while(getchar()!='\n');

        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: modifyPatient(); break;
            case 4: deletePatient(); break;
            case 5: return;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while(1);
}

void addPatient() {
    Patient p;
    FILE *fp = fopen(PATIENT_FILE, "a");
    if (!fp) { printf(RED "Unable to open file for writing.\n" RESET); return; }

    printf(WHITE "Enter Patient ID: " RESET);
    scanf("%d", &p.id); while(getchar()!='\n');
    printf(WHITE "Enter Name: " RESET);
    fgets(p.name, sizeof(p.name), stdin); p.name[strcspn(p.name, "\n")] = 0;
    printf(WHITE "Enter Age: " RESET);
    scanf("%d", &p.age); while(getchar()!='\n');
    printf(WHITE "Enter Gender: " RESET);
    fgets(p.gender, sizeof(p.gender), stdin); p.gender[strcspn(p.gender, "\n")] = 0;

    fprintf(fp, "%d|%s|%d|%s\n", p.id, p.name, p.age, p.gender);
    fclose(fp);
    printf(GREEN "Patient added successfully!\n" RESET);
}

void viewPatients() {
    FILE *fp = fopen(PATIENT_FILE, "r");
    if (!fp) { printf(RED "No patient records found.\n" RESET); return; }

    Patient p;
    printf(CYAN "\n--- Patient List ---\n" RESET);
    while (fscanf(fp, "%d|%49[^|]|%d|%9[^\n]\n", &p.id, p.name, &p.age, p.gender) == 4) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s\n", p.id, p.name, p.age, p.gender);
    }
    fclose(fp);
}

void modifyPatient() {
    FILE *fp = fopen(PATIENT_FILE, "r");
    if (!fp) { printf(RED "No records found.\n" RESET); return; }
    FILE *tmp = fopen(TEMP_FILE, "w");
    if (!tmp) { fclose(fp); printf(RED "Unable to create temporary file.\n" RESET); return; }

    int id, found = 0;
    Patient p;
    printf(WHITE "Enter Patient ID to modify: " RESET);
    if (scanf("%d", &id) != 1) { while(getchar()!='\n'); printf(RED "Invalid input.\n" RESET); fclose(fp); fclose(tmp); remove(TEMP_FILE); return; }
    while(getchar()!='\n');

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^\n]\n", &p.id, p.name, &p.age, p.gender) == 4) {
        if (p.id == id) {
            found = 1;
            printf("Current -> ID: %d | Name: %s | Age: %d | Gender: %s\n", p.id, p.name, p.age, p.gender);
            printf(WHITE "Enter new name: " RESET);
            fgets(p.name, sizeof(p.name), stdin); p.name[strcspn(p.name, "\n")] = 0;
            printf(WHITE "Enter new age: " RESET);
            scanf("%d", &p.age); while(getchar()!='\n');
            printf(WHITE "Enter new gender: " RESET);
            fgets(p.gender, sizeof(p.gender), stdin); p.gender[strcspn(p.gender, "\n")] = 0;
            printf(GREEN "Patient updated.\n" RESET);
        }
        fprintf(tmp, "%d|%s|%d|%s\n", p.id, p.name, p.age, p.gender);
    }

    fclose(fp);
    fclose(tmp);
    remove(PATIENT_FILE);
    rename(TEMP_FILE, PATIENT_FILE);

    if (!found) printf(RED "Patient not found.\n" RESET);
}

void deletePatient() {
    FILE *fp = fopen(PATIENT_FILE, "r");
    if (!fp) { printf(RED "No records found.\n" RESET); return; }
    FILE *tmp = fopen(TEMP_FILE, "w");
    if (!tmp) { fclose(fp); printf(RED "Unable to create temporary file.\n" RESET); return; }

    int id, found = 0;
    Patient p;
    printf(WHITE "Enter Patient ID to delete: " RESET);
    if (scanf("%d", &id) != 1) { while(getchar()!='\n'); printf(RED "Invalid input.\n" RESET); fclose(fp); fclose(tmp); remove(TEMP_FILE); return; }
    while(getchar()!='\n');

    while (fscanf(fp, "%d|%49[^|]|%d|%9[^\n]\n", &p.id, p.name, &p.age, p.gender) == 4) {
        if (p.id != id) {
            fprintf(tmp, "%d|%s|%d|%s\n", p.id, p.name, p.age, p.gender);
        } else found = 1;
    }

    fclose(fp);
    fclose(tmp);
    remove(PATIENT_FILE);
    rename(TEMP_FILE, PATIENT_FILE);

    if (found) printf(GREEN "Patient deleted!\n" RESET);
    else printf(RED "Patient not found.\n" RESET);
}

void appointmentMenu() {
    int choice;
    do {
        printf(CYAN "\n--- Appointment Management ---\n" RESET);
        printf("1. Add Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Modify Appointment\n");
        printf("4. Delete Appointment\n");
        printf("5. Back\n");
        printf(WHITE "Choice: " RESET);
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf(RED "Invalid input!\n" RESET); continue; }
        while(getchar()!='\n');

        switch(choice) {
            case 1: addAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: modifyAppointment(); break;
            case 4: deleteAppointment(); break;
            case 5: return;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while(1);
}

void addAppointment() {
    Appointment a;
    FILE *fp = fopen(APPOINT_FILE, "a");
    if (!fp) { printf(RED "Unable to open file for writing.\n" RESET); return; }

    printf(WHITE "Enter Appointment ID: " RESET);
    scanf("%d", &a.id); while(getchar()!='\n');
    printf(WHITE "Enter Patient ID: " RESET);
    scanf("%d", &a.patientId); while(getchar()!='\n');
    printf(WHITE "Enter Date (dd/mm/yyyy): " RESET);
    fgets(a.date, sizeof(a.date), stdin); a.date[strcspn(a.date, "\n")] = 0;
    printf(WHITE "Enter Time (HH:MM): " RESET);
    fgets(a.time, sizeof(a.time), stdin); a.time[strcspn(a.time, "\n")] = 0;
    printf(WHITE "Enter Doctor Name: " RESET);
    fgets(a.doctor, sizeof(a.doctor), stdin); a.doctor[strcspn(a.doctor, "\n")] = 0;

    fprintf(fp, "%d|%d|%s|%s|%s\n", a.id, a.patientId, a.date, a.time, a.doctor);
    fclose(fp);
    printf(GREEN "Appointment added.\n" RESET);
}

void viewAppointments() {
    FILE *fp = fopen(APPOINT_FILE, "r");
    if (!fp) { printf(RED "No appointment records found.\n" RESET); return; }

    Appointment a;
    printf(CYAN "\n--- Appointment List ---\n" RESET);
    while (fscanf(fp, "%d|%d|%19[^|]|%9[^|]|%49[^\n]\n", &a.id, &a.patientId, a.date, a.time, a.doctor) == 5) {
        printf("ID: %d | Patient ID: %d | Date: %s | Time: %s | Doctor: %s\n",
               a.id, a.patientId, a.date, a.time, a.doctor);
    }
    fclose(fp);
}

void modifyAppointment() {
    FILE *fp = fopen(APPOINT_FILE, "r");
    if (!fp) { printf(RED "No records found.\n" RESET); return; }
    FILE *tmp = fopen(TEMP_FILE, "w");
    if (!tmp) { fclose(fp); printf(RED "Unable to create temporary file.\n" RESET); return; }

    int id, found = 0;
    Appointment a;
    printf(WHITE "Enter Appointment ID to modify: " RESET);
    if (scanf("%d", &id) != 1) { while(getchar()!='\n'); printf(RED "Invalid input.\n" RESET); fclose(fp); fclose(tmp); remove(TEMP_FILE); return; }
    while(getchar()!='\n');

    while (fscanf(fp, "%d|%d|%19[^|]|%9[^|]|%49[^\n]\n", &a.id, &a.patientId, a.date, a.time, a.doctor) == 5) {
        if (a.id == id) {
            found = 1;
            printf("Current -> ID: %d | Patient ID: %d | Date: %s | Time: %s | Doctor: %s\n",
                   a.id, a.patientId, a.date, a.time, a.doctor);

            printf(WHITE "Enter new patient ID: " RESET);
            scanf("%d", &a.patientId); while(getchar()!='\n');

            printf(WHITE "Enter new Date: " RESET);
            fgets(a.date, sizeof(a.date), stdin); a.date[strcspn(a.date, "\n")] = 0;

            printf(WHITE "Enter new Time: " RESET);
            fgets(a.time, sizeof(a.time), stdin); a.time[strcspn(a.time, "\n")] = 0;

            printf(WHITE "Enter new Doctor: " RESET);
            fgets(a.doctor, sizeof(a.doctor), stdin); a.doctor[strcspn(a.doctor, "\n")] = 0;

            printf(GREEN "Appointment updated.\n" RESET);
        }
        fprintf(tmp, "%d|%d|%s|%s|%s\n", a.id, a.patientId, a.date, a.time, a.doctor);
    }

    fclose(fp);
    fclose(tmp);
    remove(APPOINT_FILE);
    rename(TEMP_FILE, APPOINT_FILE);

    if (!found) printf(RED "Appointment not found.\n" RESET);
}

void deleteAppointment() {
    FILE *fp = fopen(APPOINT_FILE, "r");
    if (!fp) { printf(RED "No records found.\n" RESET); return; }
    FILE *tmp = fopen(TEMP_FILE, "w");
    if (!tmp) { fclose(fp); printf(RED "Unable to create temporary file.\n" RESET); return; }

    int id, found = 0;
    Appointment a;
    printf(WHITE "Enter Appointment ID to delete: " RESET);
    if (scanf("%d", &id) != 1) { while(getchar()!='\n'); printf(RED "Invalid input.\n" RESET); fclose(fp); fclose(tmp); remove(TEMP_FILE); return; }
    while(getchar()!='\n');

    while (fscanf(fp, "%d|%d|%19[^|]|%9[^|]|%49[^\n]\n", &a.id, &a.patientId, a.date, a.time, a.doctor) == 5) {
        if (a.id != id) fprintf(tmp, "%d|%d|%s|%s|%s\n", a.id, a.patientId, a.date, a.time, a.doctor);
        else found = 1;
    }

    fclose(fp);
    fclose(tmp);
    remove(APPOINT_FILE);
    rename(TEMP_FILE, APPOINT_FILE);

    if (found) printf(GREEN "Appointment deleted.\n" RESET);
    else printf(RED "Appointment not found.\n" RESET);
}

void staffManageMenu() {
    int choice;
    do {
        printf(CYAN "\n--- Staff Management ---\n" RESET);
        printf("1. Add Staff\n");
        printf("2. View Staff\n");
        printf("3. Modify Staff\n");
        printf("4. Delete Staff\n");
        printf("5. Back\n");
        printf(WHITE "Choice: " RESET);
        if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf(RED "Invalid input!\n" RESET); continue; }
        while(getchar()!='\n');

        switch(choice) {
            case 1: addStaff(); break;
            case 2: viewStaff(); break;
            case 3: modifyStaff(); break;
            case 4: deleteStaff(); break;
            case 5: return;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while(1);
}

void addStaff() {
    Staff s;
    FILE *fp = fopen(STAFF_FILE, "a");
    if (!fp) { printf(RED "Unable to open file for writing.\n" RESET); return; }

    printf(WHITE "Enter Staff ID: " RESET);
    scanf("%d", &s.id); while(getchar()!='\n');

    printf(WHITE "Enter Name: " RESET);
    fgets(s.name, sizeof(s.name), stdin); s.name[strcspn(s.name, "\n")] = 0;

    printf(WHITE "Enter Role: " RESET);
    fgets(s.role, sizeof(s.role), stdin); s.role[strcspn(s.role, "\n")] = 0;

    fprintf(fp, "%d|%s|%s\n", s.id, s.name, s.role);
    fclose(fp);

    printf(GREEN "Staff added.\n" RESET);
}

void viewStaff() {
    FILE *fp = fopen(STAFF_FILE, "r");
    if (!fp) { printf(RED "No staff records found.\n" RESET); return; }

    Staff s;
    printf(CYAN "\n--- Staff List ---\n" RESET);
    while (fscanf(fp, "%d|%49[^|]|%29[^\n]\n", &s.id, s.name, s.role) == 3) {
        printf("ID: %d | Name: %s | Role: %s\n", s.id, s.name, s.role);
    }
    fclose(fp);
}

void modifyStaff() {
    FILE *fp = fopen(STAFF_FILE, "r");
    if (!fp) { printf(RED "No records found.\n" RESET); return; }
    FILE *tmp = fopen(TEMP_FILE, "w");
    if (!tmp) { fclose(fp); printf(RED "Unable to create temporary file.\n" RESET); return; }

    int id, found = 0;
    Staff s;
    printf(WHITE "Enter Staff ID to modify: " RESET);
    if (scanf("%d", &id) != 1) { while(getchar()!='\n'); printf(RED "Invalid input.\n" RESET); fclose(fp); fclose(tmp); remove(TEMP_FILE); return; }
    while(getchar()!='\n');

    while (fscanf(fp, "%d|%49[^|]|%29[^\n]\n", &s.id, s.name, s.role) == 3) {
        if (s.id == id) {
            found = 1;

            printf("Current -> ID: %d | Name: %s | Role: %s\n", s.id, s.name, s.role);

            printf(WHITE "Enter new name: " RESET);
            fgets(s.name, sizeof(s.name), stdin); s.name[strcspn(s.name, "\n")] = 0;

            printf(WHITE "Enter new role: " RESET);
            fgets(s.role, sizeof(s.role), stdin); s.role[strcspn(s.role, "\n")] = 0;

            printf(GREEN "Staff updated.\n" RESET);
        }
        fprintf(tmp, "%d|%s|%s\n", s.id, s.name, s.role);
    }

    fclose(fp);
    fclose(tmp);
    remove(STAFF_FILE);
    rename(TEMP_FILE, STAFF_FILE);

    if (!found) printf(RED "Staff not found.\n" RESET);
}

void deleteStaff() {
    FILE *fp = fopen(STAFF_FILE, "r");
    if (!fp) { printf(RED "No records found.\n" RESET); return; }
    FILE *tmp = fopen(TEMP_FILE, "w");
    if (!tmp) { fclose(fp); printf(RED "Unable to create temporary file.\n" RESET); return; }

    int id, found = 0;
    Staff s;
    printf(WHITE "Enter Staff ID to delete: " RESET);
    if (scanf("%d", &id) != 1) { while(getchar()!='\n'); printf(RED "Invalid input.\n" RESET); fclose(fp); fclose(tmp); remove(TEMP_FILE); return; }
    while(getchar()!='\n');

    while (fscanf(fp, "%d|%49[^|]|%29[^\n]\n", &s.id, s.name, s.role) == 3) {
        if (s.id != id) fprintf(tmp, "%d|%s|%s\n", s.id, s.name, s.role);
        else found = 1;
    }

    fclose(fp);
    fclose(tmp);
    remove(STAFF_FILE);
    rename(TEMP_FILE, STAFF_FILE);

    if (found) printf(GREEN "Staff deleted.\n" RESET);
    else printf(RED "Staff not found.\n" RESET);
}


void viewBills() {
    FILE *fp = fopen("bills.txt", "r");
    if (!fp) {
        printf(RED "No bills found.\n" RESET);
        return;
    }

    char line[200];
    printf(CYAN "\n--- All Generated Bills ---\n" RESET);

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void generateBill() {
    int choice;

    do {
        printf(MAGENTA "\n--- Billing Menu ---\n" RESET);
        printf("1. Generate New Bill\n");
        printf("2. View All Bills\n");
        printf("3. Back\n");
        printf(WHITE "Choice: " RESET);

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf(RED "Invalid input!\n" RESET);
            continue;
        }

        while (getchar() != '\n');

        if (choice == 1) {
            int patientId;
            float amount;

            printf(WHITE "Enter Patient ID: " RESET);
            scanf("%d", &patientId);

            printf(WHITE "Enter Bill Amount: " RESET);
            scanf("%f", &amount);

            while (getchar() != '\n');

            FILE *fp = fopen("bills.txt", "a");
            if (!fp) {
                printf(RED "Unable to open bills file.\n" RESET);
                return;
            }

            fprintf(fp, "Patient ID: %d | Amount: %.2f\n", patientId, amount);
            fclose(fp);

            printf(GREEN "Bill generated successfully!\n" RESET);
        }
        else if (choice == 2) {
            viewBills();
        }
        else if (choice == 3) {
            return;
        }
        else {
            printf(RED "Invalid choice!\n" RESET);
        }

    } while (1);
}
