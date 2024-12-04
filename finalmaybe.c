#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_SUBJECTS 4
#define FILENAME "student_data.txt"

// Structs for storing student data
typedef struct {
    char name[20];
    float midterm[NUM_SUBJECTS], classwork[NUM_SUBJECTS], final_exam[NUM_SUBJECTS];
    float gpa[NUM_SUBJECTS];
    int attendance[NUM_SUBJECTS];
    char remarks[NUM_SUBJECTS][200];
} Student;

//Global Declarations
Student ***students;
float *section_max_gpa;



// Function prototypes
void showMainMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS);
void teacherMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS);
void studentMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS);
void parentMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS);
void enterMarks(Student ***students,int section, int NUM_STUDENTS,int subIndex);
void enterAttendance(Student ***students,int section, int NUM_STUDENTS, int subIndex);
void modifyMarks(Student ***students,int section, int NUM_STUDENTS, int subIndex);
void modifyAttendance(Student ***students,int section, int NUM_STUDENTS, int subIndex);
void viewMarks(Student ***students,int section, int NUM_STUDENTS, int subIndex);
void viewAttendance(Student ***students,int section, int NUM_STUDENTS, int subIndex);
void viewHighestGPAAllSections(Student ***students,int NUM_SECTION, int NUM_STUDENTS, int subIndex);
void enterRemarks(Student ***students,int section, int NUM_STUDENTS, int subIndex);
void viewEligibleStudents(Student ***students,int section, int NUM_STUDENTS , int subIndex);
void generateReportCard(Student ***students,int section, int studentIndex);
void addNamesFromFile(Student ***students,int section,int NUM_STUDENTS,int subIndex);
void generateTextReport(Student ***students,int section,int studentIndex);
void generateClassfile(Student ***students, int secton, int NUM_STUDENTS, int subIndex);
void cleanup(Student ***students, int NUM_SECTIONS, int NUM_STUDENTS);
// Main function
int main() {
	int i=0,j=0,NUM_STUDENTS,NUM_SECTIONS;
	printf("\nEnter the number of sections:\n");
	scanf("%d",&NUM_SECTIONS);
	printf("\nEnter the number of students in a section:\n");
	scanf("%d",&NUM_STUDENTS);
	//Allocating memory for all sections
	students = (Student ***)malloc(NUM_SECTIONS * sizeof(Student **));
	if (students == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
	}
//	section_max_gpa = (float *)malloc(NUM_SECTIONS * sizeof(float));
//    if (section_max_gpa == NULL) {
//        printf("Memory allocation failed!\n");
//        exit(1);
//    }
    //Allocating memory for all students in a class
	for (i = 0; i < NUM_SECTIONS; i++) {
    	students[i] = (Student **)malloc(NUM_STUDENTS * sizeof(Student *));
    	if (students[i] == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    	}
		//Allocating memory for every student
    	for (j = 0; j < NUM_STUDENTS; j++) {
        students[i][j] = (Student *)malloc(sizeof(Student));
        if (students[i][j] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
}
	
    while(1) {
        showMainMenu(students,NUM_SECTIONS,NUM_STUDENTS);
    }
    cleanup(students, NUM_SECTIONS, NUM_STUDENTS);
    return 0;
}

void showMainMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS) {
    int choice;
    printf("\n----- Main Menu -----\n");
    printf("1. Teacher\n");
    printf("2. Student\n");
    printf("3. Parents\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("\nInvalid input. Please enter a valid option.");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }
    switch(choice) {
        case 1: teacherMenu(students,NUM_SECTION,NUM_STUDENTS); break;
        case 2: studentMenu(students,NUM_SECTION,NUM_STUDENTS); break;
        case 3: parentMenu(students,NUM_SECTION,NUM_STUDENTS); break;
        case 4: exit(0);
        default:
            printf("Invalid choice. Please try again.");
    }
}

void teacherMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS) {
    int choice, section,subject;
    while (1) {
        printf("\n----- Teacher Menu -----\n");
        printf("Enter section number (1-%d): ",NUM_SECTION);
        if (scanf("%d", &section) != 1 || section < 1 || section > NUM_SECTION) {
            printf("\nInvalid section number.");
            return;
        }
        section--; // Adjust for 0-indexing
        printf("\nEnter Subject ID:\n");
        scanf("%d",&subject);
        if(subject>NUM_SUBJECTS || subject<0){
        	printf("\nInvald subject ID");
        	return;
		}
		addNamesFromFile(students,section,NUM_STUDENTS,subject);
        printf("\n1. Enter Marks\n2. Enter Attendance\n3. Modify Marks\n4. Modify Attendance\n");
        printf("5. View Marks\n6. View Attendance\n");
        printf("7. View Highest GPA in All Sections\n8. Enter Remarks\n9. View Eligible Students\n");
        printf("10.Generate Class File\n11. Go Back\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a valid option.");
            return;
        }
        
        switch(choice) {
            case 1: enterMarks(students,section,NUM_STUDENTS,subject); break;
            case 2: enterAttendance(students,section,NUM_STUDENTS,subject); break;
            case 3: modifyMarks(students,section,NUM_STUDENTS,subject); break;
            case 4: modifyAttendance(students,section,NUM_STUDENTS,subject); break;
            case 5: viewMarks(students,section,NUM_STUDENTS,subject); break;
            case 6: viewAttendance(students,section,NUM_STUDENTS,subject); break;
            case 7: viewHighestGPAAllSections(students,NUM_SECTION,NUM_STUDENTS,subject); break;
            case 8: enterRemarks(students,section,NUM_STUDENTS,subject); break;
            case 9: viewEligibleStudents(students,section,NUM_STUDENTS,subject); break;
            case 10: generateClassfile(students,section,NUM_STUDENTS,subject); break;
            case 11: return; // Go Back
            default:
                printf("\nInvalid choice. Please try again.");
        }
    }
}

void studentMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS) {
    int section, subject;
    while (1) {
        printf("\n----- Student Menu -----\n");
        printf("Enter your section number (1-%d): ", NUM_SECTION);
        if (scanf("%d", &section) != 1 || section < 1 || section > NUM_SECTION) {
            printf("\nInvalid section number.");
            return;
        }
        section--; // Adjust for 0-indexing

        int studentIndex;
        printf("Enter your student index (0-%d): ", NUM_STUDENTS - 1);
        if (scanf("%d", &studentIndex) != 1 || studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
            printf("\nInvalid student index.");
            return;
        }
		printf("\nEnter subject code: ");
		scanf("%d", &subject);
		if(subject>NUM_SUBJECTS || subject<0){
			printf("\nInvalid subject");
			return;
		}
        printf("\n1. View Marks\n2. View Attendance\n3. View Weighatge\n4. View GPA\n");
        printf("5. Generate Report Card\n6.Generate Text File\n7. Go Back\n");
        printf("Enter your choice: ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a valid option.");
            return;
        }
        switch(choice) {
            case 1: viewMarks(students,section,NUM_STUDENTS,subject); break;
            case 2: viewAttendance(students,section,NUM_STUDENTS,subject); break;
            case 3: printf("Marks Distribution: 30%% Midterm, 20%% Classwork, 50%% Final\n"); break;
            case 4: printf("Your GPA: %.2f\n", students[section][studentIndex]->gpa[subject]); break;
            case 5: generateReportCard(students,section, studentIndex); break;
            case 6:
            	generateTextReport(students,section,studentIndex);
            case 7: return; // Go Back
            default:
                printf("\nInvalid choice. Please try again.");
                break;
        }
    }
}

void parentMenu(Student ***students,int NUM_SECTION, int NUM_STUDENTS) {
    int section,subject;
    while (1) {
        printf("\n----- Parent Menu -----\n");
        printf("Enter your section number (1-%d): ",NUM_SECTION);
        scanf("%d", &section);
        if ( section < 1 || section > NUM_SECTION) {
            printf("\nInvalid section number.");
            return;
        }
        section--; // Adjust for 0-indexing

        int studentIndex;
        printf("Enter student index (0-%d): ", NUM_STUDENTS - 1);
        if (scanf("%d", &studentIndex) != 1 || studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
            printf("\nInvalid student index.");
            return;
        }
		printf("\nEnter subject code: ");
		scanf("%d", &subject);
		if(subject>NUM_SUBJECTS || subject<0){
			printf("\nInvalid subject");
			return;
		}
        printf("\n1. View Marks\n2. View Attendance\n3. View GPA\n");
        printf("4. Generate Report Card\n5. Go Back\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        if ( choice< 1 && choice>5) {
            printf("\nInvalid input. Please enter a valid option.");
            return;
        }
        switch(choice) {
            case 1: viewMarks(students,section,NUM_STUDENTS,subject); break;
            case 2: viewAttendance(students,section,NUM_STUDENTS,subject); break;
            case 3: printf("GPA: %.2f\n", students[section][studentIndex]->gpa[subject]); break;
            case 4: generateReportCard(students,section,studentIndex); break;
            case 5: return; // Go Back
            default:
                printf("\nInvalid choice. Please try again.");
                break;
        }
    }
}
void addNamesFromFile(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
	char filename[20]="names";
	filename[6]='0'+section;
	strcat(filename,".txt");
	FILE *filenames = fopen(filename, "r");
	if(filenames == NULL){
		printf("\nError while opening file");
		return ;
	}
    int i;
    for (i = 0; i < NUM_STUDENTS; i++) {
        	fscanf(filenames,"%s", students[section][i]->name);
        	if(students[section][i]->name == NULL){
            printf("\nError reading data for student %d in section %d.\n", i + 1, section);
            fclose(filenames);
            return;
        	}
        }
    printf("Marks and attendance successfully loaded from file.\n");
    return;
}
void generateTextReport(Student ***students, int section, int studentIndex) {
    char filename[20];
    int i;
    printf("Enter filename (max 15 characters):\n");
    getchar();
    fgets(filename, 15, stdin); // Allow space for ".txt"
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character from fgets input

    // Append ".txt" to filename
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\nError opening file for writing.\n");
        return;
    }

    
        fprintf(file, "Section %d:\n", section + 1);
            fprintf(file, "Name: %s\n", students[section][studentIndex]->name);
            for(i=0;i<NUM_SUBJECTS;i++){
            fprintf(file, "Midterm: %.2f, Classwork: %.2f, Final Exam: %.2f\n",
                    students[section][studentIndex]->midterm[i],
                    students[section][studentIndex]->classwork[i],
                    students[section][studentIndex]->final_exam[i]);
            fprintf(file, "GPA: %.2f, Attendance: %d%%\n",
                    students[section][studentIndex]->gpa[i],
                    students[section][studentIndex]->attendance[i]);
            fprintf(file, "Remarks: %s\n\n", students[section][studentIndex]->remarks[i]);
            fprintf(file,"\n");
    		}
    

    fclose(file);
    printf("Report file '%s' generated successfully.\n", filename);
}

void enterMarks(Student ***students,int section, int NUM_STUDENTS , int subIndex) {
    int studentIndex,choice;
    printf("\nEnter your choice:\n1.Enter Marks for all students.\n2.Enter Marks for 1 student\n");
    scanf("%d", &choice);
    if(choice==2){
    printf("Enter student index (0-%d): ", NUM_STUDENTS - 1);
    scanf("%d", &studentIndex);
    if (studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
        printf("\nInvalid student index.");
        return;
    }
    printf("Enter Midterm marks (out of 100): ");
    scanf("%f", &students[section][studentIndex]->midterm[subIndex]);
    if (students[section][studentIndex]->midterm[subIndex]>100 || students[section][studentIndex]->midterm[subIndex]<0 ) {
        printf("\nInvalid input for Midterm marks.");
        return;
    }

    printf("Enter Classwork marks (out of 100): ");
    scanf("%f", &students[section][studentIndex]->classwork[subIndex]);
    if (students[section][studentIndex]->classwork[subIndex]>100 || students[section][studentIndex]->classwork[subIndex]<0) {
        printf("\nInvalid input for Classwork marks.");
        return;
    }

    printf("Enter Final Exam marks (out of 100): ");
    scanf("%f", &students[section][studentIndex]->final_exam[subIndex]);
    if (students[section][studentIndex]->final_exam[subIndex]>100 || students[section][studentIndex]->final_exam[subIndex]<0) {
        printf("\nInvalid input for Final Exam marks.");
        return;
    }

    // Calculate GPA
    students[section][studentIndex]->gpa[subIndex] = 0.3 * students[section][studentIndex]->midterm[subIndex]
                                        + 0.2 * students[section][studentIndex]->classwork[subIndex]
                                        + 0.5 * students[section][studentIndex]->final_exam[subIndex];
    if (students[section][studentIndex]->gpa[subIndex]>=80){
    	students[section][studentIndex]->gpa[subIndex]=4;
	}
	else if(students[section][studentIndex]->gpa[subIndex]>=70){
		students[section][studentIndex]->gpa[subIndex] = 3.0;
	}
	else if(students[section][studentIndex]->gpa[subIndex]>=60){
		students[section][studentIndex]->gpa[subIndex] = 2.0;
	}
	else{
		students[section][studentIndex]->gpa[subIndex] = 1.0;
	}
	}
	else if(choice==1){
		for(studentIndex=0;studentIndex<NUM_STUDENTS;studentIndex++){
			printf("\nEnter marks for Student %d\n", studentIndex);
			printf("Enter Midterm marks (out of 100): ");
    		scanf("%f", &students[section][studentIndex]->midterm[subIndex]);
    			if (students[section][studentIndex]->midterm[subIndex]>100 || students[section][studentIndex]->midterm[subIndex]<0 ) {
       					 printf("\nInvalid input for Midterm marks.");
        				return;
   					 }
    printf("Enter Classwork marks (out of 100): ");
    scanf("%f", &students[section][studentIndex]->classwork[subIndex]);
    	if (students[section][studentIndex]->classwork[subIndex]>100 || students[section][studentIndex]->classwork[subIndex]<0) {
        	printf("\nInvalid input for Classwork marks.");
        	return;
    	}

    printf("Enter Final Exam marks (out of 100): ");
    scanf("%f", &students[section][studentIndex]->final_exam[subIndex]);
    	if (students[section][studentIndex]->final_exam[subIndex]>100 || students[section][studentIndex]->final_exam[subIndex]<0) {
        	printf("\nInvalid input for Final Exam marks.");
        	return;
    	}

    // Calculate GPA
    students[section][studentIndex]->gpa[subIndex] = 0.3 * students[section][studentIndex]->midterm[subIndex]
                                        + 0.2 * students[section][studentIndex]->classwork[subIndex]
                                        + 0.5 * students[section][studentIndex]->final_exam[subIndex];
    if (students[section][studentIndex]->gpa[subIndex]>=80){
    	students[section][studentIndex]->gpa[subIndex]=4;
	}
	else if(students[section][studentIndex]->gpa[subIndex]>=70){
		students[section][studentIndex]->gpa[subIndex] = 3.0;
	}
	else if(students[section][studentIndex]->gpa[subIndex]>=60){
		students[section][studentIndex]->gpa[subIndex] = 2.0;
	}
	else{
		students[section][studentIndex]->gpa[subIndex] = 1.0;
	}
}
}
else{
	printf("\nInvalid Choice");
}
}


void enterAttendance(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
    int studentIndex;
    printf("Enter student index (0-%d): ", NUM_STUDENTS - 1);
    scanf("%d", &studentIndex);
    if (studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
        printf("\nInvalid student index.");
        return;
    }

    printf("Enter attendance (0-100): ");
    scanf("%d", &students[section][studentIndex]->attendance[subIndex]);
    if (students[section][studentIndex]->attendance[subIndex]<0 || students[section][studentIndex]->attendance[subIndex]>100) {
        printf("\nInvalid input for attendance.");
        return;
    }
}

void modifyMarks(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
    int studentIndex,choice;
    printf("Enter student index to modify marks (0-%d): ", NUM_STUDENTS - 1);
    scanf("%d", &studentIndex);
    if (studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
        printf("\nInvalid student index.");
        return;
    }
	else{
		printf("Choose the component whose marks you wish to modify:\n1.Classwork\n2.Midterm\n3.Final\n");
		scanf("%d", &choice);
		switch (choice){
			case 1:
			printf("Enter new Classwork marks (out of 100): ");
    		scanf("%f", &students[section][studentIndex]->classwork[subIndex]);
    		if (students[section][studentIndex]->classwork[subIndex]>100 || students[section][studentIndex]->classwork[subIndex]<0) {
       		 printf("\nInvalid input for Classwork marks.");
       		 return;
   	 		}
			break;
			case 2:
    		printf("Enter new Midterm marks (out of 100): ");
    		scanf("%f", &students[section][studentIndex]->midterm[subIndex]);
    		if (students[section][studentIndex]->midterm[subIndex]>100 || students[section][studentIndex]->midterm[subIndex]<0) {
       		printf("\nInvalid input for Midterm marks.");
        	return;
   			 }
			break;
    		case 3:
    		printf("Enter new Final Exam marks (out of 100): ");
    		scanf("%f", &students[section][studentIndex]->final_exam[subIndex]); 
    		if (students[section][studentIndex]->final_exam[subIndex]>100 || students[section][studentIndex]->final_exam[subIndex]<0) {
        	printf("\nInvalid input for Final Exam marks.");
        	return;}
        	break;
        	default:
        		printf("\nINVALIDE CHOICE");
        		break;
        	}
    }

    // Recalculate GPA after modification
    students[section][studentIndex]->gpa[subIndex] = 0.3 * students[section][studentIndex]->midterm[subIndex]
                                        + 0.2 * students[section][studentIndex]->classwork[subIndex]
                                        + 0.5 * students[section][studentIndex]->final_exam[subIndex];
}


void modifyAttendance(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
    int studentIndex;
    printf("Enter student index to modify attendance (0-%d): ", NUM_STUDENTS - 1);
    scanf("%d", &studentIndex);
    if (studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
        printf("\nInvalid student index.");
        return;
    }

    printf("Enter new attendance (0-100): ");
    if (scanf("%d", &students[section][studentIndex]->attendance[subIndex]) != 1) {
        printf("\nInvalid input for attendance.");
        return;
    }
}

void viewMarks(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
    int studentIndex;
    printf("Enter student index to view marks (0-%d): ", NUM_STUDENTS - 1);
    scanf("%d", &studentIndex);
    if (studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
        printf("\nInvalid student index.");
        return;
    }

    printf("Midterm: %.2f\n", students[section][studentIndex]->midterm[subIndex]);
    printf("Classwork: %.2f\n", students[section][studentIndex]->classwork[subIndex]);
    printf("Final Exam: %.2f\n", students[section][studentIndex]->final_exam[subIndex]);
    printf("GPA: %.2f\n", students[section][studentIndex]->gpa[subIndex]);
}

void viewAttendance(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
    int studentIndex;
    printf("Enter student index to view attendance (0-%d): ", NUM_STUDENTS - 1);
    scanf("%d", &studentIndex);
    if (studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
        printf("\nInvalid student index.");
        return;
    }

    printf("\nAttendance: %d%%\n", students[section][studentIndex]->attendance[subIndex]);
}


void viewHighestGPAAllSections(Student ***students,int NUM_SECTION, int NUM_STUDENTS, int subIndex) {
    int highestGPASection = 0;
    int highestGPAIndex = 0;
    int section,i;
    for (section = 0; section < NUM_SECTION; section++) {
        for (i = 1; i < NUM_STUDENTS; i++) {
            if (students[section][i]->gpa[subIndex] > students[highestGPASection][highestGPAIndex]->gpa[subIndex]) {
                highestGPASection = section;
                highestGPAIndex = i;
            }
        }
    }

    printf("Highest GPA across all sections: %s - Section: %d, Roll No: %d, GPA: %.2f\n",
            students[highestGPASection][highestGPAIndex]->name,
            highestGPASection + 1,
            highestGPAIndex,
            students[highestGPASection][highestGPAIndex]->gpa[subIndex]);
}

void enterRemarks(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
    int studentIndex;
    printf("Enter student index to add remarks (0-%d): ", NUM_STUDENTS - 1);
    if (scanf("%d", &studentIndex) != 1 || studentIndex < 0 || studentIndex >= NUM_STUDENTS) {
        printf("\nInvalid student index.");
        return;
    }

    printf("\nEnter remarks: ");
    getchar();  // To clear the newline character from the input buffer
    fgets(students[section][studentIndex]->remarks[subIndex], 200, stdin);
}

void generateReportCard(Student ***students,int section, int studentIndex) {
	int subIndex=0;
    printf("\n------ Report Card ------\n");
    printf("Name: %s\n", students[section][studentIndex]->name);
    printf("Section: %d\n",section);
    for(subIndex=0;subIndex<NUM_SUBJECTS;subIndex++){
    	printf("\nSubject Code: %d",subIndex);
    printf("Midterm Marks: %.2f\n", students[section][studentIndex]->midterm[subIndex]);
    printf("Classwork Marks: %.2f\n", students[section][studentIndex]->classwork[subIndex]);
    printf("Final Exam Marks: %.2f\n", students[section][studentIndex]->final_exam[subIndex]);
    printf("GPA: %.2f\n", students[section][studentIndex]->gpa[subIndex]);
    printf("Attendance: %d%%\n", students[section][studentIndex]->attendance[subIndex]);
    printf("Remarks: %s\n", students[section][studentIndex]->remarks[subIndex]);
}
    
}

void viewEligibleStudents(Student ***students,int section, int NUM_STUDENTS, int subIndex) {
	int i;
    printf("Eligible students in Section %d (GPA >= 3.0):\n", section + 1);
    for (i = 0; i < NUM_STUDENTS; i++) {
        if (students[section][i]->gpa[subIndex] >= 3.0) {
            printf("%s\n", students[section][i]->name);
        }
    }
}

void generateClassfile(Student ***students,int section,int NUM_STUDENTS,int subIndex){
	FILE *ptr;
	char sec[2];
	char filename[30];
	sprintf(filename, "Class_%d_Sub_%d.txt", section + 1, subIndex);
	ptr=fopen(filename, "w");
	if(ptr==NULL){
		printf("\nError while opening the file.\nApologies for the inconvience.\n");
	}
	else{
	int studentIndex=0;
		for (studentIndex = 0; studentIndex < NUM_STUDENTS; studentIndex++) {
    	fprintf(ptr, "\nStudent ID:\t%d", studentIndex);
    	fprintf(ptr, "\nName:\t%s", students[section][studentIndex]->name);
    	fprintf(ptr, "\nClasswork Marks: %.2f", students[section][studentIndex]->classwork[subIndex]);
    	fprintf(ptr, "\nMidterm Marks: %.2f", students[section][studentIndex]->midterm[subIndex]);
    	fprintf(ptr, "\nFinal Exam Marks: %.2f", students[section][studentIndex]->final_exam[subIndex]);
    	fprintf(ptr, "\nGPA: %.2f", students[section][studentIndex]->gpa[subIndex]);
    	fprintf(ptr, "\nAttendance: %d%%", students[section][studentIndex]->attendance[subIndex]);
    	fprintf(ptr, "\nRemarks: %s\n", students[section][studentIndex]->remarks[subIndex]);
	}
	printf("\n%s File created",filename);
	}
}
void cleanup(Student ***students, int NUM_SECTIONS, int NUM_STUDENTS) {
	int i=0,j=0;
    for (i = 0; i < NUM_SECTIONS; i++) {
        for (j = 0; j < NUM_STUDENTS; j++) {
            free(students[i][j]);
        }
        free(students[i]);
    }
    free(students);
}
