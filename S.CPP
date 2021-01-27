//////PROJECT ON SHOP SALE MANAGEMENT///////////
/* NAME   : RISHIKA AGARWAL */
//////HEADER FILES USED//////
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
/*******************************************************
		      FUNCTION INTRO
 *******************************************************/
void intro()
{
   clrscr();
   cout<<"\n\n\n\n\n\n\n\n\n\n\t\t Project On Shop Sale Management";
   cout<<"\n\n\n\n\n\t\t\t By:Rishika Agarwal";
   getch();
}
/************************************************
		CLASS ITEM
 ************************************************/
class item
{
   protected:
	   char iname[30];   //to store the name of item
	   int icode;        //to store the code of item
	   float dis;        //to store the discount rate on item
	   float price;      //to store the price of item
	   int qty;
   public:
	  //Constructors
	  item();
	  item(int,char*,float,float,int);
	  item(item&);
	  //Destructors
	  ~item();
	  //Acssessor functions
	  int geticode();
	  int getqty();
	  char* getname();
	  int cmpiname(char in[]);
	  float getprice();
	  float getdis();
	  //Mutator functions
	  void seticode(int ic);
	  void setiname(char in[]);
	  void setqty(int q);
	  void setprice(float p);
	  void setdis(float dis);
	  //Input Output functions
	  void itemin();
	  void itemout();
	  void itemmodify();
};//End of class item
/********************************************
	 GENICODE FUNCTION
 ********************************************/
void genicode(item &iob)
{
   ifstream fin("item.dat",ios::in|ios::binary);
   if(!fin)
      iob.seticode(201);
   else
   {
      long pos=sizeof(item)* -1L;
      fin.seekg(pos,ios::end);
      fin.read((char*)&iob,sizeof(iob));
      fin.close();
      iob.seticode(iob.geticode()+1);
   }
}
/*************************************************************
	  definition of member functions of item
 *************************************************************/
//Constructor
item::item()
{
  genicode(*this);
   strcpy(iname,"");
   price=0;
   dis=0;
   qty=0;
}
item::item(int code,char*in,float p,float d,int q)
{
    icode=code;
    strcpy(iname,in);
     price=p;
     dis=d;
     qty=q;
}
item::item(item&t)
{
   icode=t.icode;
   strcpy(iname,t.iname);
   price=t.price;
   dis=t.dis;
   qty=t.qty;
}
//Destructor
item::~item(){}
//Accessor
int item::geticode(){return icode;}
int item::getqty(){return qty;}
char* item::getname(){return iname;}
int item::cmpiname(char in[]){return strcmp(iname,in);}
float item::getprice(){return price;}
float item::getdis(){return dis;}
//Mutator
void item::seticode(int ic){icode=ic;}
void item::setiname(char in[]){strcpy(iname,in);}
void item::setprice(float p){price=p;}
void item::setqty(int q){qty=q;}
void item::setdis(float d){dis=d;}
//Input Output functions

void item::itemin()
{
   cout<<"\nITEM CODE:"<<icode;
   cin.get();
   cout<<"\nEnter item name     :";
   cin.getline(iname,30);
   cout<<"\nEnter price         :";
   cin>>price;
   cout<<"\nEnter discount rate :";
   cin>>dis;
   cout<<"\nEnter quantity:";
   cin>>qty;
}
void item::itemout()
{
   cout<<"\n====================================================";
   cout<<"\nItem code     :"<<icode;
   cout<<"\nItem name     :"<<iname;
   cout<<"\nPrice         :"<<price;
   cout<<"\nDiscount rate :"<<dis;
   cout<<"\nQuantity      :"<<qty;
   getch();
}
void item::itemmodify()
{
   int itdis,itp,iqty;
   char itn[20];
   cout<<"\nEnter new values to update following fields "<<endl;
   cout<<"Enter(-1) to retain previous values";
   cin.get();
   cout<<"\nenter updated item name:";
   cin.getline(itn,20);
   if(strcmp(itn,"-1")!=0)
      strcpy(iname,itn);
   cout<<"\nEnter updated price:";
   cin>>itp;
   if(itp!=-1)
     price=itp;
   cout<<"\nEnter updated discount rate:";
   cin>>itdis;
   if(itdis!=-1)
      dis=itdis;
   cout<<"\nEnter updated quantity:";
   cin>>iqty;
   if(iqty!=-1)
      qty=iqty;
}
/************************************************
	   NON MEMBER FUNCTIONS
 ************************************************/
void additem()
{
    ofstream fout;
    item iob;
    fout.open("item.dat",ios::out|ios::app|ios::binary);
    if(!fout)
       cout<<"\nFile creation Error!!!";
    else
    {
       iob.itemin();
       fout.write((char*)&iob,sizeof(iob));
       fout.close();
       cout<<"\nOne record successfully saved ";
    }
    getch();
}
void showallitem()
{
   item iob;
   ifstream fin;
   fin.open("item.dat",ios::in|ios::binary);
   if(!fin)
      cout<<"\nFile server not ready or item database missing";
   else
   {
      while(fin.read((char*)&iob,sizeof(iob)))
      {
	iob.itemout();
      }
   }
   fin.close();
   getch();
}
void searchitem()
{
 ifstream fin;
 fin.open("item.dat",ios::in|ios::binary);
 if(!fin)
 {
    cout<<"\nFile does not exist";
 }
 else
 {
   item iob;
   int ic,flag=0;
   cout<<"\nEnter item code to be searched:";
   cin>>ic;
   while(fin.read((char*)&iob,sizeof(iob)))
   {
      if(iob.geticode()==ic)
      {
	 flag=1;
	 break;
      }
   }
   if(flag==1)
   {
      cout<<"\nFound";
      iob.itemout();
   }
   else
   {
      cout<<"\nItem not found";
   }
   fin.close();
 }
 getch();
}
void moditem()
{
   fstream fio("item.dat",ios::in|ios::out|ios::binary);
  if(!fio)
    cout<<"\nServer is under maintainance";
  else
  {
    int isrch;int k=0;
    cin.get();
    cout<<"\nEnter the item code whose details you want to modify:";
    cin>>isrch;
    item iob;
    char ch;long pos;
    while(fio.read((char*)&iob,sizeof(iob)))
    {
      if(iob.geticode()==isrch)
      {
	cout<<"\nFound!!";
	iob.itemout();
	getch();
	iob.itemmodify();
	cout<<"\nAre you sure you want to modify the details?(Y/N):";
	cin>>ch;
	if(ch=='Y'||ch=='y')
	{
	  pos=-1L*sizeof(iob);
	  fio.seekg(pos,ios::cur);
	  fio.write((char*)&iob,sizeof(iob));
	  k=1;
	  break;
	}
     }
  }
   fio.close();
   if(k==1)
     cout<<"\nDetails have been modified in the database";
   else
       cout<<"\nRecord not found or modification cancelled by user!!!";
  }//end of else if file opened
}//end of function
void delitem()
{
  int flag=0;
  ifstream fin("item.dat",ios::in|ios::binary );
  ofstream fout1("temp.dat",ios::out|ios::binary);
  if(!fin||!fout1)
  {
    cout<<"\n items cannot be deleted";
  }
  else
  {
    item iob;
    int r;
    cout<<"\n Enter the item number to be removed: ";
    cin>>r;
    while(fin.read((char*)&iob,sizeof(iob)))
    {
      if(iob.geticode()!=r)
      {
	 fout1.write((char*)&iob,sizeof(iob));

      }
      else

	flag=1;

    }
  }
  fin.close();
  fout1.close();
  remove("item.dat");
  rename("temp.dat","item.dat");
   if(flag==1)
   {
     cout<<"\n the item record is deleted";
   }
   else
   {
     cout<<"\n the item does not exist";
   }
  getch();
}

/******************************************************
		  CLASS CUSTOMER
 ******************************************************/
class customer
{
   protected:
	   char cname[100];   //to store the name of customer
	   int ccode;        //to store the code of customer
	   char cadd[500];    //to store the address of customer
	   char cmob[11];    //to store the mobile number of customer

   public:
	  //Constructors
	  customer();
	  customer(int,char*,char*,char*);
	  customer(customer&);
	  //Destructor
	  ~customer();
	  //Accsessor functions
	  int getccode();
	  char* getcname();
	  int cmpname(char cn[]);
	  int cmpadd(char cadd[]);
	  int cmpmob(char cmob[]);
	  //Mutator functions
	  void setccode(int cc);
	  void setname(char cn[]);
	  void setadd(char add[]);
	  void setmob(char mob[]);
	  //Input Output functions
	  void customerin();
	  void customerout();
	  void customermod();
};//End of class customer
/********************************************
	 GENCCODE FUNCTION
 ********************************************/
void genccode(customer &cus)
{
   ifstream fin("member.dat",ios::in|ios::binary);
   if(!fin)
      cus.setccode(301);
   else
   {
      long pos=sizeof(customer)* -1L;
      fin.seekg(pos,ios::end);
      fin.read((char*)&cus,sizeof(cus));
      fin.close();
      cus.setccode(cus.getccode()+1);
   }
}
/********************************************************
	      Definition of member functions
 ********************************************************/
//Constructors
customer::customer()
{
   genccode(*this);
   strcpy(cname,"");
   strcpy(cadd,"");
   strcpy(cmob,"");
}
customer::customer(int c,char*n,char*a,char*m)
{
   ccode=c;
   strcpy(cname,n);
   strcpy(cadd,a);
   strcpy(cmob,m);
}
customer::customer(customer&t)
{
   ccode=t.ccode;
   strcpy(cname,t.cname);
   strcpy(cadd,t.cadd);
   strcpy(cmob,t.cmob);
}
//destructor
customer::~customer(){}
//accessor functions
int customer::getccode(){return ccode;}
char* customer::getcname(){return cname;}
int customer::cmpname(char cn[]){return strcmp(cname,cn);}
int customer::cmpadd(char cadd[]){return strcmp(cadd,cadd);}
int cmpmob(char cmob[]);
//mutator functions
void customer::setccode(int cc){ccode=cc;}
void customer::setname(char cn[]){strcpy(cname,cn);}
void customer::setadd(char add[]){strcpy(cadd,add);}
void customer::setmob(char mob[]){strcpy(cmob,mob);}
//input output functions
void customer::customerin()
{
  cout<<"\nMEMBER CODE: "<<ccode;
  cout<<"\nEnter your name: ";
  cin.get();
  cin.getline(cname,100);
  cout<<"\nEnter your mobile number: ";
  cin>>cmob;
  cout<<"\nEnter your address: ";
  cin.get();
  cin.getline(cadd,500);
}
void customer::customerout()
{
   cout<<"\n=============================================";
   cout<<"\nYour Member Code is   :"<<ccode;
   cout<<"\nYour Name is          :"<<cname;
   cout<<"\nYour Address is       :"<<cadd;
   cout<<"\nYour Mobile Number is :"<<cmob;
   getch();
}
void customer::customermod( )
{
   int ccd;
   char cn[20],cad[500],cmb[11];
   cout<<"\nEnter new values to update following fields "<<endl;
   cout<<"Enter(-1) to retain previous values";
   cin.get();
   cout<<"\nEnter updated customer name:";
   cin.getline(cn,20);
   if(strcmp(cn,"-1")!=0)
      strcpy(cname,cn);
   cout<<"\nEnter updated mobile number:";
   cin>>cmb;
   if(strcmp(cmb,"-1")!=0)
     strcpy(cmob,cmb);
   cout<<"\nEnter updated address:";
   cin.get();
   cin.getline(cad,500);
   if(strcmp(cad,"-1")!=0)
     strcpy(cadd,cad);
}
/*********************************************
	    Non member functions
 *********************************************/
void addcus()
{
     ofstream fout;
     customer cus;
     fout.open("member.dat",ios::in|ios::app|ios::binary);
     if(!fout)
	cout<<"\nFile creation error!";
     else
     {
	cus.customerin();
	fout.write((char*)&cus,sizeof(cus));
	fout.close();
     }
     cout<<"\nOne record successfully saved!";
     getch();
}

void searchcus()
{
 ifstream fin1;
 fin1.open("member.dat",ios::in|ios::binary);
 if(!fin1)
 {
    cout<<"\nFile does not exist";
 }
 else
 {
   customer cus;
   int mc,flag=0;
   cout<<"\nEnter member code to be searched:";
   cin>>mc;
   while(fin1.read((char*)&cus,sizeof(cus)))
   {
      if(cus.getccode()==mc)
      {
	 flag=1;
	 break;
      }
   }
   if(flag==1)
   {
      cout<<"\nFound";
      cus.customerout();
   }
   else
   {
      cout<<"\nMember not found";
   }
   fin1.close();
 }
}
void showcus()
{
   customer cus;
   ifstream fin;
   fin.open("member.dat",ios::in|ios::binary);
   if(!fin)
      cout<<"\nFile server not ready or item database missing";
   else
   {
      while(fin.read((char*)&cus,sizeof(cus)))
      {
	 cus.customerout();
      }
   }
   fin.close();
}
void modcus()
{
   fstream fio("member.dat",ios::in|ios::out|ios::binary);
   if(!fio)
      cout<<"\nServer is under maintainance";
   else
   {
     int csrch;int k=0;
     cin.get();
     cout<<"\nEnter the customer code whose details you want to modify:";
     cin>>csrch;
     customer cus;
     char ch;long pos;
     while(fio.read((char*)&cus,sizeof(cus)))
     {
       if(cus.getccode()==csrch)
       {
	 cout<<"\nFound!!";
	 cus.customerout();
	 getch();
	 cus.customermod();
	 cout<<"\nAre you sure you want to modify the details?(Y/N):";
	 cin>>ch;
	 if(ch=='Y'||ch=='y')
	 {
	   pos=-1L*sizeof(cus);
	   fio.seekg(pos,ios::cur);
	   fio.write((char*)&cus,sizeof(cus));
	   k=1;
	   break;
	 }
       }
    }
   fio.close();
   if(k==1)
      cout<<"\nDetails have been modified in the database";
   else
	cout<<"\nRecord not found or modification cancelled by user!!!";
  }//end of else if file opened
}//end of function
void delcus()
{
  int flag=0;
  ifstream fin("member.dat",ios::in|ios::binary );
  ofstream fout("temp.dat",ios::out|ios::binary);
  if(!fin||!fout)
  {
    cout<<"\n member cannot be deleted";
  }
  else
  {
    customer cus;
    int r;
    cout<<"\n Enter the customer code to be removed: ";
    cin>>r;
    while(fin.read((char*)&cus,sizeof(cus)))
    {
      if(cus.getccode()!=r)
      {
	 fout.write((char*)&cus,sizeof(cus));

      }
      else

	flag=1;

    }
  }
  fin.close();
  fout.close();
  remove("member.dat");
  rename("temp.dat","member.dat");
   if(flag==1)
   {
     cout<<"\n the member record is deleted";
   }
   else
   {
     cout<<"\n the member does not exist";
   }
  getch();
}
//Function prototype
void itemmenu();
/**********************************************
	       Class bill
 **********************************************/
class bill:private item, private customer
{
   private:
	   int billno;          //For the entry of bill number
   public:
	  //constructor
	  bill();
	  bill(int);
	  bill(bill&);
	  //destructor
	  ~bill();
	  //accessor functions
	  int getbillno();
	  //muator functions
	  void setbillno(int bn);
	  //input output functions
	  void genbill();
	  void total();
	  void showbill();
};  //End of class bill
/**************************************
       CONVERTTONO FUNCTION
 **************************************/
int converttono(char arr[])
{
   int i,number=0;
   int val=0;
   for(i=0;arr[i]!=NULL;i++)
   {
      switch(arr[i])
      {
	 case '0':val=0;break;
	 case '1':val=1;break;
	 case '2':val=2;break;
	 case '3':val=3;break;
	 case '4':val=4;break;
	 case '5':val=5;break;
	 case '6':val=6;break;
	 case '7':val=7;break;
	 case '8':val=8;break;
	 case '9':val=9;break;
      }
      number=number*10+val;
   }
   return number;
}
/*******************************************
     Definition of member functions
 ********************************************/
//constructors
bill::bill()
{
   billno=0;
}
bill::bill(int bno)
{
   billno=bno;
}
bill::bill(bill&t)
{
   billno=t.billno;
}
//Destructor
bill::~bill(){}
//accessor functions
int bill::getbillno(){return billno;}
//mutator function
void bill::setbillno(int bn){billno=bn;}
//input output function
void bill::genbill()
{
   clrscr();
   int itm,qty,flag=0;
   float sum=0;
   char ch='Y';
   item iob;
   int cd;
   cout<<"\nEnter your customer code:";
   cin>>cd;
   ifstream fin("member.dat",ios::in|ios::binary);
   customer cus;
   while(fin.read((char*)&cus,sizeof(cus)))
   {
     if(cus.getccode()==cd)
     {
	flag=1;
	break;
      }
   }
   if(!flag)
   {
      cout<<"\nYou are not authorised";
      return;
   }
   strcpy(cname,cus.getcname());
   fin.close();
   fin.open("invoice.txt",ios::in);
   if(!fin)
   {  getch();
      billno=101;
   }
   else
   {
     char word[50];
     while(fin.eof()==0)
     {
	fin>>word;
	if(fin.eof()!=0)
	   break;
	if(strcmpi(word,"BILL_NUMBER:")==0)
	{
	    fin>>word;
	    billno=converttono(word)+1;
	}
      }
      fin.close();
    }
   ofstream fout("invoice.txt",ios::out|ios::app);
   if(!fout)
     cout<<"\nServer is down try after some time!!!";
   else
   {
     fout<<"\nBILL_NUMBER: "<<billno
	 <<"\nCUSTOMER_CODE: "<<cd
	 <<"\nCUSTOMER_NAME: "<<cname;
     fout<<"\nITEM_CODE\tITEM_NAME\tPRICE\t DISCOUNT\t QUANTITY\tCOST";
    do
    {
     itemmenu();
     cout<<"\nEnter Item No : ";
     cin>>itm;
     cout<<"\nEnter qty     : ";
     cin>>qty;
     fstream fio("item.dat",ios::in|ios::out|ios::binary);
     if(!fio)
	cout<<"\nDatabase not ready!!!";
     else
     {
	while(fio.read((char*)&iob,sizeof(iob)))
	{
	  if(iob.geticode()==itm)
	  {
	   fout<<endl<<iob.geticode()
	   <<"\t\t"<<iob.getname()
	   <<"\t\t"<<iob.getprice()
	   <<"\t\t"<<iob.getdis()
	   <<"\t\t"<<qty
	   <<"\t "<<iob.getprice()*qty;

	   sum+=(iob.getprice()-iob.getdis())*qty;
	   //updating qty in database(item.dat)
	   iob.setqty(iob.getqty()-qty);
	   long pos=sizeof(iob)*-1L;
	   fio.seekp(pos,ios::cur);
	   fio.write((char*)&iob,sizeof(iob));
	  }
	}
	fio.close();
     }

     cout<<"\nDo you want to add more item [Y|N] : ";
     cin>>ch;
   }while(ch=='y'||ch=='Y');//end of do..while();

    float gst=sum*18.0/100.0;
    fout<<"\ntotal price  : "<<sum;
    fout<<"\tGST 18%      : "<<gst;
    fout<<"\nPayble amount: "<<sum+gst;
    fout<<"\n***** *****\n";
    cout<<"\n\nYour bill number: "<<billno;
     fout.close();
  }//end of else statement
}//end of function

void bill::showbill()
{
   clrscr();
   ifstream fin; int flag=0;
   char billno[20],line[200];
   fin.open("invoice.txt",ios::in);
   if(!fin)
      cout<<"\nBill details are not available!";
   else
   {
     cout<<"\nEnter your bill no: ";
     cin>>billno;
     char word1[50],word2[50];
     cout<<"\nBILL_NUMBER: "<<billno;
     while(fin.eof()==0)
     {
	fin>>word1;
	if(fin.eof()!=0)
	   break;
	if(strcmpi(word1,"BILL_NUMBER:")==0)
	{
	    fin>>word2;
	    if(strcmpi(word2,billno)==0)
	    {
	       flag=1;
	       break;
	    }
	    else
		flag=0;
	 }
      }
      while(fin.eof()==0&& flag==1)
      {
	fin.getline(line,200);
	if(strcmpi(line,"***** *****")==0)
	   break;
	cout<<"\n"<<line;
      }
    }
    fin.close();
   getch();
}
/*************************************************
      CLASS FOR CUSTOMER CARE SERVICES
 *************************************************/
class services
{
   private:
	  int n1;           //to enter the choice
	  char prob[500];   //to enter the problem
	  char inci[500];   //to enter the incident
	  char product[20]; //to enter the product
	  char matt[500];   //to enter the matter of concern
	  char sname[20];   //to enter the staff's name
   public:
	 //Constructors
	 services();
	 services(int,char*,char*,char*,char*,char*);
	 services(services&);
	 //Destructor
	 ~services();
	 //Input output functions
	 void prod();
	 void quality();
	 void staff();
	 void problem();
}; //End of class services
/**************************************
    Definition of member functions
 **************************************/
//constructors
services::services()
{
   n1=0;
   strcpy(prob,"");
   strcpy(inci,"");
   strcpy(product,"");
   strcpy(matt,"");
   strcpy(sname,"");
}
services::services(int n,char*pr,char*in,char*pd,char*ma,char*sn)
{
   n1=n;
   strcpy(prob,pr);
   strcpy(inci,in);
   strcpy(product,pd);
   strcpy(matt,ma);
   strcpy(sname,sn);
}
services::services(services&t)
{
   n1=t.n1;
   strcpy(prob,t.prob);
   strcpy(inci,t.inci);
   strcpy(product,t.product);
   strcpy(matt,t.matt);
   strcpy(sname,t.sname);
}
//Destructor
services::~services(){}
//input output functions
void services::prod()
{
   cout<<"\nLooking for some product that we don't have(yes=1 and no=0)";
   cin>>n1;
   if(n1==1)
   {
      cout<<"\nPlease write the product name and quantity:";
      cin.get();
      cin.getline(product,20);
      cout<<"\nWe will provide you this as soon as possible!!!";
   }
   else
   {
      cout<<"\nOkay";
   }
   getch();
}
void services::quality()
{
  cout<<"\nAre you not happy with the quality(yes=1 and no=0)";
  cin>>n1;
  if(n1==1)
  {
     cout<<"\nTell us your problem:";
     cin.get();
     cin.getline(prob,500);
     cout<<"\nWe will immediately take some actions";
  }
  else
      cout<<"\nOkay thanks for trusting us";
  getch();
}
void services::staff()
{
  cout<<"\nIs there any problem with the attitude of staff(yes=1 and no=0)";
  cin>>n1;
  if(n1==1)
  {
     cout<<"\nTell us the staff's name:";
     cin.get();
     cin.getline(sname,20);
     cin.get();
     cout<<"\nIncident: ";
     cin.getline(inci,500);
     cin.get();
     cout<<" and the problem is ";
     cin.getline(inci,500);
     cout<<"\nSorry about this and this won't happen again";
  }
  else
      cout<<"\nOkay";
  getch();
}
void services::problem()
{
  cout<<"\nIs there any other problem(yes=1 and no=0)";
  cin>>n1;
  if(n1==1)
  {
     cout<<"\nWrite it here:";
     cin.get();
     cin.getline(matt,500);
     cout<<"\nWe will look into the matter";
  }
  else
      cout<<"\nOkay\tThank you";
  getch();
}
/**************************************************
	       Item Menu function
 **************************************************/
void itemmenu()
{
   clrscr();
   item iob;
   cout<<"\n\n\t\tWELCOME TO THE ITEMS SELECTION MENU";
   cout<<"\n********************************************************************";
   ifstream fin("item.dat",ios::in|ios::binary);
   if(!fin)
      cout<<"\nFile opening error!";
   else
   {
    cout<<"\nITEM CODE\tITEM NAME\tPRICE\tDISCOUNT\tQUANTITY";
    while(fin.read((char*)&iob,sizeof(iob)))
     {
	cout<<endl<<iob.geticode()
	<<"\t\t"<<iob.getname()
	<<"\t\t"<<iob.getprice()
	<<"\t\t"<<iob.getdis()
	<<"\t\t"<<iob.getqty();
     }//end of while loop
     fin.close();
    }
}//end of function
/*************************************************
	      FUNCTION FOR FEEDBACK
 *************************************************/
void feedback()
{
   clrscr();
   int f1,f2,best,wrost,rec;
   char sug[500];
   cout<<"\n\n\t\tFEEDBACK";
   cout<<"\n***************************************";
   cout<<"\nOn the scale of 0-10 how much did you like our hospitality:";
   cin>>f1;
   if(f1>10)
   {
      cout<<"\nInvalid Entry!";return;
   }
   cout<<"\nWere you welcomed by our staff(yes=1 and no=0):";
   cin>>f2;
   cout<<"\nSelect the best and the worst from the following:";
   cout<<"\n\t1.Attitude of staff"
       <<"\n\t2.Quality of product"
       <<"\n\t3.Variety of product"
       <<"\n\t4.Environment of the shop"
       <<"\n\t5.Price"
       <<"\n\t6.customer care service"
       <<"\n\t7.Nothing";
   cout<<"\n\tBEST:";
   cin>>best;
   if(best>7)
   {
      cout<<"\nInvalid Entry";return;
   }
   cout<<"\n\tWORST:";
   cin>>wrost;
   if(wrost>7)
   {
      cout<<"\nInvalid Entry!";return;
   }
   cout<<"\nWould you recommend our shop to any one(yes=1 and no=0):";
   cin>>rec;
   cout<<"\nDo you have any suggestions:";
   cin.get();
   cin.getline(sug,500);
   cout<<"\nThank you for your support";
   getch();
}
/*************************************************
	  ADMINISTRATOR FUNCTION
 *************************************************/
void admin()
{
  int ch1;
  do{
      clrscr();
      cout<<"\n\n\tWelcome to the administrator page";
      cout<<"\n*********************************************";
      cout<<"\n\t01. Add item";
      cout<<"\n\t02. Show items";
      cout<<"\n\t03. Modify item";
      cout<<"\n\t04. Delete item";
      cout<<"\n\t05. Back to previous menu";
      cout<<"\n\tPlease Select Your Option (1-5) ";
      cin>>ch1;
      switch(ch1)
      {
	case 1:additem();
		break;
	case 2:showallitem();
		break;
	case 3:moditem();
		break;
	case 4:delitem();
		break;
	case 5:break;
	default:cout<<"\nInvalid Choice";
      }
      getch();
  }while(ch1!=5);
}
/**********************************************
	      ITEMBILL FUNCTION
 **********************************************/
void itembill()
{
 bill bob;
 int ch4;
 do{
    clrscr();
    cout<<"\n\n\tWelcome to the item page";
    cout<<"\n**********************************";
    cout<<"\n\t01. Select item";
    cout<<"\n\t02. Search item";
    cout<<"\n\t03. Back to previous menu";
    cout<<"\n\tPlease Select Your Option (1-3) ";
    cin>>ch4;
    switch(ch4)
    {
    case 1:bob.genbill();break;
    case 2:searchitem();break;
    case 3:break;
    default:cout<<"\nInvalid Choice";
    }
    getch();
   }while(ch4!=3);
}
/*********************************************
	 CUSMENU FUNCTION
 *********************************************/
void cusmenu()
{
 int ch5;
 do{
    clrscr();
    cout<<"\n\n   Welcome to the customer page";
    cout<<"\n**************************************";
    cout<<"\n\t01. Add member";
    cout<<"\n\t02. Dispaly members";
    cout<<"\n\t03. Modify members";
    cout<<"\n\t04. Delete member";
    cout<<"\n\t05. Back to previous menu";
    cout<<"\n\nPlease Select Your Option (1-4) ";
    cin>>ch5;
    switch(ch5)
    {
    case 1:addcus();break;
    case 2:showcus();break;
    case 3:modcus();break;
    case 4:delcus();break;
    case 5:break;
    default:cout<<"\nInvalid Choice";
    }
    getch();
   }while(ch5!=5);
}
/***********************************************
	      CARE FUNCTION
 ***********************************************/
void care()
{
 int ch3;
 services ser;
 do{
    clrscr();
    cout<<"\n\n  WELCOME TO THE CUSTOMER CARE SERVICES";
    cout<<"\n*******************************************";
    cout<<"\n\n\t1.Product Quary";
    cout<<"\n\t2.Quality Quary";
    cout<<"\n\t3.Staff Problem";
    cout<<"\n\t4.Other problem";
    cout<<"\n\t5.Back to previous Menu";
    cout<<"\n\n\tPlease Select Your Option (1-5) ";
    cin>>ch3;
    switch(ch3)
    {
    case 1:ser.prod();break;
    case 2:ser.quality();break;
    case 3:ser.staff();break;
    case 4:ser.problem();break;
    case 5:break;
    default:cout<<"\nInvalid choice";break;
    }
   }while(ch3!=5);
}
/***********************************************
	       CUSTOMER FUNCTION
 ***********************************************/
void member()
{
 bill bob;
 int ch2;
 do{
    clrscr();
    cout<<"\n\n  Welcome to the customer page";
    cout<<"\n**************************************";
    cout<<"\n\t01. ITEMS MENU";
    cout<<"\n\t02. CUSTOMER DETAILS";
    cout<<"\n\t03. BILL DETAILS";
    cout<<"\n\t04. CUSTOMER CARE SERVICES";
    cout<<"\n\t05. FEEDBACK";
    cout<<"\n\t06. BACK TO PREVIOUS MENU";
    cout<<"\n\tPlease Select Your Option (1-6) ";
    cin>>ch2;
    switch(ch2)
    {
      case 1:itembill();break;
      case 2:cusmenu();break;
      case 3:bob.showbill();break;
      case 4:care();break;
      case 5:feedback();break;
      case 6:break;
      default:cout<<"\nInvalid Choice!";
    }
    getch();
 }while(ch2!=6);
}

/*************************************************
		MAIN FUNCTION
 *************************************************/
void main()
{
  item iob;
  services ser;
  bill bob;
  customer cus;
  int ch,ch1,ch2,ch3,ch4,ch5;
  intro();
  do
  {
   clrscr();
   cout<<"\n\t\t\tWELCOME";
   cout<<"\n\n\t\tALL IN ONE GENERAL STORE";
   cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
   cout<<"\n\n\n\tMAIN MENU";
   cout<<"\n\n\t01. ADMINISTRATOR";
   cout<<"\n\n\t02. CUSTOMER";
   cout<<"\n\n\t03. EXIT";
   cout<<"\n\n\tPlease Select Your Option (1-3) ";
   cin>>ch;
   switch(ch)
  {
    case 1:admin();break;
    case 2:member();break;
    case 3:cout<<"\n\n\nThank you\t\t\t\t\t\t\t Visit again";break;
    default:cout<<"\nInvalid choice";
  }
  getch();
 }while(ch!=3);
}
/***************************************************
	       END OF PROGRAM
 ***************************************************/