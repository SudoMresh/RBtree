// RBtree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "RBTree_BL.h"


using namespace std;


int main()
{
	RBtree* rbTree = new RBtree();

	/*rbTree->Insert(123);
	rbTree->Insert(21);
	rbTree->Insert(321);
	rbTree->Insert(789);
	rbTree->Insert(4561);

	rbTree->Insert(-79);
	rbTree->Insert(-751);
	rbTree->Insert(-123);
	rbTree->Insert(1);
	rbTree->Insert(23);

	rbTree->Show();

	cout << "Num: " << rbTree->GetNodesCount() << endl;
	cout << rbTree->Find(123) << endl;*/
	cout << "\t\t\t\tWorking with tree\n\n\n\n" << endl;
	char q;
	
	do
	{
		cout << "1. Read values from file." << endl;
		cout << "2. Insert value." << endl;
		cout << "3. Find." << endl;
		cout << "4. Clear tree." << endl;
		cout << "5. Numbers of nodes." << endl;
		cout << "6. Remove value." << endl;
		cout << "7. Show tree." << endl;
		cout << "8. Min." << endl;
		cout << "9. Max." << endl;
		cout << "To quit press q." << endl;

		cin >> q;


		switch (q)
		{
		case '1':
			char path[10000];
			cout << "Enter path and file name." << endl;
			cin >> path;

			rbTree->ReadFromFile(path);
			break;
		case '2':
			int val;
			cout << "Enter value.\n";
			cin >> val;

			rbTree->Insert(val);
			break;
		case '3':
			int Findval;
			cout << "Enter the value whitch you want to find\n";
			cin >> Findval;

			if (rbTree->Find(Findval) == true)
			{
				cout << "The value: "<< Findval << " is in the tree." << endl;
				system("pause");
			}
			else
			{
				cout << "Can not find the value in tree." << endl;
				system("pause");
			}
			break;
		case '4':
			cout << "Clearing the tree." << endl;
			rbTree->Clear();
			cout << "The tree is cleared." << endl;
			system("pause");
			break;
		case '5':
			cout << "Numbers of nodes in the tree: " << rbTree->GetNodesCount() << endl;
			system("pause");
			break;
		case '6':
			int Remval;
			cout << "Enter value to remove." << endl;
			cin >> Remval;

			rbTree->Remove(Remval);
			break;
		case '7':
			cout << "Showing the tree..." << endl;

			rbTree->Show();
			system("pause");
			break;
		case '8':
			cout << "Min: " << rbTree->GetMin() << endl;
			system("pause");
			break;
		case '9':
			cout << "Max: " << rbTree->GetMax() << endl;
			system("pause");
			break;
		default:
			break;
		}
		system("cls");

	} while (q !='q');
	

	delete rbTree;

    return 0;
}

