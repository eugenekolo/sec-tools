#ifndef BLOCK_H
#define BLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <ext2fs/ext2fs.h>

struct dir_context {
        ext2_ino_t              dir;
        int             flags;
        char            *buf;
        int (*func)(ext2_ino_t  dir,
                    int entry,
                    struct ext2_dir_entry *dirent,
                    int offset,
                    int blocksize,
                    char        *buf,
                    void        *priv_data);
        void            *priv_data;
        errcode_t       errcode;
};

int extundelete_process_dir_block(ext2_filsys fs,
			     blk64_t	*blocknr,
			     e2_blkcnt_t blockcnt,
			     blk64_t	ref_block EXT2FS_ATTR((unused)),
			     int	ref_offset EXT2FS_ATTR((unused)),
			     void	*priv_data);

errcode_t extundelete_block_iterate3(ext2_filsys fs,
				struct ext2_inode inode,
				int	flags,
				char *block_buf,
				int (*func)(ext2_filsys fs,
					    blk64_t	*blocknr,
					    e2_blkcnt_t	blockcnt,
					    blk64_t	ref_blk,
					    int		ref_offset,
					    void	*priv_data),
				void *priv_data);

#ifdef __cplusplus
}
#endif

#endif /* BLOCK_H */
