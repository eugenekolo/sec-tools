#include "config.h"

/* C++ libraries */
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cerrno>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <new>
#include <set>
#include <sstream>
#include <stdint.h>
#include <vector>

/* POSIX libraries */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

/* GNU headers */
#ifndef HAVE_GETOPT_H
#define getopt_long(a,b,c,d,e)  getopt((a),(b),(c))
struct option {
	const char *name;
	int has_arg;
	int *flag;
	int val;
};
#else
#include <getopt.h>
#endif

/* ext3/4 libraries */
#include <ext2fs/ext2fs.h>
#include "extundelete.h"

#ifndef EXT2_FLAG_64BITS
#define EXT2_FLAG_64BITS 0x20000
#endif


#ifndef HAVE_EXT2FS_BLOCKS_COUNT
blk64_t ext2fs_blocks_count(struct ext2_super_block *super) {
	return super->s_blocks_count;
}
#endif


namespace Config {
	static std::string progname;
	static std::string journal_filename;
	static std::string restore_file;
	static std::string restore_files;
	static std::string restore_inode;
	static std::string fsname = "";
	static std::string outputdir = "RECOVERED_FILES/";

	static bool action = false;
	static bool journal = false;
	static bool restore_all = false;
	static bool superblock = false;

	static ext2_ino_t inode = 0;
	static ext2_ino_t inode_to_block = 0;
	static ext2_ino_t show_journal_inodes = 0;

	static blk_t backup_superblock = 0;
	static blk64_t block = 0;
	static blk_t block_size = 0;
	static blk_t journal_block = 0;

	static __u32 journal_transaction = 0;
	std::ofstream elogfile;
	std::ofstream wlogfile;
	std::ofstream slogfile;
	std::ofstream ilogfile;
	std::ofstream dlogfile;
}

std::string commandline_restore_directory;
long commandline_before = LONG_MAX;
long commandline_after = 0;


static void Log_errors(const char * whoami, long code, const char * format, va_list args) {
	char buffer[BUFSIZ];
	vsprintf (buffer, format, args);
	Log::error << whoami << ": " << error_message (code) << " " << buffer << std::endl;
}


static void print_version(void)
{
	std::cout << "extundelete version " << VERSION << std::endl;

	const char *ver;
	ext2fs_get_library_version (&ver, NULL);
	std::cout << "libext2fs version " << ver << std::endl;

	int n = 1 ;
	if(*(char *) &n == 1)  // True if the cpu is little endian.
		std::cout << "Processor is little endian." << std::endl;
	else
		std::cout << "Processor is big endian." << std::endl;
}


static void print_usage(std::ostream& os, std::string cmd)
{
  os << "Usage: " << cmd << " [options] [--] device-file\n";
  os << "Options:\n";
  os << "  --version, -[vV]       Print version and exit successfully.\n";
  os << "  --help,                Print this help and exit successfully.\n";
  os << "  --superblock           Print contents of superblock in addition to the rest.\n";
  os << "                         If no action is specified then this option is implied.\n";
  os << "  --journal              Show content of journal.\n";
  os << "  --after dtime          Only process entries deleted on or after 'dtime'.\n";
  os << "  --before dtime         Only process entries deleted before 'dtime'.\n";
  os << "Actions:\n";
  os << "  --inode ino            Show info on inode 'ino'.\n";
  os << "  --block blk            Show info on block 'blk'.\n";
  os << "  --restore-inode ino[,ino,...]\n";
  os << "                         Restore the file(s) with known inode number 'ino'.\n";
  os << "                         The restored files are created in ./RECOVERED_FILES\n";
  os << "                         with their inode number as extension (ie, file.12345).\n";
  os << "  --restore-file 'path'  Will restore file 'path'. 'path' is relative to root\n";
  os << "                         of the partition and does not start with a '/'\n";
  os << "                         The restored file is created in the current\n";
  os << "                         directory as 'RECOVERED_FILES/path'.\n";
  os << "  --restore-files 'path' Will restore files which are listed in the file 'path'.\n";
  os << "                         Each filename should be in the same format as an option\n";
  os << "                         to --restore-file, and there should be one per line.\n";
  os << "  --restore-directory 'path'\n";
  os << "                         Will restore directory 'path'. 'path' is relative to the\n";
  os << "                         root directory of the file system.  The restored\n";
  os << "                         directory is created in the output directory as 'path'.\n";
  os << "  --restore-all          Attempts to restore everything.\n";
  os << "  -j journal             Reads an external journal from the named file.\n";
  os << "  -b blocknumber         Uses the backup superblock at blocknumber when opening\n";
  os << "                         the file system.\n";
  os << "  -B blocksize           Uses blocksize as the block size when opening the file\n";
  os << "                         system.  The number should be the number of bytes.\n";
  os << "  --log 0                Make the program silent.\n";
  os << "  --log filename         Logs all messages to filename.\n";
  os << "--log D1=0,D2=filename   Custom control of log messages with comma-separated\n";
  os << "   Examples below:       list of options.  Dn must be one of info, warn, or\n";
  os << "   --log info,error      error.  Omission of the '=name' results in messages\n";
  os << "   --log warn=0          with the specified level to be logged to the console.\n";
  os << "   --log error=filename  If the parameter is '=0', logging for the specified\n";
  os << "                         level will be turned off.  If the parameter is\n";
  os << "                         '=filename', messages with that level will be written\n";
  os << "                         to filename.\n";
  os << "   -o directory          Save the recovered files to the named directory.\n";
  os << "                         The restored files are created in a directory\n";
  os << "                         named 'RECOVERED_FILES/' by default.\n";
}


static errcode_t examine_fs(ext2_filsys fs)
{
	errcode_t errcode;

	if (Config::superblock && !Config::journal) {
		// Print contents of superblock.
		std::cout << fs->super << std::endl;
	}

	if (Config::action)
	{
		Log::status << "Loading filesystem metadata ... " << std::flush;
		/* Note: for a 1 TB partition with 4k block size, these bitmaps
		 * require 40 MB memory.
		*/
		errcode = ext2fs_read_inode_bitmap(fs);
		errcode |= ext2fs_read_block_bitmap(fs);
		if (errcode) return errcode;
		Log::status << fs->super->s_inodes_count / fs->super->s_inodes_per_group
		<< " groups loaded." << std::endl;
	}

	// Check commandline options against superblock bounds.
	if (Config::inode != 0)
	{
		if ((uint32_t)Config::inode > fs->super->s_inodes_count)
		{
			Log::error << Config::progname << ": --inode: inode " << Config::inode 
			<< " is out of range. There are only " << fs->super->s_inodes_count
			<< " inodes." << std::endl;
			return EU_EXAMINE_FAIL;
		}
	}
	if (Config::block != 0)
	{
		blk64_t maxblock = ext2fs_blocks_count(fs->super);
		if (Config::block >= maxblock || Config::block == 0)
		{
			Log::error << Config::progname << ": --block: block " << Config::block
			<< " is out of range." << std::endl
			<< "Valid block numbers are from 1 to "
			<< maxblock - 1 << std::endl;
			return EU_EXAMINE_FAIL;
		}
	}

	if (Config::show_journal_inodes != 0)
	{
		if ((uint32_t)Config::show_journal_inodes > fs->super->s_inodes_count)
		{
			Log::error << Config::progname << ": --show-journal-inodes: inode "
			<< Config::show_journal_inodes
			<< " is out of range. There are only " << fs->super->s_inodes_count
			<< " inodes." << std::endl;
			return EU_EXAMINE_FAIL;
		}
	}

	// Handle --inode
	if (Config::inode != 0)
	{
		std::cout << "Group: " << ext2fs_group_of_ino(fs, Config::inode)
		<< std::endl;
		errcode = print_inode(fs, Config::inode);
		if(errcode)
			com_err(Config::progname.c_str(), errcode, "while printing inode.");
	}

	// Handle --block
	if (Config::block != 0 || (Config::journal_block != 0 && Config::journal))
	{
		classify_block(fs, Config::block);
	}

	ext2_filsys jfs = NULL;
	errcode = get_journal_fs(fs, &jfs, Config::journal_filename);
	if (errcode) {
		com_err(Config::progname.c_str(), errcode, "while opening journal.");
		return errcode;
	}

	journal_superblock_t jsb;
	journal_superblock_t *journal_superblock = &jsb;
	errcode = read_journal_superblock(fs, jfs, journal_superblock);
	if (errcode) {
		com_err(Config::progname.c_str(), errcode, "while reading journal superblock.");
		return errcode;
	}

	if (Config::superblock && Config::journal)
	{
		std::cout << jsb << std::endl;
	}

	if (Config::journal_block != 0)
	{
		if (Config::journal_block >= jsb.s_maxlen)
		{
			Log::error << Config::progname << ": --journal-block: block "
			<< Config::journal_block
			<< " is out of range. There are only "<< jsb.s_maxlen
			<< " blocks in the journal." << std::endl;
			return EU_EXAMINE_FAIL;
		}
	}


	assert(jsb.s_header.h_magic == JFS_MAGIC_NUMBER);

	// Start recovery here.
	if (!Config::restore_file.empty() ||
			!Config::restore_files.empty() ||
			Config::restore_all ||
			!Config::restore_inode.empty() ||
			!commandline_restore_directory.empty() )
	{
		//Read the descriptors from the journal here
		errcode = init_journal(fs, jfs, &jsb);
		if (errcode) {
			com_err(Config::progname.c_str(), errcode, "while reading journal descriptors.");
			return errcode;
		}

		errcode = extundelete_make_outputdir(Config::outputdir.c_str());
		if (errcode) {
			com_err(Config::progname.c_str(), errcode, "while creating output directory.");
			return errcode;
		}
	}
	// Handle --restore-all
	if (Config::restore_all)
		errcode = restore_directory (fs, jfs, EXT2_ROOT_INO, "");
	if (errcode) {
		com_err(Config::progname.c_str(), errcode, "while restoring all files.");
		return errcode;
	}

	// Handle --restore-directory
	if (!commandline_restore_directory.empty()) {
		errcode = restore_file (fs, jfs, commandline_restore_directory.c_str());
	}
	if (errcode) {
		com_err(Config::progname.c_str(), errcode, "while restoring directory.");
		return errcode;
	}

	// Handle --restore-file
	if (!Config::restore_file.empty()) {
		errcode = restore_file(fs, jfs, Config::restore_file);
	}
	if (errcode) {
		com_err(Config::progname.c_str(), errcode, "while restoring file.");
		return errcode;
	}

	// Handle --restore-files
	// FIXME: test this part thoroughly
	if (!Config::restore_files.empty()) {
		std::ifstream infile;
		// Hopefully this is long enough
		unsigned int namelen = 2560;
		char *name = new char[namelen];

		infile.open (Config::restore_files.c_str(), std::ifstream::in);
		if(infile.is_open()) {
			while (!infile.eof()) {
				infile.getline (name, namelen);
				if(strlen(name) > 0)
					errcode = restore_file (fs, jfs, std::string(name) );
					if(errcode)  com_err(Config::progname.c_str(), errcode, "while restoring file %s.", name);
			}
			infile.close();
		} else {
			errcode = EU_EXAMINE_FAIL;
			Log::error << Config::progname << ": Unable to open file "
			 << Config::restore_files << std::endl;
			return errcode;
		}
		delete[] name;
	}

	// Handle --restore-inode
	if (!Config::restore_inode.empty())
	{
		std::istringstream is (Config::restore_inode);
		ext2_ino_t ino;
		char comma;
		while(is >> ino)
		{
			std::ostringstream oss;
			oss << "file." << ino;
			restore_inode (fs, jfs, ino, oss.str());
			is >> comma;
		};
	}

	if(fs->super->s_journal_inum == 0)
		errcode = ext2fs_close(jfs);
	return errcode;
}


static int decode_options(int& argc, char**& argv)
{
	int short_option;
	static int long_option;
	enum opts {
		opt_version,
		opt_superblock,
		opt_inode,
		opt_block,
		opt_after,
		opt_before,
		opt_journal,
		opt_journal_block,
		opt_journal_transaction,
		opt_inode_to_block,
		opt_show_journal_inodes,
		opt_restore_file,
		opt_restore_files,
		opt_restore_directory,
		opt_restore_inode,
		opt_restore_all,
		opt_help,
		opt_log
	};
	struct option longopts[] = {
		{"help", 0, &long_option, opt_help},
		{"version", 0, &long_option, opt_version},
		{"superblock", 0, &long_option, opt_superblock},
		{"inode", 1, &long_option, opt_inode},
		{"block", 1, &long_option, opt_block},
		{"after", 1, &long_option, opt_after},
		{"before", 1, &long_option, opt_before},
		{"journal", 0, &long_option, opt_journal},
		{"journal-block", 1, &long_option, opt_journal_block},
		{"journal-transaction", 1, &long_option, opt_journal_transaction},
		{"inode-to-block", 1, &long_option, opt_inode_to_block},
		{"show-journal-inodes", 1, &long_option, opt_show_journal_inodes},
		{"restore-inode", 1, &long_option, opt_restore_inode},
		{"restore-file", 1, &long_option, opt_restore_file},
		{"restore-files", 1, &long_option, opt_restore_files},
		{"restore-directory", 1, &long_option, opt_restore_directory},
		{"restore-all", 0, &long_option, opt_restore_all},
		{"log", 1, &long_option, opt_log},
		{NULL, 0, NULL, 0}
	};

	while ((short_option = getopt_long(argc, argv, "j:vVb:B:o:", longopts, NULL)) != -1)
	{
		switch (short_option)
		{
		case 0:
			switch (long_option)
			{
			case opt_help:
				print_usage(std::cout, Config::progname);
				return EU_STOP;
			case opt_version:
				print_version();
				return EU_STOP;
			case opt_superblock:
				Config::superblock = true;
				break;
			case opt_journal:
				Config::journal = true;
				break;
			case opt_after:
				errno = 0;
				commandline_after = strtol(optarg, NULL, 10);
				if(errno) {
					Log::error << "Invalid parameter: --after " << optarg << std::endl;
					return EU_DECODE_FAIL;
				}
				break;
			case opt_before:
				errno = 0;
				commandline_before = strtol(optarg, NULL, 10);
				if(errno) {
					Log::error << "Invalid parameter: --before " << optarg << std::endl;
					return EU_DECODE_FAIL;
				}
				break;
			case opt_restore_inode:
				Config::restore_inode = optarg;
				break;
			case opt_restore_file:
				Config::restore_file = optarg;
				break;
			case opt_restore_files:
				Config::restore_files = optarg;
				break;
			case opt_restore_directory:
				commandline_restore_directory = optarg;
				break;
			case opt_restore_all:
				Config::restore_all = true;
				break;
			case opt_inode_to_block:
				errno = 0;
				Config::inode_to_block = strtoul(optarg, NULL, 10);
				if(errno) {
					Log::error << "Invalid parameter: --inode-to-block " << optarg << std::endl;
					return EU_DECODE_FAIL;
				}
				if (Config::inode_to_block < 1)
				{
					Log::error << Config::progname << ": --inode-to-block: inode "
					<< Config::inode_to_block << " is out of range." << std::endl;
					return EU_DECODE_FAIL;
				}
				break;
			case opt_inode:
				errno = 0;
				Config::inode = strtoul(optarg, NULL, 10);
				if(errno) {
					Log::error << "Invalid parameter: --inode " << optarg << std::endl;
					return EU_DECODE_FAIL;
				}
				if (Config::inode < 1)
				{
					Log::error << Config::progname << ": --inode: inode " << Config::inode
					<< " is out of range." << std::endl;
					return EU_DECODE_FAIL;
				}
				break;
			case opt_block:
				errno = 0;
				Config::block = strtoul(optarg, NULL, 10);
				if(errno) {
					Log::error << "Invalid parameter: --block " << optarg << std::endl;
					return EU_DECODE_FAIL;
				}
				if (Config::block < 1)
				{
					Log::error << Config::progname << ": --block: block " << Config::block
					<< " is out of range." << std::endl;
					return EU_DECODE_FAIL;
				}
				break;
			case opt_show_journal_inodes:
				errno = 0;
				Config::show_journal_inodes = strtoul(optarg, NULL, 10);
				if(errno) {
					Log::error << "Invalid parameter: --show-journal-inodes " << optarg << std::endl;
					return EU_DECODE_FAIL;
				}
				if (Config::show_journal_inodes < 1)
				{
					Log::error << Config::progname << ": --show-journal-inodes: inode "
					<< Config::show_journal_inodes << " is out of range."
					<< std::endl;
					return EU_DECODE_FAIL;
				}
				break;
			case opt_journal_transaction:
				errno = 0;
				Config::journal_transaction = strtoul(optarg, NULL, 10);
				if(errno) {
					Log::error << "Invalid parameter: --journal-transaction " << optarg << std::endl;
					return EU_DECODE_FAIL;
				}
				break;
			case opt_log:
				std::string logopts = optarg;
				while(true) {
					if( ! logopts.substr(0,5).compare("debug") ) {
						if( logopts[5] == '=' ) {
							size_t pos = logopts.find_first_of(',');
							std::string fname(logopts.substr(6, pos-6));
							if( fname.compare("0") ) {
								Config::dlogfile.open(fname.c_str());
								Log::debug.rdbuf(Config::dlogfile.rdbuf());
							} else {
								Log::debug.rdbuf(0);
							}
							logopts.erase(0, pos);
						} else {
							Log::debug.rdbuf(std::cout.rdbuf());
							logopts.erase(0,5);
						}
					} else if( ! logopts.substr(0,6).compare("status") ) {
						if( logopts[6] == '=' ) {
							size_t pos = logopts.find_first_of(',');
							std::string fname(logopts.substr(7, pos-7));
							if( fname.compare("0") ) {
								Config::slogfile.open(fname.c_str());
								Log::status.rdbuf(Config::slogfile.rdbuf());
							} else {
								Log::status.rdbuf(0);
							}
							logopts.erase(0, pos);
						} else {
							Log::status.rdbuf(std::cout.rdbuf());
							logopts.erase(0,6);
						}
					} else if( ! logopts.substr(0,4).compare("info") ) {
						if( logopts[4] == '=' ) {
							size_t pos = logopts.find_first_of(',');
							std::string fname(logopts.substr(5, pos-5));
							if( fname.compare("0") ) {
								Config::ilogfile.open(fname.c_str());
								Log::info.rdbuf(Config::ilogfile.rdbuf());
							} else {
								Log::info.rdbuf(0);
							}
							logopts.erase(0, pos);
						} else {
							Log::info.rdbuf(std::cout.rdbuf());
							logopts.erase(0,4);
						}
					} else if( ! logopts.substr(0,4).compare("warn") ) {
						if( logopts[4] == '=' ) {
							size_t pos = logopts.find_first_of(',');
							std::string fname(logopts.substr(5, pos-5));
							if( fname.compare("0") ) {
								Config::wlogfile.open(fname.c_str());
								Log::warn.rdbuf(Config::wlogfile.rdbuf());
							} else {
								Log::warn.rdbuf(0);
							}
							logopts.erase(0, pos);
						} else {
							Log::warn.rdbuf(std::cout.rdbuf());
							logopts.erase(0,4);
						}
					} else if( ! logopts.substr(0,5).compare("error") ) {
						if( logopts[5] == '=' ) {
							size_t pos = logopts.find_first_of(',');
							std::string fname(logopts.substr(6, pos-6));
							if( fname.compare("0") ) {
								Config::elogfile.open(fname.c_str());
								Log::error.rdbuf(Config::elogfile.rdbuf());
							} else {
								Log::error.rdbuf(0);
							}
							logopts.erase(0, pos);
						} else {
							Log::error.rdbuf(std::cout.rdbuf());
							logopts.erase(0,5);
						}

					} else {
						if( logopts.compare("0") ) {
							Config::elogfile.open(logopts.c_str());
							Log::info.rdbuf(Config::elogfile.rdbuf());
							Log::status.rdbuf(Config::elogfile.rdbuf());
							Log::warn.rdbuf(Config::elogfile.rdbuf());
							Log::error.rdbuf(Config::elogfile.rdbuf());
						} else {
							Log::info.rdbuf(0);
							Log::status.rdbuf(0);
							Log::warn.rdbuf(0);
							Log::error.rdbuf(0);
						}
						logopts.clear();
					}
					if(logopts.empty()) break;
					logopts.erase(0,1);
				}
				break;
			}
			break;
		case 'j':
			Config::journal_filename = std::string(optarg);
			break;
		case 'b':
			errno = 0;
			Config::backup_superblock = strtoul(optarg, NULL, 10);
			if(errno) {
				Log::error << "Invalid parameter: -b " << optarg << std::endl;
				return EU_DECODE_FAIL;
			}
			break;
		case 'B':
			errno = 0;
			Config::block_size = strtoul(optarg, NULL, 10);
			if(errno) {
				Log::error << "Invalid parameter: -B " << optarg << std::endl;
				return EU_DECODE_FAIL;
			}
			break;
		case 'o':
			Config::outputdir = std::string(optarg);
			if(Config::outputdir.at(Config::outputdir.length()-1) != '/')
				Config::outputdir.append("/");
			break;
		case 'v':
		case 'V':
			print_version();
			return EU_STOP;
		}
	}

	Config::action =
			(Config::inode != 0 ||
			 Config::block != 0 ||
			 Config::journal_block != 0 ||
			 Config::journal_transaction != 0 ||
			 Config::show_journal_inodes != 0 ||
			 Config::inode_to_block != 0 ||
			 !Config::restore_inode.empty() ||
			 !Config::restore_file.empty() ||
			 !Config::restore_files.empty() ||
			 !commandline_restore_directory.empty() ||
			 Config::restore_all);
	if (!Config::action && !Config::superblock)
	{
		Log::status << "No action specified; implying --superblock.\n";
		Config::superblock = true;
	}
	if (commandline_before < LONG_MAX || commandline_after)
	{
		Log::status << "Only show and process deleted entries if they are deleted ";
		// date -d@1234567890 converts a value to a readable string (using GNU date)
		std::string after = to_string(commandline_after);
		std::string before = to_string(commandline_before);
		if (commandline_after)
			Log::status << "on or after " << after;
		if (commandline_before && commandline_after)
			Log::status << " and ";
		if (commandline_before)
			Log::status << "before " << before;
		Log::status << '.' << std::endl;
		if (commandline_before && commandline_after)
			assert(commandline_after < commandline_before);
	}

	argv += optind;
	argc -= optind;

	// Sanity checks on the user.
	if (argc == 0)
	{
		Log::error << Config::progname << ": Missing device name." << std::endl;
		print_usage(Log::error, Config::progname);
		return EU_DECODE_FAIL;
	}
	if (argc > 1) {
		Log::error << Config::progname << ": Some unrecognized options were found. "
		<< "Use --help for a usage message." << std::endl;
		return EU_DECODE_FAIL;
	}

	return 0;
}


static errcode_t init_fs(const char* fsname, ext2_filsys *ret_fs) {
	struct stat statbuf;
	int error = 0;
	errcode_t errcode;
	io_manager io_mgr = unix_io_manager;

	// Ensure the file is a filesystem.
	errno = 0;
	if (stat (fsname, &statbuf) == -1) {
		error = errno;
		if (error != EOVERFLOW) {
			com_err(Config::progname.c_str(), error, " %s", fsname);
			return error;
		}
	}
	if (error == 0) {
		if (S_ISDIR (statbuf.st_mode))
		{
			Log::error << Config::progname << ": \"" << fsname << "\" is a directory. You need "
			<< "to use the raw filesystem device (or a copy thereof)." << std::endl;
			return EU_FS_ERR;
		}
		if (!S_ISBLK(statbuf.st_mode) && statbuf.st_size < 2048)
		{
			Log::error << Config::progname << ": \"" << fsname << "\" is too small to be a"
			<< " filesystem (" << statbuf.st_size << " bytes)." << std::endl;
			return EU_FS_ERR;
		}
	}

	errcode = ext2fs_open (fsname, EXT2_FLAG_64BITS, Config::backup_superblock,
		Config::block_size, io_mgr, ret_fs);
	return errcode;
}


int main(int argc, char* argv[])
{
	ext2_filsys fs;
	errcode_t errcode;

	Config::progname = argv[0];

	errcode = decode_options(argc, argv);
	if (errcode) {
		if (errcode == EU_STOP) return 0;
		Log::error << Config::progname << ": Error parsing command-line options." << std::endl;
		return errcode;
	}

	initialize_ext2_error_table();
	set_com_err_hook(Log_errors);

	errcode = init_fs(*argv, &fs);
	if (errcode) {
		std::cout << std::flush;
		com_err(Config::progname.c_str(), errcode, "when trying to open filesystem %s", *argv);
		return errcode;
	}

	errcode = load_super_block (fs);
	if (errcode == EU_FS_RECOVER) {
		if (!isatty(STDOUT_FILENO)) {
			Log::error << Config::progname << ": Mounted filesystem detected"
			<< " when trying to load filesystem parameters" << std::endl;
			return errcode;
		}
		char ans;
		std::cin.width (1);
		do {
			std::cout <<
			"If you decide to continue, extundelete may overwrite some of the deleted"
			<< std::endl <<
			"files and make recovering those files impossible.  You should unmount the"
			<< std::endl <<
			"file system and check it with fsck before using extundelete."
			<< std::endl <<
			"Would you like to continue? (y/n) " << std::endl;
			std::cin >> ans;
			if (ans == 'n')
				return 0;
		} while (ans != 'y');
	}
	else if (errcode) {
		com_err(Config::progname.c_str(), errcode, "when trying to load filesystem parameters");
		return errcode;
	}

	errcode = examine_fs (fs);
	if (errcode) {
		com_err(Config::progname.c_str(), errcode, "when trying to examine filesystem");
		return errcode;
	}

	errcode = ext2fs_close (fs);
	if (errcode) {
		com_err(Config::progname.c_str(), errcode, "when trying to close filesystem");
	}

	if(Config::elogfile.is_open())  Config::elogfile.close();
	if(Config::wlogfile.is_open())  Config::wlogfile.close();
	if(Config::slogfile.is_open())  Config::slogfile.close();
	if(Config::ilogfile.is_open())  Config::ilogfile.close();
	if(Config::dlogfile.is_open())  Config::dlogfile.close();
	// Sync here to ensure all recovered data is physically written to disk.
	sync();
	return 0;
}
