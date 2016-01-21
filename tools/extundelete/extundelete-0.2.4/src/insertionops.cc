#ifndef EXT2_FLAT_INCLUDES
#define EXT2_FLAT_INCLUDES 0
#endif
#include "config.h"

#include <assert.h>
#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <sys/types.h>
#include <ext2fs/ext2fs.h>
#include "extundelete.h"

// Below are a bunch of functions to allow us to print information
// about various types of data we encounter in this program.
std::ostream& operator<<(std::ostream& os, const ext2_inode& inode)
{
  // This was largely generated with:
  //   awk 'BEGIN { decode=0 } /^struct ext2_inode / { decode=1 } /^};/ { decode=0 } { if (decode) print; }' /usr/include/ext2fs/ext2_fs.h | sed -rn 's/^[[:space:]]*(|\/\*[0-9A-F]*\*\/[[:space:]]*)__[[:alnum:]_]*[[:space:]]*(i_[[:alnum:]_]*)(;|\[[0-9]+\];)[[:space:]]*\/\*[[:space:]](.*)[[:space:]]\*\/.*/  os << "\4: " << inode.\2 << 'std::endl';/p'


  os << "File mode: " << inode.i_mode << std::endl;
  os << "Low 16 bits of Owner Uid: " << inode.i_uid << std::endl;
  os << "Size in bytes: " << EXT2_I_SIZE(&inode) << std::endl;
  os << "Access time: " << inode.i_atime << std::endl;
  os << "Creation time: " << inode.i_ctime << std::endl;
  os << "Modification time: " << inode.i_mtime << std::endl;
  os << "Deletion Time: " << inode.i_dtime << std::endl;
  os << "Low 16 bits of Group Id: " << inode.i_gid << std::endl;
  os << "Links count: " << inode.i_links_count << std::endl;
  os << "Blocks count: " << inode.i_blocks << std::endl;
  //os << "Filesystem blocks count: " << inode.i_blocks * 512 / block_size_ << std::endl;
  os << "File flags: " << inode.i_flags << std::endl;
  os << "File version (for NFS): " << inode.i_generation << std::endl;
  os << "File ACL: " << inode.i_file_acl << std::endl;
  os << "Directory ACL: " << inode.i_dir_acl << std::endl;
  os << "Fragment address: " << inode.i_faddr << std::endl;
  os << "Direct blocks: ";
  for (int n = 0; n < EXT2_NDIR_BLOCKS; n++)
  {
    if (n!=0)
      os << ", ";
    os << inode.i_block[n];
  }
  os << std::endl;
  os << "Indirect block: " << inode.i_block[EXT2_IND_BLOCK] << std::endl;
  os << "Double indirect block: " << inode.i_block[EXT2_DIND_BLOCK] << std::endl;
  os << "Triple indirect block: " << inode.i_block[EXT2_TIND_BLOCK] << std::endl;
 
  return os;
}

std::ostream& operator<<(std::ostream& os, const ext2_super_block* const s_block)
{
  // This was largely generated with:
  //  awk 'BEGIN { decode=0 } /^struct ext2_super_block/ { decode=1 } /^};/ { decode=0 } { if (decode) print; }' /usr/include/ext2fs/ext2_fs.h | sed -rn 's/^[[:space:]]*(|\/\*[0-9A-F]*\*\/[[:space:]]*)__[[:alnum:]_]*[[:space:]]*(s_[[:alnum:]_]*)(;|\[[0-9]+\];)[[:space:]]*\/\*[[:space:]](.*)[[:space:]]\*\/.*/  os << "\4: " << s_block->\2 << 'std::endl';/p'
  os << "Inodes count: " << s_block->s_inodes_count << std::endl;
  os << "Blocks count: " << s_block->s_blocks_count << std::endl;
  os << "Reserved blocks count: " << s_block->s_r_blocks_count << std::endl;
  os << "Free blocks count: " << s_block->s_free_blocks_count << std::endl;
  os << "Free inodes count: " << s_block->s_free_inodes_count << std::endl;
  os << "First Data Block: " << s_block->s_first_data_block << std::endl;
  os << "Block size: " << EXT2_BLOCK_SIZE(s_block) << std::endl;
  os << "Fragment size: " << EXT2_FRAG_SIZE(s_block) << std::endl;
  os << "# Blocks per group: " << s_block->s_blocks_per_group << std::endl;
  os << "# Fragments per group: " << EXT2_FRAGS_PER_BLOCK(s_block) << std::endl;
  os << "# Inodes per group: " << s_block->s_inodes_per_group << std::endl;
  os << "Mount time: " << s_block->s_mtime << std::endl;
  os << "Write time: " << s_block->s_wtime << std::endl;
  os << "Mount count: " << s_block->s_mnt_count << std::endl;
  os << "Maximal mount count: " << s_block->s_max_mnt_count << std::endl;
  os << "Magic signature: " << s_block->s_magic << std::endl;
  os << "File system state: " << s_block->s_state << std::endl;
  os << "Behaviour when detecting errors: " << s_block->s_errors << std::endl;
  os << "minor revision level: " << s_block->s_minor_rev_level << std::endl;
  os << "time of last check: " << s_block->s_lastcheck << std::endl;
  os << "max. time between checks: " << s_block->s_checkinterval << std::endl;
  os << "OS: " << s_block->s_creator_os << std::endl;
  os << "Revision level: " << s_block->s_rev_level << std::endl;
  os << "Default uid for reserved blocks: " << s_block->s_def_resuid << std::endl;
  os << "Default gid for reserved blocks: " << s_block->s_def_resgid << std::endl;
  os << "First non-reserved inode: " << s_block->s_first_ino << std::endl;
  os << "size of inode structure: " << s_block->s_inode_size << std::endl;
  os << "block group # of this superblock: " << s_block->s_block_group_nr << std::endl;
  os << "compatible feature set: " << s_block->s_feature_compat << std::endl;
  os << "incompatible feature set: " << s_block->s_feature_incompat << std::endl;
  os << "readonly-compatible feature set: " << s_block->s_feature_ro_compat << std::endl;
  os << "128-bit uuid for volume: ";
    for(int n = 0; n < 16; n++)
      os << tohex((int) s_block->s_uuid[n], 2);
  os << std::endl;

  os << "For compression: " << s_block->s_algorithm_usage_bitmap << std::endl;
  os << "Nr to preallocate for dirs: " << (int) s_block->s_prealloc_dir_blocks << std::endl;
  os << "Per group table for online growth: " << s_block->s_reserved_gdt_blocks << std::endl;
  os << "uuid of journal superblock: ";
    for(int n = 0; n < 16; n++)
      os << tohex((int) s_block->s_journal_uuid[n], 2);
  os << std::endl;

  os << "inode number of journal file: " << s_block->s_journal_inum << std::endl;
  os << "device number of journal file: " << s_block->s_journal_dev << std::endl;
  os << "start of list of inodes to delete: " << s_block->s_last_orphan << std::endl;
  os << "HTREE hash seed: ";
    for(int n = 0; n < 4; n++)
      os << tohex((unsigned int) s_block->s_hash_seed[n], 8);
  os << std::endl;

  os << "Default hash version to use: " << (int) s_block->s_def_hash_version << std::endl;
  os << "Default type of journal backup: " << (int) s_block->s_jnl_backup_type << std::endl;
  os << "First metablock group: " << s_block->s_first_meta_bg << std::endl;
  os << "When the filesystem was created: " << s_block->s_mkfs_time << std::endl;
//  os << "Backup of the journal inode: " << s_block->s_jnl_blocks << std::endl;
//  os << "Padding to the end of the block: " << s_block->s_reserved << std::endl;


  os << "Compatible feature set:";
  if ((s_block->s_feature_compat & EXT2_FEATURE_COMPAT_DIR_PREALLOC))
    os << " DIR_PREALLOC";
  if ((s_block->s_feature_compat & EXT2_FEATURE_COMPAT_IMAGIC_INODES))
    os << " IMAGIC_INODES";
  if ((s_block->s_feature_compat & EXT3_FEATURE_COMPAT_HAS_JOURNAL))
    os << " HAS_JOURNAL";
  if ((s_block->s_feature_compat & EXT2_FEATURE_COMPAT_EXT_ATTR))
    os << " EXT_ATTR";
  if ((s_block->s_feature_compat & EXT2_FEATURE_COMPAT_RESIZE_INODE))
    os << " RESIZE_INODE";
  if ((s_block->s_feature_compat & EXT2_FEATURE_COMPAT_DIR_INDEX))
    os << " DIR_INDEX";
  os << std::endl;

  os << "Incompatible feature set:";
  if ((s_block->s_feature_incompat & EXT2_FEATURE_INCOMPAT_COMPRESSION))
    os << " COMPRESSION";
  if ((s_block->s_feature_incompat & EXT2_FEATURE_INCOMPAT_FILETYPE))
    os << " FILETYPE";
  if ((s_block->s_feature_incompat & EXT3_FEATURE_INCOMPAT_RECOVER))
    os << " RECOVER";
  if ((s_block->s_feature_incompat & EXT3_FEATURE_INCOMPAT_JOURNAL_DEV))
    os << " JOURNAL_DEV";

  if ((s_block->s_feature_incompat & EXT2_FEATURE_INCOMPAT_META_BG))
    os << " META_BG";
  os << std::endl;

  os << "Read only compatible feature set:";
  if ((s_block->s_feature_ro_compat & EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER))
    os << " SPARSE_SUPER";
  if ((s_block->s_feature_ro_compat & EXT2_FEATURE_RO_COMPAT_LARGE_FILE))
    os << " LARGE_FILE";
//  if ((s_block->s_feature_ro_compat & EXT2_FEATURE_RO_COMPAT_BTREE_DIR))
//    os << " BTREE_DIR";
  os << std::endl;

  return os;
}

std::ostream& operator<<(std::ostream& os, const ext2_group_desc& group_desc)
{
  os << "block bitmap at " << group_desc.bg_block_bitmap <<
        ", inodes bitmap at " << group_desc.bg_inode_bitmap <<
	", inode table at " << group_desc.bg_inode_table << std::endl;
  os << "\t   " << group_desc.bg_free_blocks_count << " free blocks, " <<
                   group_desc.bg_free_inodes_count << " free inodes, " <<
		   group_desc.bg_used_dirs_count << " used directory";
  return os;
}

std::ostream& operator<<(std::ostream& os, journal_header_t const& journal_header)
{
  os << "Block type: ";
  uint32_t blktype = journal_header.h_blocktype;
  switch (blktype)
  {
    case JFS_DESCRIPTOR_BLOCK:
      os << "Descriptor block";
      break;
    case JFS_COMMIT_BLOCK:
      os << "Commit block";
      break;
    case JFS_SUPERBLOCK_V1:
      os << "Superblock version 1";
      break;
    case JFS_SUPERBLOCK_V2:
      os << "Superblock version 2";
      break;
    case JFS_REVOKE_BLOCK:
      os << "Revoke block";
      break;
    default:
      os << "*UNKNOWN* (0x" << std::hex << blktype << std::dec << ')';
      break;
  }
  os << std::endl;
  uint32_t seq = journal_header.h_sequence;
  os << "Sequence Number: " << seq;
  return os;
}



std::ostream& operator<<(std::ostream& os, const journal_revoke_header_t journal_revoke_header)
{
  os << journal_revoke_header.r_header << std::endl;
  size_t count = journal_revoke_header.r_count;
  os << "Bytes used: " << count << std::endl;
  //assert(sizeof(journal_revoke_header_t) <= static_cast<unsigned int>(count) && count <= block_size_);
  count -= sizeof(journal_revoke_header_t);
  assert(count % sizeof(__u32) == 0);
  count /= sizeof(__u32);
  __u32 const* ptr = reinterpret_cast<__u32 const*>((unsigned char const*)&journal_revoke_header + sizeof(journal_revoke_header_t));
  int c = 0;
  for (uint32_t b = 0; b < static_cast<unsigned int>(count); ++b)
  {
    std::cout << std::setfill(' ') << std::setw(8) << &ptr[b];
    ++c;
    c &= 7;
    if (c == 0)
      std::cout << std::endl;
  }
  return os;
}




std::ostream& operator<<(std::ostream& os, journal_superblock_t const& journal_super_block)
{
  os << "Journal Super Block:" << std::endl;
  os << "Signature: 0x" << tohex(journal_super_block.s_header.h_magic, 8) << std::endl;
  os << journal_super_block.s_header << std::endl;
  os << "Journal block size: " << journal_super_block.s_blocksize << std::endl;
  os << "Number of journal blocks: " << journal_super_block.s_maxlen << std::endl;
  os << "Journal block where the journal actually starts: " << journal_super_block.s_first << std::endl;
  os << "Sequence number of first transaction: " << (journal_super_block.s_sequence) << std::endl;
  os << "Journal block of first transaction: " << (journal_super_block.s_start) << std::endl;
  os << "Error number: " << (journal_super_block.s_errno) << std::endl;
  if ((journal_super_block.s_header.h_blocktype) != JFS_SUPERBLOCK_V2)
    return os;
  os << "Compatible Features: " << (journal_super_block.s_feature_compat) << std::endl;
  os << "Incompatible features: " << (journal_super_block.s_feature_incompat) << std::endl;
  os << "Read only compatible features: " << (journal_super_block.s_feature_ro_compat) << std::endl;
  os << "Journal UUID: 0x";
  for (int i = 0; i < 16; ++i)
    os << std::hex << std::setfill('0') << std::setw(2) << (int)(journal_super_block.s_uuid[i]);
  os << std::dec << std::endl;
  int32_t nr_users = (journal_super_block.s_nr_users);
  os << "Number of file systems using journal: " << nr_users << std::endl;
  assert(nr_users <= 48);
  os << "Location of superblock copy: " << (journal_super_block.s_dynsuper) << std::endl;
  os << "Max journal blocks per transaction: " << (journal_super_block.s_max_transaction) << std::endl;
  os << "Max file system blocks per transaction: " << (journal_super_block.s_max_trans_data) << std::endl;
  os << "IDs of all file systems using the journal:\n";
  for (int u = 0; u < nr_users; ++u)
  {
    os << (u + 1) << '.';
    for (int i = 0; i < 16; ++i)
      os << std::hex << " 0x" << std::setfill('0') << std::setw(2) << (int)(journal_super_block.s_users[u * 16 + i]);
    os << std::dec << std::endl;
  }
  return os;
}
