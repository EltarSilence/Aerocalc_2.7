/*/CALCOLATORE AERONAUTICO BY GIO V2.7.3/*/
/*
============inizio informazioni============
|   CASE xx   | --> Informazioni da segnalare (ultima modifica)
|=============|================================================
|   CASE 01   | --> nulla da segnalare
|   CASE 02   | --> nulla da segnalare
|   CASE 03   | --> nulla da segnalare
|   CASE 04   | --> Formula puramente approssimativa, +-1,5 C. (01/2017)
|   CASE 05   | --> Formula puramente approssimativa, +-1 km (01/2017)
|   CASE 06   | --> Fonte: Wikipedia
|   CASE 07   | --> nulla da segnalare
|   CASE 08   | --> nulla da segnalare
|   CASE 09   | --> Fonte: IVAO
|   CASE 10   | --> nulla da segnalare
|   CASE 11   | --> nulla da segnalare
|   CASE 12   | --> Fonte: fuelplanner.com
|   CASE 13   | --> nulla da segnalare
|   CASE 14   | --> nulla da segnalare
|   CASE 15   | --> Programma basato sui case 1 e 2
|   CASE 16   | --> Programma in piena fase di sviluppo, possibili frequenti bug v1.0 (01/2017)
|   CASE 17   | --> Beta testing, squawk casuali. v1.4 (18/03/2017)
|   CASE 19   | --> Heat Index in arrivo (data da definire)
|   CASE 20   | --> Beta testing, spazi aerei inesistenti ammessi, v1.4 (18/03/2017)
============fine informazioni=============
*/
//Released by Giovanni Rizza, 18/03/2017

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <time.h>

//DEFINIZIONI DI COSTANTI PER L'INDICE DI CALORE HEAT INDEX
#define HIa 2.04901523
#define HIb 10.14333127
#define HIc 0.22475541
#define HId 0.00683783
#define HIe 0.05481717
#define HIf 0.00122874
#define HIg 0.00085282
#define HIh 0.00000199

using namespace std;

int main()
{
	const double t1 = -42.379;
	const double t2 = 2.04901523;
	const double t3 = 10.14333127;
	const double t4 = -.22475541;
	const double t5 = -0.00683783;
	const double t6 = -0.05481717;
	const double t7 = 0.00122874;
	const double t8 = 0.00085282;
	const double t9 = -0.00000199;
	int scelta, ore, golf;
	float stim, v, d, p, t, h, c, valt, valts, qfe, qnh;
	float altnuv, dewp1, temp2, minuti, ur, ur1, radc, vel, vel1;
	float temp1, dewp, altz, vwfield, alfa, crosswind, htwnd, carb;
	float quota, quota1, press, press1, dirwind, intwind, prua, distanza;
	string punto;
    //VARIABILI CASE 16 METAR WRITER dichiarate sotto
	int gdm, raffica, vis, snuvole, qnh1;
	string orario, osservaz, nuvole, liv_nuvole, gustquest, dirwind1, intwind1, tempx, tempy;
    //VARIABILI ORIO CLEARANCE GENERATOR
	int scelta1;
	int c1, c2, c3, c4;
	string calls, dest;
    //VARIABILI NATO COLOR INDICATOR
	int scelta_nato;
	int vis_nato, ceiling_nato;
    //VARIABILI HEAT INDEX E WIND CHILL
	float temp, windspeed, humi, wndchll, heatindex;
    //VARIABILI CASE 20
	int vis_vmc, cld_distance_v, cld_distance_orz, flightlevel;
	char airspace_cat;

	menu:
	cout << "**Calcolatore Aeronautico by Gio**" << endl;
	cout << "" <<endl;
	cout << "Consultare il codice sorgente per informazioni" <<endl;
	cout << "" <<endl;
	cout << "Scegli un'opzione:"<<endl;
	cout << "" <<endl;
	cout << "0. Esci dal programma" <<endl;
	cout << "1. Calcolo del QNH" <<endl;
	cout << "2. Calcolo del QFE" <<endl;
	cout << "3. Stimati VFR/IFR" <<endl;
	cout << "4. Approssimazione dewpoint" <<endl;
	cout << "5. Altezza stimata delle nuvole" <<endl;
	cout << "6. Campo di visione orizzonte da quota" <<endl;
	cout << "7. Convertitore hPa --> inHg" <<endl;
	cout << "8. Convertitore inHg --> hPa" <<endl;
	cout << "9. Calcolo vento in crosswind / headwind / tailwind"<<endl;
	cout << "10. Convertitore Kt --> Km/h" <<endl;
	cout << "11. Convertitore Km/h --> Kt" <<endl;
	cout << "12. Calcolatore carburante" <<endl;
	cout << "13. Convertitore ft --> m" <<endl;
	cout << "14. Convertitore m --> ft" <<endl;
	cout << "15. Utility barometrica METAR" <<endl;
	cout << "16. Costruzione METAR (alpha 1.0)" <<endl;
	cout << "17. Orio Clearance Generator (alpha 1.0)" <<endl;
	cout << "18. Indicatore di colore del cielo NATO" <<endl;
	cout << "19. Calcolo del Wind Chill (e Heat Index coming soon...)" <<endl;
	cout << "20. Calcolo delle condizioni VMC (ITALIA)" <<endl;

	cin >> scelta;
	switch (scelta)
	{
		case 0:
		goto fine2;
		break;
		case 1:
		cout << "Inserisci il valore di pressione rilevato (hPa)" <<endl;
		cin >> p;
		cout << "Inserisci l'altezza del barometro rispetto al suolo (m)" <<endl;
		cin >> h;
		cout << "Inserisci il valore di temperatura rilevata (C)" <<endl;
		cin >> t;
        //Formula spezzata in + variabili x migliore integrazione
		if (p>0 && h>0)
		{
			valt=h/29.97;
			valts=p/(t+237.15);
			c=valt*valts;
			qfe=p+c;
			qnh=4.6+1.0195*qfe;
			cout << "Il QNH e' di " << qnh << " hPa" <<endl;
			system("pause");
		}
		else
		{
			cout << "Inserire valori validi" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 2:
		cout << "Inserisci il valore di pressione rilevato" <<endl;
		cin >> p;
		cout << "Inserisci l'altezza del barometro rispetto al suolo" <<endl;
		cin >> h;
		cout << "Inserisci il valore di temperatura rilevata" <<endl;
		cin >> t;
        //Formula spezzata in + variabili x migliore integrazione
		if (p>0 && h>0)
		{
			valt=h/29.97;
			valts=p/(t+237.15);
			c=valt*valts;
			qfe=p+c;
			cout << "Il QFE e' di " << qfe << " hPa"<<endl;
			system("pause");
		}
		else
		{
			cout << "Inserire valori validi" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 3:
		cout << "Inserisci il punto dove vuoi arrivare" <<endl;
		cin >> punto;
		cout << "Inserisci la distanza (nm) da " << punto <<endl;
		cin >> d;
		cout << "Inserisci la velocita' groundspeed (kt): "<<endl;
		cin >> v;
		if (d>0 && v>0)
		{
        //conversione in kmh e km
			v=v*1.852;
			d=d*1.852;
			cout << "Velocita': " << v << " km/h"<<endl;
			cout << "Distanza: " << d << " km"<<endl;
			stim=d/v;
        //conversione in minuti e secondi
			ore = (int)stim;
			minuti = stim - ore;
			ore*60;
			minuti=minuti*60;
			cout << "Arrivo a " << punto << " stimato in " << ore << " ore e "<< floor(minuti) << " primi"<< endl;
			system("pause");
		}
		else
		{
			cout << "Inserire dei numeri validi per il calcolo" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 4:
		cout << "ATTENZIONE: il valore in output e' stimato con una precisione di +-1,5 C." <<endl;
		cout << "Inserisci l'umidita' relativa (%): "<<endl;
		cin>> ur;
		cout << "Inserisci la temperatura (C): "<<endl;
		cin >> temp1;
		if (ur<100)
		{
        //Formula spezzata in + variabili x migliore integrazione:
        /*/Dewpoint = radice ottava di umidita' fratto 100
        per (112+0,9 per temperatura) + (0,1 per temperatura) - 113/*/
			ur1=ur/100;
			radc = pow(ur1, 1.0/8);
			dewp=radc*(112+0.9*temp1)+0.1*temp1-113;
			cout << "Dewpoint: " << dewp << " C" <<endl;
			system("pause");
		}
		else
		{
			cout << "L'umidita' non puo' essere maggiore di 100%" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 5:
		cout << "ATTENZIONE: il valore in output e' stimato con scarsa precisione (+-1,5km)." <<endl;
		cout << "Inserisci la temperatura (C): "<<endl;
		cin >> temp2;
		cout << "Inserisci il dewpoint (C): "<<endl;
		cin >> dewp1;
		if (dewp1<temp2)
		{
			altnuv=213.5*(temp2-dewp1);
			cout << "Altezza stimata nuvole: "<< ceil(altnuv) << " metri"<<endl;
			altnuv=altnuv*3.28;
			cout << "Altezza stimata nuvole: "<< ceil(altnuv) << " piedi"<<endl;
			system("pause");
		}
		else
		{
			cout << "Il dewpoint non puo' mai essere maggiore della temperatura"<<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 6:
		cout << "Inserisci l'altezza (ft)"<<endl;
		cin >> altz;
		if (altz<100)
		{
			cout << "Inserisci un valore uguale o superiore a 100ft"<<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		else
		{
			altz=altz/3.28;
			vwfield=3570*sqrt(altz);
			vwfield=vwfield/1000;
			cout << "A visibilita' illimitata, il raggio di visione a " << altz*3.28 << "ft e' di " << floor(vwfield) << " km"<<endl;
			system("pause");
		}
		break;
		case 7:
		press=0;
		press1=0;
		cout << "Inserisci il valore di pressione (hPa)" <<endl;
		cin >> press;
		press1=press*0.0295301;
		cout << press << " hPa = " << press1 << " inHg"<<endl;
		system("pause");
		break;
		case 8:
		press=0;
		press1=0;
		cout << "Inserisci il valore di pressione (inHg)" <<endl;
		cin >> press;
		press1=press*33.8637526;
		cout << press << " inHg = " << press1/100 << " hPa"<<endl;
		system("pause");
		break;
		case 9:
		cout << "Inserisci la direzione del vento (gradi): "<<endl;
		cin >> dirwind;
		cout << "Inserisci l'intensita' del vento (kt): "<<endl;
		cin >> intwind;
		cout << "Inserisci la prua di riferimento (gradi): "<<endl;
		cin >> prua;
		if (dirwind<360 && prua<360)
		{
			alfa=dirwind-prua;
        //Conversione radianti-gradi
			alfa=alfa*3.14159/180;
			if (dirwind<prua)
			{
				crosswind=abs(intwind*sin(alfa));
        //htwnd = head o tail wind (dipende)
				htwnd=intwind*cos(alfa);
				cout << "Crosswind: " << abs(crosswind) << " kts da sinistra"<<endl;
				cout << "Headwind/Tailwind: " << abs(htwnd) << " kts"<<endl;
			}
			else
			{
				crosswind=intwind*sin(alfa);
        //htwnd = head o tail wind (dipende)
				htwnd=intwind*cos(alfa);
				cout << "Crosswind: " << abs(crosswind) << " kts da destra"<<endl;
				cout << "Headwind/Tailwind: " << abs(htwnd) << " kts"<<endl;
			}
			system("pause");
		}
		else
		{
			cout << "Le direzioni maggiori di 360 non sono valide, riprovare" <<endl;
			cout << ""<<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 10:
		cout << "Inserisci la velocita' (kt):" <<endl;
		cin >> vel;
		if (vel>=0)
		{
			vel1=vel*1.852;
			cout << vel << " kt = " << vel1 << " km/h" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		else
		{
			cout << "Velocita' non valida" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 11:
		cout << "Inserisci la velocita' (km/h):" <<endl;
		cin >> vel;
		if (vel>=0)
		{
			vel1=vel/1.852;
			cout << vel << " km/h = " << vel1 << " kt" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		else
		{
			cout << "Velocita' non valida" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;


		case 12:
		system("cls");
		menu1:
		cout << "CALCOLATORE CARBURANTE: SCEGLI AEREO:"<<endl;
		cout << "Attenzione: il riferimento ad ogni aereo corrisponde alla sua versione professionale" <<endl;
		cout << "Attenzione: il risultato e' il carburante totale, comprensivo di riserva" <<endl;
		cout << "" <<endl;
		cout << "0. Torna al menu principale"<<endl;
		cout << "1. Airbus 319"<<endl;
		cout << "2. Airbus 321"<<endl;
		cout << "3. Airbus 380"<<endl;
		cout << "4. Boeing 737"<<endl;
		cout << "5. Boeing 747"<<endl;
		cout << "6. Boeing 777"<<endl;
		cout << "7. MD11"<<endl;
		cout << "8. Pilatus PC-12"<<endl;
		cout << "9. Beech Baron 58"<<endl;
		cin >> golf;
		switch (golf)
		{
			case 1:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=15070*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "Inserisci un valore maggiore di 0" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			case 2:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=18341*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "Inserisci un valore maggiore di 0" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			case 3:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=73214*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "Inserisci un valore maggiore di 0" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			case 4:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
        //controllo supplementare x max serbatoio
			if (distanza>0 && distanza<1600)
			{
				carb=15772*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "L'aereo non puo' effettuare una tratta lunga " << distanza << " nm"<<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			case 5:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=58332*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "Inserisci un valore maggiore di 0" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			case 6:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=50624*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "Inserisci un valore maggiore di 0" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			case 7:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=45159*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "Inserisci un valore maggiore di 0" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			case 8:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=1401*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			case 9:
			cout << "Inserisci la distanza (nm):" <<endl;
			cin >> distanza;
			if (distanza>0)
			{
				carb=1598*distanza/571;
				cout << "Carburante da imbarcare: " << ceil(carb) << " lbs" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			else
			{
				cout << "Inserisci un valore maggiore di 0" <<endl;
				system("pause");
				system("cls");
				goto menu1;
			}
			break;
			default: goto fine;
			break;
		}
		case 13:
		cout << "Inserisci la quota (ft)" <<endl;
		cin >> quota;
		quota1=quota/3.28;
		cout << quota << "ft = " << quota1 << "m" <<endl;
		system("pause");
		system("cls");
		goto menu;
		break;
		case 14:
		cout << "Inserisci la quota (m)" <<endl;
		cin >> quota;
		quota1=quota*3.28;
		cout << quota << "m = " << quota1 << "ft" <<endl;
		system("pause");
		system("cls");
		goto menu;
		break;
		case 15:
		cout << "Inserisci il valore di pressione rilevato (hPa)" <<endl;
		cin >> p;
		cout << "Inserisci l'altezza del barometro rispetto al suolo (m)" <<endl;
		cin >> h;
		cout << "Inserisci il valore di temperatura rilevata (C)" <<endl;
		cin >> t;
		if (p>0 && h>0)
		{
			valt=h/29.97;
			valts=p/(t+237.15);
			c=valt*valts;
			qfe=p+c;
			qnh=4.6+1.0195*qfe;
			cout << "Il QNH e' " << ceil(qnh) << " hPa" <<endl;
			cout << "(" << qnh << " hPa)" <<endl;
			cout << "Il QFE e' " << qfe << " hPa" <<endl;
			system("pause");
		}
		else
		{
			cout << "Inserire valori validi" <<endl;
			system("pause");
			system("cls");
			goto menu;
		}
		break;
		case 16:
		raffica=0;
		system("cls");
		cout << "Inserisci il giorno del mese" <<endl;
		cin >> gdm;
		cout << "Inserisci l'orario in formato HHMMZ" <<endl;
		cin >> orario;
		cout << "Inserisci la direzione da dove proviene il vento"<<endl;
		cin >> dirwind1;
		cout << "Inserisci la velocita del vento (kt)"<<endl;
		cin >> intwind1;
		cout << "Ci sono raffiche? (Y/N)" <<endl;
		cin >> gustquest;
		if (gustquest=="Y" || gustquest=="y")
		{
			cout << "Inserisci l'intensita delle raffiche"<<endl;
			cin >> raffica;
		}
		cout << "Inserisci la visibilita (metri)"<<endl;
		cin >> vis;
		cout << "Inserisci l'osservazione meteorologica"<<endl;
		cin >> osservaz;
		cout << "Scegli il livello di nuvolosita:"<<endl;
		cout << "1. CAVOK"<<endl;
		cout << "2. FEW"<<endl;
		cout << "3. SCT"<<endl;
		cout << "4. BKN"<<endl;
		cout << "5. OVC"<<endl;
		cin >> snuvole;
		switch (snuvole)
		{
			case 1:
			nuvole="CAVOK";
			break;
			case 2:
			nuvole="FEW";
			break;
			case 3:
			nuvole="SCT";
			break;
			case 4:
			nuvole="BKN";
			break;
			case 5:
			nuvole="OVC";
			break;
			default: cout<< "Errore" <<endl;
		}
		cout << "Inserisci il livello delle nubi"<<endl;
		cin >> liv_nuvole;
		cout << "Inserisci la temperatura"<<endl;
		cin >> tempx;
		cout << "Inserisci la temperatura di rugiada"<<endl;
		cin >> tempy;
		cout << "Inserisci il QNH"<<endl;
		cin >> qnh1;
		system("pause");
		if (gustquest=="Y" || gustquest=="y")
		{
			cout << "METAR LIDQ " << dirwind1 << intwind1 << "G" << raffica << "KT " << vis << " " << osservaz << " " << nuvole << liv_nuvole << " " << tempx << "/" << tempy << " Q" << qnh1<<endl;
		}
		else
			cout << "METAR LIDQ " << dirwind1 << intwind1 << "KT " << vis << " " << osservaz << " " << nuvole << liv_nuvole << " " << tempx << "/" << tempy << " Q" << qnh1<<endl;
		system("pause");
		system("cls");
		goto menu;
		break;

		case 17:
		srand(time(NULL));
		cout << "Inserisci il callsign:" <<endl;
		cin >> calls;
		cout << "Inserisci la destinazione:" <<endl;
		cin >> dest;
		cout << "SELEZIONA IL NUMERO CORRISPONDENTE AL PRIMO PUNTO ROTTA";
		cout <<endl;
		cout <<endl;
		cout << "1. TZO"<<endl;
		cout << "2. BEG"<<endl;
		cout << "3. ORI"<<endl;
		cout << "4. VOG"<<endl;
		cout << "5. SRN"<<endl;
		cout << "6. TUVIB"<<endl;
		cout << "7. ABESI"<<endl;
		cout << "8. ARLES"<<endl;
		cout << "9. CANNE"<<endl;
		cout << "10. DILEB"<<endl;
		cout << "11. GEN"<<endl;
		cout << "12. LOGDI"<<endl;
		cout << "13. EKPAL"<<endl;
		cout << "14. OMETO"<<endl;
		cout << "15. OSKOR"<<endl;
		cout << "16. RIDVA"<<endl;
		cout << "17. VAKON"<<endl;
		cin >> scelta1;
		c1=rand()%4+4;
		c2=rand()%8;
		c3=rand()%8;
		c4=rand()%8;
		switch (scelta1){
			case 1:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via TZO6W, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4<<endl;
			system("pause");
			system("cls");
			break;
			case 2:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via BEG6X, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 3:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via ORI6W, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 4:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via TZO6W, transizione VOG5U, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 5:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via SRN6R, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 6:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via TUVIB5W, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 7:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via ORI6W, transizione ABESI5N, iniziali 5000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 8:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via BEG6X, transizione ARLES9T, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 9:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via ORI6W, transizione CANNE5N, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 10:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via ORI6W, transizione DILEB7S, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 11:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via TZO6W, transizione GEN5D, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 12:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via TUVIB5W, transizione LOGDI5B, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 13:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via TZO6W, transizione EKPAL5V, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 14:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via BEG6X, transizione OMETO9T, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 15:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via ORI6W, transizione OSKOR8T, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 16:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via TUVIB5W, transizione RIDVA5B, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			case 17:
			cout << calls << ", autorizzato a destinazione finale " << dest << " via VAKON6W, iniziali 6000 piedi, squawk " << c1<<c2<<c3<<c4 <<endl;
			system("pause");
			system("cls");
			break;
			default: cout << "Errore" <<endl;
			break;
		}
		case 18:
		system("cls");
		cout << "Indicatore del cielo NATO" <<endl;
		cout << "Inserisci la visibilita' (metri): ";
		cin >> vis_nato;
		cout << "Inserisci il ceiling (piedi): " <<endl;
		cout << "(Se il ceiling e' UNL, inserire 20000)"<<endl;
		cin >> ceiling_nato;
		if (vis_nato >= 8000 && ceiling_nato >= 20000)
			cout << "NATO COLOR: BLU+" <<endl;
		else
			if (vis_nato >= 8000 && ceiling_nato >= 2500)
				cout << "NATO COLOR: BLU" <<endl;
			else
				if (vis_nato >= 5000 && ceiling_nato >= 1500)
					cout << "NATO COLOR: WHT (WHITE)" <<endl;
				else
					if (vis_nato >= 3700 && ceiling_nato >= 700)
						cout << "NATO COLOR: GRN (GREEN)" <<endl;
					else
						if (vis_nato >= 1600 && ceiling_nato >= 300)
							cout << "NATO COLOR: YLO (YELLOW)" <<endl;
						else
							if (vis_nato > 800 && ceiling_nato > 200)
								cout << "NATO COLOR: AMB (AMBER)" <<endl;
							else
								cout << "NATO COLOR: RED" <<endl;
							system("pause");
							break;
    case 19: //HEAT INDEX DA SISTEMARE - CASE 19 INOPERATIVO


    cout << "Inserisci la temperatura (C): "<<endl;
    cin >> temp; //utilizzo variabile temp
    cout << "Inserisci l'umidita' relativa (percentuale): "<<endl;
    cin >> humi;
    cout << "Inserisci la velocita' del vento (nodi): "<<endl;
    cin >> windspeed;
    //CALCOLO WIND CHILL
    if ((humi>=1 && humi<=99) && (temp<=33 || windspeed>5)) //condizione di applicabilita'
    {
    	wndchll=0.045*(5.27*pow(windspeed,0.45)+10.45-0.28*windspeed)*(temp-33)+33;
    	cout << "Wind Chill: " << wndchll <<" C"<<endl;
    }
    else cout << "Valori non applicabili per il calcolo del Wind Chill" <<endl;
    system("pause");
    //RIMUOVERE IL SEGUENTE TAG PER ACCEDERE E MODIFICARE IL CODICE
    /*
    //H E A T   I N D E X

    //CONDIZIONE DI APPLICABILITA'
    if ((humi>=1 && humi<=99) && (temp>=27 && humi>=40))

    //MISTO DEFINE E NUMERI PRESI DA SITO
    heatindex = -42.379 + 2.04901*temp + 10.14333*temp - 0.22475*temp*humi - HId*temp*temp - HIe*humi*humi + HIf*temp*temp*humi + HIg*temp*humi*humi - HIh*temp*temp*humi*humi; //prese dal sito con javascript

    //CONVERSIONI
    temp=temp*1.8+32; //conversione in Fahreneit
    heatindex = (heatindex-32)/1.8; //riconversione in Celsius

    //CODICE CON FORMULA RIDOTTA
    if ((humi>=1 && humi<=99) && (temp>=27 && humi>=40))
    {
    heatindex = 0.5 * (temp + 61.0 + ((temp-68.0)*1.2)+ (humi*0.094)) + 21;
    cout << "Heat Index: " << heatindex <<" f"<<endl;
    system("pause");
    }

    //CON DEFINE
    heatindex = -42.379+HIa*temp+HIb*humi-HIc*temp*humi-HId*pow(temp,2)-HIe*pow(humi,2)+HIf*pow(temp,2)*humi+HIg*temp*pow(humi,2)+HIh*pow(temp,2)*pow(humi,2);

    //VISUALIZZAZIONE
    cout << "Heat Index: " << heatindex <<" C"<<endl;

    //CON POTENZA (PRIMO PROGETTO)
    heatindex = t1+t2*temp+t3*humi-t4*temp*humi-t5*pow(temp,2)-t6*pow(humi,2)+t7*pow(temp,2)*humi+t8*temp*pow(humi,2)+t9*pow(temp,2)*pow(humi,2);
    heatindex = (heatindex-32)/1.8;
    } //chiusura if

    else cout << "Valori non applicabili per il calcolo dell'Heat Index" <<endl; //condizione di non esistenza
    system("pause");
    */
    //FINE DEL CASE
    break;
    case 20:
    system("cls");
    cout << "Inserisci la visibilita' (m)"<<endl;
    cin >> vis_vmc;
    cout << "Inserisci la categoria di spazio aereo" <<endl;
    cin >> airspace_cat; //stringa
    cout << "Inserisci la distanza verticale dalle nubi (ft)" <<endl;
    cin >> cld_distance_v;
    cout << "Inserisci la distanza orizzontale dalle nubi (m)" <<endl;
    cin >> cld_distance_orz;
    cout << "In che spazio aereo ti trovi?" <<endl;
    cout << "1. A FL100 o sopra" <<endl;
    cout << "2. Tra FL 100 e 3000ft AMSL" <<endl;
    cout << "3. Sotto i 3000ft AMSL" <<endl;
    cin >> flightlevel;
    switch(flightlevel)
    {//apertura switch case 20
    	case 1:
    	if (vis_vmc>=8000 && ((airspace_cat=='B' || airspace_cat=='b' )||(airspace_cat=='C' || airspace_cat=='c' )||(airspace_cat=='D' || airspace_cat=='d' )||(airspace_cat=='E' || airspace_cat=='e')||(airspace_cat=='F' || airspace_cat=='f' )||(airspace_cat=='G' || airspace_cat=='g')) && (cld_distance_v>=1000 && cld_distance_orz>=1500))
    		cout << "In spazio aereo " << airspace_cat << ", nella quota selezionata, con visibilita' di " << vis_vmc << "m, con distanza dalle nubi verticalmente di " << cld_distance_v << "ft ed orizzontalmente di " << cld_distance_orz << "m, ci sono le condizioni VMC" <<endl;
    	else cout << "In spazio aereo " << airspace_cat << ", nella quota selezionata, con visibilita' di " << vis_vmc << "m, con distanza dalle nubi verticalmente di " << cld_distance_v << "ft ed orizzontalmente di " << cld_distance_orz << "m, non ci sono le condizioni VMC" <<endl;
    	system("pause");
    	break;
    	case 2:
    	if (vis_vmc>=5000 && ((airspace_cat=='B' || airspace_cat=='b' )||(airspace_cat=='C' || airspace_cat=='c' )||(airspace_cat=='D' || airspace_cat=='d' )||(airspace_cat=='E' || airspace_cat=='e')||(airspace_cat=='F' || airspace_cat=='f' )||(airspace_cat=='G' || airspace_cat=='g')) && (cld_distance_v>=1000 && cld_distance_orz>=1500))
    		cout << "In spazio aereo " << airspace_cat << ", nella quota selezionata, con visibilita' di " << vis_vmc << "m, con distanza dalle nubi verticalmente di " << cld_distance_v << "ft ed orizzontalmente di " << cld_distance_orz << "m, ci sono le condizioni VMC" <<endl;
    	else cout << "In spazio aereo " << airspace_cat << ", nella quota selezionata, con visibilita' di " << vis_vmc << "m, con distanza dalle nubi verticalmente di " << cld_distance_v << "ft ed orizzontalmente di " << cld_distance_orz << "m, non ci sono le condizioni VMC" <<endl;
    	system("pause");
    	break;
    	case 3:
    	if (vis_vmc>=5000 && ((airspace_cat=='B' || airspace_cat=='b' )||(airspace_cat=='C' || airspace_cat=='c' )||(airspace_cat=='D' || airspace_cat=='d' )||(airspace_cat=='E' || airspace_cat=='e')) && (cld_distance_v>=1000 && cld_distance_orz>=1500))
    		cout << "In spazio aereo " << airspace_cat << ", nella quota selezionata, con visibilita' di " << vis_vmc << "m, con distanza dalle nubi verticalmente di " << cld_distance_v << "ft ed orizzontalmente di " << cld_distance_orz << "m, ci sono le condizioni VMC" <<endl;
    	else cout << "In spazio aereo " << airspace_cat << ", nella quota selezionata, con visibilita' di " << vis_vmc << "m, con distanza dalle nubi verticalmente di " << cld_distance_v << "ft ed orizzontalmente di " << cld_distance_orz << "m, non ci sono le condizioni VMC" <<endl;
    	system("pause");
    	break;
    /*if (airspace_cat=='F' || airspace_cat=='f' )||(airspace_cat=='G' || airspace_cat=='g')*/
    	default: cout << "errore"<<endl;
    	break;
    }//chiusura switch case 20
    break; //break case 20 main
    default: cout << "Numero inserito non valido" <<endl;
}
cout << "" <<endl;
system("cls");
goto menu;
fine:
cout << "Numero inserito non valido" <<endl;
system("pause");
system("cls");
goto menu;
fine2:
cout << "Programma terminato" <<endl;
return 0;
}
