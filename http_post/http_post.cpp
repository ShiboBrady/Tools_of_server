//
//  main.cpp
//  短信http接口的c/c++代码调用示例
//
//  Created by Jacky on 14-8-7.
//  Copyright (c) 2014年 Jacky. All rights reserved.
//
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>

#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  2000
#define MAXPARAM 2048

#define LISTENQ         1024

extern int h_errno;

int sockfd;
char *hname = "yunpian.com";
char *send_sms_json = "/v1/sms/send.json";
char *get_user_json = "/v1/user/get.json";

/**
 * 发http post请求
 */
ssize_t http_post(char *page, char *poststr)
{
    char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
    ssize_t n;
    snprintf(sendline, MAXSUB,
             "POST %s HTTP/1.0\r\n"
             "Host: %s\r\n"
             "Content-type: application/x-www-form-urlencoded\r\n"
             "Content-length: %zu\r\n\r\n"
             "%s", page, hname, strlen(poststr), poststr);
    
    write(sockfd, sendline, strlen(sendline));
    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        printf("%s", recvline);
    }
    return n;
}

/**
 * 查账户信息
 */
ssize_t get_user(char *apikey)
{
    char params[MAXPARAM + 1];
    char *cp = params;
    sprintf(cp,"apikey=%s", apikey);
    return http_post(get_user_json, cp);
}

/**
 * 使用通用接口发短信
 */
ssize_t send_sms(char *apikey, char *mobile, char *text)
{
    char params[MAXPARAM + 1];
    char *cp = params;
    sprintf(cp,"apikey=%s&mobile=%s&text=%s", apikey, mobile, text);
    return http_post(send_sms_json, cp);
}

int main(void)
{
    struct sockaddr_in servaddr;
    char **pptr;
    char str[50];
    struct hostent *hptr;
    if ((hptr = gethostbyname(hname)) == NULL) {
        fprintf(stderr, "通过域名获取IP失败: %s: %s",
                hname, hstrerror(h_errno));
        exit(1);
    }
    printf("域名: %s\n", hptr->h_name);
    if (hptr->h_addrtype == AF_INET
        && (pptr = hptr->h_addr_list) != NULL) {
        printf("IP: %s\n",
               inet_ntop(hptr->h_addrtype, *pptr, str,
                         sizeof(str)));
    } else {
        fprintf(stderr, "Error call inet_ntop \n");
        exit(1);
    }
    
    //建立socket连接
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    inet_pton(AF_INET, str, &servaddr.sin_addr);
    
    connect(sockfd, (SA *) & servaddr, sizeof(servaddr));

    //修改为您的apikey
    char *apikey = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    //修改为您要发送的手机号
    char *mobile = "188xxxxxxxx";
    //设置您要发送的内容
    char *text = "您的验证码是1234";
    
    /**************** 查账户信息调用示例 *****************/
    get_user(apikey);
    
    /**************** 使用通用接口发短信 *****************/
    //send_sms(apikey, mobile, text);

    close(sockfd);
    exit(0);
}           