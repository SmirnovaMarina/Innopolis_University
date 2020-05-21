#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE 255

/*global variables*/
FILE *input;
FILE *output;
int error = 0; // for error checking
int numOfFiles = 0;


/*-------------Section with structs that store data---------------*/

/*
    Structures for storing input information about courses
*/
typedef struct courseNode{
    char title[MAX_LINE];
    int labNum;
    int studentNum;

    struct courseNode* next;
    struct courseNode* prev;
}CourseNode;

typedef struct courseList{
    CourseNode* head;
    CourseNode* tail;
} CourseList;

typedef struct coursePtrNode{
    CourseNode* coursePtr;
    char title[MAX_LINE];
    struct coursePtrNode* next;
    struct coursePtrNode* prev;
}CoursePtrNode;

typedef struct coursePtrList{
    CoursePtrNode* head;
    CoursePtrNode* tail;
}CoursePtrList;


/*
    Structures for storing input information about a single person: prof, ta or student
    All lists are doubly linked lists
*/
typedef struct personNode{
    char name[MAX_LINE];
    char id[MAX_LINE]; // for students only
    CoursePtrList* courseList;

    struct personNode* next;
    struct personNode* prev;
} PersonNode;

typedef struct personList{
    PersonNode* head;
    PersonNode* tail;
} PersonList;


/*
    Structures for storing information inside arrays of profs, TAs and courses
*/
typedef struct profInfo{
    char name[MAX_LINE];
    CoursePtrList* courseListPI;
    char untrainedCourse[MAX_LINE];
    char trainedCourse[2][MAX_LINE];
} ProfInfo;

typedef struct taInfo{
    char name[MAX_LINE];
    CoursePtrList* courseListTAI;
    int labs[4];
    char labTitle[4][MAX_LINE];
} TAInfo;

typedef struct courseInfo{
    char title[MAX_LINE];
    CourseNode* coursePtr;
    ProfInfo* profPtr;
    TAInfo* taPtrArray[10];
    int assignedLabs;
    int isStudentAssigned;
    PersonList* unassignedStudents;
} CourseInfo;


/*global variables*/
CourseList* courseList = NULL;
PersonList* profList = NULL;
PersonList* taList = NULL;
PersonList* studentList = NULL; 

int people = 0; // for counting profs and TAs
int profNum = 0; 
int taNum = 0;
int courseNum = 0;

CourseInfo* courseInfoArray = NULL;
ProfInfo* profArray = NULL;
ProfInfo* profArrayCopy = NULL;
TAInfo* taArray = NULL;
TAInfo* taArrayCopy = NULL;

char curCourse[MAX_LINE] = ""; // current course to be processed during tha main algorithm of arranging profs and TAs
int points = 0; // badness points




/*----------------Section with functions for creating structures------------*/

CourseNode* createCourse(char* title, int labs, int students)
{
    CourseNode* new = NULL;
    new = (CourseNode*)malloc(sizeof(CourseNode));
    strcpy(new->title, title);
    new->labNum = labs;
    new->studentNum = students;
    new->next = NULL;
    new->prev = NULL;

    return new;
}

PersonNode* createPerson(char* name, char* id, CoursePtrList* coursePtrList)
{   
    PersonNode* new = NULL;
    new = (PersonNode*)malloc(sizeof(PersonNode));
    strcpy(new->name, name);
    strcpy(new->id, id);
    new->courseList = coursePtrList; 
    new->next = NULL;
    new->prev = NULL;

    return new;
}

CoursePtrNode* createPtrNode(CourseNode* course, char* title)
{
    CoursePtrNode* new = NULL;
    new = (CoursePtrNode*)malloc(sizeof(CoursePtrNode));
    new->next = NULL;
    new->prev = NULL;
    new->coursePtr = course;
    strcpy(new->title, title);

    return new;
}

CoursePtrList* createPtrList()
{
    CoursePtrList* list = (CoursePtrList*)malloc(sizeof(CoursePtrList));
    list->head = createPtrNode(NULL, "head");
    list->tail = createPtrNode(NULL, "tail");
    list->head->next = list->tail;
    list->tail->prev = list->head;

    return list;
}

CourseList* createCourseList()
{
    CourseList* list = (CourseList*)malloc(sizeof(CourseList));
    list->head = createCourse("head", 0, 0);
    list->tail = createCourse("tail", 0, 0);
    list->head->next = list->tail;
    list->tail->prev = list->head;

    return list;
}

PersonList* createPersonList()
{
    PersonList* list = (PersonList*)malloc(sizeof(PersonList));
    list->head = createPerson("head", "", NULL);
    list->tail = createPerson("tail", "", NULL);
    list->head->next = list->tail;
    list->tail->prev = list->head;

    return list;
}

void createProfsArray()
{
    if (profNum > 0){
        profArray = (ProfInfo*)calloc(profNum, sizeof(ProfInfo));
        profArrayCopy = (ProfInfo*)calloc(profNum, sizeof(ProfInfo));
        PersonNode* cur = profList->tail->prev;
        
        for (int i = 0; i<profNum; i++){
            strcpy(profArray[i].name, cur->name);
            profArray[i].courseListPI = cur->courseList;
            strcpy(profArray[i].untrainedCourse, "");
            strcpy(profArray[i].trainedCourse[0], ""); 
            strcpy(profArray[i].trainedCourse[1], "");

            strcpy(profArrayCopy[i].name, cur->name);
            profArrayCopy[i].courseListPI = cur->courseList;
            strcpy(profArrayCopy[i].untrainedCourse, "");
            strcpy(profArrayCopy[i].trainedCourse[0], ""); 
            strcpy(profArrayCopy[i].trainedCourse[1], "");
            cur = cur->prev;
        }
    }
    else{
        profArray = NULL;
        profArrayCopy = NULL;
    }
}

void createTAArray()
{
    if (taNum >0){
        taArray = (TAInfo*)calloc(taNum, sizeof(TAInfo));
        taArrayCopy = (TAInfo*)calloc(taNum, sizeof(TAInfo));

        PersonNode* cur = taList->tail->prev;
        for (int i = 0; i<taNum; i++){
            strcpy(taArray[i].name, cur->name);
            taArray[i].courseListTAI = cur->courseList;

            strcpy(taArrayCopy[i].name, cur->name);
            taArrayCopy[i].courseListTAI = cur->courseList;
            for (int j = 0; j<4; j++){
                strcpy(taArray[i].labTitle[j], "");
                strcpy(taArrayCopy[i].labTitle[j], "");
            }
            cur = cur->prev;
        }
    }
    else{
        taArray = NULL;
        taArrayCopy = NULL;
    }
}

void createCourseArray()
{
    if (courseNum > 0){
        courseInfoArray = (CourseInfo*) calloc(courseNum, sizeof(CourseInfo));
        CourseNode* cur = courseList->tail->prev;

        for (int i = 0; i<courseNum; i++){

            strcpy(courseInfoArray[i].title, cur->title);
            courseInfoArray[i].coursePtr = cur;
            courseInfoArray[i].profPtr = NULL;
            for (int j = 0; j<10; j++){
                courseInfoArray[i].taPtrArray[j]  = NULL;
            }
            courseInfoArray[i].unassignedStudents = NULL;
            courseInfoArray[i].isStudentAssigned = 0;
            courseInfoArray[i].assignedLabs = 0;
            cur = cur->prev;
        }
    }
    else{
        courseInfoArray = NULL;
    } 
}



/*------------------Section with functions for adding elements
                    to list structures--------------*/

void addPointerNode(CoursePtrNode* node, CoursePtrList* list)
{
    node->next = list->head->next;
    node->prev = list->head;
    list->head->next->prev = node;
    list->head->next = node;
}

void addCourse(CourseNode* node)
{
    node->next = courseList->head->next;
    node->prev = courseList->head;
    courseList->head->next->prev = node;
    courseList->head->next = node;
}

void addPerson(PersonNode* node, PersonList* list)
{
    node->next = list->head->next;
    node->prev = list->head;
    list->head->next->prev = node;
    list->head->next = node;
}



/*------------------Section with functions for freeing the memory
                            allocated to structures---------------*/

void freeCourseList()
{
    if (courseList != NULL){
        CourseNode* cur = courseList->tail->prev;
        while (strcmp(cur->title, "head") != 0){
            cur = cur->prev;
            free(cur->next);
        }
        free(courseList);
        courseList = NULL;
    }   
}

void freePerson(PersonNode* node)
{
    if (node != NULL){
        if (node->courseList != NULL){
            CoursePtrNode* cur = node->courseList->tail->prev;
            while(strcmp(cur->title, "head")!=0){
                cur = cur->prev;
                free(cur->next);
            }
            free(node->courseList);
            free(node);
            node = NULL;
        }
    }   
}

void freePersonList(PersonList* list)
{
    if (list != NULL){
        PersonNode* cur = list->tail->prev; 
        while (strcmp(cur->name, "head") != 0){    
            cur = cur->prev;
            freePerson(cur->next);
        }
        free(list);
        list = NULL;
    }
}

void freeCourseArray(){
    if (courseInfoArray != NULL){
        for (int i = 0; i<courseNum; i++){
            freePersonList(courseInfoArray[i].unassignedStudents);
        }
        courseInfoArray = NULL;
    } 
}




/*------------------Section with functions for debugging-----------*/

void printList(CourseList* cList, PersonList* pList, CoursePtrList* ptrList)
{
    if (pList != NULL){
        PersonNode* cur = pList->head->next;
        while(cur->next != NULL){
            printf("%s %s\n",cur->name, cur->id);
            printList(NULL, NULL, cur->courseList);
            cur = cur->next;
        }
    }
    if (cList != NULL){
        CourseNode* cur = cList->head->next;
        while(cur->next != NULL){
            printf("%s\n",cur->title);
            cur = cur->next;
        }
    }
    if (ptrList != NULL){
        CoursePtrNode* cur = ptrList->head->next;
        while(cur->next != NULL){
            printf("cur title %s\n",cur->title);
            printf("coursePtr title %s\n", cur->coursePtr->title);
            cur = cur->next;
        }
    }
}

void printArrays(int c, int p ,int t)
{
    if (c == 1){
        printf("------courseArray------\n");
        for (int i = 0; i<courseNum; i++){
            printf("%s\n", courseInfoArray[i].title);
            printf(" prof %s\n", courseInfoArray[i].profPtr->name);
            int j = 0;
            while (courseInfoArray[i].taPtrArray[j] != NULL){
                printf("ta is %s\n", courseInfoArray[i].taPtrArray[j]->name);
                j++;
            }
        }
        printf("------the end-------\n");
    }
    if (p == 1){
        printf("-----profsArray------\n");
        for (int i = 0; i<profNum; i++){
            printf("%s\n", profArray[i].name);
            //printList(NULL, NULL, profArray[i].courseListPI);
        }
        printf("------the end-------\n");
    }
    if (t == 1) {
        printf("-------taArray---------\n");
        for (int i = 0; i<taNum; i++){
            printf("%s\n", taArray[i].name);
        }
        printf("------the end-------\n");
    } 
}

void printAttributes(CourseInfo* course, ProfInfo* prof, TAInfo* ta)
{
    if (course != NULL){
        int i = 0;
        printf("prof of %s is %s\n", course->title, course->profPtr->name);
        while (course->taPtrArray[i] != NULL){
            printf("ta is %s\n", course->taPtrArray[i]);
            i++;
        }
        printf("assigned labs %d\n", course->assignedLabs);
        
    }
    if (prof != NULL){
        printf("Prof %s \n", prof->name);
        printf("untrained %s \n", prof->untrainedCourse);
        printf("trained %s %s \n", prof->trainedCourse[0], prof->trainedCourse[1]);
    }
    if (ta != NULL){
        printf("Ta %s \n", ta->name);
        for (int i = 0; i<4; i++){
            printf("lab title %s ", ta->labTitle[i]);
            printf(" labs %d \n", ta->labs[i]);
        }
    }
}

void printListReverse(CourseList* cList, PersonList* pList, CoursePtrList* ptrList)
{
    if (pList != NULL){
        PersonNode* cur = pList->tail->prev;
        while(cur->prev != NULL){
            printf("%s\n",cur->name);
            printListReverse(NULL, NULL, cur->courseList);
            cur = cur->prev;
        }
    }
    if (cList != NULL){
        CourseNode* cur = cList->tail->prev;
        while(cur->prev != NULL){
            printf("%s\n",cur->title);
            cur = cur->prev;
        }
    }
    if (ptrList != NULL){
        CoursePtrNode* cur = ptrList->tail->prev;
        while(cur->prev != NULL){
            printf("cur title %s\n",cur->title);
            printf("coursePtr title %s\n", cur->coursePtr->title);
            cur = cur->prev;
        }
    }
}



/*------------------Section with functions for main algorithm----------------*/

/* 
    Function to determine whether a prof or a TA have 
    the certain course in their list of courses
    Return:
        1 - course is found
        0 - course was not found or the prof or TA does not exist
*/
int findCourse(char *curCourse, ProfInfo* prof, TAInfo* ta)
{
    if (prof != NULL){
        CoursePtrNode* cur = prof->courseListPI->head;
        while (cur != NULL){
            if (strcmp(curCourse, cur->title) == 0){
                return 1;
            }
            cur = cur->next;
        }
        return 0;
    }
    else{
        if (ta != NULL){
            CoursePtrNode* cur = ta->courseListTAI->head;
            while (cur != NULL){
                if (strcmp(curCourse, cur->title) == 0){
                    return 1;
                }
                cur = cur->next;
            }
            return 0;
        }
        else{
            return 0;
        }
        return 0;
    }
}

/*
    Function to count amount of labs that are already assigned to a TA
    Return: 
        amount of labs that are already assigned to a TA
*/
int sumTALabs(TAInfo* ta)
{
    int sum = 0;
    for (int i = 0; i<4; i++){
        sum += ta->labs[i];
    }
    return sum;
}

/*
    Comparator functions that is used in QuickSort of profs
    Return: 
        0 - two profs are "equal"
        1 - prof1 should go after prof2 in the array of profs
        (-1) - prof1 should go after prof2 in the array of profs 
*/
int compareProfs(const void* profArg1, const void* profArg2)
{
    ProfInfo* prof1 = (ProfInfo*) profArg1;
    ProfInfo* prof2 = (ProfInfo*) profArg2;

    int found1 = findCourse(curCourse, prof1, NULL);
    int found2 = findCourse(curCourse, prof2, NULL);

    if (found1 == 1 && found2 == 0){
        return -1;
    }
    if (found1 == 0 && found2 == 1){
        return 1;
    }
    if (found1 == 1 && found2 == 1){
        if (strcmp(prof1->trainedCourse[0], "") !=0){
            return -1;
        }
        else{
            if (strcmp(prof2->trainedCourse[0], "") != 0){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    if (found1 == 0 && found2 == 0){
        return 0;
    }
}

/*
    Comparator functions that are used in QuickSort of TAs
    Return: 
        0 - two TAs are "equal"
        1 - ta1 should go after ta2 in the array of TAs
        (-1) - ta1 should go after ta2 in the array of TAs 
*/
int compareTAs(const void* taArg1, const void* taArg2)
{
    TAInfo* ta1 = (TAInfo*) taArg1;
    TAInfo* ta2 = (TAInfo*) taArg2;

    int found1 = findCourse(curCourse, NULL, ta1);
    int found2 = findCourse(curCourse, NULL, ta2);

    if (found1 == 1 && found2 == 0){
        return -1;
    }
    if (found1 == 0 && found2 == 1){
        return 1;
    }
    if (found1 == 1 && found2 == 1){
        
        // 0 if ta can not teach other courses
        // 1 or -1 if ta can teach other courses
        int otherCourses1 = strcmp(ta1->courseListTAI->head->next->next->title, "tail");
        int otherCourses2 = strcmp(ta2->courseListTAI->head->next->next->title, "tail");
        if (otherCourses1 == 0 && otherCourses2 != 0){
            return -1;
        }
        if (otherCourses1 != 0 && otherCourses2 == 0){
            return 1;
        }
        if (otherCourses1 == 0 && otherCourses2 == 0){
            // both ta1 and ta2 can not teach other courses
            if (sumTALabs(ta1) == 0){
                return -1;
            }
            if (sumTALabs(ta2) == 0){
                return 1;
            }
            if (sumTALabs(ta1)<=sumTALabs(ta2) && sumTALabs(ta1) < 4){
                return 1;
            }
            if (sumTALabs(ta1)>sumTALabs(ta2) && sumTALabs(ta2) < 4){
                return -1;
            }
            if (sumTALabs(ta1)>=4 && sumTALabs(ta2)>=4){
                return 0;
            }
            return 0;
        }
        else{
            // both ta1 and ta2 can teach other courses
            if (sumTALabs(ta1) >= sumTALabs(ta2)){
                return -1;
            }
            if (sumTALabs(ta1)< sumTALabs(ta2)){
                return 1;
            }
            return 0;
        }
    }
    if (found1 == 0 && found2 == 0){
        return 0;
    }
}

/*
    Function to change attributes of a prof in the array of profs
    and in the copy of the array of profs
    If ditachProf is 1: ditach prof from the course and course from the prof
    If ditachProf is 0: attach the prof to the course and the course to the prof
    Return:
        1 - prof is busy(can not teach more courses)
        0 - prof is able to teach more courses
*/
int changeProfAttr(int ditachProf, ProfInfo* prof, ProfInfo* profCopy, CourseInfo* course)
{
    int foundProfCourse = findCourse(curCourse, prof, NULL);
    if (ditachProf == 0){
        if (foundProfCourse == 1){
            if (strcmp(prof->trainedCourse[0], "")==0){
                strcpy(prof->trainedCourse[0], curCourse);
                strcpy(profCopy->trainedCourse[0], curCourse);
                course->profPtr = profCopy;
                return 0;
            }
            else{
                if (strcmp(prof->trainedCourse[1], "")==0){
                    strcpy(prof->trainedCourse[1], curCourse);
                    strcpy(profCopy->trainedCourse[1], curCourse);
                    course->profPtr = profCopy;
                    return 1;
                }
                return 1;
            }
        }
        else{
            if (strcmp(prof->trainedCourse[0], "") == 0){
                strcpy(prof->untrainedCourse, curCourse);
                strcpy(profCopy->untrainedCourse, curCourse);
                course->profPtr = profCopy;
                return 1;
            }
            else{
                return 1;
            }
        }
        return 0;
    }
    else{
        strcpy(prof->untrainedCourse, "");
        strcpy(profCopy->untrainedCourse, "");
        if (strcmp(prof->trainedCourse[0], course->title)==0){
            strcpy(prof->trainedCourse[0], "");
            strcpy(profCopy->trainedCourse[0], "");
        }
        if (strcmp(prof->trainedCourse[1], course->title)==0){
            strcpy(prof->trainedCourse[1], "");
            strcpy(profCopy->trainedCourse[1], "");
        }
        course->profPtr = NULL;
    }   
}

/*
    Function to change attributes of a TA in the array of TAs
    and in the copy of the array of TAs
    If ditachCourse is 1: ditach ta from the course and course from the ta
    If ditachCourse is 0: attach the ta to the course and the course to the ta
    Return:
        -1 - ta is ditached form the course and course is ditached from the ta
        1 - ta is busy(can not have more labs)
        0 - ta is able to carry more labs
*/
int changeTAAttr(int ditachCourse, TAInfo* ta, TAInfo* taCopy, CourseInfo* course)
{
    int foundTACourse = findCourse(course->title, NULL, ta); 
    int pos = 0;
    int neededLabs = 0;
    int i = 0;

    if (foundTACourse == 0 || ditachCourse == 1){
        // ditach  all tas from the course; ditach course from all tas
        course->assignedLabs = 0;
        while (course->taPtrArray[pos] != NULL){
            i = 0;
            while (strcmp(course->taPtrArray[pos]->labTitle[i], course->title) != 0 && i<4){
                i += 1;
            }

            if (i < 4){
                strcpy(course->taPtrArray[pos]->labTitle[i], "");
                course->taPtrArray[pos]->labs[i] = 0;
            }
            course->taPtrArray[pos] = NULL;
            pos += 1;
        }
        pos = 0;
        
        // ditach current ta and tas from taArray
        for(int j = 0; j<taNum; j++){
            pos = 0;
            while (strcmp(taArray[j].labTitle[pos], course->title) != 0 && pos<4){
                pos += 1;
            }   
            if (pos < 4){
                strcpy(taArray[j].labTitle[pos], "");
                taArray[j].labs[pos] = 0;
            }
        }
        return -1;
    }

    // change attributes of the ta
    while (pos<4 && strcmp(ta->labTitle[pos], "") != 0){
        pos += 1;
    }
    if (pos<4){
        strcpy(ta->labTitle[pos], course->title);
        strcpy(taCopy->labTitle[pos], course->title);
        neededLabs = course->coursePtr->labNum - course->assignedLabs;
        if (neededLabs <= 4-sumTALabs(ta)){
            ta->labs[pos] = neededLabs;
            taCopy->labs[pos] = neededLabs;
        }
        else{
            taCopy->labs[pos] = 4 - sumTALabs(ta);
            ta->labs[pos] = 4 - sumTALabs(ta);    
        }
        course->assignedLabs += ta->labs[pos];
    }

    // change attributes of the course
    pos = 0;
    while (pos < 10 && course->taPtrArray[pos] != NULL){
        pos += 1;
    }
    if (pos<10){
        course->taPtrArray[pos] = taCopy;
    }

    if (sumTALabs(ta)==4){
        return 1;
    }
    else{
        return 0;
    }   
}

/*
    Method to assign profs and TAs to courses.
    The greedy approach is used to choose the best variant from 
    the array of profs and the array of TAs by picking the first
    element from these arrays after QuickSort performed on them. 

    Copies of profArray and taArray are used to save the initial 
    order of people in them and to assign correct pointers to elements.
*/
void mainAlgorithm()
{
    ProfInfo* startPosProfArray = NULL;
    TAInfo* startPosTAArray = NULL;

    if (profArray != NULL){
        startPosProfArray = &profArray[0];
    }
    if (taArray != NULL){
        startPosTAArray = &taArray[0];
    }

    int startIndexProfArray = 0;
    int startIndexTAArray = 0; 

    int freeTAs = 0;
    int isBusyProf = 0;
    int isBusyTA = 0;

    int bestProfIndex = 0;
    int bestTAIndex = 0;

    int profWasDitached = 0;
    int taWasDitached = 0;

    for (int i = 0; i<courseNum; i++){
        isBusyProf = 0;
        isBusyTA = 0;

        // qsort profs; pick the best one
        strcpy(curCourse, courseInfoArray[i].title);
        if (profNum - startIndexProfArray >= 1){
            qsort(startPosProfArray, profNum-startIndexProfArray, sizeof(ProfInfo), compareProfs);
            bestProfIndex = 0;
            while(bestProfIndex<profNum && strcmp(profArrayCopy[bestProfIndex].name,startPosProfArray->name)!=0){
                bestProfIndex += 1;
            }
            if (bestProfIndex >= profNum){
                bestProfIndex -= 1;
            }
            // profArray[0] elem is the best var 
            // change parameters of the best prof
            isBusyProf = changeProfAttr(0,startPosProfArray, &profArrayCopy[bestProfIndex], &courseInfoArray[i]);
            if (isBusyProf == 1){
                startIndexProfArray += 1;
                startPosProfArray += 1;
            }
        }

        //qsort tas; pick the best one
        if (courseInfoArray[i].profPtr != NULL){           
            if (taNum - startIndexTAArray >= 1){
                while ((taNum - startIndexTAArray >= 1) && courseInfoArray[i].coursePtr->labNum - courseInfoArray[i].assignedLabs > 0 && isBusyTA != -1){

                    qsort(startPosTAArray, taNum-startIndexTAArray, sizeof(TAInfo), compareTAs);

                    bestTAIndex = 0;
                    while(bestTAIndex<taNum && strcmp(taArrayCopy[bestTAIndex].name,startPosTAArray->name)!=0){
                        bestTAIndex += 1;
                    }
                    if (bestTAIndex >= taNum){
                        bestTAIndex -= 1;
                    }

                    // taArray[0] is the best var
                    // change best ta attributes
                    isBusyTA = changeTAAttr(0,startPosTAArray, &taArrayCopy[bestTAIndex], &courseInfoArray[i]);
                    if (isBusyTA != -1){
                        if (isBusyTA == 1){
                            startIndexTAArray += 1;
                            startPosTAArray += 1;
                        }
                    }   
                }
                if (courseInfoArray[i].coursePtr->labNum - courseInfoArray[i].assignedLabs > 0){
                    // if not all of labs of the course were assigned,
                    // then there are no available TAS and the course cannot be run
                    if (startIndexTAArray >= taNum){
                        startIndexTAArray -= 1;
                        startPosTAArray -= 1;
                    }
                    // ditach TAs and the prof of this course
                    changeTAAttr(1, startPosTAArray, &taArrayCopy[bestTAIndex], &courseInfoArray[i]);
                    startIndexTAArray = 0;
                    startPosTAArray = &taArray[0];

                    if (startIndexProfArray >= profNum){
                        startIndexProfArray -= 1;
                        startPosProfArray -= 1;
                    }
                    changeProfAttr(1, startPosProfArray, &profArrayCopy[bestProfIndex], &courseInfoArray[i]);
                   
                    if (isBusyProf == 1){
                        startIndexProfArray -= 1;
                        startPosProfArray -= 1;
                    }
                }
            }
            else{
                //no more unassigned TAs
                if (startIndexProfArray >= profNum){
                    startIndexProfArray -= 1;
                    startPosProfArray -= 1;
                }
                changeProfAttr(1, startPosProfArray, &profArrayCopy[bestProfIndex], &courseInfoArray[i]);
                profWasDitached = 1;
            }
        }
    }
}




/*---------------Section with functions for reading input--------------*/

/*
    Function to determine whether a character is a letter
*/
int isALetter(char ch)
{
    int code = (int)ch;
    if(((code >= 65) && (code<=90))||((code >= 97) && (code<=122))){
        return 1;
    }
    return 0;
}

/*
    Function to determine whether a character is a digit
*/
int isADigit(char ch){
    int code = (int)ch;
    if((code >= 48) && (code<=57)){
        return 1;
    }
    return 0;
}

/*
    Function to determine whether a character is a space
*/
int isASpace(char ch)
{
    if (ch == ' '){
        return 1;
    }
    return 0;
}

/*
    Function to determine whether a character is a new line char
*/
int isANewLine(char ch)
{
    if (ch == '\n'){
        return 1;
    }
    return 0;
}

/*
    Function to determine whether a character is an EOF char
*/
int isEOF(char ch)
{
    if (ch == EOF){
        return 1;
    }
    return 0;
}

/*
    Function to determine whether a character is not a digit, " ", "\n", EOF 
*/
int isInvalidChar(char ch)
{
    if (isADigit(ch)==0 && isANewLine(ch)==0 && isASpace(ch)==0 && isALetter(ch)==0 && isEOF(ch)==0){
        return 1;
    }
    return 0;
}

/*
    Function to determine whether a character is a P, T or S
*/
int isPTS(char ch)
{
    if (ch == 'P' || ch == 'T' || ch == 'S'){
        return 1;
    }
    return 0;
}

/*
    Function to determine whether the course is unique in the list of all courses
    Return: 
        1 - unique
        0 - not unique
*/
int checkCourseUniqueness(char* courseTitle, CoursePtrNode* node, CoursePtrList* list)
{
    if (node == NULL){
        CourseNode* cur = courseList->head->next;
        while (strcmp(cur->title, "tail") != 0){
            if (strcmp(cur->title, courseTitle) == 0){
                return 0;
            }
            cur = cur->next;
        }
        return 1;
    }
    else{
        CoursePtrNode* cur = list->head;
        if (cur != NULL){
            cur = cur->next;
            while (strcmp(cur->title, "tail")!=0){
                if (strcmp(cur->title, courseTitle)==0){
                    return 0;
                }
                cur = cur->next;
            }
            return 1;
        }
    }
}

/*
    Function to read a single line of courses and check validity of it
    Return: 
        the last symbol of the line
*/
char readCourseLine()
{
    char ch;
    char segment[MAX_LINE] = "";
    int i;
    int segmentNum = 0;
    char title[MAX_LINE] = "";
    long int labNum, stNum;
    char *endPtr;
    int isUnique = 0;

    do{
        strcpy(segment, "");
        i = -1;
        do{
            ch = getc(input);
            
            if (isInvalidChar(ch) == 1){
                error = 1;
                break;
            }

            if (isANewLine(ch)!=1 && isASpace(ch)!=1 && isEOF(ch)!=1){
                i++;
                segment[i] = ch;
            }
            if (segmentNum == 0){
                if (isALetter(segment[i]) != 1){
                    error = 1;
                    break;
                }
            }
            if (segmentNum > 0){
                if (isADigit(segment[i]) != 1){
                    error = 1;
                    break;
                }
            }
            
        }while(ch != EOF && isASpace(ch) != 1 && isANewLine(ch) != 1);
        
        segment[i+1] = '\0';
        segmentNum++;
        if (error == 0){
            if (segmentNum == 1){
                strcpy(title, segment);
            }

            if (segmentNum == 2){
                if (segment[0] == '0'){
                    error = 1;
                }
                else{
                    labNum = strtol(segment, &endPtr, 10);
                    if (labNum < 1){
                        error = 1;
                    }
                }
            }

            if (segmentNum == 3){
                if (segment[0] == '0'){
                    error = 1;
                }
                else{
                    stNum = strtol(segment, &endPtr, 10);
                    if (stNum < 1){
                        error = 1;
                    }
                }
            }
        }
    }while(ch != EOF && isANewLine(ch) != 1 && error == 0);

    if (segmentNum>1 && isPTS(title[0])==1 && title[1]=='\0'){
        error = 1;
    }

    if (segmentNum == 1){
        if (!(segment[0] == 'P' && segment[1] == '\0')){
            error = 1;
        }      
    }
    if (segmentNum > 1 && title[0] == 'P' && title[1] == '\0'){
        error = 1;
    }
    if (segmentNum == 2 || segmentNum>3){
        error = 1;
    }

    isUnique = checkCourseUniqueness(title, NULL, NULL);
    if (isUnique == 0){
        error = 1;
    }

    if (error == 0){
        if (!(segment[0] == 'P' && segment[1] == '\0')){
            CourseNode* node = createCourse(title, (int)labNum, (int)stNum);
            addCourse(node);   
        }    
    }
    if (segment[0] == 'P' && segment[1] == '\0'){
        ch = 'P';
    }
    
    return ch;
}

/*
    Method to read all courses
*/
void readCourses()
{
    char ch;
    courseNum = 0;

    do {
        ch = readCourseLine();
        courseNum += 1;
    }while(ch !='P' && isEOF(ch)!=1 && error == 0);
}

/*
    Function to determine whether name of a person is unique in the list of profs or TAs 
    according to the status of the person 
    Return:
        1 - unique
        0 - not unique
*/
int checkPersonUniqueness(char* nameArg, PersonList* list)
{
    PersonNode* curPerson = list->head->next;
    while (strcmp(curPerson->name, "tail") != 0){
        if (strcmp(curPerson->name, nameArg) == 0){
            return 0;
        }
        curPerson = curPerson->next;
    }
    return 1;
}

/*
    Function to read a single line with information about a prof or a TA
    and check its validity
    Return:
        the last symbol of the line
*/
char readProfAndTALine(PersonNode* node)
{
    char ch;
    char segment[MAX_LINE];
    int i;
    int segmentNum = 0;

    char name[MAX_LINE] = "";
    char surname[MAX_LINE] = "";
    char course[MAX_LINE] = "";
    CoursePtrList* list;

    int isListCreated = 0;
    int isCourseUnique = 0;

    do{
        strcpy(segment, "");
        i = -1;
        do{
            ch = getc(input);
            if (isInvalidChar(ch) == 1){
                error = 1;
                break;
            }

            if (isANewLine(ch)!=1 && isASpace(ch)!=1 && isEOF(ch)!=1){
                i++;
                segment[i] = ch;
                
            }
            if (isALetter(segment[i]) != 1){
                error = 1;
                break;
            }
            
        }while(ch != EOF && isASpace(ch) != 1 && isANewLine(ch) != 1);
        
        segment[i+1] = '\0';
        segmentNum++;
        if (error == 0){
            if (segmentNum == 1){
                
                strcpy(name, segment);
            }
            if (segmentNum == 2){
                if (isPTS(segment[0])==1 && segment[1]=='\0'){
                    error = 1;
                }
                else{
                    strcpy(surname, segment);
                    list = createPtrList();
                    isListCreated = 1;
                }
            }
            if (segmentNum > 2){
                if (isPTS(segment[0])==1 && segment[1]=='\0'){
                    error = 1;
                }
                else{
                    CoursePtrNode* ptrNode = createPtrNode(NULL, segment);
                    isCourseUnique = checkCourseUniqueness(segment, ptrNode, list);
                    if (isCourseUnique == 0){
                        error = 1;
                    }
                    else{
                        addPointerNode(ptrNode, list);
                    }
                }
            }
        }
    
    }while(isEOF(ch) != 1 && isANewLine(ch) != 1 && error == 0);
    
    if (segmentNum > 1 && isPTS(name[0])==1 && name[1] == '\0'){
        error = 1;
    }
    if (segmentNum == 1){
        if (!(name[0] == 'T' && name[1] == '\0') && !(name[0] == 'S' && name[1] == '\0')){
            error = 1;
        }
        if (name[0] == 'T' && name[1] == '\0'){
            ch = 'T';
        }
        if (name[0] == 'S' && name[1] == '\0'){
            ch = 'S';
        }
    }
    if (segmentNum == 2){
        error = 1;
    }

    if (error == 0){
        char space[] = {" "};
        strcat(name, space);
        strcat(name, surname);
        strcpy(node->name, name);
        if (isListCreated == 1){
            node->courseList = list;
        }
        else{
            node->courseList = NULL;
        }
    }
    return ch;
}

/*
    Function to determine whether a course of the person appears in the common list of courses
    Return:
        1 - appears
        0 - there is no such course
*/
int checkCourses(PersonNode* personNode)
{ 
    int found;
    CoursePtrNode* curPersonCourse = personNode->courseList->head;
    CourseNode* curCourse;
    while (curPersonCourse != NULL){
        curPersonCourse = curPersonCourse->next;
        if (curPersonCourse != NULL){
            curCourse = courseList->head;
            found = 0;

            while(curCourse != NULL){
                curCourse = curCourse->next;
                if (curCourse != NULL){
                    if (strcmp(curCourse->title, curPersonCourse->title) == 0){
                        found = 1;
                        curPersonCourse->coursePtr = curCourse;
                    }
                }
            }
            if (found == 0){
                return 0;
            }
        }
    }
    return 1;
}

/*
    Function to read profs and TAs
    Return: 
        the last symbol before students input
*/
char readProfAndTA(PersonList* list)
{
    char ch;
    int found = 0;
    people = 0;

    do {
        PersonNode* new = createPerson("", "", NULL);
        ch = readProfAndTALine(new);
        if (error == 0){
            if (ch != 'T' && ch != 'S'){

                if (checkPersonUniqueness(new->name, list) != 1){
                    error = 1;
                }
                if (new->courseList == NULL){
                    error = 1;
                }

                found = checkCourses(new);
                if (found == 0){
                    error = 1;
                }

                if (error == 0){
                    addPerson(new, list);
                    people += 1; 
                }       
            }
            else{
                free(new->courseList);
                free(new);
                new = NULL;
            }
        }  
        else{
            // free memory from new and its list of courses
            free(new->courseList);
            free(new);
            new = NULL;
        }
    }while((ch !='T' && ch != 'S') && isEOF(ch)!=1 && error == 0);
    
    return ch;
}

/*
    Function to check whether an id of the student is unique in the list of all students
    Return:
        1 - unique
        0 - not unique
*/
int checkIDUniqueness(char* id, PersonList* list)
{
    PersonNode* cur = list->head->next;
    while (strcmp(cur->name, "tail") != 0){
        if (strcmp(cur->id, id) == 0){
            return 0;
        }
        cur = cur->next;
    }
    return 1;
}

/*
    Function to read a single line of input of students and check its validity
    Return:
        the last symbol of the line
*/
char readStudentLine(PersonNode* node)
{
    char ch = 0;
    char prevCh = 0;
    char segment[MAX_LINE] = "";
    char invalidSegment[MAX_LINE] = "";
    int i;
    int j;
    int segmentNum = 0;

    char name[MAX_LINE] = "";
    char surname[MAX_LINE] = "";
    char id[MAX_LINE] = "";
    char course[MAX_LINE] = "";
    CoursePtrList* list;

    int isListCreated = 0;
    int isCourseUnique = 0;
    do{
        strcpy(invalidSegment, "");
        strcpy(segment, "");
        i = -1;
        j = -1;
        do{
            prevCh = ch;
            ch = getc(input);
            if (isInvalidChar(ch) == 1){
                error = 1;
            
                break;
            }
            if (isANewLine(ch)==0 || isASpace(ch)==0){
                j++;
                invalidSegment[j] = ch;
            }
            if (isANewLine(ch)!=1 && isASpace(ch)!=1 && isEOF(ch)!=1){
                i++;
                segment[i] = ch;      
            }
            if (i >= 0){
                if (segmentNum <= 1 && isALetter(segment[i])==0){
                    
                    error = 1;
                }
            }
             
        }while(isEOF(ch) != 1 && isASpace(ch) != 1 && isANewLine(ch) != 1);
        
        if ((isANewLine(prevCh) == 1 || isASpace(prevCh) == 1) && isEOF(ch) == 1){
            
            error = 1;
        }

        segment[i+1] = '\0';
        segmentNum++;
        if (error == 0){
            if (segmentNum == 1){
                if (isPTS(segment[0])==1 && segment[1] == '\0'){ 
                    error = 1;
                }
                else{
                    strcpy(name, segment);
                }   
            }

            if (segmentNum == 2){
                if (isPTS(segment[0]) == 1 && segment[1] == '\0'){
                    error = 1;;
                }
                else{
                    strcpy(surname, segment);
                }
            }

            if (segmentNum == 3){
                if (segment[5] == '\0' && segment[4] != '\0'){
                    strcpy(id, segment);
                    list = createPtrList();
                    isListCreated = 1;
                }
                else{
                    error = 1;
                }
            }

            if (segmentNum > 3 && error == 0){
                if (isPTS(segment[0])==1 && segment[1]=='\0'){
                    error = 1;
                }
                else{
                    CoursePtrNode* ptrNode = createPtrNode(NULL, segment);
                    isCourseUnique = checkCourseUniqueness(segment, ptrNode, list);
                    if (isCourseUnique == 0){
                        error = 1;
                    }
                    else{
                        addPointerNode(ptrNode, list);
                    }
                }
            }
        }
        
    }while(ch != EOF && isANewLine(ch) != 1 && error == 0);

    if (segmentNum == 1 && invalidSegment[0]!=EOF){
        error = 1;
    }
    else{
        if (segmentNum < 4 && segmentNum > 1){
            error = 1;
        }
    }

    if (error == 0){
        char space[] = {" "};
        strcat(name, space);
        strcat(name, surname);
        strcpy(node->name, name);
        strcpy(node->id, id);
        if (isListCreated == 1){
            node->courseList = list;
        }
        else {
            if (invalidSegment[0]!=EOF){
                node->courseList = NULL;
                error = 1;
            }
        }
    }

    return ch;
}

/*
    Method to read students input
*/
void readStudent(PersonList* list)
{
    char ch = 0;
    int found = 0;

    do {
        PersonNode* new = createPerson("", "", NULL);
        ch = readStudentLine(new);
        //printf("er after line %d\n", error);
        if (error == 0){
            //printf("name %d\n", (int)new->name[1]);
            if (strcmp(new->name, " ")!= 0){
                if (checkIDUniqueness(new->id, list) != 1){
                    error = 1;
                    freePerson(new);
                }
                found = checkCourses(new);
                if (found == 0){
                    
                    error = 1;
                    freePerson(new);
                }
                if (error == 0){
                    addPerson(new, list);
                }
            }
            else{
                freePerson(new);
            }
            
        }
        else{
            // free memory from new and its list of courses
            freePerson(new);
        }
    }while(isEOF(ch)!=1 && error == 0);
}



/*--------------- Section with print functions --------------*/

/*
    Function to determine whether a student selects a certain course
    Return:
        1 - selects
        0 - does not select
*/
int isStudentAssigned(PersonNode* student, CourseInfo* course)
{
    CoursePtrNode* curStudentCourse = student->courseList->head->next;

    while(curStudentCourse != NULL){
        if (strcmp(curStudentCourse->title, course->title)==0){
            return 1;
        }
        curStudentCourse = curStudentCourse->next;
    }
    return 0;
}

/*
    Function to determine whether a course is selected by any student
    Return:
        1 - selected
        0 - not selected
*/
int isAnyStudAssigned(CourseInfo* course)
{
    PersonNode* cur = studentList->head->next;
    while (strcmp(cur->name, "tail") != 0){
        if (isStudentAssigned(cur, course) == 1){
            return 1; 
        }
        cur = cur->next;
    }
    return 0;
}

/*
    Method to build lists of unassigned students for each course
*/
void composeUnassignedStudentLists()
{
    PersonNode* curStudent;
    int found = 0;
    int countStudents = 0;

    for (int i = 0; i<courseNum; i++){
        courseInfoArray[i].unassignedStudents = createPersonList();
        countStudents = 0;
        curStudent = studentList->tail->prev;

        while (strcmp(curStudent->name, "head") != 0){
            found = isStudentAssigned(curStudent, &courseInfoArray[i]);

            if (found == 1){
                if (countStudents >= courseInfoArray[i].coursePtr->studentNum){
                    PersonNode* newUnassignedStudent = createPerson(curStudent->name, curStudent->id, NULL);
                    addPerson(newUnassignedStudent, courseInfoArray[i].unassignedStudents); 
                }
                if (courseInfoArray[i].profPtr == NULL){
                    PersonNode* newUnassignedStudent = createPerson(curStudent->name, curStudent->id, NULL);
                    addPerson(newUnassignedStudent, courseInfoArray[i].unassignedStudents);
                }
                countStudents += 1;
            }
            curStudent = curStudent->prev;   
        }
    }
}

/*
    Method to print students that are assigned to a course
*/
void printStudentList(CourseInfo* course)
{   
    PersonNode* curStudent = studentList->tail->prev;
    int found = 0;
    int countStudents = 0;
    
    while(strcmp(curStudent->name, "head") != 0){

        found = isStudentAssigned(curStudent, course);
        if (found == 1){
            if (countStudents < course->coursePtr->studentNum){
                fprintf(output,"%s %s\n",curStudent->name, curStudent->id);
                printf("%s %s\n",curStudent->name, curStudent->id);
            }
            countStudents += 1;
        }
        curStudent = curStudent->prev;
    }
}

/*
    Method to print information about a single course: title, assigned prof, assigned TAs, assigned students
*/
void printCourseInfo(CourseInfo* course)
{
    course->isStudentAssigned = isAnyStudAssigned(course);

    if (course->profPtr != NULL && course->coursePtr->labNum - course->assignedLabs == 0){
        fprintf(output,"%s\n",course->title);
        
        fprintf(output, "%s\n", course->profPtr->name);

        int i = 0;
        int countLabs = 0;
        int curLab = 0;

        while (i<10 && course->taPtrArray[i] != NULL){

            countLabs = 0;
            curLab = 0;
            while (curLab < 4 && strcmp(course->title, course->taPtrArray[i]->labTitle[curLab]) != 0 ){
                curLab += 1;
            }
            if (curLab < 4){
                while (countLabs < course->taPtrArray[i]->labs[curLab]){
                    fprintf(output,"%s\n", course->taPtrArray[i]->name);
                    countLabs += 1;
                }
            }  
            i++; 
        }
        fprintf(output, "\n");
    }
}

/*
    Method to print information about all courses
*/
void printAllCoursesInfo()
{
    CourseInfo* cur;
    PersonList* unassignedStudents;

    composeUnassignedStudentLists();

    for (int i = 0; i < courseNum; i++){
        cur = &courseInfoArray[i];
        printCourseInfo(cur);
    }
}

/*
    Method to count badness points and print courses that can not be run
*/
void printEmptyCourses()
{
    for (int i = 0; i < courseNum; i++){
        if (courseInfoArray[i].profPtr == NULL || courseInfoArray[i].coursePtr->labNum - courseInfoArray[i].assignedLabs != 0){
            fprintf(output,"%s cannot be run.\n", courseInfoArray[i].title);
            points += 20; 
        }
    }
}

/*
    Method to count badness points and print profs that dont teach any course
*/
void printUnassignedProfs()
{
    for(int i = 0; i<profNum; i++){
        if (strcmp(profArrayCopy[i].untrainedCourse, "") == 0 && strcmp(profArrayCopy[i].trainedCourse[0], "")==0){
            fprintf(output, "%s is unassigned.\n", profArrayCopy[i].name);
            points += 10;
        }
    }
}

/*
    Method to count badness points and print profs that teach course
    they are not trained for
*/
void printUntrainedProfs()
{
    for(int i = 0; i<profNum; i++){
        if (strcmp(profArrayCopy[i].untrainedCourse, "") != 0){
            fprintf(output, "%s is not trained for %s.\n", profArrayCopy[i].name, profArrayCopy[i].untrainedCourse);
            points += 5;
        }
    }
}

/*
    Method to count badness points and print profs that teach 
    only one course they are trained for
*/
void printProfsInLack()
{   
    for (int i = 0; i<profNum; i++){
        if (strcmp(profArrayCopy[i].trainedCourse[0], "") != 0 && strcmp(profArrayCopy[i].trainedCourse[1], "") == 0){
            fprintf(output, "%s is lacking class.\n", profArrayCopy[i].name);
            points += 5;
        }
    }
}

/*
    Method to count badness points and print TAs that teach less than 4 labs
*/
void printTAsInLack()
{
    int sumOfLabs = 0;
    for (int i = 0; i<taNum; i++){
        sumOfLabs = sumTALabs(&taArrayCopy[i]);
        if (sumOfLabs < 4){
            fprintf(output, "%s is lacking %d lab(s).\n", taArrayCopy[i].name, 4-sumOfLabs);
            points += 2*(4-sumOfLabs);
        }
    }   
}

/*
    Function to find a sudent in the list of unassigned students of the course by its id
*/
int findStudent(char *id, CourseInfo* course)
{
    if (course->unassignedStudents != NULL){
        PersonNode* cur = course->unassignedStudents->tail->prev;
        while (strcmp(cur->name, "head")!=0){
            if (strcmp(cur->id, id)==0){
                return 1;
            }
            cur = cur->prev;
        }
    } 
    return 0;
}

/*
    Method to print students unassigned to any course
*/
void printUnassignedStudents()
{
    if (studentList != NULL){
        PersonNode* cur = studentList->tail->prev;

        while (strcmp(cur->name, "head") != 0){
            for (int i = 0; i<courseNum; i++){
                if (findStudent(cur->id, &courseInfoArray[i])==1){
                    fprintf(output, "%s is lacking %s.\n", cur->name, courseInfoArray[i].title);
                    points += 1;
                } 
            }
            cur = cur->prev;
        }
    }
}

void printBadnessEvents()
{
    printEmptyCourses();
    printUnassignedProfs();
    printUntrainedProfs();
    printProfsInLack();
    printTAsInLack();
    printUnassignedStudents();
    
    fprintf(output, "Total score is %d.", points);
}

void myitoa(int iArg, char *str)
{
    int i = iArg;
    char ch;
    int count = 0;

    do{ 
        ch = (i % 10)+48;
        str[count] = ch;
        i = i / 10;
        count++;
    }while(i>=1);

    str[count] = '\0';
    if (count == 2){
        ch = str[0];
        str[0] = str[1];
        str[1] = ch;
    }
}

void composeInputName(char *fileName, int i)
{
    char fileNum[3] = "";
    char template[MAX_LINE] = "";

    myitoa(i, fileNum);
    strcpy(template, "input");
    strcat(fileName, template);
    strcat(fileName, fileNum);
    strcpy(template, ".txt");
    strcat(fileName, template);
}

void composeOutputName(char *fileName, int i)
{
    char fileNum[3] = "";
    char template[MAX_LINE] = "";
    
    myitoa(i, fileNum);
    strcpy(template, "MarinaSmirnovaOutput");
    strcat(fileName, template);
    strcat(fileName, fileNum);
    strcpy(template, ".txt");
    strcat(fileName, template);
}

/*
    Method to count input files in the current folder
*/
int countFiles()
{
    int last = 0;
    char inputName[12] = "";

    for (int i = 1; i<51; i++){
        strcpy(inputName, "");
        composeInputName(inputName, i);
        input = fopen(inputName, "r");
        if (input != NULL){
            last = i;
        }
        fclose(input);
    }    
    return last;
}

/*
    Main method to read input files and print the result: 
    "Invalid input." or arrangement of profs, TAs and students
*/
void readAndPrint()
{
    char inputName[12] = ""; 
    char outputName[27] = "";  
    int count = 1;
    char ch;

    numOfFiles = countFiles();

    do{
        error = 0;

        strcpy(inputName, "");
        composeInputName(inputName, count);
        input = fopen(inputName, "r");

        // check whether the ith file in directory or not
        if (input != NULL){
            
            points = 0;
            courseList = createCourseList();
            profList = createPersonList();
            taList = createPersonList();
            studentList = createPersonList();

            readCourses();
            courseNum -= 1;
            if (error == 0){
                createCourseArray();
            }
        
            if (error == 0){
                ch = readProfAndTA(profList);
                if (ch != 'T'){
                    error = 1;
                }
                if (error == 0){
                    profNum = people;
                    createProfsArray();
                } 
            }

            if (error == 0){
                ch = readProfAndTA(taList);
                if (ch != 'S'){
                    error = 1;
                }
                
                if (error == 0){
                    taNum = people;
                    createTAArray();
                } 
                
            }
            if (error == 0){
                readStudent(studentList);
            }
            if (error == 0){
                mainAlgorithm();
            }
        }
        else{
            // if there is no input file
            error = 1;
        } 

        if (numOfFiles > 0){
            strcpy(outputName, "");
            composeOutputName(outputName, count);
            output = fopen(outputName, "w");
            if (error == 1){
                fputs("Invalid input.", output);
            }
            else{
                printAllCoursesInfo();
                printBadnessEvents();
            }
            if (input != NULL){
                freeCourseList();   
                freePersonList(profList);
                freePersonList(taList);
                freePersonList(studentList);
                freeCourseArray(courseInfoArray);
                free(profArray); 
                free(profArrayCopy);
                free(taArray); 
                free(taArrayCopy);
            }
        
            fclose(output);
        }
        
        fclose(input);
        count += 1; 
    }while(count <= numOfFiles);

    char fileName[] = "MarinaSmirnovaEmail.txt";
    output = fopen(fileName, "w");
    char email[] = "m.smirnova@innopolis.ru";
    fputs(email, output);
    fclose(output);
}


int main()
{
    readAndPrint();
    return 0;
}