
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string userid;
string pwd;
string timing[20][20];
string moviename[100];
string seatnum[10];
string hallname;

class admin
{
public:
    int m = 0;
    void adminmenu();
    void addmovie();
    void exit();
    void seatmatrix();
    void booking();
    void movielist();
    void tktptr(string x, string y, int z, int w);
};

class customer : public admin
{
public:
    string fname, lname, mno;

    void signup();
    void newsignup();
    void ecustomer();
    void cmenu();
    void mpass();
};

class moviebooking : public customer
{
public:
    void type();
};

void admin::exit()
{
    cout << "\n\t THANK YOU FOR USING OUR APPLICATION!";
}

void moviebooking::type()
{
    int t;
    int passcount = 3;
    string adminpwd;
Type:
    cout << "\n\t ENTER YOUR TYPE:" << endl;
    cout << "\n\t\t 1. ADMINISTRATOR" << endl;
    cout << "\n\t\t 2. CUSTOMER" << endl;
    cout << "Select Your Choice: ";
    cin >> t;

    switch (t)
    {
    case 1:
        while (passcount > 0)
        {
            cout << "\n\t ENTER THE ADMINISTRATION PASSWORD: ";
            cin >> adminpwd;

            if (adminpwd == "ADMIN12")
            {
                adminmenu();
                passcount = 0;
            }

            else
            {
                cout << "\n\t WRONG PASSWORD!! ENTER A VALID PASSWORD" << endl;
                passcount--;
            }
        }
        break;

    case 2:
        signup();
        break;

    default:
        cout << "\t INVALID ENTRY!! ENTER AGAIN\n";
        goto Type;
        break;
    }
}

void admin::adminmenu()
{
    int ch;
    ifstream in;
    string st;
editmovies:
    cout << "\n\t\t 1. SHOW MOVIES SCHEDULE" << endl;
    cout << "\n\t\t 2. ADD NEW MOVIES" << endl;
    cout << "\n\t\t 3. NEW BOOKING" << endl;
    cout << "\n\t\t 4. EXIT" << endl;
    cout << endl
         << "Select Your Choice: ";
    cin >> ch;

    switch (ch)
    {
    case 1:
        in.open("movie_data.txt");

        while (in.eof() == 0)
        {
            cout << "\t";
            getline(in, st);
            cout << st << endl;
        }

        in.close();
        goto editmovies;
        break;

    case 2:
        addmovie();
        break;

    case 3:
        booking();
        break;

    case 4:
        exit();
        break;

    default:
        cout << "\t INVALID ENTRY!! ENTER AGAIN\n";
        goto editmovies;
        break;
    }
}

void admin::addmovie()
{
    int i;
    int ns;
    int j;
    int *p = (int *)(malloc(sizeof(int)));
    int str_time[100];

    cout << "\tENTER THE NUMBER OF MOVIES YOU WANT TO ADD: ";
    cin >> m;

    fstream mnum;
    mnum.open("movie_num.txt", ios::in);
    mnum << m;
    (*p) = m;
    ofstream out;
    out.open("movie_data.txt", ios::app);

    for (i = 0; i < m; i++)
    {
        fflush(stdin);
        cout << "\tENTER THE NAME OF MOVIE " << i + 1 << ": ";
        getline(cin, moviename[i]);
        fflush(stdin);
        out << moviename[i] << " ";
        cout << "\tENTER THE NUMBER OF SHOWS OF MOVIE " << moviename[i] << " IN A DAY: ";
        cin >> ns;
        str_time[i] = ns;
        fflush(stdin);

        cout << "\tENTER THE SHOW TIMINGS OF THE MOVIE: " << moviename[i] << endl;

        for (j = 0; j < ns; j++)
        {
            cout << "\t";
            fflush(stdin);
            getline(cin, timing[i][j]);
            out << timing[i][j] << " ";
        }

        out << endl;
    }

    out.close();
}

void admin::movielist()
{
    int i = 0;
    cout << "\n\tTHE MOVIES RUNNING IN HALL ARE:\n\n\n";
    ifstream fin;
    fin.open("movie_data.txt");

    while (i < 5)
    {
        cout << "\n\t";
        getline(fin, moviename[i], ' ');
        cout << "MOVIE :\t" << i + 1 << "\t" << moviename[i] << endl
             << endl;
        cout << "\t";
        cout << "THE TIMINGS OF THE MOVIE : " << moviename[i] << " :- " << endl;
        int j = 0;
        getline(fin, timing[i][j], '\n');
        cout << "\t";
        cout << timing[i][j] << endl
             << endl;
        i++;
    }
}

void admin::booking()
{
    int movienum;
    int i;
    int ticketnum;
    string movietime;

    movielist();
    cout << "\n\tENTER THE MOVIE NUMBER TO BOOK TICKET: ";
    cin >> movienum;

    fstream name;
    name.open("movie_data.txt");
    for (i = 0; i < movienum - 1; i++)
    {
        getline(name, moviename[i], '\n');
    }
    getline(name, moviename[i], ' ');
    name.close();
    cout << "\n\tCHOOSE THE NUMBER CORRENSPONDING TO TIMING TO BOOK TICKET FOR MOVIE :-" << endl;
    cout << "\t" << moviename[i];
    cout << "\t";
    cin >> movietime;
    cout << "ENTER THE NUMBER OF TICKETS YOU WANT TO BOOK(MAXIMUM 10): ";
    cin >> ticketnum;
    seatmatrix();
    cout << "\n\tENTER THE SEAT NUMBER\t";
    for (i = 0; i < ticketnum; i++)
    {
        cin >> seatnum[ticketnum];
        cout << "\t";
    }
    int price;
    price = ticketnum * 275 + 21 * (275 / 100);
    tktptr(moviename[i], movietime, ticketnum, price);
}

void admin::seatmatrix()
{
    int i, j;
    cout << "\n\n";

    for (i = 0; i < 9; i++)
    {
        char ch = 'A';
        ch = ch + i;
        cout << "\t\t";

        for (j = 0; j < 13; j++)
        {
            cout << "[" << ch << j + 1 << "]";
            cout << " ";

            if (j == 3 || j == 9)
            {
                cout << "\t\t";
            }
        }

        if (i == 3)
        {
            cout << "\n\n";
        }
        cout << endl
             << endl;
    }

    cout << endl
         << endl;
    cout << "\n\t________________ SCREEN THIS WAY\n";
    cout << "\t________________";
}

void admin::tktptr(string x, string y, int z, int w)
{
    string moviename = x;
    string time = y;
    int tkt_n = z;
    int price = w;

    cout << "\n\t_____________\n";
    cout << "\n";
    cout << "\t Dear Customer,          \n";
    cout << "\tDear Customer,          \n";
    cout << "\t                      \n";
    cout << "\t THE DETAILS          \n";
    cout << "\t MOVIE HALL: " << hallname << "             \n";
    cout << "\tMOVIE NAME: " << moviename << "             \n";
    cout << "\t SHOW STARTS: " << time << "             \n";
    cout << "\t NUMBER OF TICKETS BOOKED: " << tkt_n << "             \n";
    cout << "\t PRICE:" << price << "           \n";
    cout << "\n\t__________________________\n";
}

void customer::signup()
{
SU:
    int ctype;
    cout << "\n\t1. NEW SIGNUP" << endl;
    cout << "\n\t2. EXISTING CUSTOMER" << endl;
    cout << "\t";
    cin >> ctype;

    switch (ctype)
    {

    case 1:
        newsignup();
        break;

    case 2:
        ecustomer();
        break;

    default:
        cout << "\tINVALID ENTRY!! ENTER AGAIN\n";
        goto SU;
        break;
    }
}

void customer::newsignup()
{
    ofstream fout;
    fout.open("user_data.txt", ios::app);
    fflush(stdin);
    cout << "\tENTER FIRST NAME: " << endl;
    cout << "\t";
    getline(cin, fname);
    cout << "\tENTER YOUR LAST NAME :" << endl;
    cout << "\t";
    getline(cin, lname);
    cout << "\tENTER USER ID :" << endl;
    cout << "\t";
    getline(cin, userid);

    cout << "\t ENTER PASSWORD :" << endl;
    cout << "\t";
    getline(cin, pwd);
MN:
    cout << "\t ENTER YOUR MOBILE NUMBER :" << endl;
    cout << "\t";
    getline(cin, mno);
    try
    {

        if (mno.length() == 10)
        {
            cout << "\t CREDENTIALS SAVED SUCCESSFULLY!!" << endl;
            booking();
        }
        else
        {
            throw 1;
        }
    }

    catch (int)
    {
        cout << "\t INVALID ENTRY!! ENTER AGAIN\n";
        goto MN;
    }
    fout << fname << " " << lname << " " << userid << " " << pwd << " " << mno << endl;
}

void customer::ecustomer()
{
UID:
    string user;
    string pass;
    int passcount = 3;

    fflush(stdin);
    cout << "\t ENTER USER ID: ";
    cin >> user;

    ifstream eout;
    eout.open("user_data.txt");
    while (!eout.eof())
    {
        eout >> fname >> lname >> userid >> pwd >> mno;

        if (userid == user)
        {
            cout << "\t USER ID FOUND";
            cout << "\n\t ENTER PASSWORD: ";

            while (passcount > 0)
            {
                cin >> pass;

                if (pwd == pass)
                {
                    passcount = 0;
                }

                else
                {
                    cout << "\t WRONG PASSWORD!! ENTER AGAIN" << endl;
                    passcount--;
                }
            }

            break;
        }

        eout >> fname >> lname >> userid >> pwd >> mno;
    }

    if (passcount == 0)
    {
        cmenu();
    }
}

void customer::cmenu()
{
    int cus_ch;
    string st2;
    ifstream ein;
CM:
    cout << "\n\t 1. SHOW MOVIE SCHEDULE" << endl;
    cout << "\n\t 2. NEW BOOKING" << endl;
    cout << "\t";
    cin >> cus_ch;

    switch (cus_ch)
    {
    case 1:
        ein.open("movie_data.txt");

        while (ein.eof() == 0)
        {
            cout << "\t ";
            getline(ein, st2);
            cout << st2 << endl;
        }

        ein.close();
        goto CM;
        break;

    case 2:
        booking();
        break;

    default:
        cout << "\tENTER A VALID NUMBER\n";
        goto CM;
        break;
    }
}
int main()
{
HALL:
    int hall;
    moviebooking obj;
    cout << "\n\t\t 1. FOR INOX JAIPUR";
    cout << "\n\t\t 2. FOR CINEPOLIS DLF";
    cout << "\n\t\t 3. FOR PVR LUCKNOW";
    cout << "\n\t\t 4. FOR PVR KOLKATA";
    cout << "\n\t\t 8. FOR EXIT";

    cout << endl
         << "Enter Your Choice: ";
    cin >> hall;

    switch (hall)
    {

    case 1:
        cout << "\t";
        cout << "INOX SHIPRA IS SELECTED\n\n";
        hallname = "INOX JAIPUR";
        obj.type();
        break;

    case 2:
        cout << "\t";
        cout << "CINEPOLIS DLF IS SELECTED\n\n";
        hallname = "CINEPOLIS DLF";
        obj.type();
        break;

    case 3:
        cout << "\t";
        cout << "PVR LUCKNOW IS SELECTED\n";
        hallname = "PVR LUCKNOW";
        obj.type();
        break;

    case 4:
        cout << "\t";
        cout << "PVR KOLKATA IS SELECTED\n\n";
        hallname = "PVR KOLKATA";
        obj.type();
        break;

    case 8:
        goto end;
        break;

    default:
        cout << "\tENTER A VALID NUMBER\n";
        goto HALL;
        break;
    }

end:

    obj.exit();

    return 0;
}
