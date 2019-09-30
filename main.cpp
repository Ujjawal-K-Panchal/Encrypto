#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <process.h>
#include <ctype.h>
#include<time.h>
#include<dos.h>

using namespace std;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct dataform{

    char msg[250];
    int key;


};

class processing{
                 char msg[250];
                 int shift;
                 int matcher(char arr[]);
                public:
                    processing(){
                            strcpy(msg,"DEFAULT");
                            shift=0;
                    }
                   void encryptor();
                   void decryptor();


};
int processing::matcher(char arr[])
{

    int points=0;
        fstream fout("D:\\C++ Tutorials\\CEASERCRYPTER\\TEXT_TOOLS\\CALC.txt",ios::out);

        fout<<arr<<endl;
        ifstream file("D:\\C++ Tutorials\\CEASERCRYPTER\\TEXT_TOOLS\\KEYWORDS.txt",ios::out);

        char msg_tmp[250];
        char eng_tmp[250];
                            while(fout>>msg_tmp)
                            {

                                    while(file>>eng_tmp)
                                    {
                                        if(strcmpi(msg_tmp,eng_tmp)==0)points++;
                                    }

                            }


        fout.close();
        file.close();
        return points;//temporary
}
void processing :: decryptor(){

    int choice=1;char ch='y';;int arrmatch[26];
    while(choice!=3){
            system("cls");char arrow=16;
                                cout<<"-----WELCOME TO DECRYPTOR-----"<<endl;
                                cout<<" DECRYPT SAVED MESSAGE"<<endl;
                                cout<<" DECRYPT NEW MESSSAGE"<<endl;
                                cout<<" EXIT"<<endl;
                                cout<<"------------------------------"<<endl;

                                gotoxy(0,1);cout<<arrow;
                        while(ch!=13)
                        {
                                if(kbhit())
                                {
                                    ch=getch();
                                         if(ch=='w' && choice>1)choice--;
                                    else if(ch=='w')choice=3;
                                    else if(ch=='s' && choice<3)choice++;
                                    else if(ch=='s')choice=1;
                                            for(int i=1;i<=3;i++)
                                                if(i!=choice){
                                                                gotoxy(0,i);
                                                                cout<<" ";
                                                            }
                                                else if(i==choice){
                                                                    gotoxy(0,i);
                                                                    cout<<arrow;
                                                                 }
                                }
                        }

if(choice==1)
{

    ifstream fin("D:\\C++ Tutorials\\CEASERCRYPTER\\RESULTS.DAT",ios::binary);
                int i=1;
                        dataform fetch;
                        while(fin.read((char*)&fetch,sizeof(dataform)))
                        {
                            RETRY:
                            system("cls");
                            cout<<"---------------------------------"<<endl;
                            cout<<"Message Number:"<<i<<'\t'<<"Message Key:"<<fetch.key<<endl;
                            cout<<"Message: "<<fetch.msg<<endl;
                            cout<<"---------------------------------"<<endl;
                                cout<<"Would you like to decrypt this message?(y/n):>";cin>>ch;

                                if(ch=='y')break;

                                else if(ch!='n')
                                {
                                        cout<<"Incorrect choice! Please Retry!"<<endl;
                                goto RETRY;
                                }
                                i++;
                            }
        if(ch=='y'){
                        shift=fetch.key;

                            for(int i=0;fetch.msg[i]!='\0';i++){

                                    for(int j=1;j<=shift;j++)
                                    {

                                        if(isalpha(fetch.msg[i])){
                                         fetch.msg[i]--;
                                         if(fetch.msg[i]<'a')fetch.msg[i]='z';
                                        }

                                    }
                            }

                            cout<<"---------------------------------"<<endl;
                            cout<<"The decrypted message is :> "<<fetch.msg<<endl;
                            getch();
                    }

        else if(ch=='n'){
                            cout<<"No message selected!"<<endl;
                            getch();
                        }

fin.close();
             }


else if(choice==2){
                    system("cls");
                    char str[250];
                cout<<"Enter the encrypted string:>";
                cin.getline(str,250);
                cout<<"---------------------------------"<<endl;
                for(int i=0;str[i]!='\0';i++)str[i]=tolower(str[i]);
    ch='0';

    while(ch!='y' && ch!='n')
        {
            cin.sync();
                cout<<"Do you know the key? (y/n):>";cin>>ch;
                if(ch=='y')
                    {
                            cout<<"Enter the key:>";cin>>shift;

                                    for(int i=0;str[i]!='\0';i++)
                                    {
                                        for(int j=1;j<=shift;j++)
                                        {
                                            if(isalpha(str[i]))
                                            {
                                                 str[i]--;
                                                 if(str[i]<'a')str[i]='z';
                                            }

                                        }
                                    }
                            cout<<"The Decrypted String is:> "<<str<<endl;
                            getch();

                    }
                    else if(ch=='n')
                    {
                        int i=0;
                                dataform guess;
                                fstream ans("D:\\C++ Tutorials\\CEASERCRYPTER\\ANSWERS.DAT",ios::binary|ios::app|ios::in);
                                fstream sortans("D:\\C++ Tutorials\\CEASERCRYPTER\\SORTEDANSWERS.txt",ios::binary|ios::out|ios::in|ios::app);

                                for(int z=0;z<=26;z++){
                                    shift=z;
                                    for(i=0;str[i]!='\0';i++)
                                            {
                                                for(int j=1;j<=shift;j++)
                                                {
                                                    if(isalpha(str[i]))
                                                    {
                                                         str[i]--;
                                                         if(str[i]<'a')str[i]='z';
                                                    }

                                                }

                                            }

                                    strcpy(guess.msg,str);
                                    guess.key=matcher(guess.msg);
                                    ans.write((char*)&guess,sizeof(dataform));

                                }
                                ans.seekg(0,ios::beg);

                                            i=0;
                                while(ans.read((char*)&guess,sizeof(dataform)))arrmatch[i++]=guess.key;

                                for(i=0;i<25;i++)
                                for(int j=i+1;j<26;j++){
                                    int temp;
                                    if(arrmatch[i]<arrmatch[j])
                                    {
                                        temp=arrmatch[i];
                                        arrmatch[i]=arrmatch[j];
                                        arrmatch[j]=arrmatch[i];
                                    }
                                }
                                for(int i=0;i<26;i++)
                                {
                                        while(ans.read((char*)&guess,sizeof(dataform)))
                                             {
                                                    if(guess.key==arrmatch[i])
                                                      {
                                                          sortans.write((char*)&guess,sizeof(dataform));
                                                      }
                                             }
                                            ans.seekg(0,ios::beg);
                                    }
                                    ans.close();
                                     i=1;
                                    sortans.seekg(0,ios::beg);
                                    sortans.seekp(0,ios::beg);
                                    cout<<"---------------------------------"<<endl;
                                    cout<<"The Three most probable answers are:>"<<endl;
                                while(sortans.read((char*)&guess,sizeof(dataform)) && i<=3)
                                {
                                    cout<<"Result No:"<<i<<".\t\t"<<"Match points:"<<guess.key<<endl<<"Message:>"<<guess.msg<<endl<<endl;
                                    i++;
                                }
                                cout<<"Did you find the message?(y/n):>";cin>>ch;
                                if(ch=='n'){
                                                system("cls");
                                                cout<<"All the answers are listed as below:>";
                                                int i=1;sortans.seekg(0,ios::beg);
                                                while(sortans.read((char*)&guess,sizeof(dataform)))
                                                    {
                                                            cout<<"Result No:"<<i<<".\t\t"<<"Match points:"<<guess.key<<endl<<"Message:>"<<guess.msg<<endl<<endl;
                                                            i++;
                                                    }

                                }
                        sortans.close();
                        getch();

                            }


                    }


         }



else if(choice!=3){

            while(ch!='n' && ch!='y'){

                cout<<"Wrong choice! Do you want to retry?(y/n):>";
                cin>>ch;
                if(ch=='n')break;
                else if(ch=='y')break;

            }
                                    }

                }

}


void processing :: encryptor(){
                                char choice='n';
                                fstream save("D:\\C++ Tutorials\\CEASERCRYPTER\\RESULTS.DAT",ios::binary|ios::in|ios::app);
                                srand(time(NULL));
                    cout<<"Enter the message to encrypt:>\n";
                    cin.sync();
                    cin.getline(msg,250);
                    cout<<"---------------------------------"<<endl<<"<MSG recieved!>"<<endl<<"---------------------------------"<<endl;
                    for(int i=0;msg[i]!='\0';i++)msg[i]=tolower(msg[i]);
                    cout<<"Enter numbers of characters to shift(0 for random):>";cin>>shift;
                    if(shift==0)
                                shift=rand()%25+1;
                    for(int i=0;msg[i]!='\0';i++)
                                for(int j=1;j<=shift;j++)
                                {
                                    if(isalpha(msg[i])){
                                     msg[i]++;
                                     if(msg[i]>'z')msg[i]='a';
                                    }
                                }
                    cout<<"The encrypted string is:>\n";
                    cout<<msg<<endl<<"---------------------------------"<<endl;
                    cout<<"Key:>"<<shift<<endl<<"---------------------------------"<<endl;
                    do{
                        cout<<"Would you like to save the results?(y/n):>";cin>>choice;
                        if(!(choice=='y' || choice=='n') )
                        {
                          cout<<"Incorrect choice! Do you want to retry(y) or exit(n)?:>";
                          cin>>choice;
                        }

                    }while(!(choice=='y' || choice=='n'));
                    if(choice=='y'){
                            dataform dat;
                            dat.key=shift;
                            strcpy(dat.msg,msg);
                            cout<<"------------------------------------------------"<<endl;
                            cout<<"Result is saved in :>D:\\C++ Tutorials\\CEASERCRYPTER\\RESULTS.DAT"<<endl;
                            save.write((char*)&dat,sizeof(dataform));
                        }
                        else{
                                cout<<"---------------------------------"<<endl;
                                cout<<"msg not saved !\n";

                            }


                save.close();
}

class interact{
        private:

            int point;
            char opts[5][50];
        public:
    int get_point(){
                        return point;
                   }
               void menu();
    interact(){
                point=1;

                        strcpy(opts[0],"----- CEASER CRYPTER -----");
                        strcpy(opts[1],"1.ENCRYPTION");
                        strcpy(opts[2],"2.DECRYPTION");
                        strcpy(opts[3],"3.EXIT");
                        strcpy(opts[4],"--------------------------");
              }
};

void interact :: menu()
{
    //point=1;
    system("cls");

   char ch=14,arrow=16;

                    for(int i=0;i<5;i++)
                    {
                            if((i>0)&&(i<4))cout<<" ";
                            for(int k=0;opts[i][k]!='\0';k++,_sleep(15.0))
                                            cout<<opts[i][k];
                            cout<<endl;

                    }

                    gotoxy(0,1);cout<<arrow;
                        while(ch!=13)
                        {
                                if(kbhit())
                                {
                                    ch=getch();
                                         if(ch=='w' && point>1)point--;
                                    else if(ch=='w')point=3;
                                    else if(ch=='s' && point<3)point++;
                                    else if(ch=='s')point=1;
                                            for(int i=1;i<=3;i++)
                                                if(i!=point){
                                                                gotoxy(0,i);
                                                                cout<<" ";
                                                            }
                                                else if(i==point){
                                                                    gotoxy(0,i);
                                                                    cout<<arrow;
                                                                 }
                                }
                        }
}

int main()
{
    interact x;
    processing y;
                do{
                x.menu();

                            if(x.get_point()==1){
                                                    system("cls");
                                                    y.encryptor();
                                                }
                       else if(x.get_point()==2){   system("cls");
                                                    y.decryptor();
                                                }//DECRYPTOR
                       else if(x.get_point()==3);//EXIT
                   }while(x.get_point()!=3);
    return 0;
}
