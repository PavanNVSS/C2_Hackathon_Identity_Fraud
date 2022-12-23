//Directories
#include<iostream>
#include<istream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
// Using CV directories for facial detection.
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>

//namespace
using namespace std;
using namespace cv;
//functions
void login();
void reg();
void forgot();
int detect();
//global variable
Mat img;

//main function
void main()
{
    int choice;
    cout << "***********************************************************************\n\n\n";
    cout << "                          Welcome                                  \n\n";
    cout << "*******************        MENU        *******************************\n\n";
    cout << "1.Login" << endl;
    cout << "2.Register" << endl;
    cout << "3.Forgot credentials[Name or Password]" << endl;
    cout << "4.Exit" << endl;
    cout << "\nEnter your choice :";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        login();
        break;
    case 2:
        reg();
        break;
    case 3:
        forgot();
        break;
    case 4:
        cout << "Thank you for trying out this prototype. Hope you had a nice experience.\n\n";
        exit(0);
    default:
        system("cls");
        cout << "Please try again\n" << endl;
        main();
    }

}

//Mat diff;
//detect function which uses the CV libraries imported above.
int detect()
{
    VideoCapture cam(0);
    CascadeClassifier facedetect;
    facedetect.load("haarcascade_frontalface_default.xml");

    while (true)
    {
        vector<Rect> faces;

        facedetect.detectMultiScale(img, faces, 1.3, 5);

        cout << faces.size() << endl;

        cam.read(img);
        for (int i = 0; i < faces.size(); i++) {

            if (faces.size() == 1)
            {
                waitKey(1);
                system("cls");
                cout << "Face Registered successfully" << endl;
                destroyAllWindows();

                return 1;
            }
        }
        imshow("Image", img);

        waitKey(1);
    }
}
//Check function
int check()
{
    int result;
    cout << "Please verify your identity: ";
    result = detect();
    if (result == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//Login Function
void login()
{
    int count;
    string user, pass, username, password;
    system("cls");
    cout << "please enter the following details" << endl;
    cout << "USERNAME :";
    cin >> user;
    cout << "PASSWORD :";
    cin >> pass;
    cout << "Please Confirm your Identity :";
    detect();

    ifstream input("database.txt");
    while (input >> username >> password)
    {
        if (username == user && password == pass)

        {
            count = 1;
            system("cls");
        }
    }
    input.close();
    if (count == 1)
    {
        cout << "\nHello " << user << "\nLogin Sucess\nGlad to have you back.\n";
        cin.get();
        cin.get();
        main();
    }
    else
    {
        cout << "\nLogin Failed.\nPlease check Username,Password and try again. \n";
        main();
    }
}
//Register Function
void reg()
{

    string reg_user, reg_pass;
    system("cls");
    cout << "Enter  username :";
    cin >> reg_user;
    cout << "\nEnter  password :";
    cin >> reg_pass;
    cout << "Please Register your face in the database";
    detect();
    ofstream reg("database.txt");
    reg << reg_user << ' ' << reg_pass << endl;
    system("cls");
    cout << "\nRegistration Sucess.\n";
    main();


}
//Forgot Username (or) Forgot Password Function
void forgot()
{
    int ch;
    system("cls");
    cout << "If you have forgotten your Credentials , Please choose : \n";
    cout << "1.Search your id by username" << endl;
    cout << "2.Search your id by password" << endl;
    cout << "3.Main menu" << endl;
    cout << "Enter your choice :";
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        int count = 0;
        string searchuser, su, sp;
        cout << "\nEnter the username you remember :";
        cin >> searchuser;
        cout << "Please Confirm your Identity to prevent Identity fraud: ";
        detect();
        ifstream searchu("database.txt");
        while (searchu >> su >> sp)
        {
            if (su == searchuser)
            {
                count = 1;
            }
        }
        searchu.close();
        if (count == 1)
        {
            cout << "\n\Account found,fetching details..\n";
            cout << "\nYour password is: " << sp<<endl;
            cout << "Thank you for your patience."<<endl;
            cin.get();
            cin.get();
            system("cls");
            main();
        }
        else
        {
            cout << "\nAccount not found,fetching details from database failed.\n";
            cout << "\nKindly contact  system administrator for more information. \n";
            cin.get();
            cin.get();
            main();
        }
        break;
    }
    case 2:
    {
        int count = 0;
        string searchpass, su2, sp2;
        cout << "\nEnter the password you remember :";
        cin >> searchpass;
        cout << "Please Confirm your Identity to prevent Identity fraud: ";
        detect();
        ifstream searchp("database.txt");
        while (searchp >> su2 >> sp2)
        {
            if (sp2 == searchpass)
            {
                count = 1;
            }
        }
        searchp.close();
        if (count == 1)
        {
            cout << "\nPassword found,fetching details... \n";
            cout << "\nYour ID is : " << su2<<endl;
            cout << "Thank you for your patience."<<endl;
            cin.get();
            cin.get();
            system("cls");
            main();
        }
        else
        {
            cout << "Password not found,fetching details from database failed. \n";
            cout << "\nkindly contact system administrator for more information\n";
            cin.get();
            cin.get();
            main();
        }

        break;
    }

    case 3:
    {
        cin.get();
        main();
    }
    default:
        cout << "Error,Please try again." << endl;
        forgot();
    }
}