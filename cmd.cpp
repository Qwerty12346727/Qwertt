#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <iomanip>
#include <cctype>
const std::filesystem::path homepath = std::filesystem::current_path();
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
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
			std::cout<<std::dec<<YELLOW<<"\nScanned "<<a<< " items."<<RESET;
		}
		else
		{
			if (path.empty())
			{
				path = "./";
			}
			for (auto file : std::filesystem::directory_iterator(path))
			{
				a++;
				std::cout << file.path() << "\n";
			}
			std::cout<<std::dec<<YELLOW<<"\nScanned "<<a<< " items."<<RESET;
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
		if (std::filesystem::create_directories(cmd_body))
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
		if(copy2.empty())
		{
			int i = 0;
			copy2 = "copy_"+copy1;
			while(std::filesystem::exists(copy2))
			{	 
				 
				copy2 = "copy_"+copy2;
				 
			}
		}
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
		bool list = false;
		if (path.find("--list") != std::string::npos)
		{
			size_t subPos = path.find("--list");
			if (subPos != std::string::npos)
			{
				list=true;
				size_t findPos = path.find("--list");
    			path.erase(findPos, 6);
    			if(!path.empty() && path[0] == ' ')
				{
				    path.erase(0, 1);
				}
				
				while(!path.empty() && path.back() == ' ')
				{
				    path.pop_back();
				}
				
				if(path.empty())
				{
				    path = "./";
				}
			}
		}
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
				if (list == true)
				{
					std::cout<<file.path()<<"\n";
				}
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
				if (list == true)
				{
					std::cout<<file.path()<<"\n";
				}
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
		std::string content;
		while(std::getline(file, content))
		{
			for (char c : content)
			{
				int cont = (unsigned char)c;
				std::cout <<std::hex << std::setw(2) << std::setfill('0') << (int)cont << " "<<RESET;
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
void info(std::string cmd_body)
{
	try
	{
		if(!cmd_body.empty())
		{
			std::filesystem::path file = std::filesystem::absolute(cmd_body);
			std::string fileType;
			std::string ext = file.extension().string();
			for(char& c : ext)
			{
				c = std::tolower(c);
			}
			if (!file.extension().empty())
			{
				if (ext == ".jpeg" || ext == ".jpg" || ext == ".png" || ext == ".tiff" || ext == ".tif" || ext == ".bmp" || ext == ".webp" || ext == ".gif" || ext == ".svg" || ext == ".ico" || ext == ".heic" || ext == ".heif" || ext == ".avif" || ext == ".jxl")
				{
					if ( ext == ".jpg" || ext == ".jpeg")
					{ 
						fileType = "Lossy" + ext +" Image";
					}
					else if ( ext == ".png" || ext == ".gif" || ext == ".svg")
					{
						fileType = "Lossless " + ext +" Image";
					}
					else if (ext == ".bmp")
					{
						fileType = "Bitmap Image";
					}
					else
					{
						fileType = ext + " Image";
					}
				}
				else if (ext == ".mp3" || ext == ".wav" || ext == ".flac" || ext == ".ogg" || ext == ".oga" || ext == ".opus" || ext == ".m4a" || ext == ".m4b" || ext == ".m4p" || ext == ".aac" || ext == ".wma" || ext == ".aiff" || ext == ".aif" || ext == ".aifc" || ext == ".alac" || ext == ".amr" || ext == ".ape" || ext == ".ac3" || ext == ".eac3" || ext == ".dts" || ext == ".dtshd" || ext == ".mka" || ext == ".ra" || ext == ".rm" || ext == ".au" || ext == ".snd" || ext == ".voc" || ext == ".tta" || ext == ".wv" || ext == ".tak" || ext == ".shn" || ext == ".dsf" || ext == ".dff" || ext == ".caf" || ext == ".rf64" || ext == ".bwf" || ext == ".ast" || ext == ".avr" || ext == ".raw" || ext == ".pcm" || ext == ".svx" || ext == ".vox" || ext == ".8svx" || ext == ".16sv" || ext == ".mid" || ext == ".midi" || ext == ".kar" || ext == ".mod" || ext == ".xm" || ext == ".it" || ext == ".s3m" || ext == ".stm" || ext == ".mtm" || ext == ".ult" || ext == ".669" || ext == ".amf" || ext == ".okt" || ext == ".far" || ext == ".med" || ext == ".mptm" || ext == ".psm" || ext == ".umx" || ext == ".spc" || ext == ".nsf" || ext == ".nsfe" || ext == ".gbs" || ext == ".gym" || ext == ".hes" || ext == ".kss" || ext == ".sap" || ext == ".vgm" || ext == ".vgz" || ext == ".adx" || ext == ".brstm" || ext == ".bcstm" || ext == ".bfstm" || ext == ".dsp" || ext == ".xma" || ext == ".w64" || ext == ".wve" || ext == ".mpc" || ext == ".mpc2" || ext == ".mpc3" || ext == ".mp2" || ext == ".mp1" || ext == ".mpa" || ext == ".mpp" || ext == ".webm" || ext == ".3gp" || ext == ".3g2" || ext == ".aa" || ext == ".aax" || ext == ".aaxc" || ext == ".awb" || ext == ".ec3" || ext == ".m4r")
				{
					if (ext == ".flac" || ext == ".wav" || ext == ".aiff" || ext == ".aif" || ext == ".aifc" || ext == ".alac" || ext == ".ape" || ext == ".wv" || ext == ".tta" || ext == ".tak" || ext == ".shn" || ext == ".wavpack" || ext == ".dsf" || ext == ".dff" || ext == ".pcm" || ext == ".raw" || ext == ".caf" || ext == ".bwf" || ext == ".rf64" || ext == ".au" || ext == ".snd")
					{
						fileType = "Lossless " + ext + " Audio File";
					}
					else if (ext == ".mp3" || ext == ".mp1" || ext == ".mp2" || ext == ".aac" || ext == ".amr" || ext == ".awb" || ext == ".ac3" || ext == ".eac3" || ext == ".ec3" || ext == ".dts" || ext == ".ra" || ext == ".rm" || ext == ".wma" || ext == ".spx" || ext == ".gsm" || ext == ".atrac" || ext == ".xma" || ext == ".aa" || ext == ".aax" || ext == ".aaxc")
					{
						fileType = "Lossy " + ext + " Audio File";
					}
					else
					{
						fileType = ext + " Audio File";
					}
				}
				else if ( ext == ".md" || ext == ".markdown" || ext == ".rst" || ext == ".rtf" || ext == ".doc" || ext == ".docx" || ext == ".docm" || ext == ".dot" || ext == ".dotx" || ext == ".dotm" || ext == ".odt" || ext == ".ott" || ext == ".fodt" || ext == ".pages" || ext == ".wpd" || ext == ".wps" || ext == ".wp" || ext == ".sxw" || ext == ".abw" || ext == ".lwp" || ext == ".pdf" || ext == ".djvu" || ext == ".djv" || ext == ".tex" || ext == ".latex" || ext == ".ltx" || ext == ".texi" || ext == ".texinfo" || ext == ".bib" || ext == ".epub" || ext == ".mobi" || ext == ".azw" || ext == ".azw3" || ext == ".fb2" || ext == ".chm" || ext == ".xps" || ext == ".oxps" || ext == ".pages" || ext == ".xls" || ext == ".xlsx" || ext == ".xlsm" || ext == ".xlsb" || ext == ".xlt" || ext == ".xltx" || ext == ".xltm" || ext == ".ods" || ext == ".ots" || ext == ".fods" || ext == ".numbers" || ext == ".csv" || ext == ".tsv" || ext == ".ppt" || ext == ".pptx" || ext == ".pptm" || ext == ".pps" || ext == ".ppsx" || ext == ".ppsm" || ext == ".pot" || ext == ".potx" || ext == ".potm" || ext == ".odp" || ext == ".otp" || ext == ".fodp" || ext == ".key" || ext == ".odg" || ext == ".otg" || ext == ".fodg" || ext == ".vsd" || ext == ".vsdx" || ext == ".vss" || ext == ".vst" || ext == ".vsdm" || ext == ".mpp" || ext == ".mpt" || ext == ".one" || ext == ".onetoc2" || ext == ".pub" || ext == ".pages" || ext == ".numbers" || ext == ".keynote")
				{
					fileType = ext + " Document";
				}
				else if (ext == ".c" || ext == ".h" || ext == ".cc" || ext == ".cpp" || ext == ".cxx" || ext == ".hpp" || ext == ".hxx" || ext == ".cs" || ext == ".java" || ext == ".kt" || ext == ".kts" || ext == ".swift" || ext == ".m" || ext == ".mm" || ext == ".rs" || ext == ".go" || ext == ".js" || ext == ".jsx" || ext == ".ts" || ext == ".tsx" || ext == ".py" || ext == ".pyw" || ext == ".rb" || ext == ".php" || ext == ".pl" || ext == ".pm" || ext == ".lua" || ext == ".r" || ext == ".dart" || ext == ".scala" || ext == ".sh" || ext == ".bash" || ext == ".zsh" || ext == ".fish" || ext == ".ps1" || ext == ".bat" || ext == ".cmd" || ext == ".asm" || ext == ".s" || ext == ".sql" || ext == ".html" || ext == ".htm" || ext == ".css" || ext == ".scss" || ext == ".sass" || ext == ".less" || ext == ".vue" || ext == ".svelte" || ext == ".xml" || ext == ".json" || ext == ".yaml" || ext == ".yml" || ext == ".toml" || ext == ".ini" || ext == ".cfg" || ext == ".dart")
				{
					fileType = ext + " Code File";
				}
				else if (ext == ".mp4" || ext == ".m4v" || ext == ".mkv" || ext == ".webm" || ext == ".avi" || ext == ".mov" || ext == ".qt" || ext == ".wmv" || ext == ".asf" || ext == ".flv" || ext == ".f4v" || ext == ".f4p" || ext == ".mpeg" || ext == ".mpg" || ext == ".mpe" || ext == ".m1v" || ext == ".m2v" || ext == ".m2p" || ext == ".m2ts" || ext == ".mts" || ext == ".ts" || ext == ".vob" || ext == ".evo" || ext == ".ogv" || ext == ".3gp" || ext == ".3g2" || ext == ".3gpp" || ext == ".3gpp2" || ext == ".mxf" || ext == ".rm" || ext == ".rmvb" || ext == ".amv" || ext == ".asf" || ext == ".divx" || ext == ".dv" || ext == ".fli" || ext == ".flc" || ext == ".flic" || ext == ".h264" || ext == ".h265" || ext == ".hevc" || ext == ".ivf" || ext == ".mjpg" || ext == ".mjpeg" || ext == ".nsv" || ext == ".ogm" || ext == ".rec" || ext == ".roq" || ext == ".vivo" || ext == ".yuv" || ext == ".bik" || ext == ".bk2" || ext == ".smk" || ext == ".str" || ext == ".pva" || ext == ".wtv" || ext == ".dvr-ms" || ext == ".mxf" || ext == ".nut" || ext == ".mve" || ext == ".rpl" || ext == ".svi" || ext == ".tod" || ext == ".vro" || ext == ".wtv" || ext == ".xvid")
				{
					if (ext == ".y4m" || ext == ".yuv" || ext == ".v210" || ext == ".v410" || ext == ".r210" || ext == ".r10k" || ext == ".ffv1" || ext == ".huffyuv" || ext == ".utvideo" || ext == ".lag")
					{
						fileType = "Lossless " + ext + " Video File";
					}
					else if (ext == ".mpg" || ext == ".mpeg" || ext == ".m1v" || ext == ".m2v" || ext == ".m2p" || ext == ".flv" || ext == ".f4v" || ext == ".wmv" || ext == ".rm" || ext == ".rmvb" || ext == ".3gp" || ext == ".3g2" || ext == ".amv" || ext == ".divx" || ext == ".xvid")
					{
						fileType = "Lossy " + ext+ " Video File";
					}
					else
					{
						fileType = ext + " Video File";
					}
				}
				else if (ext == ".zip" || ext == ".zipx" || ext == ".7z" || ext == ".rar" || ext == ".r00" || ext == ".r01" || ext == ".tar" || ext == ".gz" || ext == ".tgz" || ext == ".bz2" || ext == ".tbz" || ext == ".tbz2" || ext == ".xz" || ext == ".txz" || ext == ".z" || ext == ".zst" || ext == ".lz" || ext == ".lz4" || ext == ".lzh" || ext == ".lha" || ext == ".cab" || ext == ".arj" || ext == ".ace" || ext == ".arc" || ext == ".jar" || ext == ".war" || ext == ".ear" || ext == ".apk" || ext == ".ipa" || ext == ".deb" || ext == ".rpm" || ext == ".pkg" || ext == ".dmg" || ext == ".sit" || ext == ".sitx" || ext == ".sea" || ext == ".zoo" || ext == ".iso" || ext == ".cpio" || ext == ".ar" || ext == ".a" || ext == ".lzip" || ext == ".br" || ext == ".snappy" || ext == ".zpaq" || ext == ".alz" || ext == ".egg" || ext == ".pea" || ext == ".kgb" || ext == ".paq" || ext == ".arc" || ext == ".uc2" || ext == ".wim" || ext == ".swm" || ext == ".esd" || ext == ".xar" || ext == ".rpm" || ext == ".msi" || ext == ".appx" || ext == ".msix" || ext == ".appxbundle" || ext == ".msixbundle")
				{
					fileType = ext + " Archive File";
				}
				else if (ext == ".iso" || ext == ".img" || ext == ".ima" || ext == ".dmg" || ext == ".cdr" || ext == ".toast" || ext == ".bin" || ext == ".cue" || ext == ".nrg" || ext == ".mdf" || ext == ".mds" || ext == ".ccd" || ext == ".sub" || ext == ".vcd" || ext == ".vhd" || ext == ".vhdx" || ext == ".vdi" || ext == ".vmdk" || ext == ".qcow" || ext == ".qcow2" || ext == ".qed" || ext == ".raw" || ext == ".vfd" || ext == ".hdd" || ext == ".hds" || ext == ".wim" || ext == ".swm" || ext == ".esd" || ext == ".fvd" || ext == ".vma" || ext == ".ova" || ext == ".ovf" || ext == ".xva" || ext == ".vpc" || ext == ".vmdk" || ext == ".dsk" || ext == ".sdi" || ext == ".vdi" || ext == ".imgpart" || ext == ".dmgpart")
				{
					fileType = ext + " Disk Image";
				}
				else if (ext == ".ttf" || ext == ".otf" || ext == ".woff" || ext == ".woff2" || ext == ".fon" || ext == ".fnt" || ext == ".pfb" || ext == ".pfm" || ext == ".bdf" || ext == ".pcf")
				{
					fileType = ext + " Font";
				}
				else if (ext == ".obj" || ext == ".fbx" || ext == ".gltf" || ext == ".glb" || ext == ".stl" || ext == ".dae" || ext == ".3ds" || ext == ".blend" || ext == ".max" || ext == ".ma" || ext == ".mb" || ext == ".c4d" || ext == ".lwo" || ext == ".lws" || ext == ".ply" || ext == ".off" || ext == ".x3d" || ext == ".wrl" || ext == ".step" || ext == ".stp" || ext == ".iges" || ext == ".igs")
				{
					fileType = ext + " 3D Model";
				}
				else if (ext == ".db" || ext == ".db3" || ext == ".sqlite" || ext == ".sqlite3" || ext == ".mdb" || ext == ".accdb" || ext == ".mdf" || ext == ".ndf" || ext == ".ldf" || ext == ".dbf" || ext == ".fdb" || ext == ".gdb" || ext == ".realm" || ext == ".rdb")
				{
					fileType = ext + " Database File";
				}
				else if (ext == "" || ext == ".exe" || ext == ".com" || ext == ".dll" || ext == ".sys" || ext == ".scr" || ext == ".msi" || ext == ".elf" || ext == ".so" || ext == ".dylib" || ext == ".bin" || ext == ".out" || ext == ".a" || ext == ".o" || ext == ".obj" || ext == ".apk" || ext == ".aab" || ext == ".deb" || ext == ".rpm" || ext == ".appimage" || ext == ".app" || ext == ".ipa")
				{
					fileType = ext + " Binary File";
				}
				else if (ext == ".srt" || ext == ".ass" || ext == ".ssa" || ext == ".vtt" || ext == ".sub" || ext == ".sbv" || ext == ".smi" || ext == ".sami" || ext == ".dfxp" || ext == ".ttml")
				{
					fileType = ext + " Subtitle File";
				}
				else if (ext == ".pem" || ext == ".crt" || ext == ".cer" || ext == ".der" || ext == ".key" || ext == ".p12" || ext == ".pfx" || ext == ".csr" || ext == ".pub")
				{
					fileType = ext + "Certificate File";
				}
				else
				{
					fileType = ext + " File";
				}
			}
			std::cout << YELLOW
			<< "Location: "
			<< file.parent_path()
			<< std::endl
			<< "Filename: "
			<< file.filename()
			<< std::endl
			<< "Extension: "
			<< file.extension()
			<< std::endl
			<< "Type: "
			<< fileType
			<< std::endl
			<< "Size: "
			<< std::filesystem::file_size(cmd_body)
			<< " bytes"
			<< std::endl
			<< RESET;
		}
		else
		{
			std::cout << CYAN << "Qwertt 1.1.1 2026 by Qwerty123456727. Made with cpp.";
		}
	}
	catch(const std::filesystem::filesystem_error& e)
	{
		std::cout << "Cannot find info. Maybe because the item does not exist, you could be trying to print a folder (no file extention) or there are system restrictions.";
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
void callCommand(std::string cmd_type, std::string cmd_body)
{
	if (cmd_type == "exit") //all commands
				{
					std::cout << "Exiting...\n";
					exit(0);
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
				else if (cmd_type == "fileHex")
				{
					listFileHex(cmd_body);
				}
				else if (cmd_type == "version" || cmd_type == "ver")
				{
					std::cout << "1.1.1";
				}
				else if (cmd_type == "info")
				{
					info(cmd_body);
				}
				else
				{
					std::cout <<RED<< "Invalid command!!!  >:(\n"
							  << cmd_type << " is not an available command!"<< RESET;
				}
}
int main()
{
	std::cout <<"\033[36m"<< "2026 code open source. DONT MODIFY IF NOT ORIGINAL CREATOR.\n"<<RESET;
	bool on = true;
	while (on)
	{
		std::string cmd;
		std::cout << RESET;
		std::cout << "\n"
				  << std::filesystem::current_path() <<"/>";
		std::getline(std::cin, cmd);
		if (cmd.find("|") != std::string::npos)
		{
			std::stringstream ss(cmd);
			std::string part;
			while(std::getline(ss, part, '|'))
			{
				if(!part.empty() && part[0] == ' ')
				{
					part.erase(0, 1);
				}
				std::string cmd_type = getCmdType(part);
				std::string cmd_body = getCmdBody(part);
				callCommand(cmd_type, cmd_body);
			}
		}
		else
		{
			std::string cmd_type = getCmdType(cmd);
			std::string cmd_body = getCmdBody(cmd);
			callCommand(cmd_type, cmd_body);
		}
	}
}
