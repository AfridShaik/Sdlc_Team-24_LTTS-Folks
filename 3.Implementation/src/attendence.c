#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Used macro
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "studentRecordSystem.bin"
// Macro related to the students info
#define MAX_FATHER_NAME_SIZE 50
#define MAX_STUDENT_NAME_SIZE 50
#define MAX_COURSE_NAME_SIZE 50
#define MAX_STUDENT_ADDRESS_SIZE 300
#define FILE_HEADER_SIZE  sizeof(sFileHeader)

typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;

typedef struct
{
    unsigned int student_id; 
    char fatherName[MAX_FATHER_NAME_SIZE];
    char studentName[MAX_STUDENT_NAME_SIZE];
    char studentAddr[MAX_STUDENT_ADDRESS_SIZE];
    Date studentJoiningDate;
    char courseName[MAX_COURSE_NAME_SIZE];
    int attendence;
} s_StudentInfo;


void printMessage(const char* message);
void currentState(const char *message);
void welcomeMessage();
int checkIsNameValid(const char *name);
int CheckInIsValid(int);
int  checkIsLeapYear(int year);
int checkIsDateValid(Date *validDate);
void addStudent();
void searchStudentById();
void searchStudentByCourse();
void searchByAttendence();
int is_string_equal(char* str1, char* str2);
void viewStudentDetails();
void removeStudent();
void updateCredentials(void);
void displayMenu();
void login();
int checkIsFileExists(const char *path);
void init();



int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}

void printMessage(const char* message)
{
    int len =0;
    int pos = 0;
    
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        
        printf(" ");
    }
    
    printf("%s",message);
}

void currentState(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Student Record Management System Project in C   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessage(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
//Display message
void welcomeMessage()
{
    currentState("LTTS FOLKS");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    To                     =");
    printf("\n\t\t\t        =               Student Record              =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t Enter any key to continue.....");
    getch();
}

//to check whether the name is valid or not
int checkIsNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}

//to check whether the year is leap year year or not
int  checkIsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

// to check whether the date is valid or not
int checkIsDateValid(Date *validDate)
{
    
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    
    if (validDate->mm == 2)
    {
        if (checkIsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
   
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}

// Add student details in the list
void addStudent()
{
    s_StudentInfo addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    currentState("ADD NEW Students");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tStudent ID  = ");
    fflush(stdin);
    scanf("%u",&addStudentInfoInDataBase.student_id);
    do
    {
        printf("\n\t\t\tFather Name  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.fatherName,MAX_FATHER_NAME_SIZE,stdin);
        status = checkIsNameValid(addStudentInfoInDataBase.fatherName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tStudent Name  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studentName,MAX_STUDENT_NAME_SIZE,stdin);
        status = checkIsNameValid(addStudentInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    printf("\n\t\t\tCourse Name  = ");
    fflush(stdin);
    fgets(addStudentInfoInDataBase.courseName,MAX_COURSE_NAME_SIZE,stdin);;
    do
    {

        printf("\n\t\t\tStudent Address  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studentAddr,MAX_STUDENT_ADDRESS_SIZE,stdin);
        status = checkIsNameValid(addStudentInfoInDataBase.studentAddr);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addStudentInfoInDataBase.studentJoiningDate.dd,&addStudentInfoInDataBase.studentJoiningDate.mm,&addStudentInfoInDataBase.studentJoiningDate.yyyy);
        status = checkIsDateValid(&addStudentInfoInDataBase.studentJoiningDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tEnter the number days present(out of 180):");/* code */
        scanf("%d",&addStudentInfoInDataBase.attendence);
        status = CheckInIsValid(&addStudentInfoInDataBase.attendence);
        if(!status)
        {
            printf("\n\t\t\tPlease enter the valid number of presents.\n");
        }
    } while (!status);
    
    fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, fp);
    fclose(fp);
}

int CheckInIsValid(int x)
{
    if(x<0 || x>180)
    {
        return 1;
    }
}
// search student by student id
void searchStudentById()
{
    int found = 0;
    int studentId =0;
    s_StudentInfo addStudentInfoInDataBase = {1};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    currentState("SEARCH STUDENTS");
    
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Student ID NO to search:");
    fflush(stdin);
    scanf("%u",&studentId);
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if(addStudentInfoInDataBase.student_id == studentId)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tStudent id = %d\n",addStudentInfoInDataBase.student_id);
        printf("\t\t\tStudent name = %s",addStudentInfoInDataBase.studentName);
        printf("\t\t\tFather Name = %s",addStudentInfoInDataBase.fatherName);
        printf("\t\t\tCourse Name = %s",addStudentInfoInDataBase.courseName);
        printf("\t\t\tStudent Address = %s",addStudentInfoInDataBase.studentAddr);
        printf("\t\t\tStudent Admission Date(day/month/year) =  (%d/%d/%d)\n",addStudentInfoInDataBase.studentJoiningDate.dd,
               addStudentInfoInDataBase.studentJoiningDate.mm, addStudentInfoInDataBase.studentJoiningDate.yyyy);
        printf("\t\t\tNumber of present(out of 180) = %d\n\n",addStudentInfoInDataBase.attendence);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

//search student by course name
void searchStudentByCourse()
{
    int found = 0;
    char course_name[MAX_COURSE_NAME_SIZE];
    char a[MAX_COURSE_NAME_SIZE];
    s_StudentInfo addStudentInfoInDataBase = {3};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    currentState("SEARCH STUDENTS");
    
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Student Course Name to search:");
    fflush(stdin);
    gets(course_name);
    
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        
        if(is_string_equal(addStudentInfoInDataBase.courseName,course_name))
        {
            found = 1;
             
            printf("\n\t\t\tStudent id = %d",addStudentInfoInDataBase.student_id);
            printf("\n\t\t\tStudent name = %s",addStudentInfoInDataBase.studentName);
            printf("\t\t\tFather Name = %s",addStudentInfoInDataBase.fatherName);
            printf("\t\t\tCourse Name = %s",addStudentInfoInDataBase.courseName);
            printf("\t\t\tStudent Address = %s",addStudentInfoInDataBase.studentAddr);
            printf("\t\t\tStudent Admission Date(day/month/year) =  (%d/%d/%d)\n",addStudentInfoInDataBase.studentJoiningDate.dd,
                addStudentInfoInDataBase.studentJoiningDate.mm, addStudentInfoInDataBase.studentJoiningDate.yyyy);
            printf("\t\t\tNumber of present(out of 180) = %d\n\n",addStudentInfoInDataBase.attendence);
            printf("\n");
        }
    }
    if(found)
    {
       
    }
    else
    {
        printf("\n\t\t\tNo Records");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

// check whether two strings same or not
int is_string_equal(char* str1, char* str2)
{
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') 
  {
    if (str1[i] != str2[i])
        return 0; 
    i++;
  }
  
  if (str1[i] == '\0' && str2[i] == '\0') 
    return 0;
  return 1;
}

// to view te details of students 
void viewStudentDetails()
{
    int found = 0;
    s_StudentInfo addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    unsigned int countStudent = 1;
    currentState("VIEW STUDENT DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\tStudent Count = %d\n\n",countStudent);
        printf("\t\t\tStudent id = %u\n",addStudentInfoInDataBase.student_id);
        printf("\t\t\tStudent Name = %s",addStudentInfoInDataBase.studentName);
        printf("\t\t\tFather Name = %s",addStudentInfoInDataBase.fatherName);
        printf("\t\t\tCourse Name = %s",addStudentInfoInDataBase.courseName);
        printf("\t\t\tStudent Address = %s",addStudentInfoInDataBase.studentAddr);
        printf("\t\t\tStudent Admission Date(day/month/year) =  (%d/%d/%d)\n",addStudentInfoInDataBase.studentJoiningDate.dd,
               addStudentInfoInDataBase.studentJoiningDate.mm, addStudentInfoInDataBase.studentJoiningDate.yyyy);
        printf("\t\t\tNumber of present(out of 180) = %d\n\n",addStudentInfoInDataBase.attendence);
        found = 1;
        ++countStudent;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

// to remove student data
void removeStudent()
{
    int found = 0;
    int studentDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    s_StudentInfo addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    currentState("Delete Student Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter Student ID NO. for delete:");
    scanf("%d",&studentDelete);
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if(addStudentInfoInDataBase.student_id != studentDelete)
        {
            fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}

//to change the login credentials
void updateCredentials(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    currentState("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\ttLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}

//to display main menu
void displayMenu()
{
    int choice = 0;
    do
    {
        currentState("MAIN - MENU");
        printf("\n\n\n\t\t\t1.Add Student");
        printf("\n\t\t\t2.Search Student By Id");
        printf("\n\t\t\t3.Search Student By course");
        printf("\n\t\t\t4.View Student");
        printf("\n\t\t\t5.Search Student By attendence percentage less than");
        printf("\n\t\t\t6.Delete Student");
        printf("\n\t\t\t7.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            searchStudentById();
            break;
        case 3:
            searchStudentByCourse();
            break;
        case 4:
            viewStudentDetails();
            break;
        case 5:
            searchByAttendence();
            break;     
        case 6:
            removeStudent();
            break;
        case 7:
            updateCredentials();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you !!!\n\n\n\n\n");
            exit(1);
            break;   
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again.....");
        }                                            
    }
    while(choice!=0);                                        
}

//attendence Details
void searchByAttendence()
{
    int found = 0;
    int percentage;
    int status;
    int countStudent = 1;
    s_StudentInfo addStudentInfoInDataBase = {1};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    currentState("SEARCH STUDENTS by Attendence percentage");
    
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    
    do
    {
        printf("\n\t\t\tEnter percentage of attendence :");/* code */
        fflush(stdin);
        scanf("%u",&percentage);
        if(percentage<0 || percentage<=100)
        {
            status = 1;
        }
        if(!status)
        {
            printf("\n\t\t\tPlease enter the valid number of presents.\n");
        }
    } while (!status);

    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {   if((((addStudentInfoInDataBase.attendence)/180)*100) <= percentage)
        {
            printf("\n\t\t\tStudent Count = %d\n\n",countStudent);
            printf("\t\t\tStudent id = %u\n",addStudentInfoInDataBase.student_id);
            printf("\t\t\tStudent Name = %s",addStudentInfoInDataBase.studentName);
            printf("\t\t\tFather Name = %s",addStudentInfoInDataBase.fatherName);
            printf("\t\t\tCourse Name = %s",addStudentInfoInDataBase.courseName);
            printf("\t\t\tStudent Address = %s",addStudentInfoInDataBase.studentAddr);
            printf("\t\t\tStudent Admission Date(day/month/year) =  (%d/%d/%d)\n",addStudentInfoInDataBase.studentJoiningDate.dd,
                addStudentInfoInDataBase.studentJoiningDate.mm, addStudentInfoInDataBase.studentJoiningDate.yyyy);
            printf("\t\t\tNumber of present(out of 180) = %d\n\n",addStudentInfoInDataBase.attendence);
            found = 1;
            ++countStudent;
        }
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}


//login function
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int count=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    currentState("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            displayMenu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            count++;
        }
    }
    while(count<=3);
    if(count>3)
    {
        currentState("Login Failed");
        printf("\t\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}


int checkIsFileExists(const char *path)
{
   
    FILE *fp = fopen(path, "rb");
    int status = 0;
    
    if (fp != NULL)
    {
        status = 1;
        
        fclose(fp);
    }
    return status;
}
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char setUsername[] ="ltts folks\n";
    const char setPassword[] ="ltts folks\n";
    sFileHeader fileHeaderInfo = {0};
    status = checkIsFileExists(FILE_NAME);
    if(!status)
    {
        
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            
            strncpy(fileHeaderInfo.password,setPassword,sizeof(setPassword));
            strncpy(fileHeaderInfo.username,setUsername,sizeof(setUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
