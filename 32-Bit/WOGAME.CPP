#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<dos.h>
#include<string.h>
#include<stdlib.h>

void details();
void header();
void header2();
void help();
void editldr();
void loadscrn();
void strtmnu();
void ldrbord();
void verif();
void game();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Structure of player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct playr{
     char name[40];
     int scor;
     public:
     ldrdisplay();
}ply,p1,p2;
//********************************
//Header of the Program
//********************************
void header2(){
		clrscr();

       cout<<"\t\t\t       O B S E M B E R\n";
       for(int i=0;i<80;i++) cout<<(char)219;

	cout<<"\nUser: "<<ply.name<<"\t\t\t\t\tScore: "<<ply.scor;

       cout<<endl<<endl;
       for(i=0;i<80;i++) cout<<(char)219;
}

//********************************
//Primary header of program
//********************************
void header(){
	clrscr();
	cout<<"\t\t\t       O B S E M B E R\n";
       for(int i=0;i<80;i++) cout<<(char)219;

	cout<<"\nUser: "<<ply.name;;

       cout<<endl<<endl;
       for(i=0;i<80;i++) cout<<(char)219;

}

//***************************************
//Function to get details of user
//***************************************

void details(){
	clrscr();
	cout<<"\t\t\t       O B S E M B E R\n";
       for(int i=0;i<80;i++) cout<<(char)219;
	cout<<"\n\n\n\n\n\t\t\t\tUsername:";
	cin>>ply.name;
}

//*********************************
//Function to show instructions
//*********************************

void help(){
	clrscr();
	fstream out;
       char ch[200];

       out.open("HELP.txt",ios::in);
       out.seekg(0);
      for(;!out.eof();){
	      out.getline(ch,200);
		  cout<<ch<<endl;
      }
       out.close();
       getch();
       strtmnu();

}
//****************************
//Function to edit leaderboard of the program
//****************************
void editldr(){
		char last='y';
		fstream fil;
		fstream temp;
		temp.open("TEMP.DAT",ios::out|ios::in|ios::binary);
		fil.open("LEAD.DAT",ios::in|ios::binary);
		fil.seekg(0);
		while(!fil.eof()){
				fil.read((char*)&p1,sizeof(p1));
				if(ply.scor>=p1.scor){
					temp.write((char*)&ply,sizeof(playr));
					temp.write((char*)&p1,sizeof(p1));
					last='n';
					break;
				}
			else{
				temp.write((char*)&p1,sizeof(p1));
			}
		}
			if(last=='y'){
				temp.write((char*)&ply,sizeof(ply));
			}
			else if(!fil.eof()){
				while(!fil.eof()){
					fil.read((char*)&p1,sizeof(p1));
					temp.write((char*)&p1,sizeof(p1));
				}
			}
			fil.close();
			temp.close();
			remove("LEAD.DAT");
			rename("TEMP.DAT","LEAD.DAT");
			ldrbord();
}



//*******************************
//Loading Screen of Program
//*******************************
void loadscrn(){	//load screen
	clrscr();
	gotoxy(20,50);
	cout<<"\t\t\tWelcome to OBSEMBER (v 1.0.0)\n\n\n\n\n\t\t\t\t LOADING.....\n\n\n\n\t\t\t";

	gotoxy(50,50);
	for(int i=0;i<29;i++){		//loop for displaying loading bar
		cout<<(char)219;
		delay(200);
	}
	cout<<"\n\n\n\t\t\t\tAll Done!!!!\n\n\n\n\n\t\t\tHit ANY KEY to continue.....";
	//details();
	getch();
}

//*************************************
//Start Menu of Program
//*************************************
void strtmnu(){		//start menu of program

    clrscr();
	header();
	cout<<"\n\n\t\t\t\t  Main Menu\n";
	gotoxy(33,15);
	cout<<"1.NEW GAME";
	cout<<"\n\t\t\t\t2.VIEW LEADERBOARD";
	cout<<"\n\t\t\t\t3.HELP";
	cout<<"\n\t\t\t\t4.EXIT";
	cout<<"\n\n\nPlease select your choice:>>";
    int choic;
    cin>>choic;
	switch(choic){
		case 1:
			game();
		case 2:
			ldrbord();
		case 3:
			help();
			break;
		case 4:
			exit(0);
		default:
		clrscr();
		strtmnu();
	}
	getch();
}

//*********************************
//Leaderboard of program
//*********************************
void ldrbord(){ //must be a member fun of player
	clrscr();
	int i=0;
	fstream ldr;
	ldr.open("Lead.dat",ios::in|ios::binary|ios::app);
	ldr.seekg(0);
	if(ldr.eof()) cout<<"No Records Present....";
	else{
		cout<<"\nS.no  Name\t\t\t\tScore\n";
		for(int a=0;a<80;a++)cout<<(char)247;
		ldr.seekg(0);
	    while(!ldr.eof()&&i<10){
	    ldr.read((char*)&p2,sizeof(ply));
		cout<<"   ";
	      cout<<(i+1)<<"."<<p2.	name<<"\t\t\t\t"<<p2.scor<<"  pts."<<endl;
	      i++;
		}
	}
	ldr.close();
	cout<<"\n\n\nPress any Key to continue......";
	getch();
	strtmnu();
}

//*********************************
//Game Engine of program
//*********************************

/*~~~~~~~~~~~~~~~~~~~~~~~~~
class for words def.
~~~~~~~~~~~~~~~~~~~~~~~~*/
class words{
    public:
    char word[20];
    int lvl,ord;
    words(){
	ord=lvl=1;
	strcpy(word,"best");
    }
    words(words &w){
		strcpy(word,w.word);
		ord=w.ord;
		lvl=w.lvl;
    }
}wr[3],tst;
int verif(int l){
	char word[20];
	for(int i=0;i<3;i++){
		clrscr();
		header2();
		cout<<"Level: "<<l;
		cout<<"\nRound:"<<(i+1);
		cout<<"\n\n\n\t\t\tWord: "<<wr[i].word;
		delay(2000-l*190);
		clrscr();
		header2();
		cout<<"Level: "<<l;
		cout<<"\nRound:"<<(i+1);
		cout<<"\n\n\n\t\t\tWord >>";
		cin>>word;
		int k=strcmp(wr[i].word,word);
		if(k==0){
			ply.scor+=l*100;	//Score addition
		}
		else{
			return 2;
		}
	}
	return 0;
}
void game(){
	ply.scor=0;
	int k=7;
	fstream file;
	clrscr();
	int ord,i=1;
	randomize();
	file.open("DATA.CAB",ios::in,ios::app|ios::binary);
	header2();
	for(int lvl=1;lvl<10;lvl++){
		file.seekg(0);i=0;
				if(lvl<7){
						ord=random(7)+1;
						while(!file.eof()){
							file.read((char*)&wr[i],sizeof(wr[i]));
							if(wr[i].ord==ord && lvl==wr[i].lvl)
								break;
						}
								i++;
								file.read((char*)&wr[i],sizeof(wr[i]));
								i++;
								file.read((char*)&wr[i],sizeof(wr[i]));
								i++;
								k=verif(lvl);
								if(k==2){
									clrscr();
									header2();
									cout<<"\n\n\n\n\t\t\t\tGAME OVER !!!!!!!\n\n\n\t\t\tYou misspelt a word\n\n\t\t\tHit ANY KEY to view leaderboard.";
									getch();
									editldr();

								}
				}
				else{
					//for level exceeding 7
					ord=random(3)+1;
						while(!file.eof()){
							file.read((char*)&wr[i],sizeof(wr[i]));
							if(wr[i].ord==ord && lvl==wr[i].lvl)
								break;
						}
								i++;
								file.read((char*)&wr[i],sizeof(wr[i]));
								i++;
								file.read((char*)&wr[i],sizeof(wr[i]));
								i++;
								k=verif(lvl);
								if(k==2){
									clrscr();
									header2();
									cout<<"\n\n\n\n\t\t\t\tGAME OVER !!!!!!!\n\n\n\t\t\tYou misspelt a word\n\n\t\t\tHit ANY KEY to view leaderboard.";
									getch();
									editldr();
								}
				}
	}
	clrscr();
	header2();
	cout<<"\t\t\t\tCongratulations!!!!!!\n\n \t\t\tYou have compleated the game!!!!!\n\n\n\t\t\tHit ANY KEY to continue.......";
	getch();
	editldr();
}
//END of game Engine
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void main(){
	clrscr();
	loadscrn();
	details();
	strtmnu();
}
