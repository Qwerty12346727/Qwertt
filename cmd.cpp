#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <iomanip>
const std::filesystem::path homepath = std::filesystem::current_path();
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";
void strToInt(std::string cmd_body) //convert str to int
{
	std::error_code error;
	for (char c : cmd_body)
	{
		std::cout << (int)c << " ";
	}
}
void createFile(std::string cmd_body) //create file
{
	std::error_code error;
	try
	{
		std::stringstream ss(cmd_body);
		std::string name;
		std::string contents;
		ss >> name;
		std::getline(ss >> std::ws, contents);
		std::ofstream file(name);
		file << contents;
		file.close();
		std::cout <<GREEN<< "\nFile written."<<RESET;
	}
	catch(const std::filesystem::filesystem_error& e)
	{
		std::cout <<"Cannot create. Maybe because the item does not exist, you could be trying to print a folder (no file extention) or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
		
	}
}
void readRam(std::string cmd_body) //read ram fuction
{
	std::error_code error;
	std::string allocated_ram_str = cmd_body;
	try
	{
		int allocated_ram = std::stoi(allocated_ram_str);

		char *block = new char[allocated_ram];
		for (int i = 0; i < allocated_ram; i++)
		{
			block[i] = (char)(i + 1);
		}
		for (char *ptr = block; ptr < block + allocated_ram; ptr++)
		{
			std::cout << (void *)ptr << " "
					  << std::hex
					  << std::setw(2)
					  << std::setfill('0')
					  << (int)(unsigned char)*ptr
					  << " ";
		}
		std::cout << "\n\n";
		delete[] block;
	}
	catch (const std::invalid_argument &e)
	{
		std::cout <<"Invalid argument. You may have put a charachter that is not an integer or left it blank.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << "Unable to read that much ram!! " << allocated_ram_str << " bytes is WAAAAAY too much!";
	std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;;
	}
	catch (const std::bad_alloc &e)
	{
		std::cout << "Unable to read that much ram!! " << allocated_ram_str << " bytes is WAAAAAY too much!";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void ls(std::string cmd_body) //list files
{
	std::error_code error;
	int a = 0;
	try
	{
		bool sub = false;
		std::string path = cmd_body;
		if (path.find("--sub") != std::string::npos)
		{
			size_t subPos = path.find("--sub");
			if (subPos != std::string::npos)
			{
				sub=true;
				path.erase(subPos, 5);
			}
			if(!path.empty() && path[0] == ' ')
			{
				path.erase(0, 1);
			}
			while(!path.empty() && path.back() == ' ')
			{
				path.pop_back();
			}
			if (path.empty())
			{
				path = "./";
			}
			for (auto file : std::filesystem::recursive_directory_iterator(path))
			{
				a++;
				std::cout << file.path() << "\n";
			}
			std::cout<<YELLOW<<"\nScanned "<<a<< " items."<<RESET;
		}
		else
		{
			if (path.empty())
			{
				path = "./";
			}
			for (auto file : std::filesystem::directory_iterator(path))
			{
				std::cout << file.path() << "\n";
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot list folder. Maybe because its an invalid folder, you might have written an invalid argument or there are system restrictions.";
		std::cout<<"/nScanned "<<a<< " items.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void cd(std::string cmd_body) //move working folder.
{
	std::error_code error;
	try
	{
		std::filesystem::current_path(cmd_body);
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot change folder. Maybe because its an invalid folder or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void makeDirectory(std::string cmd_body) //make directory
{
	try
	{
		if (std::filesystem::create_directory(cmd_body))
		{
			std::cout<<GREEN << "Successfully created folder."<<RESET;
		}
		else
		{
			std::cout << "Unable to create folder. Folder might already exist or system restrictions might be present.";
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot create folder. Maybe because another folder of the same name exists or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void remove(std::string cmd_body) //deletion script
{
	std::error_code error;
	try
	{
		if (std::filesystem::remove_all(cmd_body) > 0)
		{
			std::cout <<GREEN<< "Removed successfully."<<RESET;
		}
		else
		{
			std::cout << "Unable to remove. Check if the file or folder exists or if you are restricted by your system.";
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot remove. Maybe because the item does not exist or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void rename(std::string cmd_body) //file moving renaming script
{
	std::error_code error;
	try
	{
		std::stringstream ss(cmd_body);
		std::string name1;
		std::string name2; //path variables for the move or rename
		ss >> name1;
		std::getline(ss >> std::ws, name2);
		std::filesystem::rename(name1, name2);
		std::cout <<GREEN<< "Renamed/Moved successfully."<<RESET;
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot rename/move. Maybe because the item does not exist, you could be renaming to a folder (no file extention) or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void copy(std::string cmd_body) //file copying script
{
	std::error_code error;
	try
	{
		std::stringstream ss(cmd_body);
		std::string copy1;
		std::string copy2; //path variables for the copy
		ss >> copy1;
		std::getline(ss >> std::ws, copy2);
		std::filesystem::copy(copy1, copy2, std::filesystem::copy_options::overwrite_existing);
		std::cout <<GREEN<< "Copied successfully."<<RESET;
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot copy. Maybe because the item does not exist, you could be renaming to a folder (no file extention) or there are system restrictions.";std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;	}
}
void cat(std::string cmd_body)
{
	std::error_code error;
	try
	{
		std::ifstream file(cmd_body);
		std::string content;
		while (std::getline(file, content))
		{
			std::cout << content << "\n";
		}
		file.close();
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot print. Maybe because the item does not exist, you could be trying to print a folder (no file extention) or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void find(std::string cmd_body)
{
	std::filesystem::path found_path;
	std::error_code error;
	try
	{
		std::stringstream ss(cmd_body);
		std::string name;
		std::string path;
		ss >> name;
		std::getline(ss >> std::ws, path);
		bool sub = false;
		if (path.find("--goTo") != std::string::npos)
		{
			size_t subPos = path.find("--goTo");
			if (subPos != std::string::npos)
			{
				sub=true;
				path.erase(subPos, 6);
			}
			if(!path.empty() && path[0] == ' ')
			{
				path.erase(0, 1);
			}
			while(!path.empty() && path.back() == ' ')
			{
				path.pop_back();
			}
			if (path.empty())
			{
				path = "./";
			}
			for (auto file : std::filesystem::recursive_directory_iterator(path))
			{
				if(file.path().filename() == name)
				{
						
					std::cout<<YELLOW<<file.path()<<"\n"<<RESET;
					std::cout<<GREEN<<"Successfully found file."<<RESET;
					found_path = file.path().parent_path();
				}
			}
			std::filesystem::current_path(found_path);	
		}
		else
		{
			if(path.empty())
			{
				path = "./";
			}
			for (auto file : std::filesystem::recursive_directory_iterator(path))
			{
				if(file.path().filename() == name)
				{		
					std::cout<<YELLOW<<file.path()<<"\n"<<RESET;
					std::cout<<GREEN<<"Successfully found file."<<RESET;
				}
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot find. Maybe because the item does not exist, you wrote an invalid argument or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
void listFileHex(std::string cmd_body)
{
	std::error_code error;
	try
	{
		std::ifstream file(cmd_body);
		std::string(content);
		while(std::getline(file, content))
		{
			for (char c : content)
			{
				int cont = (unsigned char)c;
				std::cout << GREEN<<std::hex << std::setw(2) << std::setfill('0') << (int)cont << " "<<RESET;
			}
		}
		std::cout << "\n";		
		file.close();
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot print. Maybe because the item does not exist, you could be trying to print a folder (no file extention) or there are system restrictions.";
		std::cout <<RED<< "ERROR: " << e.what() << "\n"<<RESET;
	}
}
		
std::string getCmdType(std::string cmd) //get cmd type
{
	std::stringstream ss(cmd);
	std::string cmd_type;
	ss >> cmd_type;
	return cmd_type;
}

std::string getCmdBody(std::string cmd) //get cmd body
{
	std::stringstream ss(cmd);
	std::string cmd_type;
	std::string cmd_body;
	ss >> cmd_type;
	std::getline(ss >> std::ws, cmd_body);
	return cmd_body;
}
int main()
{
	std::cout <<"\033[36m"<< "2026 code open source. DONT MODIFY IF NOT ORIGINAL CREATOR.\n"<<RESET;
	bool on = true;
	while (on)
	{
		std::string cmd;
		std::cout << "\n"
				  << std::filesystem::current_path() <<"/>";
		std::getline(std::cin, cmd);
		std::string cmd_type = getCmdType(cmd);
		std::string cmd_body = getCmdBody(cmd);

		if (cmd_type == "exit") //all commands
		{
			std::cout << "Exiting...\n";
			return 0;
		}
		else if (cmd_type == "strToInt")
		{
			strToInt(cmd_body); //connects int main() vars to custom fuctions and activates fuction
		}
		else if (cmd_type == "createFile")
		{
			createFile(cmd_body);
		}
		else if (cmd_type == "readRam")
		{
			readRam(cmd_body);
		}
		else if (cmd_type == "ls" || cmd_type == "list")
		{
			ls(cmd_body);
		}
		else if (cmd_type == "cd" || cmd_type == "changeDirectory")
		{
			cd(cmd_body);
		}
		else if (cmd_type == "mkdir" || cmd_type == "makeDirectory")
		{
			makeDirectory(cmd_body);
		}
		else if (cmd_type == "rm" || cmd_type == "remove")
		{
			remove(cmd_body);
		}
		else if (cmd_type == "rn" || cmd_type == "rename")
		{
			rename(cmd_body);
		}
		else if (cmd_type == "cp" || cmd_type == "copy")
		{
			copy(cmd_body);
		}
		else if (cmd_type == "cat")
		{
			cat(cmd_body);
		}
		else if (cmd_type == "find")
		{
			find(cmd_body);
		}
		else if (cmd_type == "home")
		{
			std::filesystem::current_path(homepath);
		}
		else if (cmd_type == "listFileHex")
		{
			listFileHex(cmd_body);
		}
		else
		{
			std::cout <<RED<< "Invalid command!!!  >:(\n"
					  << cmd_type << " is not an available command!"<< RESET;
		}
	}
}
