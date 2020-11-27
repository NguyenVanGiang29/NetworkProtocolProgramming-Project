#include <stdio.h>
#include <stdlib.h>
#include <string.h>




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



struct highscore{
    int entries;
    char aName[15];
    char score[7];
}top[100],top2[100]; //Array size for high scores txt file

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
    makeQuesEasy();
    for (int i = 0; i < 30; i++)
    {
        printf("%s", questionEasy[i].word);
    }
    makeQuesHard();
    for (int i = 0; i < 30; i++)
    {
        printf("%s", questionHard[i].word);
    }
    makeQuesMod();
    for (int i = 0; i < 30; i++)
    {
        printf("%s", questionMod[i].word);
    }
    
    
  
}