#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <time.h>



#define MAXLINE 100
#define MAX_LISTEN_QUEUE 100

int count = 0, check = 0, NumberQuestion = 0, i = 0, point = 0, tus1 = 0, tus2 = 0;
char message[200] = "Goodbye ", code[200], messagePoint[200] = "Bạn đã thua cuộc. Số điểm bạn có là: ";
char level[10];
char *strScore, *AnsRand, *strInstr;
//Account
typedef struct node {
  	char username[20];
	char password[20];
	int status;
	char homepage[200];
	struct node *next;
}node;

node *head = NULL;

//Bank question
typedef struct bank{
    char question[120];
    char choiceA[70];
    char choiceB[70];
    char choiceC[70];
    char choiceD[70];
    char answer[5];
}Bank;                                  //Array size for getting questions per level

//Question
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
            for(int x=0; x<30; x++){ // Reads the questions from file
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
		(*buff).answer[strlen((*buff).answer) - 1] = '\0';
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
		(*buff).answer[strlen((*buff).answer) - 1] = '\0';
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
		(*buff).answer[strlen((*buff).answer) - 1] = '\0';
        strcpy(questionMod[i].word, (*buff).word);
        strcpy(questionMod[i].answer, (*buff).answer);
        free(buff);
        
    }
}

//Function of account


void insert(char username[20], char password[20], int status, char homepage[200]){
	node *temp;
	temp=(node *)malloc(sizeof(node));
	strcpy(temp->username, username);
	strcpy(temp->password, password);
	temp->status = status;
	strcpy(temp->homepage, homepage);
	temp->next = head;
	head = temp;
}

node *find(char name[20]){
   node *current = head;
   if(head == NULL)
	{
      return NULL;
    }
   while(strcmp(current->username, name) != 0){
      if(current->next == NULL){
         return NULL;
      }else {
         current = current->next;
	
      }
   }      
   return current;
}

node *findpass(char pass[20]){
   node *current = head;
   if(head == NULL)
	{
      return NULL;
    }
   while(strcmp(current->password, pass) != 0){
      if(current->next == NULL){
         return NULL;
      }else {
         current = current->next;
      }
   }      
   return current;
}

void printAll()
{
    node *temp;
    temp = head;
    while(temp)
    {
    	printf("%20s %20s %d %200s",temp->username, temp->password, temp->status, temp->homepage);
        printf("\n");
        temp=temp->next;
    }
    printf("\n");
}

void openFile(){
	node *acc;
	char *username;
	char *password;
	char *homepage;
	int status;
	char c;
	int u = 0, p = 0, blank = 0;
	username = (char *)malloc(20);
	password = (char *)malloc(20);
	homepage = (char *)malloc(200);
    FILE *fptr;
	if((fptr=fopen("account.txt","r+"))==NULL){
		printf("Not find%s\n","account.txt");
		return;
	}
	while(1){
		fscanf(fptr,"%s",username);
		fscanf(fptr,"%s",password);
		fscanf(fptr,"%d",&status);
		fscanf(fptr,"%s",homepage);
		if(feof(fptr)) break;
		insert(username, password, status, homepage);
	}
	free(username); free(password);
	fclose(fptr);
}

void writeFile(){
	FILE *fptr;
	node *temp;
    temp = head;
    fptr=fopen("account.txt","w+");
    while(temp){
    	fprintf(fptr, "%s %s %d %s", temp->username, temp->password, temp->status, temp->homepage);
    	fprintf(fptr, "\n");
    	temp=temp->next;
    }
    fclose(fptr);
}

void registerAccount(){
	char username[20];
	char password[20];
	char homepage[200];
	printf("---------Register\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	printf("Password: "); scanf("%s", password);
	printf("\n");
	int choice =0;
	printf("Choice Homepage(IP(choice = 1) or Domain(choice = 2)):\n");
	scanf("%d",&choice);
	
	switch (choice)
	{
	case 1:
		printf("Make IP:");
		scanf("%s",homepage);
		break;
	case 2:
		printf("Make Domain:");
		scanf("%s",homepage);
		break;
	default:
		break;
	}

	if(find(username) != NULL){
	printf("Account existed!");	
	} 
	else{
		insert(username, password, 2, homepage);
		writeFile();
		printf("Successful registration. Activation required.\n");
		// printAll();
	}
	printf("\n");
}

void Activate(){
	char usename[20];
	char password[20];
	char activationcode[20];
	char code[20] = "LTM121216";
	int countlogin = 0;
	printf("TO ACTIVATE ACCOUNT- PLEASE GIVE SOME INFORMATION\n");
	printf("Usename: "); scanf("%s", usename);
	printf("Password:"); scanf("%s",password);
	node *acc = find(usename);
	while (countlogin <5)
	{
		printf("Code:"); scanf("%s", activationcode);
		if(strcmp(activationcode, code) == 0){
			acc->status = 1;
			writeFile();
			printf("Account is activated\n");
			countlogin = 6;
		}else
		{
			printf("Account is not activated\n");
			countlogin +=1;
		}
	}
	if(countlogin == 5){
		acc->status = 0;
		writeFile();
		printf("Activation code is incorrect. Account is blocked\n");
	}
}

node *signin(){
	char username[20];
	char password[20];
	int login_count = 0;
	printf("---------Sign In\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){
		if(acc->status == 0){
			printf("Account has been blocked!\n");
			return NULL;
		}
		do{
		printf("Password: "); scanf("%s", password);
		printf("\n");
		if(strcmp(acc->password,password) == 0){
			printf("Hello %s\n", acc->username);
			return acc;
			}
		else {
			printf("Password is incorrect.Account is blocked\n");
			login_count++;
			}
		}while(login_count < 3);
		if(login_count == 3) {
			printf("Account is blocked\n");
			acc->status = 0;
			writeFile();
			return NULL;
		}
	}
	else{
		printf("Cannot find account\n");
		return NULL; 
	} 
}

void search(){																																																																																		
	char username[20];
	printf("---------Search\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){ 
		if(acc->status = 1){
			printf("Account is active\n");
		}else if(acc->status = 0)
		{
			printf("Account is blocked\n");
		}
		
	}
	else printf("Cannot find account\n");
}

node *signout(){
	char username[20];
	printf("---------Sign Out\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc == NULL){
		printf("Cannot find account\n");
		return NULL;
	}
	else return acc;
}

typedef struct score
{
    char level[5];
    char aName[20];
    int  aScore;
    struct score *next;
}score;

//Function of Score
score *head1 = NULL;

void insertScore(char level[5], char aName[20], int aScore){
	score *temp;
	temp=(score *)malloc(sizeof(score));
	strcpy(temp->level, level);
	strcpy(temp->aName, aName);
	temp->aScore = aScore;
	temp->next = head1;
	head1 = temp;
}

void printAllScore()
{
    score *temp;
    temp = head1;
    while(temp)
    {
    	printf("%5s %20s %d",temp->level, temp->aName, temp->aScore);
        printf("\n");
        temp=temp->next;
    }
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
    temp = head1;
    fptr=fopen("score.txt","w+");
    while(temp){
    	fprintf(fptr, "%s %s %d", temp->level, temp->aName, temp->aScore);
    	fprintf(fptr, "\n");
    	temp=temp->next;
    }
    fclose(fptr);
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
    readedContent[len] = '\0';                      // Is needed only for printing to stdout with printf

    bytesRead = fread(readedContent, sizeof(char), len, f2);
    fclose(f2);
    return readedContent;
}

char *special_char_remplace1(){

    size_t len, bytesRead;
    char *readedContent;
    FILE* f2;

    f2 = fopen("instruction.txt", "rb");

    fseek(f2, 0, SEEK_END);
    len = ftell(f2);
    rewind(f2);

    readedContent = (char*) malloc(sizeof(char) * len + 1);
    readedContent[len] = '\0';                      // Is needed only for printing to stdout with printf

    bytesRead = fread(readedContent, sizeof(char), len, f2);
    fclose(f2);
    return readedContent;
}

void sendMess(char *content, int sockfd, struct sockaddr *servaddr){
	int len, sendBytes;
	  
	len = sizeof(*servaddr);

	sendBytes = send(sockfd, content, strlen(content) +1, 0);

	if(sendBytes < 0){
		perror("Error: \n");
	}
	
}

int CheckString(char a[100]){		
	for(int i = 0; i < strlen(a); i++){
		if(a[i] >= 'A' && a[i] <= 'Z' || a[i] >= 'a' && a[i] <= 'z' || a[i] >= '0' && a[i] <= '9'){
		}else
		{
			return 0;
		}
	}
	return 1;
}

char* Encode(char Str[200]){
	char NewStr[200];
	int count = 0;

	for(int i = 0; i < strlen(Str); i++)
		if(Str[i] >= '0' && Str[i] <= '9'){
			NewStr[count] = Str[i];
			count++;
		}

	for(int i = 0; i < strlen(Str); i++){
		if(Str[i] < '0' || Str[i] > '9'){
			NewStr[count] = Str[i];
			count++;
		}
	}

	NewStr[count] = '\0';
    return strdup(NewStr);
}

int ranDomAns(int a){
    int intRandom;
    srand(time(NULL));
    do{
        intRandom = (rand()%5);

    }while (intRandom == 0 || intRandom == a);
    
    return intRandom;
} 

int changeStrtoInt(char *a){
	int num;

	if(strcmp(a, "A") == 0){
		return num = 1;
	}else if(strcmp(a, "B") == 0)
	{
		return num = 2;
	}
	else if(strcmp(a, "C") == 0)
	{
		return num = 3;
	}
	else if(strcmp(a, "D") == 0)
	{
		return num = 4;
	}
	
}

char *changeInttoStr(int a){
	char *b;
	if(a == 1){
		return b = "A";
	}else if(a == 2)
	{
		return b = "B";
	}
	else if(a == 3)
	{
		return b = "C";
	}
	else if(a == 4)
	{
		return b = "D";
	}
	
}

void swap (Question *a, Question *b) 
{ 
    Question temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
// A function to generate a random permutation of arr[] 
void randomize ( Question arr[], int n ) 
{ 
    srand ( time(NULL) ); 

    for (int i = n-1; i > 0; i--) 
    { 
        int j = rand() % (i+1); 
        swap(&arr[i], &arr[j]); 
    } 
}

pid_t fork(void);


int main(int argc, char* argv[]){

    openFile();
	openFileScore();

	strScore = special_char_remplace();
	strInstr = special_char_remplace1();
	

	pid_t pid;
    int listenfd, connfd, n, portNumber;
    pid_t childpid;
    socklen_t clilen;
    char buff[MAXLINE];
    struct sockaddr_in cliaddr, servaddr;

    portNumber = atoi(argv[1]);


    // construct socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // bind socket to ip address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portNumber);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    listen(listenfd, MAX_LISTEN_QUEUE);

    printf("%s\n", "Server running...waiting for connections.");

	
	makeQuesEasy();
	makeQuesHard();
	makeQuesMod();


    node *acc;

	int option = 0, regis = 0, login = 0, numAns = 0, num = 0;

	char username[20], password[20], chuoi[10] = "abc", chuoi1[100] = "Lựa chọn còn lại: " ;
	

    // communicate with client
    while(1){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
        printf("%s\n", "Received request...");

		if( (pid = fork()) == 0) {           //process in child (forking)
			
			close(listenfd); 	             // child closes listening socket
			
			while(n = recv(connfd, buff, MAXLINE, 0) > 0){

				if(strcmp(buff, "1") == 0 && tus1 == 0 ){
					tus1 = 1;
					option = 1;
					sendMess("--- Đăng kí ---", connfd, (struct sockaddr*) &cliaddr);

				}else if(strcmp(buff, "2") == 0 && tus2 == 0)
				{
					option = 2;
					tus2 = 1;
					tus1 = 1;
					
					sendMess("--- Đăng nhập ---", connfd, (struct sockaddr*) &cliaddr);
				}
				
				else{
					switch (option)
							{
							case 1:
								switch (regis)
								{
								case 0:
									acc = find(buff);
									if(acc == NULL){
										sendMess("Tạo mật khẩu:", connfd, (struct sockaddr*) &cliaddr);
										strcpy(username, buff);
										regis = 1;
										tus1 = 1;
									}else
									{
										tus1 = 1;
										tus2 = 1;
										sendMess("Tên tài khoản đã tồn tại! Hãy thử với tên khác.", connfd, (struct sockaddr*) &cliaddr);
									}								
									break;
								case 1:
									sendMess("Tạo tài khoản thành công.", connfd, (struct sockaddr*) &cliaddr);
									strcpy(password, buff);
									insert(username, password, 1, "123.12");
									writeFile();
									tus1 = 0;
									tus2 = 0;
									option = 0;
									regis = 0;
									break;
								default:
									break;
								}
								break;

							case 2:
								switch (login)
								{
								case 0:
									acc = find(buff);
									if(acc == NULL){
										sendMess("Tên đăng nhập không đúng! Hãy nhập lại.", connfd, (struct sockaddr*) &cliaddr);
									}else{
										sendMess("Mật khẩu:", connfd, (struct sockaddr*) &cliaddr);
										login = 1;
									}
									break;
								case 1:
									if(strcmp(acc->password, buff) == 0){
										sendMess("Đăng nhập thành công.", connfd, (struct sockaddr*) &cliaddr);
										login = 2;

									}else{
									
										sendMess("Sai mật khẩu, hãy nhập lại!", connfd, (struct sockaddr*) &cliaddr);
									}
									break;
								case 2:
									if(strcmp(buff, "2-1") == 0){
										sendMess("--- Ai là triệu phú ---", connfd, (struct sockaddr*) &cliaddr);
										login = 4;
									}
									else if(strcmp(buff, "2-2") == 0){
										sendMess("--- Đổi mật khẩu ---", connfd, (struct sockaddr*) &cliaddr);
										login = 3;
									}									
									else if(strcmp(buff, "2-3") == 0){
										option = 0;
										regis = 0;
										login = 0;
										tus1 = 0;
										tus2 = 0;
										sendMess("Đã đăng xuất.", connfd, (struct sockaddr*) &cliaddr);
									}
									else if(strcmp(buff, "2-4") == 0)
									{
										login = 2;
										sendMess(strScore, connfd, (struct sockaddr*) &cliaddr);
									}else if(strcmp(buff, "2-5") == 0){
										login = 2;
										sendMess(strInstr, connfd, (struct sockaddr*) &cliaddr);
									}
									else
									{
										sendMess("Lựa chọn sai cú pháp. Mời nhập lại (2-1, 2-2, 2-3, 2-4).", connfd, (struct sockaddr*) &cliaddr);
									}
									
									break;
								case 3:
									check = CheckString(buff);
									if(check == 1){
										strcpy(acc->password, buff);
										writeFile();
										login = 2;
										sendMess("Đổi mật khẩu thành công.", connfd, (struct sockaddr*) &cliaddr);
										
									}else
									{
										sendMess("Error", connfd, (struct sockaddr*) &cliaddr);
									}
									break;

								case 4:
									if(strcmp(buff, "D") == 0){
										sendMess("Bạn đã sẵn sàng chưa? (Nhập \"SS\" để bắt đầu)", connfd, (struct sockaddr*) &cliaddr);
										login = 5;
									}else if (strcmp(buff, "BT") == 0)
									{
										sendMess("Bạn đã sẵn sàng chưa? ( Nhập \"SS\" để bắt đầu)", connfd, (struct sockaddr*) &cliaddr);
										login = 7;
									}
									else if (strcmp(buff, "K") == 0)
									{
										sendMess("Bạn đã sẵn sàng chưa? ( Nhập \"SS\" để bắt đầu)", connfd, (struct sockaddr*) &cliaddr);
										login = 9;
									}else
									{
										sendMess("Sai cú pháp!", connfd, (struct sockaddr*) &cliaddr);
									}
									
									
									break;

		//Case 5 + 6 : Question Easy
								case 5:
									if(strcmp(buff, "SS") == 0 || strcmp(buff, "OK") == 0){
										randomize(questionEasy, 30);
										sendMess(questionEasy[i].word, connfd, (struct sockaddr*) &cliaddr);
										login = 6;
									}else if(strcmp(buff, "STOP") == 0){
										insertScore("Dễ", acc->username, point);
										writeFileScore();
										snprintf(chuoi,sizeof(chuoi), "%d", point);
										strcat(messagePoint, chuoi);
										sendMess(messagePoint, connfd, (struct sockaddr*) &cliaddr);
										strcpy(messagePoint, "Bạn đã thua cuộc. Số điểm bạn có là: ");
										point = 0;
										login = 2;
									}else
									{
										sendMess("Sai cú pháp.", connfd, (struct sockaddr*) &cliaddr);
									}
									
									break;

								case 6:
									if(strcmp(buff, "H") == 0){
										num = changeStrtoInt(questionEasy[i].answer);
										numAns = ranDomAns(num);
										AnsRand = changeInttoStr(numAns);
										strcat(chuoi1, questionEasy[i].answer);
										strcat(chuoi1, "\t");
										strcat(chuoi1, AnsRand);
										sendMess(chuoi1, connfd, (struct sockaddr*) &cliaddr);
										strcpy(chuoi1, "Lựa chọn còn lại: ");
									
									}else if(strcmp(buff, "A") != 0 && strcmp(buff, "B") != 0  && strcmp(buff, "C") != 0 && strcmp(buff, "D") != 0){
										sendMess("Nhập sai cú pháp lựa chọn đáp án. Hoặc nhập \"H\" để nhận được sự trợ giúp 50/50. Mời nhập lại!", connfd, (struct sockaddr*) &cliaddr);
									}
									else{
										if(strcmp(buff, questionEasy[i].answer) == 0){
											if(i < 15){	
												i++;
												login = 5;
												point = point + 100;
												sendMess("Đáp án chính xác.", connfd, (struct sockaddr*) &cliaddr);
											}else
											{
												sendMess("Bạn đã trở thành triệu phú. Chúc mừng bạn!", connfd, (struct sockaddr*) &cliaddr);
												point = 0;
												login = 2;
												i = 0;
											}
										}else{
											insertScore("Dễ", acc->username, point);
											writeFileScore();
											snprintf(chuoi,sizeof(chuoi), "%d", point);
											strcat(messagePoint, chuoi);
											sendMess(messagePoint, connfd, (struct sockaddr*) &cliaddr);
											strcpy(messagePoint, "Bạn đã thua cuộc. Số điểm bạn có là: ");
											point = 0;
											login = 2;
											i = 0;
											
										}
									}
					
									break;

		//Case 7 + 8 : Question Mod
								case 7:
									if(strcmp(buff, "SS") == 0 || strcmp(buff, "OK") == 0){
										randomize(questionEasy, 30);
										sendMess(questionMod[i].word, connfd, (struct sockaddr*) &cliaddr);
										login = 8;
									}else if(strcmp(buff, "STOP") == 0){
										insertScore("Trung bình", acc->username, point);
										writeFileScore();
										snprintf(chuoi,sizeof(chuoi), "%d", point);
										strcat(messagePoint, chuoi);
										sendMess(messagePoint, connfd, (struct sockaddr*) &cliaddr);
										strcpy(messagePoint, "Bạn đã thua cuộc. Số điểm bạn có là: ");
										point = 0;
										login = 2;
									}else
									{
										sendMess("Sai cú pháp.", connfd, (struct sockaddr*) &cliaddr);
									}
									
									break;

								case 8:
									if(strcmp(buff, "help") == 0){
										num = changeStrtoInt(questionMod[i].answer);
										numAns = ranDomAns(num);
										AnsRand = changeInttoStr(numAns);
										strcat(chuoi1, questionMod[i].answer);
										strcat(chuoi1, "\t");
										strcat(chuoi1, AnsRand);
										sendMess(chuoi1, connfd, (struct sockaddr*) &cliaddr);
										strcpy(chuoi1, "Lựa chọn còn lại: ");
									
									}else if(strcmp(buff, "A") != 0 && strcmp(buff, "B") != 0  && strcmp(buff, "C") != 0 && strcmp(buff, "D") != 0){
										sendMess("Nhập sai cú pháp lựa chọn đáp án. Hãy nhập lại!", connfd, (struct sockaddr*) &cliaddr);
									}
									else{
										if(strcmp(buff, questionMod[i].answer) == 0){
											if(i < 15){	
												i++;
												login = 5;
												point = point + 200;
												sendMess("Đáp án chính xác.", connfd, (struct sockaddr*) &cliaddr);
											}else
											{
												sendMess("Bạn đã trở thành triệu phú. Chúc mừng bạn!", connfd, (struct sockaddr*) &cliaddr);
												point = 0;
												login = 2;
												i = 0;
												chuoi[0] = '\0';
											}
										}else{
											insertScore("Trung bình", acc->username, point);
											writeFileScore();
											snprintf(chuoi,sizeof(chuoi), "%d", point);
											strcat(messagePoint, chuoi);
											chuoi[0] = '\0';
											sendMess(messagePoint, connfd, (struct sockaddr*) &cliaddr);
											strcpy(messagePoint, "Bạn đã thua cuộc. Số điểm bạn có là: ");
											point = 0;
											login = 2;
											i = 0;
											
										}
									}
									
									break;

		//Case 9 + 10 : Question Hard							
								case 9:
									if(strcmp(buff, "SS") == 0 || strcmp(buff, "OK") == 0){
										randomize(questionEasy, 30);
										sendMess(questionHard[i].word, connfd, (struct sockaddr*) &cliaddr);
										login = 10;
									}
									else if(strcmp(buff, "STOP") == 0){
										insertScore("Khó", acc->username, point);
										writeFileScore();
										snprintf(chuoi,sizeof(chuoi), "%d", point);
										strcat(messagePoint, chuoi);
										sendMess(messagePoint, connfd, (struct sockaddr*) &cliaddr);
										strcpy(messagePoint, "Bạn đã thua cuộc. Số điểm bạn có là: ");
										point = 0;
										login = 2;
									}else
									{
										sendMess("Sai cú pháp.", connfd, (struct sockaddr*) &cliaddr);
									}

									break;

								case 10:
									if(strcmp(buff, "H") == 0){
										num = changeStrtoInt(questionHard[i].answer);
										numAns = ranDomAns(num);
										AnsRand = changeInttoStr(numAns);
										strcat(chuoi1, questionHard[i].answer);
										strcat(chuoi1, "\t");
										strcat(chuoi1, AnsRand);
										sendMess(chuoi1, connfd, (struct sockaddr*) &cliaddr);
										strcpy(chuoi1, "Lựa chọn còn lại: ");
									
									}else if(strcmp(buff, "A") != 0 && strcmp(buff, "B") != 0  && strcmp(buff, "C") != 0 && strcmp(buff, "D") != 0){
										sendMess("Nhập sai cú pháp lựa chọn đáp án. Hãy nhập lại!", connfd, (struct sockaddr*) &cliaddr);
									}
									else{
										if(strcmp(buff, questionHard[i].answer) == 0){
											if(i < 15){	
												i++;
												login = 5;
												point = point + 300;
												sendMess("Đáp án chính xác.", connfd, (struct sockaddr*) &cliaddr);
											}else
											{
												sendMess("Bạn đã trở thành triệu phú. Chúc mừng bạn!", connfd, (struct sockaddr*) &cliaddr);
												point = 0;
												login = 2;
												i = 0;
												chuoi[0] = '\0';
											}
										}else{
											insertScore("Khó", acc->username, point);
											writeFileScore();
											snprintf(chuoi,sizeof(chuoi), "%d", point);
											strcat(messagePoint, chuoi);
											chuoi[0] = '\0';
											sendMess(messagePoint, connfd, (struct sockaddr*) &cliaddr);
											strcpy(messagePoint, "Bạn đã thua cuộc. Số điểm bạn có là: ");
											point = 0;
											login = 2;
											i = 0;
											
										}
									}
									
									break;

								default:
									break;
								}
								break;

							case 0:
								sendMess("Nhập sai cú pháp. Mời nhập lại ( option = 1 || option =2)", connfd, (struct sockaddr*) &cliaddr);
								break;
								
							default:
								break;
						}
				}
   
        	}

			exit(0);			
		
			
		}
        
       

        if(n < 0){
            perror("Read error: ");
            exit(-1);
        }

        close(connfd);
    }

    close(listenfd);

    return 0;
}