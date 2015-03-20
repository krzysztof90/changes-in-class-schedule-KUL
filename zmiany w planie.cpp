#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>
#include<ctime>
#include<conio.h>
using namespace std;

int Zwischenraum=2;
int zuerstZwischenraum=1;
int letztenZwischenraum=1;

string Textteil (string a, int l, int p)
{
	string b="";
	for(int i=0; i<=p-l; i++)
		b+=a[l+i];
	return b;
}

int suchenText (string a, string gesucht, int von, int bis, int Elementnummer)
{
	int Ausgang=-1;
	for(int i=von; i<bis+1 && Elementnummer!=0; i++)
	{
		int j=0;
		while(a[i+j]==gesucht[j] && j<gesucht.size())
			j++;
		if(j==gesucht.size())
		{
			Ausgang=i;
			Elementnummer--;
		}
	}
	if(Elementnummer!=0)
		return -1;
	return Ausgang;
}

int suchenText (string a, string gesucht, int l, int p)
{
	int Umfang=gesucht.size();
	for(int i=l; i<=p; i++)
	{
		int j=0;
		while(a[i+j]==gesucht[j] && j<Umfang)
			j++;
		if(j==Umfang)
			return i;
	}
	return -1;
}

string ausschliessenTextteil(string a, int l, int p)
{
	if(l<=p)
		return Textteil(a,0,l-1)+Textteil(a,p+1,a.size()-1);
	return a;
}

string ausschliessen_vorn_Raume (string a)
{
	int c=0;
	while(c<=a.size()-1 && a[c]==' ')
		c++;
	if(c==a.size())
		return a;
	return ausschliessenTextteil(a,0,c-1);
}

string int_zu_string (int x)
{
	string s="";
	string hilfe="";
	while(x>0)
	{
		hilfe+=(x%10)+48;
		x/=10;
	}
	for(int i=hilfe.size()-1; i>=0; i--)
		s+=hilfe[i];
	return s;
}

const int l=250; //liczba kierunków

void herunterladen(string was, string nach)
{
	string a="powershell (New-Object System.Net.WebClient).DownloadFile(\\\""+was+"\\\",\\\""+nach+"\\\")";
	const char* b=a.c_str();
	fstream Datei;
	do
	{
		system(b);
		Datei.open(nach.c_str());
		if(!Datei)
		{
			system("cls");
			cout<<"B\210\245d pobierania. Ponowne pobieranie...";
		}
	} while(!Datei);
}

void stellenFenstertitel()
{
	SetConsoleTitle("Zmiany w planie KUL");
}

void Fenstergrosse(int &Weite, int &Hohe)
{
	CONSOLE_SCREEN_BUFFER_INFO Konsolepufferinformationen;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Konsolepufferinformationen);
	SMALL_RECT Rechteck=Konsolepufferinformationen.srWindow;
	SMALL_RECT* Rechteck2=&Rechteck;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, Rechteck2);
	Weite=Rechteck2->Right+1;
	Hohe=Rechteck2->Bottom+1;
}

int anfanglichWeite;
int anfanglichHohe;

void stellenPuffergrosse(int Weite, int Hohe)
{
	if(Weite<anfanglichWeite)
		Weite=anfanglichWeite;
	if(Hohe<anfanglichHohe)
		Hohe=anfanglichHohe;
	system("cls");
	//rozmiar buforu
	string a="mode con: cols="+int_zu_string(Weite)+" lines="+int_zu_string(Hohe);
	const char* b=a.c_str();
	system(b);
	//rozmiar okna (zmienia tylko na czas jednorazowego otwarcia okna). Tylko zmniejsza, nie mo¿e zwiêkszyæ, dlatego wartoœci nie mog¹ przekraczaæ rozmiarów buforu
  SMALL_RECT WinRect = {0, 0, anfanglichWeite-1, anfanglichHohe-1};
  SMALL_RECT* WinSize=&WinRect;
  SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, WinSize);
}

void tauschen_zu_PL(string &a)
{
	if(a=="")
		return;
	int wo_sie_PL[a.size()/2];
		for(int i=a.size()/2-1; i>=0; i--)
			wo_sie_PL[i]=0;
	int c=0;
	for(int i=0; i<a.size()-1; i++)
	{
		if(a[i]==-60)
			switch(a[i+1])
			{
				case -124: {a[i]='\244'; wo_sie_PL[c]=i+1; c++; break;} //¥
				case -123: {a[i]='\245'; wo_sie_PL[c]=i+1; c++; break;} //¹
				case -122: {a[i]='\217'; wo_sie_PL[c]=i+1; c++; break;} //Æ
				case -121: {a[i]='\206'; wo_sie_PL[c]=i+1; c++; break;} //æ
				case -104: {a[i]='\250'; wo_sie_PL[c]=i+1; c++; break;} //Ê
				case -103: {a[i]='\251'; wo_sie_PL[c]=i+1; c++; break;} //ê
			}
		if(a[i]==-59)
			switch(a[i+1])
			{
				case -127: {a[i]='\235'; wo_sie_PL[c]=i+1; c++; break;} //£
				case -126: {a[i]='\210'; wo_sie_PL[c]=i+1; c++; break;} //³
				case -125: {a[i]='\343'; wo_sie_PL[c]=i+1; c++; break;} //Ñ
				case -124: {a[i]='\344'; wo_sie_PL[c]=i+1; c++; break;} //ñ
				case -102: {a[i]='\227'; wo_sie_PL[c]=i+1; c++; break;} //Œ
				case -101: {a[i]='\230'; wo_sie_PL[c]=i+1; c++; break;} //œ
				case -71: {a[i]='\215'; wo_sie_PL[c]=i+1; c++; break;} //
				case -70: {a[i]='\253'; wo_sie_PL[c]=i+1; c++; break;} //Ÿ
				case -69: {a[i]='\275'; wo_sie_PL[c]=i+1; c++; break;} //¯
				case -68: {a[i]='\276'; wo_sie_PL[c]=i+1; c++; break;} //¿
			}
		if(a[i]==-61)
			switch(a[i+1])
			{
				case -109: {a[i]='\340'; wo_sie_PL[c]=i+1; c++; break;} //Ó
				case -77: {a[i]='\242'; wo_sie_PL[c]=i+1; c++; break;} //ó
			}
	}
	for(int i=c-1; i>=0; i--)
		a=ausschliessenTextteil(a,wo_sie_PL[i],wo_sie_PL[i]);
}

void KurselisteHerunterladen(string (&Kurs)[l][3], int &wie_viele_Kurse) //[][0] - nr kierunku; [][1] - nazwa kierunku; [][2] - nr wydzia³u
{
	stellenPuffergrosse(38+letztenZwischenraum,10); //"B³¹d pobierania..."
	cout<<"Pobieranie listy kierunk\242w...";
	herunterladen("http://e.kul.pl/qlplan.html","qwerty");
	stellenFenstertitel();
	ifstream Datei ("qwerty");
	int k=15; //liczba wydzia³ów
	string a;
	while(suchenText(a,"<tr><td><strong>Prosz",0,0)==-1 && !Datei.eof())
		getline(Datei,a);
	getline(Datei,a);
	string Abteilungnummer[k];
	//pierwsza linijka:
	Abteilungnummer[0]=Textteil(a,107,suchenText(a,"\"",107,111)-1);
	getline(Datei,a);
	for(int i=1; a!="</select></td></tr>"; i++)
	{
		Abteilungnummer[i]=Textteil(a,15,suchenText(a,"\"",15,19)-1);
		getline(Datei,a);
	}
	Datei.close();
	remove("qwerty");
	wie_viele_Kurse=0;
	for(int i=0; Abteilungnummer[i]!=""; i++)
	{
		Datei.close(); //nie wiadomo dlaczego, ale za pierwszym razem siê nie zamyka
		herunterladen("http://e.kul.pl/qlplan.html?wid=" +Abteilungnummer[i]+ "&op=1","qwerty");
		Datei.open("qwerty");
		while(suchenText(a,"<tr><td><strong>Prosz",0,0)==-1 && !Datei.eof())
			getline(Datei,a);
		getline(Datei,a); getline(Datei,a);
		while(suchenText(a,"</select></td></tr>",0,0)==-1)
		{
			Kurs[wie_viele_Kurse][0]=Textteil(a,15,suchenText(a,"\"",15,19)-1);
			Kurs[wie_viele_Kurse][1]=Textteil(a,suchenText(a,">",18,a.size()-10)+1,a.size()-10);
			tauschen_zu_PL(Kurs[wie_viele_Kurse][1]);
			Kurs[wie_viele_Kurse][2]=Abteilungnummer[i];
			wie_viele_Kurse++;
			getline(Datei,a);
		}
		Datei.close();
		remove("qwerty");
	}
	stellenFenstertitel();
}

void quicksort(string a[l][3], int s, int e)
{
	int i=s, j=e;
	string hilfs_variable;
	string x=a[(s+e)/2][1];
	do
	{
		while(a[i][1]<x)
			i++;
		while(a[j][1]>x)
			j--;
		if(i<=j)
    {
			hilfs_variable=a[i][0];
			a[i][0]=a[j][0];
		 	a[j][0]=hilfs_variable;
			hilfs_variable=a[i][1];
			a[i][1]=a[j][1];
			a[j][1]=hilfs_variable;
			hilfs_variable=a[i][2];
			a[i][2]=a[j][2];
			a[j][2]=hilfs_variable;
				i++;
				j--;
		}
	} while(i<=j);
	if(s<j)
		quicksort(a,s,j);
	if(i<e)
		quicksort(a,i,e);
}

bool gleichText(string a, string b) //bez rozró¿niania wielkoœci liter
{
	if(a.size()!=b.size()) return 0;
	for(int i=0; i<a.size(); i++)
	{
		if(a[i]>='A' && a[i]<='Z')
		{
			if (a[i]!=b[i] && a[i]+32!=b[i])
				return 0;
		}
		else
		{
			if(a[i]>='a' && a[i]<='z')
			{
				if(a[i]!=b[i] && a[i]-32!=b[i])
					return 0;
			}
			else
			{
				if(a[i]==-92 || a[i]==-88 || a[i]==-29 || a[i]==-105 || a[i]==-67)
				{
					if(a[i]!=b[i] && a[i]+1!=b[i])
						return 0;
				}
				else
				{
					if(a[i]==-91 || a[i]==-87 || a[i]==-28 || a[i]==-104 || a[i]==-66)
					{
						if(a[i]!=b[i] && a[i]-1!=b[i])
							return 0;
					}
					else
					{
						if(a[i]==-113 || a[i]==-122)
						{
							if(b[i]!=-113 && b[i]!=-122)
								return 0;
						}
						else
						{
							if(a[i]==-99 || a[i]==-120)
							{
								if(b[i]!=-99 && b[i]!=-120)
									return 0;
							}
							else
							{
								if(a[i]==-115 || a[i]==-85)
								{
									if(b[i]!=-115 && b[i]!=-85)
									return 0;
								}
								else
								{
									if(a[i]==-32 || a[i]==-94)
									{
										if(b[i]!=-32 && b[i]!=-94)
											return 0;
									}
									else
										if(a[i]!=b[i])
											return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

int aktuelleDatum()
{
	time_t a=time(NULL);
	struct tm *y=localtime(&a);
	if(y->tm_mon>6)
		return (y->tm_year-114)*10; //od sierpnia
	return (y->tm_year-115)*10+5; //od pocz¹tku roku
}

int q=400; //liczba przedmiotów. Maksymalnie znalaz³o 187 (48: semestr7)

int string_zu_int (string s)
{
	int x=0;
	int y=1;
	for(int i=s.size()-1; i>=0; i--)
	{
		if(s[i]-48<0 || s[i]-48>9)
			return -1;
		x+=(s[i]-48)*y;
		y*=10;
	}
	return x;
}

int zuruck_suchen (string a, string gesucht, int p, int l, int Elementnummer)
{
	int Ausgang=-1;
	for(int i=p; i>=l && Elementnummer!=0; i--)
	{
		int j=0;
		while(a[i+j]==gesucht[j] && j<gesucht.size())
			j++;
		if(j==gesucht.size())
		{
			Ausgang=i;
			Elementnummer--;
		}
	}
	if(Elementnummer!=0)
		return -1;
	return Ausgang;
}

bool jaODERnein(string a, int Weite, int Hohe)
{
	cout<<a<<"\n(T/N): ";
	do
	{
	char c=getch();
	switch(c)
		{
			case 'Y': case 'y': case 'T': case 't': case 'J': case 'j': case 13: return 1; //13 - enter
			/*case 'H': //czasem strza³ka w górê interpretowana jako 'H'*/ case 'h': case 0:
			{
				stellenPuffergrosse(108+letztenZwischenraum,12);
				cout<<"Aby zmieni\206 rozmiar okna lub cznionk\251 kliknij prawym przyciskiem myszy na belce okna, nast\251pnie w\210a\230ciwo\230ci."<<endl;
				cout<<"Aby przejrze\206 wszystkie zmiany u\276ywaj poziomych pask\242w przewijania."<<endl;
				cout<<"My\230lnik w kom\242rce oznacza brak zmian."<<endl;
				cout<<"Pami\251taj, \276e program uwzgl\251dnia zmiany tylko wybranych przez Ciebie specjalizacji."<<endl;
				cout<<"Program tworzy pliki:\n\tzmiany w planie.ini\n\tstary plan.html\n\tnowy plan.html\nPrzechowuj je w folderze razem z programem."<<endl;
				cout<<"Aby uzyska\206 wi\251cej pomocy skontaktuj si\251 ze mn\245: chrisek1000@gmail.com;"<<endl;
				system("pause");
				stellenPuffergrosse(Weite, Hohe);
				return jaODERnein(a, Weite, Hohe);
			}
			case 'N': case 'n': case ' ': case 27: return 0; //27 - esc
		}
	} while(1);
}

void loschen(string a1[], string a2[][2], int Nummer)
{
	for(int i=Nummer; a1[i]!=""; i++)
	{
		a1[i]=a1[i+1];
		a2[i][0]=a2[i+1][0];
		a2[i][1]=a2[i+1][1];
	}
}

int suchen_oder (string a, string gesucht[], int wie_viele, int l, int p)
{
	for(int i=l; i<=p; i++)
		for(int k=0; k<wie_viele; k++)
		{
			int Umfang=gesucht[k].size();
			int j=0;
			while(a[i+j]==gesucht[k][j] && j<Umfang)
				j++;
			if(j==Umfang)
				return i;
		}
	return -1;
}

string tauschenText(string a, string was, string zu)
{
	int wo=suchenText(a,was,0,a.size()-1);
	if(wo!=-1)
		a=Textteil(a,0,wo-1)+zu+Textteil(a,wo+was.size(),a.size()-1);
	return a;
}

void wahlenSpezialitaten(string Semester, string Kurs, string NICHTzeigen[][2])
{
	stellenPuffergrosse(38+letztenZwischenraum,10); //"B³¹d pobierania..."
	cout<<"Pobieranie listy specjalno\230ci...";
	herunterladen("http://e.kul.pl/qlprogram.html?ra=1&etap="+Semester+"&kid="+Kurs+"&op=2","qwerty");
	stellenFenstertitel();
	ifstream Datei("qwerty");
	string Gattung[q]; //pomocnicza zwi¹zana z NICHTzeigen
	int i=0;
	string Spezialitaten[40]; //maksymalnie znalaz³o 24 specjalnoœci
	int j=0; //ile specjalnoœci
	string a;
	while(suchenText(a,"&nbsp",0,0)==-1 && !Datei.eof())
		getline(Datei,a);
	while(!Datei.eof()) //dalej jest break
	{
		if(suchenText(a,"Brak danych",0,a.size()-1)!=-1)
			break;
		if(a[a.size()-1]!='>') //czasem linijki s¹ rozdzielone
		{
			string b;
			getline(Datei,b);
			a+=b;
		}
		string c;
		if(i) //¿eby nie wziê³o [-1]
			c=Gattung[i-1];
		int d=8;
		if(a[suchenText(a,"<",0,a.size()-1,d-1)+4]=='c')
		{
			c=Textteil(a,suchenText(a,">",0,a.size()-1,d-1)+1,suchenText(a,"<",0,a.size()-1,d)-1);
			if(a[suchenText(a,"<",0,a.size()-1,d)+2]!='t') //niektóre nazwy specjalnoœci s¹ z podzia³em wiersza. Zapis tylko do dwóch, bo ewentualny trzeci wiersz mo¿na pomin¹æ
				c+="\t"+Textteil(a,suchenText(a,">",0,a.size()-1,d)+1,suchenText(a,"<",0,a.size()-1,d+1)-1);
		}
		if(a[0]=='&')
		{
			d=23;
			c=Textteil(a,suchenText(a,">",0,a.size()-1,d-1)+1,suchenText(a,"<",0,a.size()-1,d)-1);
			if(a[suchenText(a,"<",0,a.size()-1,d)+2]!='t')
				c+="\t"+Textteil(a,suchenText(a,">",0,a.size()-1,d-1)+1,suchenText(a,"<",0,a.size()-1,d)-1);
		}
		tauschen_zu_PL(c);
		Gattung[i]=c;
		if(i)
		{
			NICHTzeigen[i-1][1]=Textteil(a,suchenText(a,">",0,a.size()-1,2)+1,suchenText(a,"<",0,a.size()-1,3)-1); //mo¿e byæ szukanie nie do size()-1, tylko do tego powy¿szego pi¹tego nawiasu od koñca
			tauschen_zu_PL(NICHTzeigen[i-1][1]);
		}
		string Gegenstand=
			Textteil(a,zuruck_suchen(a,">",a.size()-1,0,5)+1,zuruck_suchen(a,"<",a.size()-1,0,4)-1)+
			Textteil(a,zuruck_suchen(a,">",a.size()-1,0,4)+1,zuruck_suchen(a,"<",a.size()-1,0,3)-1);
		tauschen_zu_PL(Gegenstand);
		Gegenstand=tauschenText(Gegenstand, "Grupa:", "Grupa"); //w planie studiów jest "Grupa: ", w rozk³adzie zajêæ jest "Grupa "
		if(Gegenstand=="Obja\230nienia:" || suchenText(a,"Notes:",0,a.size()-1)!=-1) //w ang. jest Notes zamiast Objaœnienia, ale miêdzy 7-6 nawiasach trójk¹tnych od ty³u
		{
			Gattung[i]=""; //trzeba zerowaæ, ¿eby liczba w Gattung odpowiada³a NICHTzeigen, bo potem pêtla do Gattung[i]!=""
			break;
		}
		NICHTzeigen[i][0]=Gegenstand;
		i++;
		if(!j || c!=Spezialitaten[j-1])
		{
			Spezialitaten[j]=c;
			j++;
		}
		getline(Datei,a);
		if(a[a.size()-1]!='>')
		{
			string b;
			getline(Datei,b);
			a+=b;
		}
		getline(Datei,a);
	}
	bool zeigen[j];
		for(int i=0; i<j; i++)
			zeigen[i]=0;
	//j - ile specjalnoœci
	if(j>1)
	{
		string a="";
		int Weite=60+letztenZwischenraum, Hohe=4+j;
		for(int i=0; i<j; i++)
		{
			int hilfsWeite=8+Spezialitaten[i].size()+letztenZwischenraum;
			int u=suchenText(Spezialitaten[i], "\t", 0, Spezialitaten[i].size()-1);
			if(u!=-1)
				hilfsWeite=hilfsWeite+8-u%8-1; //maksymalny tabulator to 8 (ró¿ny w zale¿noœci od tego, w której kolumnie jest). -1, bo tabulator ju¿ policzony jako size()
			if(hilfsWeite>Weite)
				Weite=hilfsWeite;
		}
		stellenPuffergrosse(Weite, Hohe);
		do
		{
			bool bereits_leer=1;
			for(int i=0; i<j; i++)
				if(!zeigen[i])
				{
					bereits_leer=0;
					break;
				}
			if(bereits_leer)
				break;
			cout<<"Wybierz grupy zaj\251\206, kt\242re chcesz, aby by\210y brane pod uwag\251:\n";
			bool z=1;
			for(int i=0; i<j; i++)
				if(zeigen[i])
				{
					z=0;
					break;
				}
			if(z)
				cout<<"0\tPOKAZUJ WSZYSTKIE\n";
			for(int i=0; i<j; i++)
				if(!zeigen[i])
					cout<<i+1<<"\t"<<Spezialitaten[i]<<endl;
			if(!z)
				cout<<"0\tZAKO\343CZ WYB\340R\n00\tZACZNIJ WYB\340R OD NOWA\n";
			cout<<"Wpisuj numery: ";
			getline(cin,a);
			a=ausschliessen_vorn_Raume(a);
			if(a=="0")
			{
				if(z)
					{
						for(int i=0; i<j; i++)
							zeigen[i]=1;
					}
				break;
			}
			if(a=="00")
				for(int i=0; i<j; i++)
					zeigen[i]=0;
			bool ob_ohne_raum=1;
			for(int i=0; i<a.size(); i++)
				if(a[i]==' ' || a[i]==',' || a[i]==';' || a[i]=='-')
				{
					ob_ohne_raum=0;
					break;
				}
			if(!ob_ohne_raum)
			{
				string h[3]={" ",",",";"};
				string g[10]={"0","1","2","3","4","5","6","7","8","9"};
				int n1=0, n2=suchen_oder(a,h,3,0,a.size()-1);
				while(n1!=-1)
				{
					string vorubergehend1=Textteil(a,n1,n2-1);
					int hilfs_variable=suchenText(vorubergehend1,"-",0,vorubergehend1.size()-1);
					if(hilfs_variable!=-1) //Je¿eli myœlnik
					{
						int vorubergehend1_1=string_zu_int(Textteil(vorubergehend1,0,hilfs_variable-1));
						int vorubergehend1_2=string_zu_int(Textteil(vorubergehend1,hilfs_variable+1,vorubergehend1.size()-1));
						if(vorubergehend1_1!=-1 && vorubergehend1_2!=-1)
						{
							if(vorubergehend1_1<=vorubergehend1_2)
							{
								for(int i=vorubergehend1_1;i<=vorubergehend1_2; i++)
									if(i>=1 && i<=j)
										zeigen[i-1]=1;
							}
							else
							{
								for(int i=vorubergehend1_1;i>=vorubergehend1_2; i--)
									if(i>=1 && i<=j)
										zeigen[i-1]=1;
							}
						}
					}
					else
					{
						int vorubergehend2=string_zu_int(vorubergehend1);
						if(vorubergehend2>=1 && vorubergehend2<=j)
							zeigen[vorubergehend2-1]=1;
					}
					n1=suchen_oder(a,g,10,n2+1,a.size()-1);
					n2=suchen_oder(a,h,3,n1+1,a.size()-1);
						if(n2==-1)
							n2=a.size();
				}
			}
			else
			{
				if(j<=9)
				{
					for(int i=0; i<a.size(); i++) if(a[i]>='1' && a[i]<=j+48)
						zeigen[a[i]-48-1]=1; //je¿eli wybór jednocyfrowych i kilka cyfr wpisane bez spacji (i innych wy¿ej wymienionych znaków)
				}
				else
				{
					int hilfs_variable=string_zu_int(a);
					if(hilfs_variable>=1 && hilfs_variable<=j)
						zeigen[hilfs_variable-1]=1;
				} //je¿eli normalnie: dwucyfrowe, linijkê wy¿ej normalnie dla jednocyfrowych
			}
			system("cls");
		} while(a!="0");
	}
	if(j==1)
		zeigen[0]=1;
	for(int i=0; i<j; i++)
		if(zeigen[i])
		{
			string Feld[15]={"to choose from","at Choice","nieobowi\245zkowe","seminar","lective","Obligatory","przygotowanie pracy","promotora","jeden","thesis","Thesis","Fakult","Seminar","Praca","do wyboru"};
			//w wypadku zmiany iloœci zmiennych zmieniæ liczbê przy deklaracji tablicy i linijkê ni¿ej
			if(suchen_oder(Spezialitaten[i],Feld,15,0,Spezialitaten[i].size()-1)!=-1 &&
				suchenText(Spezialitaten[i],"Specjalno\230ci fakultatywne",0,Spezialitaten[i].size()-1)==-1 &&
				suchenText(Spezialitaten[i],"fakultatywnie",0,Spezialitaten[i].size()-1)==-1 &&
				suchenText(Spezialitaten[i],"\227cie\276ka dydaktyczna do wyboru",0,Spezialitaten[i].size()-1)==-1 &&
				suchenText(Spezialitaten[i],"proseminarium obowi\245zkowe",0,Spezialitaten[i].size()-1)==-1 &&
				suchenText(Spezialitaten[i],"w ramach proseminarium",0,Spezialitaten[i].size()-1)==-1)
			{
				int wo_Gattung=0;
				while(Gattung[wo_Gattung]!=Spezialitaten[i])
					wo_Gattung++;
				int wie_viele_Gegenstand=0;
				while(Gattung[wo_Gattung+wie_viele_Gegenstand]==Spezialitaten[i])
					wie_viele_Gegenstand++;
				bool zeigen2[wie_viele_Gegenstand];
				if(wie_viele_Gegenstand>1)
				{
					for(int l=0; l<wie_viele_Gegenstand; l++)
						zeigen2[l]=0;
					int Weite=29+letztenZwischenraum; //"zakoñcz wybór + tabulator
					int Hohe=5+wie_viele_Gegenstand;
					for(int l=0; l<wie_viele_Gegenstand; l++)
					{
						int hilfsWeite=8+NICHTzeigen[wo_Gattung+l][0].size()+14+NICHTzeigen[wo_Gattung+l][1].size()+letztenZwischenraum;
						if(hilfsWeite>Weite) Weite=hilfsWeite;
					}
					stellenPuffergrosse(Weite, Hohe);
					do
					{
						bool bereits_leer=1;
							for(int l=0; i<wie_viele_Gegenstand; l++)
								if(!zeigen2[l])
								{
									bereits_leer=0;
									break;
								}
						if(bereits_leer)
							break;
						cout<<"Wybierz z:"<<endl<<Spezialitaten[i]<<endl;
						bool z=1;
						for(int l=0; l<wie_viele_Gegenstand; l++)
							if(zeigen2[l])
							{
								z=0;
								break;
							}
						if(z)
							cout<<"0\tPOKAZUJ WSZYSTKIE\n";
						for(int l=0; l<wie_viele_Gegenstand; l++)
							if(!zeigen2[l])
						cout<<l+1<<"\t"<<NICHTzeigen[wo_Gattung+l][0]<<"; prowadz\245cy: "<<NICHTzeigen[wo_Gattung+l][1]<<endl;
						if(!z)
							cout<<"0\tZAKO\343CZ WYB\340R\n00\tZACZNIJ WYB\340R OD NOWA\n";
						cout<<"Wpisuj numery: ";
						getline(cin,a);
						a=ausschliessen_vorn_Raume(a);
						if(a=="0")
						{
							if(z)
							{
								for(int l=0; l<wie_viele_Gegenstand; l++)
									zeigen2[l]=1;
							}
							break;
						}
						if(a=="00")
						for(int l=0; l<wie_viele_Gegenstand; l++)
							zeigen2[l]=0;
						bool ob_ohne_raum=1;
						for(int l=0; l<a.size(); l++)
							if(a[l]==' ' || a[l]==',' || a[l]==';' || a[l]=='-')
							{
								ob_ohne_raum=0;
								break;
							}
						if(!ob_ohne_raum)
						{
							string h[3]={" ",",",";"};
							string g[10]={"0","1","2","3","4","5","6","7","8","9"};
							int n1=0;
							int n2=suchen_oder(a,h,3,0,a.size()-1);
							while(n1!=-1)
							{
								string vorubergehend1=Textteil(a,n1,n2-1);
								int hilfs_variable=suchenText(vorubergehend1,"-",0,vorubergehend1.size()-1);
								if(hilfs_variable!=-1)
								{
									int vorubergehend1_1=string_zu_int(Textteil(vorubergehend1,0,hilfs_variable-1));
									int vorubergehend1_2=string_zu_int(Textteil(vorubergehend1,hilfs_variable+1,vorubergehend1.size()-1));
									if(vorubergehend1_1!=-1 && vorubergehend1_2!=-1)
									{
										if(vorubergehend1_1<=vorubergehend1_2)
										{
											for(int l=vorubergehend1_1;l<=vorubergehend1_2; l++)
												if(l>=1 && l<=wie_viele_Gegenstand)
													zeigen2[l-1]=1;
										}
										else
										{
											for(int l=vorubergehend1_1;l>=vorubergehend1_2; l--)
												if(l>=1 && l<=wie_viele_Gegenstand)
													zeigen2[l-1]=1;
										}
									}
								}
								else
								{
									int vorubergehend2=string_zu_int(vorubergehend1);
									if(vorubergehend2>=1 && vorubergehend2<=wie_viele_Gegenstand)
										zeigen2[vorubergehend2-1]=1;
								}
								n1=suchen_oder(a,g,10,n2+1,a.size()-1);
								n2=suchen_oder(a,h,3,n1+1,a.size()-1);
								if(n2==-1)
									n2=a.size();
							}
						}
						else
						{
							if(wie_viele_Gegenstand<=9)
							{
								for(int l=0; l<a.size(); l++) if(a[l]>='1' && a[l]<=wie_viele_Gegenstand+48)
									zeigen2[a[l]-48-1]=1;
							}
							else
							{
								int hilfs_variable=string_zu_int(a);
								if(hilfs_variable>=1 && hilfs_variable<=wie_viele_Gegenstand)
									zeigen2[hilfs_variable-1]=1;
							}
						}
						system("cls");
					} while(a!="0");
				}
				if(wie_viele_Gegenstand==1)
					zeigen2[0]=1;
				for(int k=wie_viele_Gegenstand-1; k>=0; k--)
					if(zeigen2[k])
						loschen(Gattung, NICHTzeigen, wo_Gattung+k);
			}
			else
			{
				for(int k=0; Gattung[k]!="";)
					if(Spezialitaten[i]==Gattung[k])
						loschen(Gattung, NICHTzeigen, k);
					else
						k++;
			}
		}
		Datei.close(); remove("qwerty");
}

void Ende()
{
	system("cls");
	for(int i=0; i<anfanglichHohe-1; i++)
		cout<<endl;
	cout<<"Autor: Krzysztof Szulc"<<endl;
	Sleep(400);
	exit(EXIT_SUCCESS);
}

void ladenKurs(string &Kurs, string &Semester, string &letztenSemester, int &Datum, string &Kursname, string NICHTzeigen[][2])
{
	ifstream Einstellungen ("zmiany w planie.ini");
	if(!Einstellungen)
	{
		remove("stary plan.html");
		remove("nowy plan.html");
		string Kurse[l][3];
		int c;
		KurselisteHerunterladen(Kurse,c);
		int Weite=89+letztenZwischenraum, Hohe=7+c;
		for(int i=c-1; i>=0; i--)
		{
			if(8+Kurse[i][1].size()+letztenZwischenraum>Weite)
				Weite=8+Kurse[i][1].size()+letztenZwischenraum;
		}
		stellenPuffergrosse(Weite, Hohe);
		if(c==0)
		{
			cout<<"Brak listy kierunk\242w\n";
			system("pause");
			Ende();
		}
		else
		{
			Kurs="0";
			quicksort(Kurse, 0, c-1);
			string h="";
			int welcheKurs;
			do
			{
				system("cls");
				cout<<"WYBIERZ KIERUNEK:\n";
				bool leereListe=1;
				for(int i=0; i<c; i++)
					if(gleichText(Textteil(Kurse[i][1],0,h.size()-1),h))
					{
						cout<<Kurse[i][0]<<"\t"<<Kurse[i][1]<<endl;
						leereListe=0;
					}
					if(h=="")
						cout<<"-1\tWyznaj\251 Jezusa Panem\n";
					if(leereListe)
						h="";
					else
					{
						cout<<endl<<"Aby zaw\251zi\206 list\251, wpisz pocz\245tkow\245 nazw\251 kierunku; aby wybra\206 kierunek wpisz jego numer:\n"<<h;
						string t;
						getline(cin,t);
						string ohneRaume=ausschliessen_vorn_Raume(t);
						for(welcheKurs=0; welcheKurs<c; welcheKurs++)
							if(ohneRaume==Kurse[welcheKurs][0])
							{
								Kurs=ohneRaume;
								Kursname=Kurse[welcheKurs][1];
								break;
							} //usuwanie spacji z przodu tylko je¿eli nr kierunku
						if(t=="-1")
						{
							system("cls");
							cout<<"Niech B\242g Ci b\210ogos\210awi!\n";
							system("pause");
							system("cls");
						}
						h+=t;
					}
			} while(Kurs=="0");
			stellenPuffergrosse(38+letztenZwischenraum,10); //"B³¹d pobierania..."
			cout<<"Pobieranie informacji o semestrze...";
			herunterladen("http://e.kul.pl/qlplan.html?wid="+Kurse[welcheKurs][2]+"&kid="+Kurs+"&op=1","qwerty"); //[2] to nr wydzia³u
			stellenFenstertitel();
			system("cls");
			ifstream Datei("qwerty");
			string a;
			while(suchenText(a,"</select>",0,0)==-1)
				getline(Datei,a);
			for(int i=1; i<=7; i++)
				getline(Datei,a);
			string Hilfs=a; //¿eby cofn¹æ ostatni getline
			if(suchenText(a,"</select>",0,0)!=-1)
			{
				stellenPuffergrosse(80+letztenZwischenraum,3);
				cout<<"B\210\245d programu. Sprawd\253 na stronie internetowej, czy plan wy\233wietla si\251 poprawnie\n";
				system("pause");
				Ende();
			}
			else
			{
				while(suchenText(a,"</select>",9,9)==-1)
				{
					Hilfs=a;
					getline(Datei,a);
				}
				a=Hilfs;
				letztenSemester=Textteil(a,suchenText(a,"=\"",0,a.size()-1)+2,suchenText(a,"\">",0,a.size()-1)-1);
			}
			Datei.close();
			remove("qwerty");
			int Weite=24+letztenZwischenraum;
			if(letztenSemester[letztenSemester.size()-1]=='R')
				Weite-=4;
			if(Kursname.size()+letztenZwischenraum>Weite)
				Weite=Kursname.size()+letztenZwischenraum;
			stellenPuffergrosse(Weite,3);
			if(letztenSemester[letztenSemester.size()-1]!='R')
			{
				do
				{
					cout<<Kursname<<"\nWpisz numer semestru: ";
					cin>>h;
					system("cls");
					h=ausschliessen_vorn_Raume(h);
				} while(string_zu_int(h)<=0 || string_zu_int(h)>string_zu_int(letztenSemester));
				Semester=h;
			}
			else
			{
				do
				{
					cout<<Kursname<<"\nWpisz numer roku: ";
					cin>>h;
					system("cls");
					h=ausschliessen_vorn_Raume(h);
				} while(string_zu_int(h)<=0 || string_zu_int(h)>string_zu_int(Textteil(letztenSemester,0,letztenSemester.size()-2)));
				Semester=h+"R";
			}
			wahlenSpezialitaten(Semester, Kurs, NICHTzeigen);
			Datum=aktuelleDatum();
			ofstream Einstellungen ("zmiany w planie.ini");
			Einstellungen<<"To jest plik z ustawieniami do programu. Zmiany w planie s\245 wy\230wietlane w programie"<<endl
				<<Kurs<<" "
				<<Kursname<<"\n"
				<<Semester<<" "
				<<letztenSemester<<"\n"
				<<Datum<<"\n";
			for(int i=0; NICHTzeigen[i][0]!=""; i++)
			{
				 Einstellungen<<NICHTzeigen[i][0]<<endl;
				 Einstellungen<<NICHTzeigen[i][1]<<endl;
		  }
			Einstellungen.close();
		}
	}
	else
	{
		getline(Einstellungen,Kurs); Einstellungen>>Kurs;
		Einstellungen.get(); getline(Einstellungen,Kursname);
		Einstellungen>>Semester;
		Einstellungen>>letztenSemester;
		Einstellungen>>Datum;
		Einstellungen.get(); //bo nie chce dzia³aæ poprawnie: Einstellungen.seekg(1, Einstellungen.cur);
		for(int i=0; !Einstellungen.eof(); i++)
		{
		 	getline(Einstellungen,NICHTzeigen[i][0]);
		 	getline(Einstellungen,NICHTzeigen[i][1]);
		}
		Einstellungen.close();
	}
}

void ersetzenKurs(string &Kurs, string &Semester, string &letztenSemester, bool &ob_war_Veranderung, string &Kursname, string NICHTzeigen[][2])
{
	if(letztenSemester[letztenSemester.size()-1]!='R')
		cout<<endl<<endl<<Kursname<<", semestr "<<Semester<<endl;
	else
		cout<<endl<<endl<<Kursname<<", rok "<<Textteil(Semester,0,Semester.size()-2)<<endl;
	string Anfrage="Czy chcesz zmieni\206 kierunek?";
	int Weite=28+letztenZwischenraum;
	int hilfsWeite=Kursname.size()+10+letztenZwischenraum;
	if(Semester[Semester.size()-1]=='R')
		hilfsWeite=hilfsWeite-5+Textteil(Semester,0,Semester.size()-2).size();
	else
		hilfsWeite+=Semester.size();
	if(hilfsWeite>Weite)
		Weite=hilfsWeite;
	if(jaODERnein(Anfrage, Weite, 3))
	{
		remove("nowy plan.html");
		remove("stary plan.html");
		remove("zmiany w planie.ini");
		Kurs="";
		int Datum;
		ladenKurs(Kurs, Semester, letztenSemester, Datum, Kursname, NICHTzeigen);
		if(Kurs!="")
			ob_war_Veranderung=1;
	}
	else
		cout<<endl;
}

void aktualisierenSemester(string &Semester, string letztenSemester, int Datum, bool &nicht_existieren_alt, string Kursname) //'&' przy nicht_existieren_alt, ¿eby po aktualizacji wiedzia³o, gdzie iœæ
{
	int Abstand=(aktuelleDatum()-Datum)/5;
	if(letztenSemester[letztenSemester.size()-1]!='R')
	{
		int s=string_zu_int(Semester)+Abstand;
		if(Abstand>0 && s<=12)
		{
			int Weite=37+int_zu_string(s).size()+letztenZwischenraum, Hohe=4;
			if(!nicht_existieren_alt)
				Weite+=43;
			if(Kursname.size()+letztenZwischenraum>Weite)
				Weite=Kursname.size()+letztenZwischenraum;
			stellenPuffergrosse(Weite, Hohe);
			cout<<Kursname<<endl;
			string Anfrage="Czy chcesz zaktualizowa\206 semestr do "+int_zu_string(s)+"?";
			if(!nicht_existieren_alt)
				Anfrage+=" (aktualne pliki z planem zostan\245 usuni\251te)";
			Weite=37+int_zu_string(s).size()+letztenZwischenraum;
			if(!nicht_existieren_alt)
				Weite+=43;
			int hilfsWeite=Kursname.size()+letztenZwischenraum;
			if(hilfsWeite>Weite)
				Weite=hilfsWeite;
			if(jaODERnein(Anfrage, Weite, 4))
			{
				remove("nowy plan.html");
				remove("stary plan.html");
				Semester=int_zu_string(s);
				ifstream vorubergehendDatei("zmiany w planie.ini");
				string Kurs;
				string vorubergehend;
				getline(vorubergehendDatei,Kurs);
				vorubergehendDatei>>Kurs;
				getline(vorubergehendDatei,vorubergehend);
				vorubergehendDatei.close();
				remove("zmiany w planie.ini");
				string NICHTzeigen[q][2];
				wahlenSpezialitaten(Semester, Kurs, NICHTzeigen);
				ofstream Datei("zmiany w planie.ini");
				Datei<<"To jest plik z ustawieniami do programu. Zmiany w planie s\245 wy\230wietlane w programie"<<endl
					<<Kurs<<vorubergehend<<endl
					<<Semester<<" "
					<<letztenSemester<<endl
					<<aktuelleDatum()<<endl;
				for(int i=0; NICHTzeigen[i][0]!=""; i++)
				{
					Datei<<NICHTzeigen[i][0]<<endl;
					Datei<<NICHTzeigen[i][1]<<endl;
				}
				Datei.close();
				nicht_existieren_alt=1;
			}
			else
			{
				rename("zmiany w planie.ini","qwerty");
				ifstream vorubergehendDatei("qwerty");
				ofstream Datei("zmiany w planie.ini");
				string vorubergehend;
				for(int i=0; i<3; i++)
				{
					getline(vorubergehendDatei,vorubergehend);
					Datei<<vorubergehend<<endl;
				}
				Datei<<aktuelleDatum()<<endl;
				getline(vorubergehendDatei,vorubergehend);
				while(!vorubergehendDatei.eof() && vorubergehend!="") //¿eby nie wstawia³o pustych getline'ów
				{
					getline(vorubergehendDatei,vorubergehend);
					Datei<<vorubergehend<<endl;
				}
				Datei.close();
				vorubergehendDatei.close();
				remove("qwerty");
			}
		}
	}
	else
	{
		int s=string_zu_int(Textteil(Semester,0,Semester.size()-2))+Abstand/2;
		if(Abstand>0 && s<=string_zu_int(Textteil(letztenSemester,0,letztenSemester.size()-2)))
		{
			int Weite=33+int_zu_string(s).size()+letztenZwischenraum, Hohe=4;
			if(!nicht_existieren_alt)
				Weite+=43;
			stellenPuffergrosse(Weite, Hohe);
			cout<<Kursname<<endl;
			string Anfrage="Czy chcesz zaktualizowa\206 rok do "+int_zu_string(s)+"?";
			if(!nicht_existieren_alt)
				Anfrage+=" (aktualne pliki z planem zostan\245 usuni\251te)";
			Weite=37+int_zu_string(s).size()+letztenZwischenraum;
			if(!nicht_existieren_alt)
				Weite+=43;
			int hilfsWeite=Kursname.size()+letztenZwischenraum;
			if(hilfsWeite>Weite)
				Weite=hilfsWeite;
			if(jaODERnein(Anfrage, Weite, 4))
			{
				remove("nowy plan.html");
				remove("stary plan.html");
				Semester=int_zu_string(s)+"R";
				ifstream vorubergehendDatei("zmiany w planie.ini");
				string Kurs;
				string vorubergehend;
				getline(vorubergehendDatei,Kurs);
				vorubergehendDatei>>Kurs;
				getline(vorubergehendDatei,vorubergehend);
				vorubergehendDatei.close();
				remove("zmiany w planie.ini");
				string NICHTzeigen[q][2];
				wahlenSpezialitaten(Semester, Kurs, NICHTzeigen);
				ofstream Datei("zmiany w planie.ini");
				Datei<<"To jest plik z ustawieniami do programu. Zmiany w planie s\245 wy\230wietlane w programie"<<endl
					<<Kurs<<vorubergehend<<endl
					<<Semester<<" "
					<<letztenSemester<<endl
					<<aktuelleDatum()<<endl;
				for(int i=0; NICHTzeigen[i][0]!=""; i++)
				{
					Datei<<NICHTzeigen[i][0]<<endl;
					Datei<<NICHTzeigen[i][1]<<endl;
				}
				Datei.close();
				nicht_existieren_alt=1;
			}
			else
			{
				rename("zmiany w planie.ini","qwerty");
				ifstream vorubergehendDatei("qwerty");
				ofstream Datei("zmiany w planie.ini");
				string vorubergehend;
				for(int i=0; i<3; i++)
				{
					getline(vorubergehendDatei,vorubergehend);
					Datei<<vorubergehend<<endl;
				}
				Datei<<aktuelleDatum()<<endl;
				getline(vorubergehendDatei,vorubergehend);
				while(!vorubergehendDatei.eof() && vorubergehend!="")
				{
					getline(vorubergehendDatei,vorubergehend);
					Datei<<vorubergehend<<endl;
				}
				Datei.close();
				vorubergehendDatei.close();
				remove("qwerty");
			}
		}
	}
}

string zwischenDreieckigeklammern(string s, int x) //koniec: x-ty od lewej; pocz¹tek: pierwszy znak po pierwszym '<' przed koñcem
{
	int c=-1;
	for(int i=s.size()-x; i>=0 && c==-1; i--)
		if(s[i]=='>')
			c=i;
	return Textteil(s, c+1, s.size()-x);
}

struct Daten
{
	string Tag;
	string Zimmer;
	string Zeit;
	string Zyklus;
	string Gegenstand;
	string Lehrer;
};

void ausschliessenDaten(Daten e[], int nr)
{
	for(int i=nr; e[i].Zyklus!=""; i++)
		e[i]=e[i+1]; //koñcowy wpis kopiowany z pustego
}

void rucksetzen(Daten Feld[])
{
	int c=0;
	while(Feld[c].Zyklus!="")
		c++;
	while(c)
	{
		Feld[c-1]=Feld[c];
		c--;
	}
}

void ausschliessen_gleische(Daten neu[], Daten alt[])
{
	int i=0;
	while(alt[i].Zyklus.size()==1) //posortowane wg Tag,Zeit
	{
		int j=0;
		while((alt[i].Tag!=neu[j].Tag || alt[i].Zeit!=neu[j].Zeit) && neu[j].Zyklus.size()==1)
			j++;
		while((alt[i].Tag==neu[j].Tag && alt[i].Zeit==neu[j].Zeit) && neu[j].Zyklus.size()==1)
		{
			if(alt[i].Zyklus==neu[j].Zyklus && alt[i].Gegenstand==neu[j].Gegenstand && alt[i].Lehrer==neu[j].Lehrer && alt[i].Zimmer==neu[j].Zimmer)
		 	{
			 	ausschliessenDaten(alt, i);
				ausschliessenDaten(neu, j);
				i--;
				break;
			}
			j++;
		}
		i++;
	}
	//dla nieregularnych:
	while(alt[i].Zyklus!="") //posortowane wg Zyklus,Zeit
	{
		int j=0;
		while((alt[i].Zyklus!=neu[j].Zyklus || alt[i].Zeit!=neu[j].Zeit) && neu[j].Zyklus!="")
			j++;
		while((alt[i].Zyklus==neu[j].Zyklus && alt[i].Zeit==neu[j].Zeit) && neu[j].Zyklus!="")
		{
			if(alt[i].Gegenstand==neu[j].Gegenstand && alt[i].Lehrer==neu[j].Lehrer && alt[i].Zimmer==neu[j].Zimmer)
		 	{
			 	ausschliessenDaten(alt, i);
				ausschliessenDaten(neu, j);
				i--;
				break;
			}
			j++;
		}
		i++;
	}
}

void ausschliessen_von_NICHTzeigen(Daten neu[], Daten alt[], string NICHTzeigen[][2])
{
	for(int i=0; NICHTzeigen[i][0]!=""; i++)
	{
		int j=0;
		while(NICHTzeigen[i][0]!=neu[j].Gegenstand && neu[j].Zyklus!="")
			j++;
		if(neu[j].Zyklus!="")
		{
			bool allein_Gegenstand=1;
			for(int g=j+1; neu[g].Zyklus!=""; g++)
			{
				if(NICHTzeigen[i][0]==neu[g].Gegenstand)
				{
			 		allein_Gegenstand=0;
			 		break;
			 	}
			}
			//nie jest porównywanie w ka¿dym przypadku nauczyciela, dlatego, ¿e czasem jest "VACAT" (w NICHTzeigen mo¿e pozostaæ, a w planie mo¿e siê zmieniæ). Mog¹ tu wyst¹piæ ewentualne b³êdy (w wyœwietalniu po¿¹danych przedmiotów)
	 		if(allein_Gegenstand)
	 			ausschliessenDaten(neu,j);
			else
			{
				for(int g=j; neu[g].Zyklus!=""; g++)
				if(NICHTzeigen[i][0]==neu[g].Gegenstand && NICHTzeigen[i][1]==neu[g].Lehrer)
				{
					ausschliessenDaten(neu,g);
					break;
				}
		  }
	  }
    j=0;
		while(NICHTzeigen[i][0]!=alt[j].Gegenstand && alt[j].Zyklus!="")
			j++;
	 	if(alt[j].Zyklus!="")
		{
			bool allein_Gegenstand=1;
			for(int g=j+1; alt[g].Zyklus!=""; g++)
			{
				if(NICHTzeigen[i][0]==alt[g].Gegenstand)
				{
					allein_Gegenstand=0;
					break;
				}
			}
			if(allein_Gegenstand)
				ausschliessenDaten(alt,j);
			else
			{
				for(int g=j; alt[g].Zyklus!=""; g++)
				if(NICHTzeigen[i][0]==alt[g].Gegenstand && NICHTzeigen[i][1]==alt[g].Lehrer)
				{
					ausschliessenDaten(alt,g);
					break;
				}
		  }
		}
	}
}

void zeigen_verandert_Zeile(bool zuerstZeile, string Schluss, int wie_setw, string alt, string neu)
{
	string Ausgang;
	if(zuerstZeile)
	{
		Ausgang+="star"+Schluss+": ";
		for(int i=wie_setw-Zwischenraum-7-alt.size(); i>0; i--)
			Ausgang+=" ";
		Ausgang+=alt;
	}
	else
	{
		Ausgang+=" now"+Schluss+": ";
		for(int i=wie_setw-Zwischenraum-7-neu.size(); i>0; i--)
			Ausgang+=" ";
		Ausgang+=neu;
	}
	cout<<setw(wie_setw)<<Ausgang;
}

void quicksort2(Daten a[], int l, int r)
{
	int i=l, j=r;
	Daten hilfs_variable;
	string x=a[(l+r)/2].Gegenstand;
	do
	{
		while(a[i].Gegenstand<x)
			i++;
		while(a[j].Gegenstand>x)
			j--;
		if(i<=j)
	  {
	    hilfs_variable=a[i];
	    a[i]=a[j];
	    a[j]=hilfs_variable;
			i++;
			j--;
	  }
	} while(i<=j);
	if(l<j)
		quicksort2(a,l,j);
	if(i<r)
		quicksort2(a,i,r);
}

void zeigenUberschrift (string a)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hStdout=GetStdHandle( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	WORD aktuelleFarbe=csbiInfo.wAttributes;
	SetConsoleTextAttribute(hStdout, 112);
	cout<<a;
	SetConsoleTextAttribute(hStdout, aktuelleFarbe);	
}

void zeigenVeranderungen(Daten alt[], Daten neu[], string Kursname, string Semester, bool &ob_ohne_Anderungen)
{
	int max=Kursname.size()+2+8+letztenZwischenraum;
	if(Semester[Semester.size()-1]=='R')
		max=max-5+Textteil(Semester,0,Semester.size()-2).size();
	else
		max+=Semester.size();
	int hilfsMax=28+letztenZwischenraum; //"Czy chcesz zmieniæ kierunek?"
	if(hilfsMax>max)
		max=hilfsMax;
	if(alt[0].Zyklus!="" || neu[0].Zyklus!="")
	{
		hilfsMax=72+letztenZwischenraum; //"Czy pobraæ nowy plan..."
		if(hilfsMax>max)
			max=hilfsMax;
	}
	
	int wo_irregular_alt=0;
	while(alt[wo_irregular_alt].Zyklus.size()==1)
		wo_irregular_alt++;
	int wie_viele_alt=wo_irregular_alt;
	while(alt[wie_viele_alt].Zyklus!="")
		wie_viele_alt++;
	int wo_irregular_neu=0;
	while(neu[wo_irregular_neu].Zyklus.size()==1)
		wo_irregular_neu++;
	int wie_viele_neu=wo_irregular_neu;
	while(neu[wie_viele_neu].Zyklus!="")
		wie_viele_neu++;
	//sortowanie nieregularnych wg przedmiotu
	if(wie_viele_alt-wo_irregular_alt!=0)
		quicksort2(alt,wo_irregular_alt,wie_viele_alt-1);
	if(wie_viele_neu-wo_irregular_neu!=0)
		quicksort2(neu,wo_irregular_neu,wie_viele_neu-1);
	
	Daten alt2[q];
	for(int i=0; alt[i].Zyklus!=""; i++) //do szukania rozmiaru kolumny, bo trzeba usun¹æ wiersze
	{
		alt2[i].Tag=alt[i].Tag;
		alt2[i].Gegenstand=alt[i].Gegenstand;
		alt2[i].Zimmer=alt[i].Zimmer;
		alt2[i].Zeit=alt[i].Zeit;
		alt2[i].Zyklus=alt[i].Zyklus;
		alt2[i].Lehrer=alt[i].Lehrer;
	}
	Daten neu2[q]; for(int i=0; neu[i].Zyklus!=""; i++)
	{
		neu2[i].Tag=neu[i].Tag;
		neu2[i].Gegenstand=neu[i].Gegenstand;
		neu2[i].Zimmer=neu[i].Zimmer;
		neu2[i].Zeit=neu[i].Zeit;
		neu2[i].Zyklus=neu[i].Zyklus;
		neu2[i].Lehrer=neu[i].Lehrer;
	}
	int Hohe=0;
	//regularny, ten sam przedmiot
	int Gegenstand1=9+zuerstZwischenraum;
	int Tag_und_Zeit1=14+Zwischenraum;
	int Zimmer1=4+Zwischenraum;
	int Zyklus1=4+Zwischenraum;
	int Lehrer1=10+Zwischenraum;
	
	for(int i=0; alt2[i].Zyklus.size()==1; i++)
	{
		int j=0;
		while(alt2[i].Gegenstand!=neu2[j].Gegenstand && neu2[j].Zyklus.size()==1)
			j++;
		if(alt2[i].Gegenstand==neu2[j].Gegenstand)
		{
			if(Hohe==0)
				Hohe=1;
			if(alt2[i].Gegenstand.size()>Gegenstand1-zuerstZwischenraum)
				Gegenstand1=alt2[i].Gegenstand.size()+zuerstZwischenraum;
			if(alt2[i].Tag!=neu2[j].Tag || alt2[i].Zeit!=neu2[j].Zeit)
			{
				if(alt2[i].Tag.size()+alt2[i].Zeit.size()+9>Tag_und_Zeit1-Zwischenraum)
					Tag_und_Zeit1=alt2[i].Tag.size()+alt2[i].Zeit.size()+9+Zwischenraum;
				if(neu2[j].Tag.size()+neu2[j].Zeit.size()+9>Tag_und_Zeit1-Zwischenraum)
					Tag_und_Zeit1=neu2[j].Tag.size()+neu2[j].Zeit.size()+9+Zwischenraum;
			}
			else
			{
				if(alt2[i].Tag.size()+alt2[i].Zeit.size()+2>Tag_und_Zeit1-Zwischenraum) Tag_und_Zeit1=alt2[i].Tag.size()+alt2[i].Zeit.size()+2+Zwischenraum;
			}
			if(alt2[i].Zimmer!=neu2[j].Zimmer)
			{
				if(alt2[i].Zimmer.size()+7>Zimmer1-Zwischenraum)
					Zimmer1=alt2[i].Zimmer.size()+7+Zwischenraum;
				if(neu2[j].Zimmer.size()+7>Zimmer1-Zwischenraum)
					Zimmer1=neu2[j].Zimmer.size()+7+Zwischenraum;
			}
			if(alt2[i].Zyklus!=neu2[j].Zyklus)
			{
				Zyklus1=8+Zwischenraum;
			}
			if(alt2[i].Lehrer!=neu2[j].Lehrer)
			{
				if(alt2[i].Lehrer.size()+7>Lehrer1-Zwischenraum)
					Lehrer1=alt2[i].Lehrer.size()+7+Zwischenraum;
				if(neu2[j].Lehrer.size()+7>Lehrer1-Zwischenraum)
					Lehrer1=neu2[j].Lehrer.size()+7+Zwischenraum;
			}
			ausschliessenDaten(alt2,i);
				i--;
			ausschliessenDaten(neu2,j);
				Hohe+=2;
		}
	}
			
	if(wo_irregular_alt!=0)
	{
		hilfsMax=Gegenstand1+Tag_und_Zeit1+Zimmer1+Zyklus1+Lehrer1+letztenZwischenraum;
		if(hilfsMax>max)
			max=hilfsMax;
	}
	//regularny, przedmioty bez odpowiedników
	int Gegenstand2=15+zuerstZwischenraum;
	if(alt2[0].Zyklus.size()==1)
		Gegenstand2=35+zuerstZwischenraum;
	int Tag_und_Zeit2=14+Zwischenraum;
	int Zimmer2=4+Zwischenraum;
	int Zyklus2=4+Zwischenraum;
	int Lehrer2=10+Zwischenraum;

	if(alt2[0].Zyklus.size()==1)
	{
		Hohe++;
		if(Hohe!=1) //¿eby uwzglêdniæ endl miêdzy jedn¹ tabel¹ i drug¹
			Hohe++;
	}
	bool ob_werden_Tabelle=0;
	if(alt2[0].Zyklus.size()==1 || neu2[0].Zyklus.size()==1)
		ob_werden_Tabelle=1;
	while(alt2[0].Zyklus.size()==1)
	{
		if(alt2[0].Gegenstand.size()>Gegenstand2-zuerstZwischenraum)
			Gegenstand2=alt2[0].Gegenstand.size()+zuerstZwischenraum;
		if(alt2[0].Tag.size()+alt2[0].Zeit.size()+2>Tag_und_Zeit2-Zwischenraum)
			Tag_und_Zeit2=alt2[0].Tag.size()+alt2[0].Zeit.size()+2+Zwischenraum;
		ausschliessenDaten(alt2,0);
		Hohe++;
	}
	if(neu2[0].Zyklus.size()==1)
	{
		Hohe++;
		if(Hohe!=1)
			Hohe++;
	}
	while(neu2[0].Zyklus.size()==1)
	{
		if(neu2[0].Gegenstand.size()>Gegenstand2-zuerstZwischenraum)
			Gegenstand2=neu2[0].Gegenstand.size()+zuerstZwischenraum;
		if(neu2[0].Tag.size()+neu2[0].Zeit.size()+2>Tag_und_Zeit2-Zwischenraum)
			Tag_und_Zeit2=neu2[0].Tag.size()+neu2[0].Zeit.size()+2+Zwischenraum;
		if(neu2[0].Zimmer.size()>Zimmer2-Zwischenraum)
			Zimmer2=neu2[0].Zimmer.size()+Zwischenraum;
		if(neu2[0].Zyklus.size()>Zyklus2-Zwischenraum)
			Zyklus2=neu2[0].Zyklus.size()+Zwischenraum;
		if(neu2[0].Lehrer.size()>Lehrer2-Zwischenraum)
			Lehrer2=neu2[0].Lehrer.size()+Zwischenraum;
		ausschliessenDaten(neu2,0);
		Hohe++;
	}
	if(ob_werden_Tabelle)
	{
		hilfsMax=Gegenstand2+Tag_und_Zeit2+Zimmer2+Zyklus2+Lehrer2+letztenZwischenraum;
		if(hilfsMax>max)
			max=hilfsMax;
	}
	//cykl nieregularny
	int Gegenstand3=9+zuerstZwischenraum;
	int Datum3=25+Zwischenraum;
	int Zimmer3=4+Zwischenraum;
	int Lehrer3=10+Zwischenraum;
	bool ob_zeigen_string_alt_Datum=0;
	bool ob_zeigen_string_alt_Zimmer=0;
	bool ob_zeigen_string_alt_Lehrer=0;
	
	if(neu2[0].Zyklus!="" || alt2[0].Zyklus!="")
	{
		Hohe++;
		if(Hohe!=1)
			Hohe++;
	}
	for(int i=0; alt2[i].Zyklus!=""; i++)
	{
		bool brechen=0;
		int j=0;
		while(neu2[j].Zyklus!="" && !brechen)
		{
			while(alt2[i].Gegenstand!=neu2[j].Gegenstand && neu2[j].Zyklus!="")
				j++;
			if(alt2[i].Gegenstand==neu2[j].Gegenstand)
			{
				if(alt2[i].Gegenstand.size()>Gegenstand3-zuerstZwischenraum)
					Gegenstand3=alt2[i].Gegenstand.size()+zuerstZwischenraum;
				if(alt2[i].Zyklus==neu2[j].Zyklus && alt2[i].Zeit==neu2[j].Zeit)
				{
					if(alt2[i].Zimmer!=neu2[j].Zimmer)
					{
					 	ob_zeigen_string_alt_Zimmer=1;
						if(alt2[i].Zimmer.size()+7>Zimmer3-Zwischenraum)
							Zimmer3=alt2[i].Zimmer.size()+7+Zwischenraum;
						if(neu2[j].Zimmer.size()+7>Zimmer3-Zwischenraum)
							Zimmer3=neu2[j].Zimmer.size()+7+Zwischenraum;
					}
					if(alt2[i].Lehrer!=neu2[j].Lehrer)
					{
			 			ob_zeigen_string_alt_Lehrer=1;
						if(alt2[i].Lehrer.size()+7>Lehrer3-Zwischenraum)
							Lehrer3=alt2[i].Lehrer.size()+7+Zwischenraum;
						if(neu2[j].Lehrer.size()+7>Lehrer3-Zwischenraum)
							Lehrer3=neu2[j].Lehrer.size()+7+Zwischenraum;
					}
					ausschliessenDaten(alt2, i); i--;
					ausschliessenDaten(neu2, j);
					Hohe+=2;
					brechen=1;
				}
			}
			j++;
		}
	}
	//bez odpowiednika w przedmiocie lub dacie - stare
	for(int i=0; alt2[i].Zyklus!=""; i++)
	{
		if(alt2[i].Gegenstand.size()>Gegenstand3-zuerstZwischenraum)
			Gegenstand3=alt2[i].Gegenstand.size()+zuerstZwischenraum;
		ob_zeigen_string_alt_Datum=1;
		Datum3=32+Zwischenraum;
	}
	for(int i=0; alt2[i].Zyklus!=""; i++)
		Hohe++;
	//bez odpowiednika w przedmiocie lub dacie - nowe
	for(int i=0; neu2[i].Zyklus!=""; i++)
	{
		if(neu2[i].Gegenstand.size()>Gegenstand3-zuerstZwischenraum)
			Gegenstand3=neu2[i].Gegenstand.size()+zuerstZwischenraum;
		if(!ob_zeigen_string_alt_Datum)
		{
			Datum3=31+Zwischenraum;
			if(Zwischenraum==0)
				Datum3++; //¿eby miêdzy kolumnami by³a przynajmniej jedna SPACJA, tak samo Zimmer3 i Lehrer3
		} //najlepiej by by³o, ¿eby dodatkowo wyœwietla³o "nowy" bez spacji z przodu i wtedy bez warunku Zwischenraum==0
		if(ob_zeigen_string_alt_Zimmer)
		{
			if(neu2[i].Zimmer.size()+7>Zimmer3-Zwischenraum)
				Zimmer3=neu2[i].Zimmer.size()+7+Zwischenraum;
		}
		else
		{
			if(neu2[i].Zimmer.size()>Zimmer3-Zwischenraum)
				Zimmer3=neu2[i].Zimmer.size()+Zwischenraum; //wtedy nie wyœwietla "nowy", tak samo dla Lehrer; dlatego bez +6 (je¿eli by by³o, to wtedy if(Zwischenraum==0) Zimmer3++;
		}
		if(ob_zeigen_string_alt_Lehrer)
		{
			if(neu2[i].Lehrer.size()+7>Lehrer3-Zwischenraum)
				Lehrer3=neu2[i].Lehrer.size()+7+Zwischenraum;
		}
		else
		{
			if(neu2[i].Lehrer.size()>Lehrer3-Zwischenraum)
				Lehrer3=neu2[i].Lehrer.size()+Zwischenraum;
		}
		Hohe++;
	}

	if(alt[0].Zyklus=="" && neu[0].Zyklus=="") //je¿eli "bez zmian"
		Hohe=2;
	else
		Hohe+=4; //+ "czy pobraæ nowy plan
	if(wie_viele_alt-wo_irregular_alt!=0 || wie_viele_neu-wo_irregular_neu!=0)
	{
		hilfsMax=Gegenstand3+Datum3+Zimmer3+Lehrer3+letztenZwischenraum;
		if(hilfsMax>max)
			max=hilfsMax;
	}
	stellenPuffergrosse(max, Hohe+4);
	
	if(alt[0].Zyklus=="" && neu[0].Zyklus=="")
	{
		cout<<"BEZ ZMIAN";
		ob_ohne_Anderungen=1;
	}
	else
	{ //wypisywanie zmian
		//cykl regularny, ten sam przedmiot
		bool c=0, d=0, e=0;
		for(int i=0; alt[i].Zyklus.size()==1; i++)
		{
			int j=0;
			while(alt[i].Gegenstand!=neu[j].Gegenstand && neu[j].Zyklus.size()==1)
				j++;
			if(alt[i].Gegenstand==neu[j].Gegenstand)
			{
				if(!c)
				{
					cout<<setw(Gegenstand1);
					zeigenUberschrift("PRZEDMIOT");
					cout<<setw(Tag_und_Zeit1);
					zeigenUberschrift("DZIE\343, GODZINA");
					cout<<setw(Zimmer1);
					zeigenUberschrift("SALA");
					cout<<setw(Zyklus1);
					zeigenUberschrift("CYKL");
					cout<<setw(Lehrer1);
					zeigenUberschrift("PROWADZ\244CY");
					cout<<endl;
					c=1;
				}
				bool zuerstZeile=1;
				for(int k=1; k<=2; k++)
				{
					cout<<setw(Gegenstand1);
					if(zuerstZeile)
						cout<<alt[i].Gegenstand;
					else
						cout<<"";
					if(alt[i].Tag==neu[j].Tag && alt[i].Zeit==neu[j].Zeit)
					{
						if(zuerstZeile)
							cout<<setw(Tag_und_Zeit1)<<alt[i].Tag+", "+alt[i].Zeit;
						else
							cout<<setw(Tag_und_Zeit1)<<"";
					}
					else
						zeigen_verandert_Zeile(zuerstZeile, "y", Tag_und_Zeit1, alt[i].Tag+", "+alt[i].Zeit, neu[j].Tag+", "+neu[j].Zeit);
					if(alt[i].Zimmer!=neu[j].Zimmer)
						zeigen_verandert_Zeile(zuerstZeile, "a", Zimmer1, alt[i].Zimmer, neu[j].Zimmer);
					else
						cout<<setw(Zimmer1)<<"-";
					if(alt[i].Zyklus!=neu[j].Zyklus)
						zeigen_verandert_Zeile(zuerstZeile, "y", Zyklus1, alt[i].Zyklus, neu[j].Zyklus);
					else cout<<setw(Zyklus1)<<"-";
					if(alt[i].Lehrer!=neu[j].Lehrer)
						zeigen_verandert_Zeile(zuerstZeile, "y", Lehrer1, alt[i].Lehrer, neu[j].Lehrer);
					else
						cout<<setw(Lehrer1)<<"-";
					cout<<endl;
					if (!zuerstZeile)
					{
						ausschliessenDaten(alt, i);
						ausschliessenDaten(neu, j);
						i--;
					}
					zuerstZeile=0;
				}
			}
		}
		//cykl regularny, przedmioty bez odpowiedników - nowy i stary
		if(alt[0].Zyklus.size()==1)
		{
			if(c)
				cout<<endl;
			cout<<setw(Gegenstand2);
			zeigenUberschrift("STARE PRZEDMIOTY (usuni\251te z planu)");
			cout<<setw(Tag_und_Zeit2);
			zeigenUberschrift("DZIE\343, GODZINA");
			cout<<endl;
			d=1;
		}
		while(alt[0].Zyklus.size()==1)
		{
			cout<<setw(Gegenstand2)<<alt[0].Gegenstand<<setw(Tag_und_Zeit2)<<alt[0].Tag+", "+alt[0].Zeit<<endl;
			ausschliessenDaten(alt, 0);
		}
			
		if(neu[0].Zyklus.size()==1)
		{
			if(c || d)
				cout<<endl;
			cout<<setw(Gegenstand2);
			zeigenUberschrift("NOWE PRZEDMIOTY");
			cout<<setw(Tag_und_Zeit2);
			zeigenUberschrift("DZIE\343, GODZINA");
			cout<<setw(Zimmer2);
			zeigenUberschrift("SALA");
			cout<<setw(Zyklus2);
			zeigenUberschrift("CYKL");
			cout<<setw(Lehrer2);
			zeigenUberschrift("PROWADZ\244CY");
			cout<<endl;
			e=1;
		}
	
		while(neu[0].Zyklus.size()==1)
		{
			cout<<setw(Gegenstand2)<<neu[0].Gegenstand
				<<setw(Tag_und_Zeit2)<<neu[0].Tag+", "+neu[0].Zeit
				<<setw(Zimmer2)<<neu[0].Zimmer
				<<setw(Zyklus2)<<neu[0].Zyklus
				<<setw(Lehrer2)<<neu[0].Lehrer
				<<endl;
			ausschliessenDaten(neu, 0);
		}
			
		//cykl nieregularny
		if(alt[0].Zyklus!="" || neu[0].Zyklus!="")
		{
			if(c || d || e)
				cout<<endl;
			cout<<setw(Gegenstand3);
			zeigenUberschrift("PRZEDMIOT");
			cout<<setw(Datum3);
			zeigenUberschrift("DATA");
			cout<<setw(Zimmer3);
			zeigenUberschrift("SALA");
			cout<<setw(Lehrer3);
			zeigenUberschrift("PROWADZ\244CY");
			cout<<endl;
		}
		//przedmioty wg alt[]
		while(alt[0].Zyklus!="")
		{
			string gegenwartigGegenstand=alt[0].Gegenstand;
			int wo_neu_Gegenstand=0;
			while(neu[wo_neu_Gegenstand].Gegenstand!=gegenwartigGegenstand && neu[wo_neu_Gegenstand].Zyklus!="")
				wo_neu_Gegenstand++;
			bool zuerstGegenstand=1;
			//ta sama data
			for(int i=0; alt[i].Gegenstand==gegenwartigGegenstand; i++)
			{
				bool brechen=0;
				for(int j=wo_neu_Gegenstand; neu[j].Gegenstand==gegenwartigGegenstand && !brechen; j++)
					if(alt[i].Zyklus==neu[j].Zyklus && alt[i].Zeit==neu[j].Zeit)
					{
						bool zuerstDatum=1;
						for(int k=1; k<=2; k++)
						{
							cout<<setw(Gegenstand3);
							if(zuerstGegenstand)
							{
								cout<<alt[i].Gegenstand;
								zuerstGegenstand=0;
							}
							else
								cout<<"";
							cout<<setw(Datum3);
							if(zuerstDatum)
								cout<<alt[i].Zyklus+", "+alt[i].Zeit;
							else
								cout<<"";
							if(alt[i].Zimmer!=neu[j].Zimmer)
								zeigen_verandert_Zeile(zuerstDatum,"a",Zimmer3,alt[i].Zimmer, neu[j].Zimmer);
							else
								cout<<setw(Zimmer3)<<"-";
							if(alt[i].Lehrer!=neu[j].Lehrer)
								zeigen_verandert_Zeile(zuerstDatum,"y",Lehrer3,alt[i].Lehrer, neu[j].Lehrer);
							else
								cout<<setw(Lehrer3)<<"-";
							cout<<endl;
							if (!zuerstDatum)
							{
								ausschliessenDaten(alt, i);
								ausschliessenDaten(neu, j);
								brechen=1; i--;
							}
						 	zuerstDatum=0;
					 	}
					}
			}
			//stare
			while(alt[0].Gegenstand==gegenwartigGegenstand)
			{
				cout<<setw(Gegenstand3);
				if(zuerstGegenstand)
				{
					cout<<alt[0].Gegenstand;
					zuerstGegenstand=0;
				}
				else
					cout<<"";
				zeigen_verandert_Zeile(1,"a",Datum3,alt[0].Zyklus+", "+alt[0].Zeit,"");
				cout<<endl;
				ausschliessenDaten(alt, 0);
			}
			//nowe
			while(neu[wo_neu_Gegenstand].Gegenstand==gegenwartigGegenstand)
			{
				cout<<setw(Gegenstand3);
				if(zuerstGegenstand)
				{
					cout<<neu[wo_neu_Gegenstand].Gegenstand;
					zuerstGegenstand=0;
				}
				else
					cout<<"";
				zeigen_verandert_Zeile(0,"a",Datum3,"",neu[wo_neu_Gegenstand].Zyklus+", "+neu[wo_neu_Gegenstand].Zeit);
				cout<<setw(Zimmer3)<<neu[wo_neu_Gegenstand].Zimmer
					<<setw(Lehrer3)<<neu[wo_neu_Gegenstand].Lehrer
					<<endl;
				ausschliessenDaten(neu, wo_neu_Gegenstand);
			}
		}
		//tylko nowe
		for(int i=0; neu[i].Zyklus!=""; i++)
		{
			cout<<setw(Gegenstand3)<<neu[i].Gegenstand;
			zeigen_verandert_Zeile(0,"a",Datum3,"",neu[i].Zyklus+", "+neu[i].Zeit);
			zeigen_verandert_Zeile(0,"a",Zimmer3,"",neu[i].Zimmer);
			zeigen_verandert_Zeile(0,"y",Lehrer3,"",neu[i].Lehrer);
			cout<<endl;
		}
	}
}

void offnenDatei(string Dateiname, Daten Feld[], bool &nichtDatei, bool &nichtDaten)
{
	nichtDatei=0; nichtDaten=0;
	ifstream Datei (Dateiname.c_str());
	if(!Datei)
		nichtDatei=1;
	else
	{
		string d[7]={"PONIEDZIA\235EK", "WTOREK", "\227RODA", "CZWARTEK", "PI\244TEK", "SOBOTA", "NIEDZIELA"};
		string e[7]={"Poniedzia\210ek", "Wtorek", "\227roda", "Czwartek", "Pi\245tek", "Sobota", "Niedziela"};
		int i=-1;
		string a;

		while(Textteil(a, 0, 2)!="<hr" && !Datei.eof())
			getline(Datei,a);
		tauschen_zu_PL(a);
		int j=0;
		string s=zwischenDreieckigeklammern(a, 11);
		for(int k=0; k<7; k++)
			if(s==d[k]+" (Zaj\251cia cykliczne)")
				i=k;
		if(i!=-1)
		{
			while(Textteil(a,0,3)!="</ta" && !Datei.eof())
			{
				for(int k=i; k<7; k++)
					if(zwischenDreieckigeklammern(a, 11)==d[k]+" (Zaj\251cia cykliczne)")
					{
						i=k+1;
						getline(Datei,a);
					}
				Feld[j].Tag=e[i-1];
				Feld[j].Zimmer=zwischenDreieckigeklammern(a,10);
				getline(Datei,a); tauschen_zu_PL(a); Feld[j].Zeit=Textteil(a, 4, 8)+" - "+Textteil(a, 22, 26);
				getline(Datei,a); tauschen_zu_PL(a); Feld[j].Zyklus=a[a.size()-6];
				getline(Datei,a); tauschen_zu_PL(a); Feld[j].Gegenstand=zwischenDreieckigeklammern(a,5)+" ";
				getline(Datei,a); tauschen_zu_PL(a); Feld[j].Gegenstand+=Textteil(a, 0, suchenText(a, "<", 0, a.size()-1)-1);
				Feld[j].Lehrer=zwischenDreieckigeklammern(a,15);
				getline(Datei,a); tauschen_zu_PL(a);
				j++;
			}
		}
		if(suchenText(a,"<div",14,14)!=-1 || suchenText(a,"<div",20,20)!=-1)
		{
			while(a!="</table><br />" && !Datei.eof())
			{
				tauschen_zu_PL(a);
				if(suchenText(a, " (Zaj\251cia w cyklu nieregularnym)",0,a.size()-1)!=-1)
					getline(Datei,a);
				Feld[j].Zyklus=zwischenDreieckigeklammern(a,a.size()-(suchenText(a,"<",0,a.size()-1,3)-1));
				Feld[j].Zimmer=zwischenDreieckigeklammern(a,10);
				getline(Datei,a); Feld[j].Zeit=Textteil(a, 4, 8)+" - "+Textteil(a, 22, 26);
				getline(Datei,a); tauschen_zu_PL(a); Feld[j].Gegenstand=zwischenDreieckigeklammern(a,5)+" ";
				getline(Datei,a); tauschen_zu_PL(a); Feld[j].Gegenstand+=Textteil(a, 0, suchenText(a, "<", 0, a.size()-1)-1);
				Feld[j].Lehrer=zwischenDreieckigeklammern(a,15);
				getline(Datei,a);
				j++;
			}
		}
		if(j==0)
			nichtDaten=1;
		Datei.close();
	}
}

int main(){
Fenstergrosse(anfanglichWeite, anfanglichHohe);
stellenFenstertitel();

string Kurs, Semester, letztenSemester, Kursname;
string NICHTzeigen[q][2];
int Datum;

ladenKurs(Kurs, Semester, letztenSemester, Datum, Kursname, NICHTzeigen);

Daten alt[q];
bool nichtDateiA;
bool nichtDatenA;
offnenDatei("stary plan.html", alt, nichtDateiA, nichtDatenA);
Daten neu[q];
bool nichtDateiN;
bool nichtDatenN;
offnenDatei("nowy plan.html",neu, nichtDateiN, nichtDatenN);

if(nichtDatenA)
{
	remove("stary plan.html");
	nichtDateiA=1;
}
if(nichtDatenN)
{
	remove("nowy plan.html");
	nichtDateiN=1;
}

aktualisierenSemester(Semester, letztenSemester, Datum, nichtDateiA, Kursname);

if(nichtDateiA)
{
	if(!nichtDateiN)
	{
		rename("nowy plan.html","stary plan.html");
		offnenDatei("stary plan.html", alt, nichtDateiA, nichtDatenA);
		goto Punkt2;
	}
	Punkt1:
	stellenPuffergrosse(38+letztenZwischenraum,10); //"B³¹d pobierania..."
	cout<<"Pobieranie planu...";
	herunterladen("http://e.kul.pl/qlplan.html?ra=1&etap="+Semester+"&lekt=on&kid="+Kurs,"stary plan.html");
	stellenFenstertitel();
	offnenDatei("stary plan.html", alt, nichtDateiA, nichtDatenA);
	int Weite=45+letztenZwischenraum, Hohe=7;
	if(!nichtDatenA)
	{
		Weite=69+letztenZwischenraum;
		Hohe=6;
	}
	int hilfsWeite=Kursname.size()+2+8+letztenZwischenraum;
	if(Semester[Semester.size()-1]=='R')
		hilfsWeite=hilfsWeite-5+Textteil(Semester,0,Semester.size()-2).size();
	else
		hilfsWeite+=Semester.size();
	if(hilfsWeite>Weite)
		Weite=hilfsWeite;
	stellenPuffergrosse(Weite, Hohe);
	cout<<"Pobrano plan.";
	if(nichtDatenA)
	{
		cout<<"\nBrak danych w planie. Spr\242buj pobra\206 p\242\253niej.";
		remove("stary.html");
	}
	else
		cout<<" Aby por\242wnywa\206 zmiany uruchom p\242\253niej ponownie program.";
	bool ob_war_Veranderung=0;
	ersetzenKurs(Kurs, Semester, letztenSemester, ob_war_Veranderung, Kursname, NICHTzeigen);
	if(ob_war_Veranderung)
		goto Punkt1;
}
else
{
	if(nichtDateiN)
	{
		Punkt2:
		stellenPuffergrosse(38+letztenZwischenraum,10); //"B³¹d pobierania..."
		cout<<"Pobieranie planu...";
		herunterladen("http://e.kul.pl/qlplan.html?ra=1&etap="+Semester+"&lekt=on&kid="+Kurs,"nowy plan.html");
		stellenFenstertitel();
		offnenDatei("nowy plan.html", neu, nichtDateiN, nichtDatenN);
		
		if(nichtDatenN)
		{
			int Weite=45+letztenZwischenraum, Hohe=7;
			int hilfsWeite=Kursname.size()+2+8+letztenZwischenraum;
			if(Semester[Semester.size()-1]=='R')
				hilfsWeite=hilfsWeite-5+Textteil(Semester,0,Semester.size()-2).size();
			else
				hilfsWeite+=Semester.size();
			if(hilfsWeite>Weite)
				Weite=hilfsWeite;
			stellenPuffergrosse(Weite, Hohe);
			cout<<"Pobrano plan.\nBrak danych w planie. Spr\242buj pobra\206 p\242\253niej.";
			remove("nowy plan.html");
		}
		else
		{
			ausschliessen_von_NICHTzeigen(neu, alt, NICHTzeigen); //w tej kolejnoœci te dwie linijki, np. ¿eby dobrze zadzia³a³o usuwanie z NICHTzeigen je¿eli dwa takie same przemdioty
			ausschliessen_gleische(neu, alt);
			bool b;
			zeigenVeranderungen(alt, neu, Kursname, Semester, b);
			//ewentualnie mo¿na to, co na dole ("czy pobraæ nowy plan
		}
		bool ob_war_Veranderung=0;
		ersetzenKurs(Kurs, Semester, letztenSemester, ob_war_Veranderung, Kursname, NICHTzeigen);
		if(ob_war_Veranderung)
			goto Punkt1; //nie trzeba zerowaæ tablic, bo i tak nie bêdzie wyœwietlanych zmian
	}
	else
	{
		ausschliessen_von_NICHTzeigen(neu, alt, NICHTzeigen);
		ausschliessen_gleische(neu, alt);
		bool ob_ohne_Anderungen=0;
		zeigenVeranderungen(alt, neu, Kursname, Semester, ob_ohne_Anderungen);
		if(ob_ohne_Anderungen)
		{
			remove("nowy plan.html");
			offnenDatei("stary plan.html", alt, nichtDateiA, nichtDatenA);
			rucksetzen(neu);
			goto Punkt2;
			//nie trzeba zerowaæ tablicy alt, bo otworzenie zape³ni usuniête podczas usuniêcia powtarzaj¹cych siê
		}
		cout<<endl;
		string Anfrage="Czy pobra\206 nowy plan? (Zmiany b\251d\245 dotyczy\206 aktualnie najnowszego pliku)";
		int Weite=72+letztenZwischenraum;
		int hilfsWeite=Kursname.size()+10+letztenZwischenraum;//+ersetzenKurs
		if(Semester[Semester.size()-1]=='R')
			hilfsWeite=hilfsWeite-5+Textteil(Semester,0,Semester.size()-2).size();
		else
			hilfsWeite+=Semester.size();
		if(hilfsWeite>Weite)
			Weite=hilfsWeite;
		if(jaODERnein(Anfrage,Weite,7))
		{
			remove("stary plan.html");
			rename("nowy plan.html", "stary plan.html");
			offnenDatei("stary plan.html", alt, nichtDateiA, nichtDatenA);
			rucksetzen(neu);
			goto Punkt2;
		}
		bool ob_war_Veranderung=0;
		ersetzenKurs(Kurs, Semester, letztenSemester, ob_war_Veranderung, Kursname, NICHTzeigen);
		if(ob_war_Veranderung)
			goto Punkt1;
	}
}
Ende();
}
