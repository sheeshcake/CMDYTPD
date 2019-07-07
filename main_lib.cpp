
/*


CMD YouTube Player and Downloader v2.1_beta

Release Update
(2.1)
1. Playlist Player
2. Search History
3. Help Section Updated
4. App Optimization
5. Bug Fixed

(2.0)
1. Youtube Search added
2. App Optimization


*/






#include <iostream>
#include <conio.h>
#include "proccess_lib.h"
using namespace std;


int main(){
	system(("title CMDYTPD " + get_version()).c_str());
/////////////////// Code Testing Area  //////////////////////////
//	cout << "Testing Code...." << endl;
//	
//	ifstream file("history.txt");
//	string line = "";
//	history_count = 0;
//	while(file >> line){
//		cout << history_count << line << endl;
//		//search_history[history_count] = line;
//		//cout << search_history[history_count] << " = " << line << endl;
//		history_count++;
//	}
//
//
//
//
//
//
//
//
//	system("pause");
////////////////////////////////////////////////////////////////
	int ch;
	string search = "";
	while(ch != 6){
		title_display();
		cout << "1. Search\n2. Download\n3. Play\n4. Help\n5. About\n6. Exit\nCommand: ";
		cin >> ch;
		switch(ch){
			case 1: {
				title_display();
				cout << "Search Query: " << endl;
				get_history(true);
				string search_command = "";
				char character = ' ';
				while(character != 13){
					if(kbhit()){
						character = getch();
						if((character == 8) && (search.length() > 0)){
							search.erase(search.length()-1);
						}
						else{
							search += character;
							string first_command = "youtube-dl ytsearch20:\"";
							string second_command = "\" --get-title --get-id";
							search_command = first_command;
							search_command += search;
							search_command += second_command;
						}
						title_display();
						cout << "Search Query: " ;
						cout << search << endl;
						get_history(true);
//						cout << search_command;
					}
				}
				cs();
				add_history(search);
				search_youtube(search_command, search);
				break;
			}
			case 2: {
				title_display();
				cout << "Download URL: " ;
				string url;
				cin >> url;
				title_display();
				cout << "1. Download Video\n2. Download Audio\n\nCommand: ";
				int ch1;
				cin >> ch1;
				switch(ch1){
					case 1:{
						download_video(url);
						break;
					}
					case 2:{
						download_audio(url);
						break;
					}
				}
				break;
			}
			case 3: {
				title_display();
				cout << "Stream URL: " ;
				string url;
				cin >> url;
				title_display();
				cout << "By Dee" << endl << endl;
				cout << "1. Stream Video\n2. Stream Audio\n\nCommand: ";
				int ch1;
				cin >> ch1;
				switch(ch1){
					case 1:{
						stream_video(url);
						break;
					}
					case 2:{
						stream_audio(url);
						break;
					}
				}
				break;
			}
			case 4: {
				title_display();
				cout << "Help" << endl << endl;
				cout << "Key\t\t\tDescription" << endl;
				cout << "'space' or 'p'\t\tPause or Play" << endl;
				cout << "'q'\t\t\tEnd music" << endl;
				cout << "'arrow keys'\t\tSeek" << endl;
				cout << "'m'\t\t\tMute" << endl;
				cout << "'j'\t\t\tSelect Subtitle" << endl;
				cout << "'v'\t\t\tSubtitle On and Off" << endl;
				cout << "'['']'\t\t\tChange Speed" << endl;
				cout << "'9''0'\t\t\tVolume" << endl;
				cout << endl;
				system("pause");
				break;
			}
			case 5: {
				title_display();
				cout << "Copyright 2018-2019" << endl;
				cout << "\nThanks to" << endl;
				cout << "Github" << endl;
				cout << "YouTube" << endl;
				cout << "Google" << endl;
				cout << "mpv Player" << endl;
				cout << "StackOverFlow" << endl;
				cout << "" << endl;
				cout << "This App is For Personal Use Only Not For Sale" << endl;
				cout << "Download Copyright Musics at your own RISK!" << endl;
				cout << "Dont Blame me if you are in jail. :)" << endl;
				cout << "" << endl;
				cout << "About (CMDYTPD) v2.1_beta" << endl;
				cout << "" << endl;
				cout << "1. Playlist\n\t(2.1) You can now Play or Download YouTube Playlists" << endl;
				cout << "2. Help Section Added\n\t(2.1) Help Section is now Updated!" << endl;
				cout << "3. Search History Added\n\t(2.1) Search History Added!" << endl;
				cout << "4. Optimized!\n\t(2.1) Code improvements and optimized!" << endl;
				cout << "5. Bug Fixed!\n\t(2.1) Fixed! Search Result Bug\n\t(2.1) Fixed! Exits after playing." << endl;
				cout << "About (CMDYTPD) v2.0_beta" << endl;
				cout << "" << endl;
				cout << "1. Search Menu Added!\n\t(2.0) You can now Search youtube videoes and stream or download" << endl;
				cout << "2. Optimized!\n\t(2.0) Optimized and Much Faster.." << endl;
				cout << "About (CMDYTPD) v1.0_alpha" << endl;
				cout << "" << endl;
				cout << "1. You can download and stream music on youtube\n\t(1.0) You can now download or stream music using youtube url." << endl;
				cout << "2. More Bugs To Fix Later.." << endl;
				system("pause");
				break;
			}
			case 6 :{
				return 0;
				break;
			}
			case 7:{
				search_results();
				break;
			}
		}
		
	}
	
	
}
