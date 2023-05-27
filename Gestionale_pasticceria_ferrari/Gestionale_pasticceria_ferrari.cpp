#include <iostream>
#include <fstream> 
#include <string> 
#include <vector> 
#include <stdlib.h> 
#include <cstdio>
#include <conio.h> 
#include <Windows.h> 

using namespace std;

string fileRicette = "ricette.dat", fileDispensa = "dispensa.dat", fileSpesa = "spesa.dat";

struct Ingrediente {
    string nome;
    int quantita{};
    string unita;
};

struct Ricetta
{
    string nome;
    int quantita = 1;
    vector <Ingrediente> ingredienti;
    vector <string> istruzioni;
};

vector <Ricetta> ricette;

string OutputRicette() {
    string a = "Scelta:", t;
    ifstream file(fileRicette);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, t, ';');
            a += "\n" + t;
            getline(file, t);
        }
    }
    return a;
};

int RicercaNome(string nome, string path) {
    int pos = -1, i = 0;
    string c;
    ifstream file(path);
    if (file.is_open()) {
        while (!file.eof()) {
            string b;
            getline(file, b, ';');
            if (b == nome)
                pos = i;
            getline(file, c);
            i++;
        }
        file.close();
    }
    return pos;
};

Ricetta Ricerca(string nome, string path)
{
    Ricetta a;                                      //dichiara una ricetta di nome a
    Ingrediente b;                                  //dichiara un ingrediente di nome b
    string s, n;
    ifstream file(path);                            //apertura del file delle ricette in lettura
    if (file.is_open()) {                           //controlla se il file è stato aperto
        while (!file.eof()) {                       //ciclo while che si ripete non siamo alla fine del file
            getline(file, n, ';');                  //legge il primo campo fino al ; e lo salva in n
            if (n == nome) {                        //controlla se n corrisponde al nome ricercato
                a.nome = n;                         //la ricetta prende il nome di n
                getline(file, s, ';');              //legge il secondo campo fino a ; e lo salva in s
                int num;
                num = stoi(s);                      //converte in un intero s, salvandolo in num
                for (int i = 0; i < num; i++) {     //per num istruzioni legge i campi (nome), (quantita) e (unita) 
                    getline(file, b.nome, ';');
                    getline(file, s, ';');
                    getline(file, b.unita, ';');
                    b.quantita = stoi(s);           //conversione in intero del valore di quantità
                    a.ingredienti.push_back(b);     //inserisce l'ingrediente nel vector ingredienti della ricetta a
                }
                getline(file, s, ';');              //legge il secondo campo fino a ; e lo salva in s
                num = stoi(s);                      //converte in un intero s, salvandolo in num
                for (int i = 0; i < num; i++) {
                    getline(file, s, ';');
                    a.istruzioni.push_back(s);      //inserisce l'istruzione del vettore istruzioni delal ricetta a
                }
                break;
            }
            else {
                string x;
                getline(file, x);               //se non è la riga corretta la legge e la ignora
            }
        }
        file.close();                           //chiusura del file (stream)
    }
    return a;
};

void Aggiunta(Ricetta ric, int numIngredienti, int numIstruzioni, string path) {
    string n;
    ifstream fileT(fileRicette);
    getline(fileT, n);
    fileT.close();
    ofstream file(path, ios::app);              //apertura del file in append
    if (file.is_open())
    {
        if (!n.empty())                         //se la stringa n non è vuota 
            file << '\n';                       //a capo nel file
        file << ric.nome << ';' << numIngredienti << ';';
        for (int i = 0; i < numIngredienti; i++)
        {
            file << ric.ingredienti[i].nome << ';' << ric.ingredienti[i].quantita << ';' << ric.ingredienti[i].unita << ';';
        }
        file << numIstruzioni << ';';
        for (int i = 0; i < numIstruzioni; i++)
        {
            file << ric.istruzioni[i] << ';';
        }
        file.close();
    }
};

void Modifica(Ricetta ric, int numIngredienti, int numIstruzioni, string path, int pos) {
    int i = 0;
    string s, pathTemp = "ricettetemp.dat";
    ofstream filetemp(pathTemp);
    ifstream file(path);
    if (file.is_open() && filetemp.is_open())
    {
        if (i == pos) {
            filetemp << ric.nome << ';' << numIngredienti << ';';
            for (int i = 0; i < numIngredienti; i++)
            {
                filetemp << ric.ingredienti[i].nome << ';' << ric.ingredienti[i].quantita << ';' << ric.ingredienti[i].unita << ';';
            }
            filetemp << numIstruzioni << ';';
            for (int i = 0; i < numIstruzioni; i++)
            {
                filetemp << ric.istruzioni[i] << ';';
            }
            getline(file, s);
        }
        else {
            getline(file, s);
            filetemp << s;
        }
        i++;
        while (!file.eof())
        {
            if (i == pos) {
                filetemp << endl << ric.nome << ';' << numIngredienti << ';';
                for (int i = 0; i < numIngredienti; i++)
                {
                    filetemp << ric.ingredienti[i].nome << ';' << ric.ingredienti[i].quantita << ';' << ric.ingredienti[i].unita << ';';
                }
                filetemp << numIstruzioni << ';';
                for (int i = 0; i < numIstruzioni; i++)
                {
                    filetemp << ric.istruzioni[i] << ';';
                }
                getline(file, s);
            }
            else {
                getline(file, s);
                filetemp << endl << s;
            }
            i++;
        }
        file.close();
        filetemp.close();
        const char* pathC = path.c_str();
        remove(pathC);
        int r = rename(pathTemp.c_str(), pathC);
    }
};

void Cancellazione(string path, int pos) {
    int i = 0;
    string s, pathTemp = "ricettetemp.dat";
    ofstream filetemp(pathTemp);
    ifstream file(path);
    if (file.is_open() && filetemp.is_open())
    {
        if (i == pos) {
            getline(file, s);
        }
        else {
            getline(file, s);
            if (!s.empty())
                filetemp << s;
        }
        i++;
        while (!file.eof())
        {
            if (i == pos) {
                getline(file, s);
            }
            else {
                getline(file, s);
                if (!s.empty())
                    filetemp << endl << s;
            }
            i++;
        }
        file.close();
        filetemp.close();
        const char* pathC = path.c_str();
        remove(pathC);
        int r = rename(pathTemp.c_str(), pathC);
    }
};

void Spesa(string nome, int quantita, string unit) {
    string n, q, u, pathTemp = "spesatemp.dat";
    int necessario, compra;
    bool inserito = false;
    ofstream filetemp(pathTemp);
    ifstream file(fileSpesa);
    if (file.is_open() && filetemp.is_open())
    {
        while (!file.eof())
        {
            getline(file, n, ';');
            getline(file, q, ';');
            getline(file, u, ';');
            if (n == nome) {
                compra = quantita + stoi(q);
                filetemp << n << ';' << compra << ';' << u << ';' << endl;
                inserito = true;
            }
            else if (n != "")
                filetemp << n << ';' << q << ';' << u << ';' << endl;
            getline(file, n);
        }
        if (!inserito)
            filetemp << nome << ';' << quantita << ';' << unit << ';';
        file.close();
        filetemp.close();
        const char* pathSC = fileSpesa.c_str();
        remove(pathSC);
        int r = 1;
        do {
            r = rename(pathTemp.c_str(), pathSC);
        } while (r != 0);
    }
};

void ConfDispensa(string nome, int quantita, string unit, int num) {
    string n, q, u, pathTemp = "dispensatemp.dat";
    int necessario = 0, dispensa = 0, compra = 0;
    bool inserito = false;
    ofstream filetemp(pathTemp);
    ifstream file(fileDispensa);
    getline(file, n);
    file.close();
    ifstream fileDis(fileDispensa);
    necessario = quantita * num;
    if (fileDis.is_open() && filetemp.is_open())
    {
        if (n[0] != ' ') {
            while (!fileDis.eof())
            {
                getline(fileDis, n, ';');
                getline(fileDis, q, ';');
                getline(fileDis, u, ';');
                if (n == nome) {
                    if (stoi(q) >= necessario) {
                        dispensa = stoi(q) - necessario;
                    }
                    else {
                        while (compra < necessario) {
                            if (unit == "g")
                                compra += 5000;
                            else if (unit == "ml")
                                compra += 2000;
                            else if (unit == "pz")
                                compra += 24;
                        }
                        dispensa = compra + stoi(q) - necessario;
                        Spesa(nome, compra, unit);
                    }
                    filetemp << nome << ';' << dispensa << ';' << u << ';' << endl;
                    inserito = !inserito;
                }
                else if (n != "")
                    filetemp << n << ';' << q << ';' << u << ';' << endl;
                getline(fileDis, n);
            }
        }
        if (!inserito) {
            while (compra < necessario) {
                if (unit == "g")
                    compra += 5000;
                else if (unit == "ml")
                    compra += 2000;
                else if (unit == "pz")
                    compra += 24;
            }
            dispensa = compra - necessario;
            Spesa(nome, compra, unit);
            filetemp << nome << ';' << dispensa << ';' << unit << ';';
        }
        fileDis.close();
        filetemp.close();
        const char* pathDC = fileDispensa.c_str();
        remove(pathDC);
        int r = rename(pathTemp.c_str(), pathDC);
    }
};

bool ControlloConversioneStringToInt(string daControllare) {
    bool valida = true;
    for (int i = 0; i < daControllare.length(); i++) {
        if (daControllare[i] < 48 || daControllare[i] > 57)
            valida = false;
    }
    return valida;
};

void Visualizza(string path) {
    string s;
    ifstream file(path);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, s, ';');
            cout << s << " ";
            getline(file, s, ';');
            cout << s << " ";
            getline(file, s, ';');
            cout << s << endl;
            getline(file, s);
        }
        file.close();
    }
}

void DispensaHTML(string path) {
    ofstream fileHTML("Dispensa.html");
    fileHTML << "<!DOCTYPE html> <html style = \"font-size: 16px;\" lang=\"it\" class=\"u-responsive-xl\"><link type=\"text/css\" rel=\"stylesheet\" id=\"dark-mode-custom-link\"><link type=\"text/css\" rel=\"stylesheet\" id=\"dark-mode-general-link\"><style lang=\"en\" type=\"text/css\" id=\"dark-mode-custom-style\"></style><style lang=\"en\" type=\"text/css\" id=\"dark-mode-native-style\"></style><style lang=\"en\" type=\"text/css\" id=\"dark-mode-native-sheet\"></style><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <meta name=\"keywords\" content=\"\"> <meta name=\"description\" content=\"\"> <title>Dispensa</title> <link rel=\"stylesheet\" href=\"./Dispensa_files/nicepage.css\" media=\"screen\"> <link rel=\"stylesheet\" href=\"./Dispensa_files/nicepage-site.css\" media=\"screen\"> <link rel=\"stylesheet\" href=\"./Dispensa_files/Dispensa.css\" media=\"screen\"> <script class=\"u-script\" type=\"text/javascript\" src=\"./Dispensa_files/jquery-3.5.1.min.js.download\" defer=\"\"></script> <script class=\"u-script\" type=\"text/javascript\" src=\"./Dispensa_files/nicepage.js.download\" defer=\"\"></script> <meta name=\"generator\" content=\"Nicepage 5.10.1, nicepage.com\"> <link rel=\"icon\" href=\"https://ciccio-pasticcio.nicepage.io/favicon.png\"> <link id=\"u-theme-google-font\" rel=\"stylesheet\" href=\"./Dispensa_files/css\"> <link id=\"u-page-google-font\" rel=\"stylesheet\" href=\"./Dispensa_files/css(1)\"> <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin> <link href=\"https://fonts.googleapis.com/css2?family=Oswald:wght@200;300;400;500;600;700&display=swap\" rel=\"stylesheet\"> <link href=\"https://fonts.googleapis.com/css2?family=Lobster&display=swap\" rel=\"stylesheet\"> <link href=\"https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100;0,300;0,400;0,500;0,700;0,900;1,100;1,300;1,400;1,500;1,700;1,900&display=swap\" rel=\"stylesheet\"> <link href=\"https://fonts.googleapis.com/css2?family=Open+Sans:ital,wght@0,300;0,400;0,500;0,600;0,700;0,800;1,300;1,400;1,500;1,600;1,700;1,800&display=swap\" rel=\"stylesheet\"> <script type=\"application/ld+json\">{ \"@context\": \"http://schema.org\", \"@type\": \"Organization\", \"name\": \"WebSite4752412\", \"logo\": \"https://assets.nicepagecdn.com/bebc01ee/4752412/images/logo_pasticceria.png\", \"sameAs\": [ \"https://facebook.com/cicciopasticcios\", \"https://twitter.com/cicciopasticcios\", \"https://instagram.com/cicciopasticcios\" ] }</script> <meta name=\"theme-color\" content=\"#478ac9\"> <meta name=\"twitter:site\" content=\"@\"> <meta name=\"twitter:card\" content=\"summary_large_image\"> <meta name=\"twitter:title\" content=\"Dispensa\"> <meta name=\"twitter:description\" content=\"WebSite4752412\"> <meta property=\"og:title\" content=\"Dispensa\"> <meta property=\"og:description\" content=\"\"> <meta property=\"og:type\" content=\"website\"> </head> <body class=\"u-body u-xl-mode\" data-lang=\"it\"><header class=\" u-border-no-bottom u-border-no-left u-border-no-right u-border-no-top u-clearfix u-header u-section-row-container\" id=\"sec-abb2\" style=\"\" data-animation-name=\"\" data-animation-duration=\"0\" data-animation-delay=\"0\" data-animation-direction=\"\"><div class=\"u-section-rows\"> <div class=\"u-clearfix u-custom-color-5 u-section-row\" data-animation-name=\"\" data-animation-duration=\"0\" data-animation-delay=\"0\" data-animation-direction=\"\" id=\"sec-397d\"> <div class=\"u-clearfix u-sheet u-sheet-1\"> <a href=\"\" class=\"logo u-align-center u-hidden-sm u-hidden-xs u-image u-logo u-image-1\" data-image-width=\"607\" data-image-height=\"768\" title=\"Pagina 1\"> <img src=\"./Dispensa_files/logo_pasticceria.png\" class=\"u-logo-image u-logo-image-1\"> </a> <h1 class=\"titolo u-align-center u-text u-text-custom-color-3 u-text-1\">Ciccio Pasticcio's</h1> </div> </div> <div class=\"u-custom-color-3 u-section-row u-sticky\" id=\"sec-06ce\" style=\"\"> <div class=\"u-clearfix u-sheet u-valign-middle u-sheet-2\"> <nav class=\"navbar u-menu u-menu-one-level u-offcanvas u-menu-1\"> <div class=\"menu-collapse\" style=\"font-size: 1rem; letter-spacing: 0px; text-transform: uppercase; font-weight: 600;\"> <a class=\"u-button-style u-custom-active-border-color u-custom-active-color u-custom-border u-custom-border-color u-custom-border-radius u-custom-borders u-custom-color u-custom-hover-border-color u-custom-hover-color u-custom-left-right-menu-spacing u-custom-padding-bottom u-custom-text-active-color u-custom-text-color u-custom-text-decoration u-custom-text-hover-color u-custom-top-bottom-menu-spacing u-nav-link u-text-custom-color-4\" href=\"https://ciccio-pasticcio.nicepage.io/Dispensa.html#\" style=\"padding: 6px 14px; font-size: calc(1em + 12px);\"> <svg class=\"u-svg-link\" viewBox=\"0 0 24 24\"><use xlink:href=\"#svg-c2be\"></use></svg> <svg class=\"u-svg-content\" version=\"1.1\" id=\"svg-c2be\" viewBox=\"0 0 16 16\" x=\"0px\" y=\"0px\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns=\"http://www.w3.org/2000/svg\"><g><rect y=\"1\" width=\"16\" height=\"2\"></rect><rect y=\"7\" width=\"16\" height=\"2\"></rect><rect y=\"13\" width=\"16\" height=\"2\"></rect> </g></svg> </a> </div> <div class=\"u-custom-menu u-nav-container\"> <ul class=\"u-nav u-spacing-30 u-unstyled u-nav-1\"> <li class=\"u-nav-item\"><a class=\"u-border-2 u-border-custom-color-5 u-button-style u-hover-custom-color-5 u-nav-link u-radius-33 u-text-active-palette-1-base u-text-grey-90 u-text-hover-black\" href=\"HomePage.html\" target=\"_self\" style=\"padding: 10px 96px;\">Home</a> </li><li class=\"u-nav-item\"><a class=\"u-border-2 u-border-custom-color-5 u-button-style u-hover-custom-color-5 u-nav-link u-radius-33 u-text-active-palette-1-base u-text-grey-90 u-text-hover-black\" href=\"Ricettario.html\" target=\"_self\" style=\"padding: 10px 96px;\">Ricettario</a> </li><li class=\"u-nav-item\"><a class=\"u-border-2 u-border-custom-color-5 u-button-style u-hover-custom-color-5 u-nav-link u-radius-33 u-text-active-palette-1-base u-text-grey-90 u-text-hover-black\" href=\"Spesa.html\" target=\"_self\" style=\"padding: 10px 96px;\">Spesa</a> </li></ul> </div> <div class=\"u-custom-menu u-nav-container-collapse\"> <div class=\"u-black u-container-style u-inner-container-layout u-opacity u-opacity-95 u-sidenav\"> <div class=\"u-inner-container-layout u-sidenav-overflow\"> <div class=\"u-menu-close\"></div> <ul class=\"u-align-center u-nav u-popupmenu-items u-unstyled u-nav-2\"> <li class=\"u-nav-item\"><a class=\"u-button-style u-nav-link\" href=\"HomePage.html\" target=\"_self\">Home</a> </li><li class=\"u-nav-item\"><a class=\"u-button-style u-nav-link\" href=\"Ricettario.html\" target=\"_self\">Ricettario</a> </li><li class=\"u-nav-item\"><a class=\"u-button-style u-nav-link\" href=\"Spesa.html\" target=\"_self\">Spesa</a> </li></ul> </div> </div> <div class=\"u-black u-menu-overlay u-opacity u-opacity-70\"></div> </div> <style class=\"offcanvas-style\"> .u-offcanvas .u-sidenav { flex-basis: 250px !important; } .u-offcanvas:not(.u-menu-open-right) .u-sidenav { margin-left: -250px; } .u-offcanvas.u-menu-open-right .u-sidenav { margin-right: -250px; } @keyframes menu-shift-left { from { left: 0; } to { left: 250px; } } @keyframes menu-unshift-left { from { left: 250px; } to { left: 0; } } @keyframes menu-shift-right { from { right: 0; } to { right: 250px; } } @keyframes menu-unshift-right { from { right: 250px; } to { right: 0; } } </style></nav> </div> <style class=\"u-sticky-style\" data-style-id=\"c477\">.u-sticky-fixed.u-sticky-c477:before, .u-body.u-sticky-fixed .u-sticky-c477:before { borders: top right bottom left !important; border-color: #ffc857 !important; border-width: 2px !important }</style> </div> </div></header> <section class=\"u-align-center u-clearfix u-image u-shading u-section-1\" src=\"\" data-image-width=\"2008\" data-image-height=\"1004\" id=\"sec-f1c9\"> <div class=\"u-clearfix u-sheet u-sheet-1\"> <h1 class=\"u-custom-font u-font-oswald u-text u-text-default u-title u-text-1\">Dispensa</h1> </div> </section> <section class=\"u-clearfix u-custom-color-5 u-section-2\" id=\"sec-7e06\"> <div class=\"u-clearfix u-sheet u-valign-middle u-sheet-1\"> <div class=\"u-expanded-width-sm u-expanded-width-xs u-list u-list-1\"> <div class=\"u-repeater u-repeater-1\"> <div class=\"u-container-style u-custom-color-1 u-list-item u-radius-31 u-repeater-item u-shape-round\"> <div class=\"u-container-layout u-similar-container u-valign-bottom-sm u-valign-bottom-xs u-valign-top-lg u-valign-top-md u-valign-top-xl u-container-layout-1\"> <h4 class=\"u-text u-text-1\">Ingredienti</h4> <ul class=\"u-text u-text-2\">";
    string n, q, u;
    ifstream file(path);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, n, ';');
            getline(file, q, ';');
            getline(file, u, ';');
            fileHTML << "<li>" + n + " " + q + " " + u + "<br></li>";
            getline(file, n);
        }
        file.close();
        fileHTML << "</ul> </div> </div> </div> </div> </div> </section> <footer class=\"u-align-center u-clearfix u-footer u-grey-90 u-footer\" id=\"sec-4834\"><div class=\"u-clearfix u-sheet u-valign-middle-lg u-valign-middle-md u-valign-middle-sm u-valign-middle-xs u-sheet-1\"> <p class=\"infos u-small-text u-text u-text-variant u-text-1\">Sito a cura di: Caslini Alessandro, Dridi Ayoub, Ferrari Michele.<br>Tutti i diritti sono riservati alla società Ciccio Pasticcio's S.R.L.<br>Per ulteriori informazioni o eventuali richieste commerciali contattare il proprietario al seguente numero: </p> <div class=\"loghiSocial u-social-icons u-spacing-10 u-social-icons-1\"> <a class=\"u-social-url\" title=\"facebook\" target=\"_blank\" href=\"https://facebook.com/cicciopasticcios\"><span class=\"u-icon u-social-facebook u-social-icon u-text-custom-color-2 u-icon-1\"><svg class=\"u-svg-link\" preserveAspectRatio=\"xMidYMin slice\" viewBox=\"0 0 112 112\" style=\"\"><use xlink:href=\"#svg-b831\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 112 112\" x=\"0\" y=\"0\" id=\"svg-b831\"><path fill=\"currentColor\" d=\"M75.5,28.8H65.4c-1.5,0-4,0.9-4,4.3v9.4h13.9l-1.5,15.8H61.4v45.1H42.8V58.3h-8.8V42.4h8.8V32.2 c0-7.4,3.4-18.8,18.8-18.8h13.8v15.4H75.5z\"></path></svg></span> </a> <a class=\"u-social-url\" title=\"twitter\" target=\"_blank\" href=\"https://twitter.com/cicciopasticcios\"><span class=\"u-icon u-social-icon u-social-twitter u-text-custom-color-2 u-icon-2\"><svg class=\"u-svg-link\" preserveAspectRatio=\"xMidYMin slice\" viewBox=\"0 0 112 112\" style=\"\"><use xlink:href=\"#svg-1cc2\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 112 112\" x=\"0\" y=\"0\" id=\"svg-1cc2\"><path fill=\"currentColor\" d=\"M92.2,38.2c0,0.8,0,1.6,0,2.3c0,24.3-18.6,52.4-52.6,52.4c-10.6,0.1-20.2-2.9-28.5-8.2 c1.4,0.2,2.9,0.2,4.4,0.2c8.7,0,16.7-2.9,23-7.9c-8.1-0.2-14.9-5.5-17.3-12.8c1.1,0.2,2.4,0.2,3.4,0.2c1.6,0,3.3-0.2,4.8-0.7 c-8.4-1.6-14.9-9.2-14.9-18c0-0.2,0-0.2,0-0.2c2.5,1.4,5.4,2.2,8.4,2.3c-5-3.3-8.3-8.9-8.3-15.4c0-3.4,1-6.5,2.5-9.2 c9.1,11.1,22.7,18.5,38,19.2c-0.2-1.4-0.4-2.8-0.4-4.3c0.1-10,8.3-18.2,18.5-18.2c5.4,0,10.1,2.2,13.5,5.7c4.3-0.8,8.1-2.3,11.7-4.5 c-1.4,4.3-4.3,7.9-8.1,10.1c3.7-0.4,7.3-1.4,10.6-2.9C98.9,32.3,95.7,35.5,92.2,38.2z\"></path></svg></span> </a> <a class=\"u-social-url\" title=\"instagram\" target=\"_blank\" href=\"https://instagram.com/cicciopasticcios\"><span class=\"u-icon u-social-icon u-social-instagram u-text-custom-color-2 u-icon-3\"><svg class=\"u-svg-link\" preserveAspectRatio=\"xMidYMin slice\" viewBox=\"0 0 112 112\" style=\"\"><use xlink:href=\"#svg-7e18\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 112 112\" x=\"0\" y=\"0\" id=\"svg-7e18\"><path fill=\"currentColor\" d=\"M55.9,32.9c-12.8,0-23.2,10.4-23.2,23.2s10.4,23.2,23.2,23.2s23.2-10.4,23.2-23.2S68.7,32.9,55.9,32.9z M55.9,69.4c-7.4,0-13.3-6-13.3-13.3c-0.1-7.4,6-13.3,13.3-13.3s13.3,6,13.3,13.3C69.3,63.5,63.3,69.4,55.9,69.4z\"></path><path fill=\"#FFFFFF\" d=\"M79.7,26.8c-3,0-5.4,2.5-5.4,5.4s2.5,5.4,5.4,5.4c3,0,5.4-2.5,5.4-5.4S82.7,26.8,79.7,26.8z\"></path><path fill=\"currentColor\" d=\"M78.2,11H33.5C21,11,10.8,21.3,10.8,33.7v44.7c0,12.6,10.2,22.8,22.7,22.8h44.7c12.6,0,22.7-10.2,22.7-22.7 V33.7C100.8,21.1,90.6,11,78.2,11z M91,78.4c0,7.1-5.8,12.8-12.8,12.8H33.5c-7.1,0-12.8-5.8-12.8-12.8V33.7 c0-7.1,5.8-12.8,12.8-12.8h44.7c7.1,0,12.8,5.8,12.8,12.8V78.4z\"></path></svg></span> </a> </div> <a class=\"numeroDiTelefono u-active-none u-bottom-left-radius-0 u-bottom-right-radius-0 u-btn u-btn-rectangle u-button-style u-hover-none u-none u-radius-0 u-text-custom-color-2 u-top-left-radius-0 u-top-right-radius-0 u-btn-1\"><span class=\"u-icon\"><svg class=\"u-svg-content\" viewBox=\"0 0 405.333 405.333\" x=\"0px\" y=\"0px\" style=\"width: 1em; height: 1em;\"><path d=\"M373.333,266.88c-25.003,0-49.493-3.904-72.704-11.563c-11.328-3.904-24.192-0.896-31.637,6.699l-46.016,34.752 c-52.8-28.181-86.592-61.952-114.389-114.368l33.813-44.928c8.512-8.512,11.563-20.971,7.915-32.64 C142.592,81.472,138.667,56.96,138.667,32c0-17.643-14.357-32-32-32H32C14.357,0,0,14.357,0,32 c0,205.845,167.488,373.333,373.333,373.333c17.643,0,32-14.357,32-32V298.88C405.333,281.237,390.976,266.88,373.333,266.88z\"></path></svg></span>&nbsp;​ 06 164 164 </a> </div></footer> <style>.u-disable-duration * {transition-duration: 0s !important;}</style></body></html>";
    }
    fileHTML.close();
}

void SpesaHTML(string path) {
    ofstream fileHTML("Spesa.html");
    fileHTML << "<!DOCTYPE html> <html style = \"font-size: 16px;\" lang=\"it\" class=\"u-responsive-xl\"><link type=\"text/css\" rel=\"stylesheet\" id=\"dark-mode-custom-link\"><link type=\"text/css\" rel=\"stylesheet\" id=\"dark-mode-general-link\"><style lang=\"en\" type=\"text/css\" id=\"dark-mode-custom-style\"></style><style lang=\"en\" type=\"text/css\" id=\"dark-mode-native-style\"></style><style lang=\"en\" type=\"text/css\" id=\"dark-mode-native-sheet\"></style><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <meta name=\"keywords\" content=\"\"> <meta name=\"description\" content=\"\"> <title>Spesa</title> <link rel=\"stylesheet\" href=\"./Spesa_files/nicepage.css\" media=\"screen\"> <link rel=\"stylesheet\" href=\"./Spesa_files/nicepage-site.css\" media=\"screen\"> <link rel=\"stylesheet\" href=\"./Spesa_files/Spesa.css\" media=\"screen\"> <script class=\"u-script\" type=\"text/javascript\" src=\"./Spesa_files/jquery-3.5.1.min.js.download\" defer=\"\"></script> <script class=\"u-script\" type=\"text/javascript\" src=\"./Spesa_files/nicepage.js.download\" defer=\"\"></script> <meta name=\"generator\" content=\"Nicepage 5.10.1, nicepage.com\"> <link rel=\"icon\" href=\"https://ciccio-pasticcio.nicepage.io/favicon.png\"> <link id=\"u-theme-google-font\" rel=\"stylesheet\" href=\"./Spesa_files/css\"> <link id=\"u-page-google-font\" rel=\"stylesheet\" href=\"./Spesa_files/css(1)\"> <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin> <link href=\"https://fonts.googleapis.com/css2?family=Oswald:wght@200;300;400;500;600;700&display=swap\" rel=\"stylesheet\"> <link href=\"https://fonts.googleapis.com/css2?family=Lobster&display=swap\" rel=\"stylesheet\"> <link href=\"https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100;0,300;0,400;0,500;0,700;0,900;1,100;1,300;1,400;1,500;1,700;1,900&display=swap\" rel=\"stylesheet\"> <link href=\"https://fonts.googleapis.com/css2?family=Open+Sans:ital,wght@0,300;0,400;0,500;0,600;0,700;0,800;1,300;1,400;1,500;1,600;1,700;1,800&display=swap\" rel=\"stylesheet\"> <script type=\"application/ld+json\">{ \"@context\": \"http://schema.org\", \"@type\": \"Organization\", \"name\": \"WebSite4752412\", \"logo\": \"https://assets.nicepagecdn.com/bebc01ee/4752412/images/logo_pasticceria.png\", \"sameAs\": [ \"https://facebook.com/cicciopasticcios\", \"https://twitter.com/cicciopasticcios\", \"https://instagram.com/cicciopasticcios\" ] }</script> <meta name=\"theme-color\" content=\"#478ac9\"> <meta name=\"twitter:site\" content=\"@\"> <meta name=\"twitter:card\" content=\"summary_large_image\"> <meta name=\"twitter:title\" content=\"Spesa\"> <meta name=\"twitter:description\" content=\"WebSite4752412\"> <meta property=\"og:title\" content=\"Spesa\"> <meta property=\"og:description\" content=\"\"> <meta property=\"og:type\" content=\"website\"> </head> <body class=\"u-body u-xl-mode\" data-lang=\"it\"><header class=\" u-border-no-bottom u-border-no-left u-border-no-right u-border-no-top u-clearfix u-header u-section-row-container\" id=\"sec-abb2\" style=\"\" data-animation-name=\"\" data-animation-duration=\"0\" data-animation-delay=\"0\" data-animation-direction=\"\"><div class=\"u-section-rows\"> <div class=\"u-clearfix u-custom-color-5 u-section-row\" data-animation-name=\"\" data-animation-duration=\"0\" data-animation-delay=\"0\" data-animation-direction=\"\" id=\"sec-397d\"> <div class=\"u-clearfix u-sheet u-sheet-1\"> <a href=\"\" class=\"logo u-align-center u-hidden-sm u-hidden-xs u-image u-logo u-image-1\" data-image-width=\"607\" data-image-height=\"768\" title=\"Pagina 1\"> <img src=\"./Spesa_files/logo_pasticceria.png\" class=\"u-logo-image u-logo-image-1\"> </a> <h1 class=\"titolo u-align-center u-text u-text-custom-color-3 u-text-1\">Ciccio Pasticcio's</h1> </div> </div> <div class=\"u-custom-color-3 u-section-row u-sticky\" id=\"sec-06ce\"> <div class=\"u-clearfix u-sheet u-valign-middle u-sheet-2\"> <nav class=\"navbar u-menu u-menu-one-level u-offcanvas u-menu-1\"> <div class=\"menu-collapse\" style=\"font-size: 1rem; letter-spacing: 0px; text-transform: uppercase; font-weight: 600;\"> <a class=\"u-button-style u-custom-active-border-color u-custom-active-color u-custom-border u-custom-border-color u-custom-border-radius u-custom-borders u-custom-color u-custom-hover-border-color u-custom-hover-color u-custom-left-right-menu-spacing u-custom-padding-bottom u-custom-text-active-color u-custom-text-color u-custom-text-decoration u-custom-text-hover-color u-custom-top-bottom-menu-spacing u-nav-link u-text-custom-color-4\" href=\"https://ciccio-pasticcio.nicepage.io/Spesa.html#\" style=\"padding: 6px 14px; font-size: calc(1em + 12px);\"> <svg class=\"u-svg-link\" viewBox=\"0 0 24 24\"><use xlink:href=\"#svg-c2be\"></use></svg> <svg class=\"u-svg-content\" version=\"1.1\" id=\"svg-c2be\" viewBox=\"0 0 16 16\" x=\"0px\" y=\"0px\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns=\"http://www.w3.org/2000/svg\"><g><rect y=\"1\" width=\"16\" height=\"2\"></rect><rect y=\"7\" width=\"16\" height=\"2\"></rect><rect y=\"13\" width=\"16\" height=\"2\"></rect> </g></svg> </a> </div> <div class=\"u-custom-menu u-nav-container\"> <ul class=\"u-nav u-spacing-30 u-unstyled u-nav-1\"><li class=\"u-nav-item\"><a class=\"u-border-2 u-border-custom-color-5 u-button-style u-hover-custom-color-5 u-nav-link u-radius-33 u-text-active-palette-1-base u-text-grey-90 u-text-hover-black\" href=\"HomePage.html\" target=\"_self\" style=\"padding: 10px 96px;\">Home</a> </li><li class=\"u-nav-item\"><a class=\"u-border-2 u-border-custom-color-5 u-button-style u-hover-custom-color-5 u-nav-link u-radius-33 u-text-active-palette-1-base u-text-grey-90 u-text-hover-black\" href=\"Ricettario.html\" target=\"_self\" style=\"padding: 10px 96px;\">Ricettario</a> </li><li class=\"u-nav-item\"><a class=\"u-border-2 u-border-custom-color-5 u-button-style u-hover-custom-color-5 u-nav-link u-radius-33 u-text-active-palette-1-base u-text-grey-90 u-text-hover-black\" href=\"Dispensa.html\" target=\"_self\" style=\"padding: 10px 96px;\">Dispensa</a> </li></ul> </div> <div class=\"u-custom-menu u-nav-container-collapse\"> <div class=\"u-black u-container-style u-inner-container-layout u-opacity u-opacity-95 u-sidenav\"> <div class=\"u-inner-container-layout u-sidenav-overflow\"> <div class=\"u-menu-close\"></div> <ul class=\"u-align-center u-nav u-popupmenu-items u-unstyled u-nav-2\"> <li class=\"u-nav-item\"><a class=\"u-button-style u-nav-link\" href=\"HomePage.html\" target=\"_self\">Home</a> </li><li class=\"u-nav-item\"><a class=\"u-button-style u-nav-link\" href=\"Ricettario.html\" target=\"_self\">Ricettario</a> </li><li class=\"u-nav-item\"><a class=\"u-button-style u-nav-link\" href=\"Dispensa.html\" target=\"_self\">Dispensa</a> </li></ul> </div> </div> <div class=\"u-black u-menu-overlay u-opacity u-opacity-70\"></div> </div> <style class=\"offcanvas-style\"> .u-offcanvas .u-sidenav { flex-basis: 250px !important; } .u-offcanvas:not(.u-menu-open-right) .u-sidenav { margin-left: -250px; } .u-offcanvas.u-menu-open-right .u-sidenav { margin-right: -250px; } @keyframes menu-shift-left { from { left: 0; } to { left: 250px; } } @keyframes menu-unshift-left { from { left: 250px; } to { left: 0; } } @keyframes menu-shift-right { from { right: 0; } to { right: 250px; } } @keyframes menu-unshift-right { from { right: 250px; } to { right: 0; } } </style></nav> </div> <style class=\"u-sticky-style\" data-style-id=\"c477\">.u-sticky-fixed.u-sticky-c477:before, .u-body.u-sticky-fixed .u-sticky-c477:before { borders: top right bottom left !important; border-color: #ffc857 !important; border-width: 2px !important }</style> </div> </div></header> <section class=\"u-align-center u-clearfix u-image u-shading u-section-1\" src=\"\" data-image-width=\"2560\" data-image-height=\"1671\" id=\"sec-f1c9\"> <div class=\"u-clearfix u-sheet u-sheet-1\"> <h1 class=\"u-custom-font u-font-oswald u-text u-text-default u-title u-text-1\">Spesa</h1> </div> </section> <section class=\"u-clearfix u-custom-color-5 u-section-2\" id=\"sec-7e06\"> <div class=\"u-clearfix u-sheet u-valign-middle u-sheet-1\"> <div class=\"u-expanded-width-sm u-expanded-width-xs u-list u-list-1\"> <div class=\"u-repeater u-repeater-1\"> <div class=\"u-container-style u-custom-color-1 u-list-item u-radius-31 u-repeater-item u-shape-round\"> <div class=\"u-container-layout u-similar-container u-valign-bottom-sm u-valign-bottom-xs u-valign-top-lg u-valign-top-md u-valign-top-xl u-container-layout-1\"> <h4 class=\"u-text u-text-1\">Ingredienti</h4> <ul class=\"u-text u-text-2\">";
    string n, q, u;
    ifstream file(path);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, n, ';');
            getline(file, q, ';');
            getline(file, u, ';');
            fileHTML << "<li>" + n + " " + q + " " + u + "<br></li>";
            getline(file, n);
        }
        file.close();
        fileHTML << "</ul> </div> </div> </div> </div> </div> </section> <footer class=\"u-align-center u-clearfix u-footer u-grey-90 u-footer\" id=\"sec-4834\"><div class=\"u-clearfix u-sheet u-valign-middle-lg u-valign-middle-md u-valign-middle-sm u-valign-middle-xs u-sheet-1\"> <p class=\"infos u-small-text u-text u-text-variant u-text-1\">Sito a cura di: Caslini Alessandro, Dridi Ayoub, Ferrari Michele.<br>Tutti i diritti sono riservati alla società Ciccio Pasticcio's S.R.L.<br>Per ulteriori informazioni o eventuali richieste commerciali contattare il proprietario al seguente numero: </p> <div class=\"loghiSocial u-social-icons u-spacing-10 u-social-icons-1\"> <a class=\"u-social-url\" title=\"facebook\" target=\"_blank\" href=\"https://facebook.com/cicciopasticcios\"><span class=\"u-icon u-social-facebook u-social-icon u-text-custom-color-2 u-icon-1\"><svg class=\"u-svg-link\" preserveAspectRatio=\"xMidYMin slice\" viewBox=\"0 0 112 112\" style=\"\"><use xlink:href=\"#svg-b831\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 112 112\" x=\"0\" y=\"0\" id=\"svg-b831\"><path fill=\"currentColor\" d=\"M75.5,28.8H65.4c-1.5,0-4,0.9-4,4.3v9.4h13.9l-1.5,15.8H61.4v45.1H42.8V58.3h-8.8V42.4h8.8V32.2 c0-7.4,3.4-18.8,18.8-18.8h13.8v15.4H75.5z\"></path></svg></span> </a> <a class=\"u-social-url\" title=\"twitter\" target=\"_blank\" href=\"https://twitter.com/cicciopasticcios\"><span class=\"u-icon u-social-icon u-social-twitter u-text-custom-color-2 u-icon-2\"><svg class=\"u-svg-link\" preserveAspectRatio=\"xMidYMin slice\" viewBox=\"0 0 112 112\" style=\"\"><use xlink:href=\"#svg-1cc2\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 112 112\" x=\"0\" y=\"0\" id=\"svg-1cc2\"><path fill=\"currentColor\" d=\"M92.2,38.2c0,0.8,0,1.6,0,2.3c0,24.3-18.6,52.4-52.6,52.4c-10.6,0.1-20.2-2.9-28.5-8.2 c1.4,0.2,2.9,0.2,4.4,0.2c8.7,0,16.7-2.9,23-7.9c-8.1-0.2-14.9-5.5-17.3-12.8c1.1,0.2,2.4,0.2,3.4,0.2c1.6,0,3.3-0.2,4.8-0.7 c-8.4-1.6-14.9-9.2-14.9-18c0-0.2,0-0.2,0-0.2c2.5,1.4,5.4,2.2,8.4,2.3c-5-3.3-8.3-8.9-8.3-15.4c0-3.4,1-6.5,2.5-9.2 c9.1,11.1,22.7,18.5,38,19.2c-0.2-1.4-0.4-2.8-0.4-4.3c0.1-10,8.3-18.2,18.5-18.2c5.4,0,10.1,2.2,13.5,5.7c4.3-0.8,8.1-2.3,11.7-4.5 c-1.4,4.3-4.3,7.9-8.1,10.1c3.7-0.4,7.3-1.4,10.6-2.9C98.9,32.3,95.7,35.5,92.2,38.2z\"></path></svg></span> </a> <a class=\"u-social-url\" title=\"instagram\" target=\"_blank\" href=\"https://instagram.com/cicciopasticcios\"><span class=\"u-icon u-social-icon u-social-instagram u-text-custom-color-2 u-icon-3\"><svg class=\"u-svg-link\" preserveAspectRatio=\"xMidYMin slice\" viewBox=\"0 0 112 112\" style=\"\"><use xlink:href=\"#svg-7e18\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 112 112\" x=\"0\" y=\"0\" id=\"svg-7e18\"><path fill=\"currentColor\" d=\"M55.9,32.9c-12.8,0-23.2,10.4-23.2,23.2s10.4,23.2,23.2,23.2s23.2-10.4,23.2-23.2S68.7,32.9,55.9,32.9z M55.9,69.4c-7.4,0-13.3-6-13.3-13.3c-0.1-7.4,6-13.3,13.3-13.3s13.3,6,13.3,13.3C69.3,63.5,63.3,69.4,55.9,69.4z\"></path><path fill=\"#FFFFFF\" d=\"M79.7,26.8c-3,0-5.4,2.5-5.4,5.4s2.5,5.4,5.4,5.4c3,0,5.4-2.5,5.4-5.4S82.7,26.8,79.7,26.8z\"></path><path fill=\"currentColor\" d=\"M78.2,11H33.5C21,11,10.8,21.3,10.8,33.7v44.7c0,12.6,10.2,22.8,22.7,22.8h44.7c12.6,0,22.7-10.2,22.7-22.7 V33.7C100.8,21.1,90.6,11,78.2,11z M91,78.4c0,7.1-5.8,12.8-12.8,12.8H33.5c-7.1,0-12.8-5.8-12.8-12.8V33.7 c0-7.1,5.8-12.8,12.8-12.8h44.7c7.1,0,12.8,5.8,12.8,12.8V78.4z\"></path></svg></span> </a> </div> <a class=\"numeroDiTelefono u-active-none u-bottom-left-radius-0 u-bottom-right-radius-0 u-btn u-btn-rectangle u-button-style u-hover-none u-none u-radius-0 u-text-custom-color-2 u-top-left-radius-0 u-top-right-radius-0 u-btn-1\"><span class=\"u-icon\"><svg class=\"u-svg-content\" viewBox=\"0 0 405.333 405.333\" x=\"0px\" y=\"0px\" style=\"width: 1em; height: 1em;\"><path d=\"M373.333,266.88c-25.003,0-49.493-3.904-72.704-11.563c-11.328-3.904-24.192-0.896-31.637,6.699l-46.016,34.752 c-52.8-28.181-86.592-61.952-114.389-114.368l33.813-44.928c8.512-8.512,11.563-20.971,7.915-32.64 C142.592,81.472,138.667,56.96,138.667,32c0-17.643-14.357-32-32-32H32C14.357,0,0,14.357,0,32 c0,205.845,167.488,373.333,373.333,373.333c17.643,0,32-14.357,32-32V298.88C405.333,281.237,390.976,266.88,373.333,266.88z\"></path></svg></span>&nbsp;​ 06 164 164 </a> </div></footer> <style>.u-disable-duration * {transition-duration: 0s !important;}</style></body></html>";
    }
    fileHTML.close();
}

int main()
{
    bool ripeti = true;
    bool altro;
    string sceltastr, ricettestr, stringNumeroIngredientiIstruzioni;
    int delay = 1000;
    ofstream ofs;
    Ricetta ric;
    do {
        cout << "Scelta:\n1 - Ordina dalla cucina\n2 - Aggiungi ricetta\n3 - Modifica ricetta\n4 - Cancella ricetta\n5 - Svuota dispensa\n0 - Uscita" << endl << endl;
        getline(cin, sceltastr);
        cin.clear();
        if (!ControlloConversioneStringToInt(sceltastr)) {
            do {
                cout << endl << "Input non valido" << endl << endl;
                _getch();
                system("CLS");
                cout << "Scelta:\n1 - Ordina dalla cucina\n2 - Aggiungi ricetta\n3 - Modifica ricetta\n4 - Cancella ricetta\n5 - Svuota dispensa\n0 - Uscita" << endl << endl;
                getline(cin, sceltastr);
                cin.clear();
            } while (!ControlloConversioneStringToInt(sceltastr));
        }
        int sceltaint = stoi(sceltastr);
        int pos;
        switch (sceltaint) {
        case 1:
#pragma region case 1
            do {
                altro = true;
                system("CLS");
                ricettestr = OutputRicette();
                cout << ricettestr << endl << endl;
                getline(cin, sceltastr);
                cin.clear();
                pos = RicercaNome(sceltastr, fileRicette);
                if (pos != -1) {
                    bool lista = false;
                    for (int i = 0; i < ricette.size(); i++) {
                        if (ricette[i].nome == sceltastr) {
                            ricette[i].quantita++;
                            lista = true;
                            break;
                        }
                    }
                    if (!lista) {
                        Ricetta ric = Ricerca(sceltastr, fileRicette);
                        ricette.push_back(ric);
                    }
                    ric.ingredienti.clear();
                    cout << endl << "Desidera aggiungere altro?\n0 - NO\n1 - SI\n" << endl;
                    int sceltaint;
                    bool altroScelta = false;
                    do {
                        getline(cin, sceltastr);
                        cin.clear();
                        if (!ControlloConversioneStringToInt(sceltastr)) {
                            do {
                                cout << endl << "Input non valido" << endl << endl;
                                _getch();
                                system("CLS");
                                cout << ricettestr << endl << endl << ricette[ricette.size() - 1].nome << endl << endl << "Desidera aggiungere altro?\n0 - NO\n1 - SI\n" << endl;
                                getline(cin, sceltastr);
                                cin.clear();
                            } while (!ControlloConversioneStringToInt(sceltastr));
                        }
                        sceltaint = stoi(sceltastr);
                        switch (sceltaint) {
                        case 0:
                            altro = false;
                            altroScelta = true;
                            break;
                        case 1:
                            altroScelta = true;
                            break;
                        default:
                            cout << endl << "Input non valido" << endl << endl;
                            _getch();
                            altroScelta = false;
                            system("CLS");
                            cout << ricettestr << endl << endl << ricette[ricette.size() - 1].nome << endl << endl << "Desidera aggiungere altro?\n0 - NO\n1 - SI\n" << endl;
                            break;
                        }
                    } while (!altroScelta);
                }
                else
                {
                    cout << endl << "Ricetta inesistente\n";
                    _getch();
                }
            } while (altro);
            ofs.open("spesa.dat", ofstream::out | ofstream::trunc);
            ofs.close();
            for (int i = 0; i < ricette.size(); i++) {
                for (int j = 0; j < ricette[i].ingredienti.size(); j++)
                    ConfDispensa(ricette[i].ingredienti[j].nome, ricette[i].ingredienti[j].quantita, ricette[i].ingredienti[j].unita, ricette[i].quantita);
            }
            system("CLS");
            cout << "Spesa: " << endl;
            Visualizza(fileSpesa);
            SpesaHTML(fileSpesa);
            _getch();
            system("CLS");
            for (int i = 0; i < ricette.size(); i++) {
                system("CLS");
                cout << ricette[i].nome << endl;
                for (int j = 0; j < ricette[i].ingredienti.size(); j++) {
                    int q = ricette[i].ingredienti[j].quantita * ricette[i].quantita;
                    cout << ricette[i].ingredienti[j].nome << ": " << q << "" << ricette[i].ingredienti[j].unita << endl;
                }
                cout << endl << "Istruzioni: " << endl;
                for (int j = 0; j < ricette[i].istruzioni.size(); j++) {
                    cout << ricette[i].istruzioni[j] << endl;
                }
                _getch();
            }
            system("CLS");
            cout << "Dispensa: " << endl;
            Visualizza(fileDispensa);
            DispensaHTML(fileDispensa);
            _getch();
            ricette.clear();
            break;
#pragma endregion
#pragma region case 2
        case 2:
            system("CLS");
            cout << "Inserire nome ricetta:" << endl << endl;
            getline(cin, ric.nome);
            cin.clear();
            if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                do {
                    cout << endl << "Input non valido" << endl << endl;
                    _getch();
                    system("CLS");
                    cout << "Inserire numero di ingredienti" << endl << endl;
                    getline(cin, stringNumeroIngredientiIstruzioni);
                    cin.clear();
                } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
            }
            pos = RicercaNome(ric.nome, fileRicette);
            if (pos == -1) {
                system("CLS");
                int numeroIstruzioni, numeroIngredienti;
                cout << "Inserire numero di ingredienti" << endl << endl;
                getline(cin, stringNumeroIngredientiIstruzioni);
                cin.clear();
                if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                    do {
                        cout << endl << "Input non valido" << endl << endl;
                        _getch();
                        system("CLS");
                        cout << "Inserire numero di ingredienti" << endl << endl;
                        getline(cin, stringNumeroIngredientiIstruzioni);
                        cin.clear();
                    } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                }
                numeroIngredienti = stoi(stringNumeroIngredientiIstruzioni);
                ric.ingredienti.clear();
                for (int i = 0; i < numeroIngredienti; i++) {
                    system("CLS");
                    Ingrediente ing;
                    cout << "Inserire ingrediente " << i + 1 << ":" << endl << endl;
                    getline(cin, ing.nome);
                    cin.clear();
                    cout << endl << "Inserire quantita ingrediente " << i + 1 << ":" << endl << endl;
                    getline(cin, stringNumeroIngredientiIstruzioni);
                    cin.clear();
                    if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                        do {
                            cout << endl << "Input non valido" << endl << endl;
                            _getch();
                            system("CLS");
                            cout << "Inserire ingrediente " << i + 1 << ":" << endl << endl << ing.nome << endl << endl << "Inserire quantita ingrediente " << i + 1 << ":" << endl << endl;
                            getline(cin, stringNumeroIngredientiIstruzioni);
                            cin.clear();
                        } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                    }
                    ing.quantita = stoi(stringNumeroIngredientiIstruzioni);
                    int unit;
                    bool unitCheck = false;
                    do {
                        system("CLS");
                        cout << "Inserire ingrediente " << i + 1 << ":" << endl << endl << ing.nome << endl << endl << "Inserire quantita ingrediente " << i + 1 << ":" << endl << endl << ing.quantita << endl << endl << "Inserire unita di misura dell'ingrediente " << i + 1 << ":" << endl << "1 - g (grammi)\n2 - ml (millilitri)\n3 - pz (pezzi)" << endl << endl;
                        getline(cin, stringNumeroIngredientiIstruzioni);
                        cin.clear();
                        if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                            do {
                                cout << endl << "Input non valido" << endl << endl;
                                _getch();
                                system("CLS");
                                cout << "Inserire ingrediente " << i + 1 << ":" << endl << endl << ing.nome << endl << endl << "Inserire quantita ingrediente " << i + 1 << ":" << endl << endl << ing.quantita << endl << endl << "Inserire unita di misura dell'ingrediente " << i + 1 << ":" << endl << "1 - g (grammi)\n2 - ml (millilitri)\n3 - pz (pezzi)" << endl << endl;
                                getline(cin, stringNumeroIngredientiIstruzioni);
                                cin.clear();
                            } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                        }
                        unit = stoi(stringNumeroIngredientiIstruzioni);
                        switch (unit) {
                        case 1:
                            ing.unita = "g";
                            unitCheck = true;
                            break;
                        case 2:
                            ing.unita = "ml";
                            unitCheck = true;
                            break;
                        case 3:
                            ing.unita = "pz";
                            unitCheck = true;
                            break;
                        default:
                            cout << endl << "Unita di misura non valida" << endl << endl;
                            _getch();
                            break;
                        }
                    } while (!unitCheck);
                    ric.ingredienti.push_back(ing);
                }
                system("CLS");
                cout << "Inserire numero di istruzioni" << endl << endl;
                getline(cin, stringNumeroIngredientiIstruzioni);
                cin.clear();
                if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                    do {
                        cout << endl << "Input non valido" << endl << endl;
                        _getch();
                        system("CLS");
                        cout << "Inserire numero di istruzioni" << endl << endl;
                        getline(cin, stringNumeroIngredientiIstruzioni);
                        cin.clear();
                    } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                }
                numeroIstruzioni = stoi(stringNumeroIngredientiIstruzioni);
                ric.istruzioni.clear();
                for (int i = 0; i < numeroIstruzioni; i++) {
                    system("CLS");
                    string s;
                    cout << "Inserire istruzione " << i + 1 << ":" << endl << endl;
                    getline(cin, s);
                    cin.clear();
                    ric.istruzioni.push_back(s);
                }
                Aggiunta(ric, numeroIngredienti, numeroIstruzioni, fileRicette);
                _getch();
            }
            else {
                cout << endl << "Ricetta esistente\n";
                _getch();
            }
            break;
#pragma endregion
#pragma region case 3
        case 3:
            system("CLS");
            ricettestr = OutputRicette();
            cout << ricettestr << endl << endl;
            cout << "Inserire nome ricetta:" << endl << endl;
            getline(cin, sceltastr);
            cin.clear();
            pos = RicercaNome(sceltastr, fileRicette);
            if (pos != -1) {
                system("CLS");
                cout << "Inserire nome ricetta:" << endl << endl;
                getline(cin, ric.nome);
                cin.clear();
                system("CLS");
                int numeroIngredienti, numeroIstruzioni;
                cout << "Inserire numero di ingredienti" << endl << endl;
                getline(cin, stringNumeroIngredientiIstruzioni);
                cin.clear();
                if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                    do {
                        cout << endl << "Input non valido" << endl << endl;
                        _getch();
                        system("CLS");
                        cout << "Inserire numero di ingredienti" << endl << endl;
                        getline(cin, stringNumeroIngredientiIstruzioni);
                        cin.clear();
                    } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                }
                numeroIngredienti = stoi(stringNumeroIngredientiIstruzioni);
                ric.ingredienti.clear();
                for (int i = 0; i < numeroIngredienti; i++) {
                    system("CLS");
                    Ingrediente ing;
                    cout << "Inserire ingrediente " << i + 1 << ":" << endl << endl;
                    getline(cin, ing.nome);
                    cin.clear();
                    cout << endl << "Inserire quantita ingrediente " << i + 1 << ":" << endl << endl;
                    getline(cin, stringNumeroIngredientiIstruzioni);
                    cin.clear();
                    if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                        do {
                            cout << endl << "Input non valido" << endl << endl;
                            _getch();
                            system("CLS");
                            cout << "Inserire ingrediente " << i + 1 << ":" << endl << endl << ing.nome << endl << endl << "Inserire quantita ingrediente " << i + 1 << ":" << endl << endl;
                            getline(cin, stringNumeroIngredientiIstruzioni);
                            cin.clear();
                        } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                    }
                    ing.quantita = stoi(stringNumeroIngredientiIstruzioni);
                    int unit;
                    bool unitCheck = false;
                    do {
                        cout << endl << "Inserire unita di misura dell'ingrediente " << i + 1 << ":" << endl << "1 - g (grammi)\n2 - ml (millilitri)\n3 - pz (pezzi)" << endl << endl;
                        getline(cin, stringNumeroIngredientiIstruzioni);
                        cin.clear();
                        if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                            do {
                                cout << endl << "Input non valido" << endl << endl;
                                _getch();
                                system("CLS");
                                cout << "Inserire ingrediente " << i + 1 << ":" << endl << endl << ing.nome << endl << endl << "Inserire quantita ingrediente " << i + 1 << ":" << endl << endl << ing.quantita << endl << endl << "Inserire unita di misura dell'ingrediente " << i + 1 << ":" << endl << "1 - g (grammi)\n2 - ml (millilitri)\n3 - pz (pezzi)" << endl << endl;
                                getline(cin, stringNumeroIngredientiIstruzioni);
                                cin.clear();
                            } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                        }
                        unit = stoi(stringNumeroIngredientiIstruzioni);
                        switch (unit) {
                        case 1:
                            ing.unita = "g";
                            unitCheck = true;
                            break;
                        case 2:
                            ing.unita = "ml";
                            unitCheck = true;
                            break;
                        case 3:
                            ing.unita = "pz";
                            unitCheck = true;
                            break;
                        default:
                            cout << endl << "Unita di misura non valida" << endl << endl;
                            _getch();
                            break;
                        }
                        if (!unitCheck) cout << endl << "Unita di misura non valida" << endl << endl;
                    } while (!unitCheck);
                    ric.ingredienti.push_back(ing);
                }
                cout << "Inserire numero di istruzioni" << endl << endl;
                getline(cin, stringNumeroIngredientiIstruzioni);
                cin.clear();
                if (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni)) {
                    do {
                        cout << endl << "Input non valido" << endl << endl;
                        _getch();
                        system("CLS");
                        cout << "Inserire numero di istruzioni" << endl << endl;
                        getline(cin, stringNumeroIngredientiIstruzioni);
                        cin.clear();
                    } while (!ControlloConversioneStringToInt(stringNumeroIngredientiIstruzioni));
                }
                numeroIstruzioni = stoi(stringNumeroIngredientiIstruzioni);
                ric.istruzioni.clear();
                for (int i = 0; i < numeroIstruzioni; i++) {
                    system("CLS");
                    string s;
                    cout << "Inserire istruzione " << i + 1 << ":" << endl << endl;
                    getline(cin, s);
                    cin.clear();
                    ric.istruzioni.push_back(s);
                }
                Modifica(ric, numeroIngredienti, numeroIstruzioni, fileRicette, pos);
            }
            else
            {
                cout << "Ricetta inesistente\n";
                _getch();
            }
            break;
#pragma endregion
#pragma region case 4
        case 4:
            system("CLS");
            ricettestr = OutputRicette();
            cout << ricettestr << endl << endl;
            cout << "Inserire nome ricetta:" << endl << endl;
            getline(cin, sceltastr);
            cin.clear();
            pos = RicercaNome(sceltastr, fileRicette);
            if (pos != -1) {
                Cancellazione(fileRicette, pos);
            }
            else
            {
                cout << "Ricetta inesistente\n";
                _getch();
            }
            break;
#pragma endregion
#pragma region case 5
        case 5:
            ofs.open(fileDispensa, ofstream::out | ofstream::trunc);
            ofs.close();
            break;
#pragma endregion 
        case 0:
            ripeti = false;
            break;
        }
        system("CLS");
    } while (ripeti);
}