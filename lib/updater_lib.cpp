#include <iostream>
#include <fstream>
#include <pthread.h>
using namespace std;

/* Global Variable */
bool silent = false;


string get_version(){
	return "v1.5";
}

void *done(void *){
	system("lib\\done_update.cmd");
	return NULL;
}

void display(){
}

void kill(){
	system("taskkill /IM CMDYTPD_v3.x_beta.exe -f");
	system("taskkill /IM cmd.exe -f");
}	

main(int argc, char* argv[]){
	string command_input = "";
	system("cls");
	ifstream old_file("../CMDYTPD_v2.x_beta.exe");
	if(old_file.good()){
		remove("../CMDYTPD_v2.x_beta.exe");
		cout << "Cleaning files... " << endl;
	}
	for(int i = 1; i < argc; i++ ){
		command_input = argv[i];
	}
	cout << command_input << endl;
	if(command_input == "get-version"){
		get_version();
	}
	else{
		if(command_input == "silent"){
			silent = true;
		}
		if(!silent){
			system(("title CMDYTPD Updater " + get_version()).c_str());
			cout << "Checking The Latest Version.." << endl;
		}
		string user_version = command_input;

		try{
			string command1 = "powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://www.dropbox.com/s/zl3co84h06swa2c/version.txt?dl=1', 'lib\\version.txt')\"";
			string command2 = "powershell -Command \"Invoke-WebRequest https://www.dropbox.com/s/zl3co84h06swa2c/version.txt?dl=1 -OutFile lib\\version.txt\"";
			system((command1 + "\n" + command2).c_str());
		}catch(int e){
//			system("pause");
		}
	
		ifstream file("lib\\version.txt");
		string new_version[10] = {};
		string version_link[10] = {};
		string destination[10] = {};
		string temp1, temp2, temp3;
		int i = 0;
		while(file >> temp1 >> temp2 >> temp3){
			new_version[i] = temp1;
			version_link[i] = temp2;
			destination[i] = temp3;
			i++;
			cout << new_version[i] << "-" << version_link[i] << "-" << destination[i] << endl;
		}
		file.close();
		system("cls");
		if(new_version[0] != user_version && (user_version != "silent")){
			int ch;
			while(ch!=2){
				cout << "CMDYTPD " << user_version << endl;
				cout << "HEY! THERE IS A NEW VERSION!" << endl;
				cout << "NEW VERSION: " << new_version[0] << endl;
				cout << "1. Update Now\n2. Not now\n3. ChangeLog\nCommand: " << endl;
				cin >> ch;
				switch(ch){
					case 1 :{
						system("cls");
						cout << "CMDYTPD " << user_version << endl;
						cout << "Updating.." << endl;
						int updates = 0;
						for(int i = 0; i < 10; i++){
							if(!(new_version[i].empty())){
								updates++;
							}
							else{
								break;
							}
						}
						for(int i = 0; i < updates; i++){
							system("cls");
							cout << "CMDYTPD " << user_version << endl;
							cout << "Updating.." << endl;
							cout << 100+((i-updates)*10) << "% Done.";
							string command1 = "powershell -Command \"(New-Object Net.WebClient).DownloadFile('" + version_link[i] + "', '" + destination[i] + "')\"";
							string command2 = "powershell -Command \"Invoke-WebRequest " + version_link[i] + " -OutFile " + destination[i] + "\"";
							system((command1 + "\n" + command2).c_str());
						}
						ch=2;
						cout << "UPDATE SUCCESS!" << endl;
						break;
					}
					case 2: {
						pthread_t t1;
						pthread_create(&t1, NULL, done, NULL);
						pthread_join(t1, NULL);
						break;
					}
					case 3:{
						if(!silent){
							system("cls");
							cout << "Version Changelog" << endl;
							string command1 = "powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://www.dropbox.com/s/nfqtip600dfwk32/changelog.txt?dl=1', 'lib\\changelog.txt')\"";
							string command2 = "powershell -Command \"Invoke-WebRequest https://www.dropbox.com/s/nfqtip600dfwk32/changelog.txt?dl=1 -OutFile lib\\changelog.txt\"";
							system((command1 + "\n" + command2).c_str());
							ifstream file("lib\\changelog.txt");
							string line;
							while(std::getline (file,line)){
								std::string s(line);
								cout << line << endl;
							}
							file.close();
							system("pause");	
						}
						break;
					}
				}
			}
		}
		else{
			if(!silent){
				cout << "CMDYTPD " << user_version << endl;
				cout << "Your CMDYTPD is up to date! :)" << endl;
				cout << "Version Changelog" << endl;
				string command1 = "powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://www.dropbox.com/s/nfqtip600dfwk32/changelog.txt?dl=1', 'lib\\changelog.txt')\"";
				string command2 = "powershell -Command \"Invoke-WebRequest https://www.dropbox.com/s/nfqtip600dfwk32/changelog.txt?dl=1 -OutFile lib\\changelog.txt\"";
				system((command1 + "\n" + command2).c_str());
				ifstream file("lib\\changelog.txt");
				string line;
				while(std::getline (file,line)){
					std::string s(line);
					cout << line << endl;
				}
				file.close();
				system("pause");
			}

		}
		if(!silent){
			pthread_t t1;
			pthread_create(&t1, NULL, done, NULL);
			pthread_join(t1, NULL);
		}
		else{
			system("exit");
		}

	}

	return 0;
}
