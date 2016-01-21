#ifndef EXTUNDELETEPRIV_H
#define EXTUNDELETEPRIV_H
#include <climits>
#include <cstring>
#include <iomanip>
#include <list>
#include <map>
#include <stdint.h>
#include <utility>

#include <sys/types.h>
#include <ext2fs/ext2fs.h>

// Global variables
extern std::string outputdir;

// Frequently used constant values from the superblock.
extern uint32_t block_size_;

// Information from journal
typedef std::vector<blk64_t>  block_list_t;
extern std::vector<uint32_t> tag_seq;
extern block_list_t tag_jblk;
extern block_list_t tag_fsblk;
extern block_list_t rvk_block;
/*
 * journ_map is meant to contain the
 * (file system block number, (journal block number, sequence number)),
 * in that order, for each descriptor in the journal.
 * block_pair_t is (journal block number, sequence number).
*/
typedef std::pair<blk64_t, uint32_t>   block_pair_t;
typedef std::pair<blk64_t, block_pair_t>  journal_map_item;
typedef std::multimap<blk64_t, block_pair_t>  journal_map_t;
extern journal_map_t journ_map;

static void parse_inode_block(ext2_filsys fs, struct ext2_inode *inode, const char *buf, ext2_ino_t ino);
static errcode_t recover_inode(ext2_filsys fs, ext2_filsys jfs, ext2_ino_t ino,
		struct ext2_inode *&inode, int ver);
static int pair_names_with(ext2_filsys fs, ext2_filsys jfs, std::vector<ext2_ino_t>& inolist,
		ext2_ino_t ino, std::string dirname, int del, std::vector<ext2_ino_t>& parent_inos);

#endif //EXTUNDELETEPRIV_H
