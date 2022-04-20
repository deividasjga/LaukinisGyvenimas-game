#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "PapildomasR.h"
using namespace std;
/*
int getRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}
	*/
class Bendras
{
protected:
	string m_name;
	char m_symbol;
	int m_health;
	int m_power;
	int m_gold;

public:
	Bendras(string name, char symbol, int health, int power, int gold)
		: m_name(name), m_symbol(symbol), m_health(health), m_power(power), m_gold(gold){}

	const string getName()       {return m_name;}
	char getSymbol()             {return m_symbol;}
	int getHealth()              {return m_health;}
	int getPower()               {return m_power;}
	int getGold()                {return m_gold;}

	void reduceHealth(int damage) {m_health -= damage;}
	void addHealth(int damage){m_health+=damage;}
	bool operator--() {return m_health <= 0;}
	void addGold(int value) {m_gold += value;}
	void minusGold(int value){m_gold-=value;}
};

class Zaidejas: public Bendras
{
	int m_level;

public:
	Zaidejas(string name)
		: Bendras(name, '@', 100, 1, 0), m_level(1)
	{
	}

	void levelUp() {++m_level; ++m_power;}
	int getLevel() {return m_level;}
	bool operator++() {return m_level >= 20;}
};

class Gyvunas: public Bendras
{
public:
	enum Type
	{
        GRIZLIS,
		KROKODILAS,
		VILKAS,
		SKORPIONAS,
        GYVATE,
		MAX_TYPES,
	};

	struct GyvunasData
	{
		string name;
		char symbol;
		int health;
		int power;
		int gold;
	};

	static GyvunasData gyvunasData[MAX_TYPES];

	Gyvunas(Type type)
		: Bendras(gyvunasData[type].name,
             gyvunasData[type].symbol,
		     gyvunasData[type].health,
             gyvunasData[type].power,
             gyvunasData[type].gold)
	{
	}

	static Gyvunas getRandomGyvunas()
	{
		return Gyvunas(static_cast<Type>(getRandomNumber(0, MAX_TYPES - 1)));
	}
};

Gyvunas::GyvunasData Gyvunas::gyvunasData[Gyvunas::MAX_TYPES] =
{                //       HP DMG $$$
    {"Pilkasis lokys", 'g', 50, 5, 100},
	{"Krokodilas", 'c', 15, 5, 70},
	{"Vilkas", 'w', 10, 4, 50},
	{"Skorpionas", 'n', 4, 3, 30},
	{"Gyvatë", 's', 2, 1, 15},
};

void attackZaideja(Zaidejas &p, Gyvunas &m)
{
	p.reduceHealth(m.getPower());
	cout<< m.getName() << " tau trenkë ir padarë " << m.getPower() << " þalos."<<endl;
}

void attackGyvunas(Zaidejas &p, Gyvunas &m)
{
	m.reduceHealth(p.getPower());
	cout << "Tu trenkei " << m.getName() << " ir padarei " << p.getPower() << " þalos."<<endl;
	if (m.operator--())
	{
	    cout<<"****************"<<endl;
		cout << "Tu nugalëjai " << m.getName() << "."<<endl;
		p.levelUp();
		cout << "Padidinai savo galià iki " << p.getLevel() << "."<<endl;
		p.addGold(m.getGold());
		cout << "Uþ " << m.getName() << " gavai " << m.getGold() << " $."<<endl;
			    cout<<"****************"<<endl;
	}
	else
		attackZaideja(p, m);
}
void shop(Zaidejas &p, Gyvunas &m){
    cout<<endl;
    cout<<"~~~~~~~~~~~~~~ PARDUOTUVË ~~~~~~~~~~~~~~"<<endl;
    cout<<"Sveikas atvykæs á parduotuvæ! Èia gali nusipirkti daiktø. (Áveskite norimo daikto numerá)"<<endl;
    cout<<"1. Gyvybës eleksyras, kuris suteiks 10 gyvybiø (kaina: 125$)"<<endl;
    cout<<"2. Didysis gyvybës eleksyras, kuris suteiks 20 gyvybiø (kaina: 220$)"<<endl;
    cout<<endl;
    cout<<"                                                     Tavo piniginë: "<<p.getGold()<<endl;
    char numeris1;
    cin>>numeris1;
    if((numeris1=='1' && p.getGold()>=125)){p.minusGold(125); p.addHealth(10);cout<<"Nusipirkta ir panaudota."<<endl;cout<<"Tu iðëjai ið parduotuvës."<<endl;}
    else if((numeris1=='1' && p.getGold()<125)){cout<<"X"<<endl; cout<<"Nepakanka pinigø nusipirkti ði daiktà."<<endl;cout<<"Tu iðëjai ið parduotuvës."<<endl;}
    if((numeris1=='2' && p.getGold()>=220)){p.minusGold(220); p.addHealth(20);cout<<"Nusipirkta ir panaudota."<<endl;cout<<"Tu iðëjai ið parduotuvës."<<endl;}
    else if((numeris1=='2' && p.getGold()<220)){cout<<"X"<<endl;cout<<"Nepakanka pinigø nusipirkti ði daiktà."<<endl;cout<<"Tu iðëjai ið parduotuvës."<<endl;}
    else { cout<<"Jei nori iðeiti ið parduotuvës, spausk bet kà."<<endl; char iseiti; cin>>iseiti; if(1==1){cout<<"Tu iðëjai ið parduotuvës."<<endl;}
    }
}

void fightGyvunas(Zaidejas &p)
{
	Gyvunas m(Gyvunas::getRandomGyvunas());
	//cout
	bool hasRun(false);
	while (!m.operator--() && !p.operator--() && !hasRun)
	{
	    cout<<"----------------------------------------------------------------------------"<<endl;
	    	cout << "Pasiruoðk! " << m.getName() << " tave puola (GYVYBËS: "<<m.getHealth()<<"; GALIA: "<<m.getPower()<<"; VERTË: "<<m.getGold()<<"$)"<<endl;
		cout << "Tavo statistika: GALIA: " << p.getLevel() << ", GYVYBËS: " << p.getHealth() << "/100. Tavo piniginë: "<<p.getGold()<<endl; cout<<"Pasirink: 1) Kovoti     (spausk F);"<<endl;
                                                                                                                                 cout<<"          2) Slëptis    (spausk H);"<<endl;
                                                                                                                                 cout<<"          3) Parduotuvë (spausk B). "<<endl;
		char choice;
		cin >> choice;

		if (choice == 'h' || choice == 'H')
		{
			hasRun = getRandomNumber(0,1);

			if (hasRun)
				cout << "Tu sëkmingai pasislëpei."<<endl;
			else
			{
				cout << "Nepaëjo pasislëpti. Bandyk dar kartà arba kovok."<<endl;
				attackZaideja(p, m);
			}
		}
		else if (choice == 'f' || choice == 'F')
			attackGyvunas(p, m);
        else if (choice=='b' || choice=='B'){shop(p, m);}
	}
}


struct maistas
{
    int x,y;
    char value;
};
struct gyvatele
{
    int x,y;
    char value;
};
void mapas(char map[][50])
{
    for(int i=0; i<20; ++i)
    {
        for(int j=0; j<50; ++j)
        {
            cout<<map[i][j];
        }
        cout<<endl;
    }
}
void gamaistas(char map[][50],maistas &f)
{
    srand((unsigned)time(0));
    f.x=rand()%19;
    f.y=rand()%49;
    map[f.x][f.y]=f.value;
}
char so='a';
void change(vector<struct gyvatele> &v,char &ch)
{
    int a=0,b=0;
    if(ch!='a'&&ch!='s'&&ch!='d'&&ch!='w')
        ch=so;
    else if(((ch=='a')&&(so=='d'))||((ch=='d')&&(so=='a')))
    {
        ch=so;
    }
    else if(((ch=='w')&&(so=='s'))||((ch=='s')&&(so=='w')))
    {
        ch=so;
    }
    if(ch=='a')
        b=-1;
    else if(ch=='w')
        a=-1;
    else if(ch=='s')
        a=1;
    else if(ch=='d')
        b=1;
    for(int i=v.size()-1; i>0; --i)
    {
        v[i].x=v[i-1].x;
        v[i].y=v[i-1].y;
    }
    v[0].x+=a;
    v[0].y+=b;
    if(v[0].x==-1)
        v[0].x=19;
    else if(v[0].x==20)
        v[0].x=0;
    if(v[0].y==-1)
        v[0].y=49;
    else if(v[0].y==50)
        v[0].y=0;
    for(int i=v.size()-1; i>3; --i)
    {
        if(v[0].x==v[i].x&&v[0].y==v[i].y)
        {
            cout<<"Ooops! Save suvalgei...";
            exit(0);
        }
    }
    so=ch;
}
void start(char map[][50],maistas &f,vector<struct gyvatele> &v)
{
    char ch='a';
    map[f.x][f.y]=f.value;
    for(int i=0; i<v.size(); ++i)
    {
        map[v[i].x][v[i].y]=v[i].value;
    }
    mapas(map);
    for(int i=0; i<v.size(); ++i)
    {
        map[v[i].x][v[i].y]=' ';
    }
    while(1)
    {
        if(kbhit())
            ch=getch();
        if(ch=='p')
            break;
        system("cls");
        change(v,ch);
        if(f.x==v[0].x&&f.y==v[0].y)
        {
            struct gyvatele s;
            s.x=v[0].x;
            s.y=v[0].y;
            s.value='o';
            gamaistas(map,f);
            v.insert(v.begin()+1,s);
            change(v,ch);
        }
        map[f.x][f.y]=f.value;
        for(int i=0; i<v.size(); ++i)
        {
            map[v[i].x][v[i].y]=v[i].value;
        }
        mapas(map);
        for(long long num=0; num<10000000; ++num);
        for(int i=0; i<v.size(); ++i)
        {
            map[v[i].x][v[i].y]=' ';
        }
    }
}


int main()
{
    setlocale(LC_ALL, "Lithuanian");
	srand(static_cast<unsigned int>(time(0)));
	rand();
    char numBetkas;
	cout<<endl;
	cout<<"                   LAUKINIS GYVENIMAS       "<<endl;
    cout<<"           +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"<<endl;
	cout<<endl;
	cout<<"      (Press any character and ENTER to start the game)."<<endl;
	cin>>numBetkas;
	string name="";
	Zaidejas p(name);
	//char op;
	//cout<<"1. Lengvas"<<endl;
	//cin>>op;
	//if(op=='1'){
	cout << "Sveikas. Pasiek 20 galios ir laimësi þaidimà."<<endl;
	cout<<"Tu gali kovoti su prieðais ir uþ jø nuþudymà gauti pinigø. Jei nori iðvengti"<<endl;  cout<<"prieðo, gali bandyti slëptis nuo jo, taèiau tai padaryti sëkmingai yra 50%."<<endl;
	cout<<"Sekmës!"<<endl;
	while (!p.operator++() && !p.operator--())
		fightGyvunas(p);
//} /////////////////
	if (p.operator++())
        {cout<<endl;
        cout<<endl;
        cout<<endl;
        cout <<"Laimëjai!"<<endl;
        cout<<endl;
        cout<<"Dabar gali þaisti uþ tuos gyvûnus."<<endl;
        cout<<"Atrankinti gyvûnai:"<<endl;
        cout<<"1. Gyvatë"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
    char c;
    cin>>c;
   if(c=='1'){
    char map[20][50];
    for(int i=0; i<20; ++i)
    {
        for(int j=0; j<50; ++j)
        {
            map[i][j]=' ';
        }
    }
    struct maistas f;
    vector<struct gyvatele> v;
    struct gyvatele s;
    f.x=0; f.y=5;
    f.value='@';
    s.x=4;s.y=4;
    s.value='O';
    v.push_back(s);
    s.x=4;s.y=5;
    s.value='o';
    v.push_back(s);
    s.x=4;s.y=6;
    s.value='o';
    v.push_back(s);
    s.x=4;s.y=7;
    s.value='o';
    v.push_back(s);
    if(c=='y')
    {
        cin>>so;
        if(cin.eof())
            so='a';
        else
        {
            v.clear();
            cin>>f.x;
            cin>>f.y;
            while(!cin.eof())
            {
                cin>>s.x>>s.y>>s.value;
                v.push_back(s);
            }
            v.pop_back();
        }
    }
    start(map,f,v);
    cout<<so<<endl;
    cout<<f.x<<endl;
    cout<<f.y<<endl;
    for(int i=0; i<v.size(); ++i)
    {
        cout<<v[i].x<<endl;
        cout<<v[i].y<<endl;
        cout<<v[i].value;
        if(i!=v.size()-1)
            cout<<endl;
    }
   }
   else cout<<"neatrakintas"<<endl;
	}
	else{cout <<"Tu mirei."<<endl;}
	return 0;
}
