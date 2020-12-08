#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char revertStr[20];
char *strScore;

typedef struct bank{
    char question[120];
    char choiceA[70];
    char choiceB[70];
    char choiceC[70];
    char choiceD[70];
    char answer[5];
}Bank;                                  //Array size for getting questions per level

typedef struct question
{
    char word[1000];
    char answer[5];
}Question;

Bank setEasy[30];
Bank setHard[30];
Bank setMod[30];

Question questionEasy[30];
Question questionHard[30];
Question questionMod[30];


typedef struct score
{
    char level[5];
    char aName[20];
    int  aScore;
    struct score *next;
}score;

score *head = NULL;

void insertScore(char level[5], char aName[20], int aScore){
	score *temp;
	temp=(score *)malloc(sizeof(score));
	strcpy(temp->level, level);
	strcpy(temp->aName, aName);
	temp->aScore = aScore;
	temp->next = head;
	head = temp;
}

void printAll()
{
    score *temp;
    temp = head;
    while(temp)
    {
    	printf("%5s %20s %d",temp->level, temp->aName, temp->aScore);
        printf("\n");
        temp=temp->next;
    }
    printf("\n");
}

void openFileScore(){
	score *user;
	char *level;
	char *aName;
	int score;
	char c;
	int u = 0, p = 0, blank = 0;
	level = (char *)malloc(5);
	aName = (char *)malloc(20);
    FILE *fptr;
	if((fptr=fopen("score.txt","r+"))==NULL){
		printf("Not find%s\n","score.txt");
		return;
	}
	while(1){
		fscanf(fptr,"%s",level);
		fscanf(fptr,"%s",aName);
		fscanf(fptr,"%d",&score);
		if(feof(fptr)) break;
		insertScore(level, aName, score);
	}
	free(level); free(aName);
	fclose(fptr);
}

void writeFileScore(){
	FILE *fptr;
	score *temp;
    temp = head;
    fptr=fopen("score.txt","w+");
    while(temp){
    	fprintf(fptr, "%s %s %d", temp->level, temp->aName, temp->aScore);
    	fprintf(fptr, "\n");
    	temp=temp->next;
    }
    fclose(fptr);
}

void save(){
    score *temp;
    temp = head;
	while(temp != NULL)
    {
    	strcpy(strScore, temp->level);
        strcat(strScore, "\t");
		strcat(strScore, temp->aName);
        snprintf(revertStr,sizeof(revertStr), "%d", temp->aScore);
        strcat(strScore, "\t");
		strcat(strScore, revertStr);
        temp = temp->next;
    }
}

char *special_char_remplace(){

    size_t len, bytesRead;
    char *readedContent;
    FILE* f2;

    f2 = fopen("score.txt", "rb");

    fseek(f2, 0, SEEK_END);
    len = ftell(f2);
    rewind(f2);

    readedContent = (char*) malloc(sizeof(char) * len + 1);
    readedContent[len] = '\0'; // Is needed only for printing to stdout with printf

    bytesRead = fread(readedContent, sizeof(char), len, f2);
    fclose(f2);
    return readedContent;
}


FILE*eBank;
FILE*mBank;
FILE*hBank;
FILE*sBank;
FILE*sBank2;

void doEASYROUND(){ // Gets and stores questions for Easy Round
    if((eBank = fopen("easybank.txt", "r"))==NULL){
        printf("Not find%s\n","easybank.txt");
		return;
    }
    else{
        while(!feof(eBank)){
            for(int x=0; x<30; x++){ // Reads the questions from file
                fgets(setEasy[x].question, 120, eBank);
                fgets(setEasy[x].choiceA, 70, eBank);
                fgets(setEasy[x].choiceB, 70, eBank);
                fgets(setEasy[x].choiceC, 70, eBank);
                fgets(setEasy[x].choiceD, 70, eBank);
                fgets(setEasy[x].answer, 70, eBank);
            }
        }
    }
  
    fclose(eBank);
}

void doMODERATEROUND(){ // Gets and stores questions for Moderate Round
    if((mBank = fopen("moderatebank.txt", "r"))==NULL){
        printf("Not find%s\n","moderatebank.txt");
		return;
    }
    else{
        while(!feof(mBank)){
            for(int x=0; x<30; x++){ // Reads the questions from file
                fgets(setMod[x].question, 120, mBank);
                fgets(setMod[x].choiceA, 70, mBank);
                fgets(setMod[x].choiceB, 70, mBank);
                fgets(setMod[x].choiceC, 70, mBank);
                fgets(setMod[x].choiceD, 70, mBank);
                fgets(setMod[x].answer, 70, mBank);
            }
        }
    }
    fclose(mBank);
}

void doHARDROUND(){ // Gets and stores questions for Hard Round
    if((hBank = fopen("hardbank.txt", "r"))==NULL){
        printf("Not find%s\n","hradbank.txt");
		return;
    }else{
        while(!feof(hBank)){
            for(int x=0;x<30; x++){ // Reads the questions from file
                fgets(setHard[x].question, 120, hBank);
                fgets(setHard[x].choiceA, 70, hBank);
                fgets(setHard[x].choiceB, 70, hBank);
                fgets(setHard[x].choiceC, 70, hBank);
                fgets(setHard[x].choiceD, 70, hBank);
                fgets(setHard[x].answer, 70, hBank);
            }
        }
    }
    fclose(hBank);
    
}

void makeQuesEasy(){
    Question *buff;
    doEASYROUND();
    for (int i = 0; i < 30; i++)
    {
        buff = (Question *)malloc(sizeof(Question));
        strcpy((*buff).word, setEasy[i].question);
        strcat((*buff).word, setEasy[i].choiceA);
        strcat((*buff).word, setEasy[i].choiceB);
        strcat((*buff).word, setEasy[i].choiceC);
        strcat((*buff).word, setEasy[i].choiceD);
        (*buff).word[strlen((*buff).word) - 1] = '\0';
        strcpy((*buff).answer, setEasy[i].answer);
        strcpy(questionEasy[i].word, (*buff).word);
        strcpy(questionEasy[i].answer, (*buff).answer);
        free(buff);
        
    }
}

void makeQuesHard(){
    Question *buff;
    doHARDROUND();
    for (int i = 0; i < 30; i++)
    {
        buff = (Question *)malloc(sizeof(Question));
        strcpy((*buff).word, setHard[i].question);
        strcat((*buff).word, setHard[i].choiceA);
        strcat((*buff).word, setHard[i].choiceB);
        strcat((*buff).word, setHard[i].choiceC);
        strcat((*buff).word, setHard[i].choiceD);
        (*buff).word[strlen((*buff).word) - 1] = '\0';
        strcpy((*buff).answer, setHard[i].answer);
        strcpy(questionHard[i].word, (*buff).word);
        strcpy(questionHard[i].answer, (*buff).answer);
        free(buff);
        
    }
}

void makeQuesMod(){
    Question *buff;
    doMODERATEROUND();
    for (int i = 0; i < 30; i++)
    {
        buff = (Question *)malloc(sizeof(Question));
        strcpy((*buff).word, setMod[i].question);
        strcat((*buff).word, setMod[i].choiceA);
        strcat((*buff).word, setMod[i].choiceB);
        strcat((*buff).word, setMod[i].choiceC);
        strcat((*buff).word, setMod[i].choiceD);
        (*buff).word[strlen((*buff).word) - 1] = '\0';
        strcpy((*buff).answer, setMod[i].answer);
        strcpy(questionMod[i].word, (*buff).word);
        strcpy(questionMod[i].answer, (*buff).answer);
        free(buff);
        
    }
}

int main(){
    char level[5];
    char aName[20];
    int aScore;
    openFileScore();
    strScore = special_char_remplace();
    printf("%s", strScore);

}