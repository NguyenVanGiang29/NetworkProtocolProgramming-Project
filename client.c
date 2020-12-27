#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 1000
#define MAX_LISTEN_QUEUE 1000

void Ailatrieuphu(){
    printf("%s\n", "----- GAME AI LÀ TRIỆU PHÚ -----");
    printf("%s\n", "1. Đăng kí");
    printf("%s\n", "2. Đăng nhập");
    printf("%s\n", "Hãy lựa chọn(1-2)");
}

void Play(){
    printf("%s\n", "----- GAME AI LÀ TRIỆU PHÚ -----");
    printf("%s\n", "2-1. Chơi");
    printf("%s\n", "2-2. Đổi mật khẩu");
    printf("%s\n", "2-3. Đăng xuất");
    printf("%s\n", "2-4. Xem điểm");
    printf("%s\n", "2-5. Hướng dẫn chơi");
    printf("%s\n", "Hãy lựa chọn(2-1 -> 2-5)");
}

void Question(){
    printf("%s\n", "Mức độ chơi");
    printf("%s\n", "Mức Dễ  (Nhập \"D\")");
    printf("%s\n", "Mức Trung Bình  (Nhập \"BT\")");
    printf("%s\n", "Mức Khó  (Nhập \"K\")");
}

int main(int argc, char *argv[]){
    int sockfd, serverPortNum, sendBytes, rcvBytes;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE], server_response[256], string1[100];

    // create a socket for theo client
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Error: ");
        exit(-1);
    }

    serverPortNum = atoi(argv[2]);

    // create the remote server socket information structure
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    // inet_aton("127.0.0.1", &servaddr.sin_addr); 
    servaddr.sin_port = htons(serverPortNum);

    // connection theo client to the server socket
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        perror("Problem in connecting to the server");
        exit(-1);
    }
   Ailatrieuphu();


    while(1){
        fflush(stdin);
        fgets(sendline, MAXLINE,stdin);
        sendline[strlen(sendline) -1] = '\0';
        sendBytes = send(sockfd, sendline , strlen(sendline) +1, 0);
        if(sendBytes < 0){
            perror("Error: ");
            return 0;
        }
        
        rcvBytes = recv(sockfd, &server_response, MAXLINE, 0);
        if(rcvBytes <0){
            perror("Error: ");
            return 0;
        }
        server_response[rcvBytes] = '\0';
        printf("%s\n", server_response);


        if(strcmp(server_response, "--- Đăng kí ---") == 0){
            printf("%s\n", "Tạo tên đăng nhập:");
        }

        if(strcmp(server_response, "--- Đăng nhập ---") == 0){
            printf("%s\n", "Tên đăng nhập:");
        }

        if(strcmp(server_response, "Tạo tài khoản thành công.") == 0){
            Ailatrieuphu();
        }

         if(strcmp(server_response, "Đăng nhập thành công.") == 0){
            Play();
        }

        if(strcmp(server_response, "--- Ai là triệu phú ---") == 0 || strstr(server_response, "Sai cú pháp!") != NULL){
            Question();
        }

        if(strcmp(server_response, "Đã đăng xuất.") == 0 || strstr(server_response, "Hãy tạo tài khoản rồi đăng nhập!") != NULL){
            Ailatrieuphu();
        }
        

        if(strcmp(server_response, "--- Đổi mật khẩu ---") == 0){
            printf("%s\n","Mật khẩu mới:");
        }

        if(strcmp(server_response, "Đổi mật khẩu thành công.") == 0){
            Play();
        }

        if(strcmp(server_response, "Đáp án chính xác.") == 0)
        {
            printf("%s\n","Tiếp tục cuộc chơi nhập \"OK\". Dừng cuộc chơi nhập \"STOP\"");
        }
        
        if(strstr(server_response, "Bạn đã thua cuộc.") != NULL )
        {
            Play();
        }

        if(strcmp(server_response, "Sai cú pháp.") == 0 )
        {
            printf("%s\n","Bạn đã sẵn sàng chưa? ( Nhập \"SS\" để bắt đầu hoặc \"OK\" để tiếp tục câu tiếp theo)");
        }

        if(strstr(server_response, "Dễ") != NULL || strstr(server_response, "Khó") != NULL || strstr(server_response, "TB") != NULL  )
        {
            Play();
        }

        if(strcmp(server_response, "Bạn đã trở thành triệu phú. Chúc mừng bạn!") == 0 )
        {
            Play();
        }

    }
}