/*
Memo


youtube-dl gvsearch5:how to develop for android --no-playlist --write-info-json --write-annotation --write-thumbnail --write-sub --skip-download


*/

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>


using namespace std;

// Objects
void cs();
void download_video(string video_url);
void download_audio(string audio_url);
void stream_video(string video_url);
void stream_audio(string audio_url);
int main();

// Universal Variable
string search_result[20][2] = {};
string search_history[10] = {};
int history_count = 0;


string get_version(){
	return "v3.1.2_beta";
}

void title_display(){

	cs();
	cout << "CMD YouTube Player and Downloader(CMDYTPD) " << get_version() << endl;
	cout << "By Dee" << endl << endl;

}

void get_result(){

	ifstream file("lib\\result.txt");
	string line = "";
	int counter = 0;
	int counter1 = 0;
    while (getline (file,line)){
		if(counter % 2 == 0){
			search_result[counter1][0] = line;
			cout << counter1+1 << ". " << line << endl;
		}
		else{
			search_result[counter1][1] = line;
			counter1++;
		}
		counter++;
    }
    file.close();

}

/// Radio Online List
// https://www.dropbox.com/s/5q89kilper41jbt/radio_link.txt?dl=1

void play_radio(string name, string link){

	title_display();
	cout << "Playing: " << name << endl;
	system(("lib\\mpv " + link +" --no-video").c_str());
	system("pause");

}


void get_radio(){
	title_display();
	cout << "Getting Online Radio Channels..." << endl;
	string command1 = "powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://www.dropbox.com/s/5q89kilper41jbt/radio_link.txt?dl=1', 'lib\\radio_link.txt')\"";
	string command2 = "powershell -Command \"Invoke-WebRequest https://www.dropbox.com/s/5q89kilper41jbt/radio_link.txt?dl=1 -OutFile lib\\radio_link.txt\"";
	system((command1 + "\n" + command2).c_str());
	title_display();
	cout << "Available Radio Channel" << endl;
	ifstream file("lib\\radio_link.txt");
	string temp1, temp2;
	string links[100][2] = {{}};
	int i = 0;
	while(file >> temp1 >> temp2){
		links[i][0] = temp1;
		links[i][1] = temp2;
		cout << i+1 << ". " << links[i][0] << endl;
		i++;
	}
	cout << "Command: ";
	int ch;
	cin >> ch;
	play_radio(links[ch-1][0], links[ch-1][1]);

}




void get_history(bool display){
	ifstream file("lib\\history.txt");
	string line = "";
	history_count = 0;
	while(file >> line && history_count < 20){
		search_history[history_count] = line;
		history_count++;
	}
	file.close();
	if(display == true){
		cout << "Search History" << endl;
		for(int i = 0; i < 20; i++){
			if(search_history[i].empty()){
				break;
			}
			cout << i+1 << ". " << search_history[i] << endl;
		}
	}
}

void add_history(string search){

	string temp_data[100] = {};
	temp_data[0] = search;
	for(int i = 0; i <= history_count; i++){
		temp_data[i+1] = search_history[i];
	}
	ofstream file("lib\\history.txt");
	for(int i = 0; i <= history_count; i++){
		file << temp_data[i] << endl;
	}
	file.close();
}


std::string removeAll( std::string str, const std::string& from) {
    size_t start_pos = 0;
    while( ( start_pos = str.find( from)) != std::string::npos) {
        str.erase( start_pos, from.length());
    }
    return str;
}

//void search_display(string s){
//	while(1){
//		title_display();
//		cout << "Search Input: " << s << endl;
//		cout << "Loading";
//		for(int i= 0; i < 5; i++){
//			Sleep(500);
//			cout << ".";
//		}
//	}
////	return NULL;
//}

//void start_search(string search_command){
//	system((search_command + " > " + "lib\\result.txt").c_str());
//
//}

string search_youtube(string search_command, string search){
	int ss = 1;
	string line = "";
	int result_counter = 0;
	//system("pause");
	title_display();
	cout << "Search Input: " << search  << endl;
	cout << "Loading.." << endl;
	system((search_command + " > " + "lib\\result.txt").c_str());
    cout << "Search Results" << endl;
    get_result();
    cout << "Command: ";
    int choice;
    cin >> choice;
	title_display();
	choice--;
	cout << "Choice: " << search_result[choice][0] << endl;
	cout << "1. Download Video\n2. Download Audio\n3. Play Video\n4. Play Audio\n\nCommand: ";
	int ch;
	cin >> ch;
	switch(ch){
		case 1:{
			download_video(search_result[choice][1]);
			break;
		}
		case 2:{
			download_audio(search_result[choice][1]);
			break;
		}
		case 3:{
			stream_video(search_result[choice][1]);
			break;
		}
		case 4:{
			stream_audio(search_result[choice][1]);
			break;
		}
		default:{
			search_youtube(search_command, search);
			break;
		}
	}

}

void cs(){
	system("cls");
}

void download_video(string video_url){

	title_display();
	string command = "";
	if(video_url.rfind("https://www.youtube.com/playlist?list=", 0) == 0){
		video_url = removeAll(video_url,"https://www.youtube.com/playlist?list=");
		command = "lib\\youtube-dl -o \"Downloads/Video/%(title)s.%(ext)s\" -f 136+140 https://www.youtube.com/playlist?list=" + video_url;
	}
	else{
		video_url = removeAll(video_url, "https://www.youtube.com/watch?v=");
		command = "lib\\youtube-dl -o \"Downloads/Video/%(title)s.%(ext)s\" -f 136+140 https://www.youtube.com/watch?v=" + video_url;
	}
	system(command.c_str());
	main();

}

void download_audio(string audio_url){

	title_display();
	string command = "";
	if(audio_url.rfind("https://www.youtube.com/playlist?list=", 0) == 0){
		audio_url = removeAll(audio_url, "https://www.youtube.com/playlist?list=");
		command = "lib\\youtube-dl -o \"Downloads/Audio/%(title)s.%(ext)s\"  --extract-audio --audio-format mp3 --audio-quality=320k https://www.youtube.com/playlist?list=" + audio_url;
	}
	else{
		audio_url = removeAll(audio_url, "https://www.youtube.com/watch?v=");
		command = "lib\\youtube-dl -o \"Downloads/Audio/%(title)s.%(ext)s\"  --extract-audio --audio-format mp3 --audio-quality=320k https://ww.youtube.com/watch?v=" + audio_url;
	}
	system(command.c_str());
	main();

}

void stream_video(string video_url){

	title_display();
	string command = "";
	if(video_url.rfind("https://www.youtube.com/playlist?list=", 0) == 0){
		video_url = removeAll(video_url, "https://www.youtube.com/playlist?list=");
		command = "lib\\mpv https://www.youtube.com/playlist?list=" + video_url;
	}
	else{
		video_url = removeAll(video_url, "https://www.youtube.com/watch?v=");
		command = "lib\\mpv https://www.youtube.com/watch?v=" + video_url;
	}
	system(command.c_str());
	main();

}


void stream_audio(string audio_url){

	try{
		title_display();
		string command = "";
		if(audio_url.rfind("https://www.youtube.com/playlist?list=", 0) == 0){
			audio_url = removeAll(audio_url, "https://www.youtube.com/playlist?list=");
			command = "lib\\mpv https://www.youtube.com/playlist?list="+ audio_url + " --no-video";
		}
		else{
			audio_url = removeAll(audio_url, "https://www.youtube.com/watch?v=");
			command = "lib\\mpv https://www.youtube.com/watch?v="+ audio_url + " --no-video";
		}
		system("pause");
		system(command.c_str());
		system("pause");
	}catch(int e){
		cout << "Stopped!!" << endl;
		system("pause");
		main();
	}



}

///////                                    Note
//                                      update code
//
//
//  powershell -Command "(New-Object Net.WebClient).DownloadFile('https://www.dropbox.com/s/a4cydl3y5kj29bh/version.txt?dl=1', 'version.txt')"
//  powershell -Command "Invoke-WebRequest https://www.dropbox.com/s/a4cydl3y5kj29bh/version.txt?dl=1 -OutFile version.txt"
//
//
///////

void get_update(){
	system(("lib\\updater_lib " + get_version()).c_str());
}

//void silent_update(){
//	system(("lib\\updater_lib " + get_version() + " silent").c_str());
//}

void updater_update(){
	ifstream file("lib\\updater_version.txt");
	if(file){
		string temp1, temp2;
		string updater_user_version = "";
		while(file >> temp1 >> temp2){
			updater_user_version = temp1;
		}
		file.close();
		string command1 = "powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://www.dropbox.com/s/fv2jrdggmmiv4i1/updater_version.txt?dl=1', 'lib\\updater_version.txt')\"";
		string command2 = "powershell -Command \"Invoke-WebRequest https://www.dropbox.com/s/fv2jrdggmmiv4i1/updater_version.txt?dl=1 -OutFile lib\\updater_version.txt\"";
		system((command1 + "\n" + command2).c_str());
		ifstream file("lib\\updater_version.txt");
		string new_version = "";
		string version_link = "";
		title_display();
		cout << "Please wait.. ";
		if(system("lib\\youtube-dl -U")){
			get_update();
		}
		while(file >> temp1 >> temp2){
			new_version = temp1;
			version_link = temp2;
//			cout << new_version << " " << version_link << endl;
//			system("pause");
		}
		if(new_version != updater_user_version){
			title_display();
			cout << "Updating CMDYTPD Libaries.." << endl;
			system("lib\\youtube-dl -U");
			string command1 = "powershell -Command \"(New-Object Net.WebClient).DownloadFile('" + version_link + "', 'lib\\updater_lib.exe')\"";
			string command2 = "powershell -Command \"Invoke-WebRequest " + version_link + " -OutFile lib\\updater_lib.exe\"";
			system((command1 + "\n" + command2).c_str());
			title_display();
			cout << "Libraries Successfully Updated!! :)" << endl;
			system("pause");
		}
	}
	else{
		system("powershell -Command \"(New-Object Net.WebClient).DownloadFile('https://www.dropbox.com/s/tj9210a2ny56b6b/temp_updater_version.txt?dl=1', 'lib\\updater_version.txt')\"");
		system("powershell -Command \"Invoke-WebRequest https://www.dropbox.com/s/tj9210a2ny56b6b/temp_updater_version.txt?dl=1 -OutFile lib\\updater_version.txt\"");
		updater_update();
	}
}


