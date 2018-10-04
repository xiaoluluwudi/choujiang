#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

using namespace std;

#define s_c sizeof(char)
#define n_name 10
#define min_n 0
#define max_n 100
#define id_len 15

FILE* inf_itdc;
FILE* inf_hstr;
FILE* inf_prz;
FILE* inf_prz_1;
FILE* inf_prz_2;
FILE* inf_prz_3;
FILE* inf_user;
FILE* IDs;

int i = 0;

void Instructions();
int MainPage();
void clrscr();
void hitback();
void Blank(FILE* file);
void Lottery();
void Back_Stage();
void User_set();
void User_add();
void User_delete();
void User_info_c();
void Info_set();
void Lottery_set();
void History_set();
void Info();
void Info_User();
void Info_introduce();
void Info_prize();
void Info_history();
void Delete_ID(char *ID);
int Existe_ID(char *ID);


int main()
{
    Instructions();
    MainPage();
    return 0;
}

void Instructions()
{
    clrscr();
//    cout << "欢迎来到抽奖系统" << endl;
    cout << "1.开始抽奖" << endl;
    cout << "2.后台管理" << endl;
    cout << "3.信息查看" << endl;
    cout << "4.退出" << endl;
}

int MainPage()
{
    int answer = 0;
    while(1){
        cin >> answer;
        switch(answer){
//        case 1: Lottery(); break;
        case 2: Back_Stage(); break;
        case 3: Info(); break;
        case 4: exit(0); break;
        }
        Instructions();
    }
}

void Back_Stage()
{
    int answer = 0;
    while(!answer){
        clrscr();
        cout << "-----欢迎来到后台-----" << endl;
        cout << "1.设置信息简介" << endl;
        cout << "2.设置奖项" << endl;
        cout << "3.修改抽奖历史信息" << endl;
        cout << "4.用户管理" << endl;
        cout << "5.返回" << endl;
        cin >> answer;
        switch(answer){
            case 1: Info_set(); break;
            case 2: Lottery_set(); break;
            case 3: History_set(); break;
            case 4: User_set(); break;
            case 5: return;
            default: answer = 0;
        }
        answer = 0;
    }
}

void Info_set()
{
    clrscr();
    if((inf_itdc = fopen("inf_itdc.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        hitback();
        return;
    }
    char inf[max_n+1];
    cout << "编辑抽奖信息简介：" << endl;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_itdc);
    fclose(inf_itdc);
}

void History_set()
{
    clrscr();
    if((inf_hstr = fopen("inf_hstr.txt","w+")) == NULL){
        cout << "读取信息失败" << endl;
        return;
    }
    int times = 0;  //总抽奖次数
    int t_f = 0;    //一等奖抽奖次数
    int t_s = 0;    //二等奖抽奖次数
    int t_t = 0;    //三等奖抽奖次数
    while(times<=0||times>=10000){
        cout << "总抽奖次数(大于0小于10000)：";
        cin >> times;
    }
    while(t_f<=0||t_f>times){
        cout << "一等奖次数(大于0小于" << times+1 << "):";
        cin >> t_f;
    }
    while(t_s<=0||t_s>times){
        cout << "二等奖次数(大于0小于" << times+1 << "):";
        cin >>t_s;
    }
    while(t_t<=0||t_s>times){
        cout << "三等奖次数(大于0小于" << times+1 << "):";
        cin >> t_t;
    }
    char times_c[5];
    char t_f_c[5];
    char t_s_c[5];
    char t_t_c[5];
    itoa(times,times_c,10);
    itoa(t_f,t_f_c,10);
    itoa(t_s,t_s_c,10);
    itoa(t_t,t_t_c,10);
    fwrite(times_c,s_c,strlen(times_c),inf_hstr);
    Blank(inf_hstr);
    fwrite(t_f_c,s_c,strlen(t_f_c),inf_hstr);
    Blank(inf_hstr);
    fwrite(t_s_c,s_c,strlen(t_s_c),inf_hstr);
    Blank(inf_hstr);
    fwrite(t_t_c,s_c,strlen(t_t_c),inf_hstr);
    Blank(inf_hstr);
    fclose(inf_hstr);
}

void Lottery_set()
{
    clrscr();
    if((inf_itdc = fopen("inf_prz.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        return;
    }
    char name[n_name];
    char N[3];
    char inf[max_n+1];
    int num = 0;
    for(i=1;i<4;i++){
        cout << "设置" << i << "等奖" << endl;;
        cout << "名称：" ;
        cin >> name;
        while(1){
            cout << "奖品数量(大于" << min_n << "小于" << max_n << ")" << endl;
            cin >> num;
            if(num<=min_n||num >= max_n) cout << "不合法的数字，请重新输入" <<endl;
            else break;
        }
        itoa(num,N,10);
        fwrite(name,s_c,strlen(name),inf_itdc);
        fwrite("\n",s_c,1,inf_itdc);
        fwrite(N,s_c,strlen(N),inf_itdc);
        fwrite("\n",s_c,1,inf_itdc);
    }
    fclose(inf_itdc);
    if((inf_prz_1 = fopen("inf_prz_1.txt","w"))==NULL||(inf_prz_2 = fopen("inf_prz_2.txt","w"))==NULL||(inf_prz_3 = fopen("inf_prz_3.txt","w"))==NULL){
        cout << "编辑奖品详情页失败！" << endl;
        return;
    }
    for(i=0;i<max_n+1;i++)
        inf[i] = '\0';
    cout << "一等奖信息：" ;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_prz_1);
    for(i=0;i<max_n+1;i++)
        inf[i] = '\0';
    cout << "二等奖信息：" ;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_prz_2);
    for(i=0;i<max_n+1;i++)
        inf[i] = '\0';
    cout << "三等奖信息：" ;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_prz_3);
    fclose(inf_prz_1);
    fclose(inf_prz_2);
    fclose(inf_prz_3);
}

void Info()
     int answer=0;
    while(!answer){
        clrscr();
        cout << "1.抽奖简介" << endl;
        cout << "2.奖品信息" << endl;
        cout << "3.历史抽奖信息" << endl;
        cout << "4.用户信息" << endl;
        cout << "5.返回" << endl;
        cin >> answer;
        switch(answer){
            case 1: Info_introduce(); break;
            case 2: Info_prize(); break;
            case 3: Info_history(); break;
            case 4: Info_User(); break;
            case 5: return;
            default: answer = 0;break;
        }
        answer = 0;
    }
}

void Info_introduce()
{
    clrscr();
    if((inf_itdc = fopen("inf_itdc.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        return;
    }
    char word = 'a';
    while(word!=EOF){
        word = fgetc(inf_itdc);
        cout << word;
    }
    cout << endl;
    hitback();
    fclose(inf_itdc);
}

void Info_prize()
{
    clrscr();
    if((inf_prz = fopen("inf_prz.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        return;
    }
    char word = 'a';

    for(i=1;i<4;i++){
        cout << i << "等奖: ";
        while(1){
            word = fgetc(inf_prz);
            if(word == '\n') break;
            cout << word;
        }
        cout << " 数量: ";
        while(1){
            word = fgetc(inf_prz);
            if(word == '\n') break;
            cout << word;
        }
        cout << endl;
    }
    if((inf_prz_1 = fopen("inf_prz_1.txt","r"))==NULL){
        cout << "读取奖品详情失败" << endl;
        return;
    }
    if((inf_prz_2 = fopen("inf_prz_2.txt","r"))==NULL){
        cout << "读取奖品详情失败" << endl;
        return;
    }
    if((inf_prz_3 = fopen("inf_prz_3.txt","r"))==NULL){
        cout << "读取奖品详情失败" << endl;
        return;
    }
    word = 'a';
    cout << "奖品详情:" << endl;
    cout << "一等奖：";
    while(word!=EOF){
        word = fgetc(inf_prz_1);
        cout << word;
    }
    word = 'a';
    cout << endl << "二等奖: ";
    while(word!=EOF){
        word = fgetc(inf_prz_2);
        cout << word;
    }
    word = 'a';
    cout << endl << "三等奖: ";
    while(word!=EOF){
        word = fgetc(inf_prz_3);
        cout << word;
    }
    cout<<endl;
    hitback();
    fclose(inf_prz);
}

void Info_history()
{
    clrscr();
    if((inf_hstr = fopen("inf_hstr.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        return;
    }
    char word = 'a';
    cout << "总开奖次数：" ;
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl << "一等奖开奖次数：";
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl << "二等奖开奖次数：";
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl << "三等奖开奖次数：" ;
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl;
    hitback();
    fclose(inf_hstr);
}

void Info_User()
{
    clrscr();
    char word = 'a';
    char ID[id_len];
    cout << "输入想要查看的用户ID: ";
    cin >> ID;
    if((inf_user = fopen(ID,"r"))==NULL){
        cout << "不存在用户";
        hitback();
        return;
    }
    cout << "姓名：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "年龄：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "性别：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "简介：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    cout << endl;
    hitback();
    fclose(inf_user);
}

void clrscr()
{
    system("cls");
}

void hitback()
{
    system("pause");
}

void Blank(FILE* file)
{
    fwrite("\n",s_c,1,file);
}

void User_set()
{
    int answer = 0;
    while(1){
        clrscr();
        cout << "1.添加用户" << endl;
        cout << "2.删除用户" << endl;
        cout << "3.修改用户信息" << endl;
        cout << "4.返回" << endl;
        cin >> answer;
        if(answer == 1) User_add();
        else if(answer == 2) User_delete();
        else if(answer == 3) User_info_c();
        else if(answer == 4) return;
        else answer = 0;
    }
}

void User_add()
{
    char name[11];
    int age = 0;
    int sex = 0;
    char AGE[3];
    char ID[14];
    char info[101];
    clrscr();
    cout << "登记用户信息：" << endl;
    cout << "ID(用户身份识别码): ";
    cin >> ID;
    if((inf_user = fopen(ID,"r"))!=NULL){
        cout << "用户已存在" << endl;
        hitback();
        fclose(inf_user);
        return;
    }

    cout << "姓名(10字节)：" ;
    cin >> name;
    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        cin >> age;
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        cin >> sex;
    }
    cout << "个人简介(100字节):" << endl;
    cin >> info;

    if((inf_user = fopen(ID,"w+"))==NULL){
        cout << "添加用户失败" << endl;
        hitback();
        return;
    }

    fwrite(name,s_c,strlen(name),inf_user);
    Blank(inf_user);
    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1) fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);
    fclose(inf_user);
}

void User_delete()
{
    int answer = 0;
    char ID[14];
    cout << "请输入要删除的用户的ID" << endl;
    cin >> ID;
    if((inf_user = fopen(ID,"r")) == NULL){
        cout << "不存在用户，请检查输入" << endl;
        hitback();
        return;
    }

    clrscr();
    char word = 'a';
    cout << "用户姓名：";
    while(word!='\n'){
        word = fgetc(inf_user);
        cout << word;
    }
    fclose(inf_user);
    while(answer == 0){
        cout << "1.确认删除" <<endl<<"2.返回" << endl;
        cin>>answer;
        if(answer == 1) remove(ID);
        else if(answer == 2) return;
        else answer = 0;
    }

}

void User_info_c()
{
    char name[11];
    int age = 0;
    int sex = 0;
    char AGE[3];
    char ID[14];
    char info[101];
    clrscr();
    cout << "修改用户信息：" << endl;
    cout << "输入要修改的ID" << endl;
    cin >> ID;
    if((inf_user = fopen(ID,"r+")) == NULL){
        cout << "读取用户数据失败" << endl;
        hitback();
        return;
    }

    cout << "姓名(10字节)：" ;
    cin >> name;
    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        cin >> age;
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        cin >> sex;
    }
    cout << "个人简介(100字节):" << endl;
    cin >> info;
    remove(ID);
    if((inf_user = fopen(ID,"w")) == NULL){
        cout << "写入用户数据失败" << endl;
        return;
    }
    fwrite(name,s_c,strlen(name),inf_user);
    Blank(inf_user);
    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1)
        fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);
    fclose(inf_user);

}

