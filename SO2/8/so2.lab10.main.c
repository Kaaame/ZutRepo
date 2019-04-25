#include "so2ext2.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>

void readsuperblock(int fd, struct ext2_super_block * sblock);
void printsuperblock(struct ext2_super_block);

void readgroupdesc(int fd, struct ext2_group_desc ** dblock);
void printgroupdesc(struct ext2_group_desc *, int index);

void readinodes(int fd, unsigned int ssize, unsigned int gsize, struct ext2_inode ** inodes);
void printinode(struct ext2_inode inodes);

void printcurrentposition(int fd);

void readrootinode(int fd, int gsize, struct ext2_inode * root);
void readfolder(int fd, struct ext2_inode root, int gsize, struct ext2_group_desc *);
void printdir(struct ext2_dir_entry dir);

void displaytree();

struct ext2_inode * findinodeoffile(int fd, struct ext2_dir_entry dir, struct ext2_group_desc * gd);

int main(int argc, char ** argv)
{
  if(argc!=2)
  {
    printf("Pass only filename as an argument.\n");
    exit(EXIT_FAILURE);
  }
  char * filename = argv[1];
  printf("Reading file = %s\n", filename);

  int exfile = open(filename, O_RDONLY);
  if(exfile == -1)
  {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  struct ext2_super_block begin;
  struct ext2_group_desc * descc;
  struct ext2_inode * inodes = NULL;
  //inodes = (struct ext2_inode *)malloc(sizeof(struct ext2_inode) * (begin.s_inodes_count - begin.s_free_inodes_count));
  //for(int i = 0; i < (begin.s_inodes_count - begin.s_free_inodes_count); i++) inodes[i] = emptyinode;

  //lseek(exfile, 0x401, SEEK_SET);
  //while(byte == 0) read(exfile, &byte, sizeof(byte));
  readsuperblock(exfile, &begin);
  printsuperblock(begin);
  printcurrentposition(exfile);
  //off_t offset = lseek(exfile, 0, SEEK_CUR);
  //printf("%08x\n\n\n",offset);

  readgroupdesc(exfile, &descc);
  printgroupdesc(descc, 0);
  printcurrentposition(exfile);

  int directory = 0;
  int fifo = 0;
  int symblink = 0;
  int regularfile = 0;
  int characterdevice = 0;
  int blockdevice = 0;
  int unixsocket = 0;

  struct ext2_dir_entry de;

  struct ext2_inode root;

  readrootinode(exfile, descc[0].bg_inode_table, &root);
  printinode(root);

  readfolder(exfile, root, descc[0].bg_inode_table, descc);
}

void readsuperblock(int fd, struct ext2_super_block * sblock)
{
  lseek(fd, 1024, SEEK_SET);
  int size = read(fd, sblock, sizeof(*sblock));
}

void printsuperblock(struct ext2_super_block begin)
{
  printf("rysowanko.\n");
  printf("inode count %u = %04x\n",begin.s_inodes_count,begin.s_inodes_count);
  printf("block count %u = %04x\n",begin.s_blocks_count, begin.s_blocks_count);
  printf("reserved block %u = %04x\n",begin.s_r_blocks_count, begin.s_r_blocks_count);
  printf("free blocks %u = %04x\n",begin.s_free_blocks_count, begin.s_free_blocks_count);
  printf("free inodes %u = %04x\n",begin.s_free_inodes_count, begin.s_free_inodes_count);
  printf("first data block %u = %04x\n",begin.s_first_data_block, begin.s_first_data_block);
  printf("log block size %u = %04x\n",begin.s_log_block_size, begin.s_log_block_size);
  printf("log frag size %u = %04x\n",begin.s_log_frag_size, begin.s_log_frag_size);
  printf("blocks per group %u = %04x\n",begin.s_blocks_per_group, begin.s_blocks_per_group);
  printf("frags per group %u = %04x\n",begin.s_frags_per_group, begin.s_frags_per_group);
  printf("inodes per group %u = %04x\n",begin.s_inodes_per_group, begin.s_inodes_per_group);
  printf("mount time%u = %04x\n",begin.s_mtime, begin.s_mtime);
  printf("write time %u = %04x\n",begin.s_wtime, begin.s_wtime);
  printf("mount count %u = %02x\n",begin.s_mnt_count, begin.s_mnt_count);
  printf("maximal mount count %i = %02x\n",begin.s_max_mnt_count, begin.s_max_mnt_count);
  printf("magic %u = %02x\n",begin.s_magic, begin.s_magic);
  printf("fsystem state %u = %02x\n",begin.s_state, begin.s_state);
  printf("error %u = %02x\n",begin.s_errors, begin.s_errors);
  printf("padding %u = %02x\n",begin.s_pad, begin.s_pad);
  printf("last check %u = %04x\n",begin.s_lastcheck, begin.s_lastcheck);
  printf("check interval %u = %04x\n",begin.s_checkinterval, begin.s_checkinterval);
  printf("creator os %u = %04x\n",begin.s_creator_os, begin.s_creator_os);
  printf("revision level %u = %04x\n",begin.s_rev_level, begin.s_rev_level);
  printf("def uid %u = %02x\n",begin.s_def_resuid, begin.s_def_resuid);
  printf("def gid %u = %02x\n",begin.s_def_resgid, begin.s_def_resgid);
  printf("numb %u = %04x\n",begin.s_reserved[0], begin.s_reserved[0]);
}

void readgroupdesc(int fd, struct ext2_group_desc ** dblock)
{
  struct ext2_group_desc hold;
  struct ext2_super_block sb;

readsuperblock(fd, &sb);

  int number = (int)ceilf(sb.s_blocks_count / (float)sb.s_blocks_per_group);
  struct ext2_group_desc * temp = (struct ext2_group_desc *)malloc(sizeof(struct ext2_group_desc) * number);
  for(int i = 0; i < number; i++)
  {
    lseek(fd, 2048 + i*sizeof(struct ext2_group_desc), SEEK_SET);
    read(fd, &hold, sizeof(hold));
    temp[i] = hold;
  }
  for(int i = 0; i < number; i++) printgroupdesc(temp, i);
  int size = read(fd, dblock, sizeof(*dblock));
  *dblock = temp;
}

void printgroupdesc(struct ext2_group_desc * descc, int index)
{

  printf("blocks bitmap block %u = %08x\n",descc[index].bg_block_bitmap,descc[index].bg_block_bitmap);
  printf("inodes bitmap block %u = %08x\n",descc[index].bg_inode_bitmap, descc[index].bg_inode_bitmap);
  printf("starting address of inode %u = %08x\n",descc[index].bg_inode_table, descc[index].bg_inode_table);
  printf("free block count %u = %04x\n",descc[index].bg_free_blocks_count, descc[index].bg_free_blocks_count);
  printf("free inodes count %u = %04x\n",descc[index].bg_free_inodes_count, descc[index].bg_free_inodes_count);
  printf("number of dirs %u = %04x\n",descc[index].bg_used_dirs_count, descc[index].bg_used_dirs_count);
  printf("%u = %04x\n",descc[index].bg_pad, descc[index].bg_pad);
}

void printcurrentposition(int fd)
{
  printf("\n%08x\n", lseek(fd, 0, SEEK_CUR));
}

void printinode(struct ext2_inode in)
{
	  printf("\n\nmode %u = %02x\n\n",in.i_mode, in.i_mode);
	  printf("uid %u = %02x\n",in.i_uid, in.i_uid);
	  printf("size %u = %04x\n",in.i_size, in.i_size);
	  printf("access time %u = %04x\n",in.i_atime,in.i_atime);
	  printf("ctime %u = %04x\n",in.i_ctime, in.i_ctime);
	  printf("mtime %u = %04x\n",in.i_mtime, in.i_mtime);
	  printf("dtime %u = %04x\n",in.i_dtime, in.i_dtime);
	  printf("gid %u = %02x\n",in.i_gid, in.i_gid);
	  printf("links %u = %02x\n",in.i_links_count, in.i_links_count);
	  printf("blocks %u = %04x\n",in.i_blocks, in.i_blocks);
	  printf("flags %u = %04x\n",in.i_flags, in.i_flags);
	  printf("block 0 %u = %04x\n",in.i_block[0], in.i_block[0]);
	  printf("version %u = %04x\n",in.i_version, in.i_version);
	  printf("file acl %u = %04x\n",in.i_file_acl, in.i_file_acl);
	  printf("dir acl %u = %04x\n",in.i_dir_acl, in.i_dir_acl);
	  printf("fragment address %u = %04x\n",in.i_faddr, in.i_faddr);
}

void readrootinode(int fd, int gsize, struct ext2_inode * root)
{
  lseek(fd, (gsize*1024) + 128*1, SEEK_SET);
  read(fd, root, sizeof(*root));
}

void readfolder(int fd, struct ext2_inode root, int gsize, struct ext2_group_desc * gd)
{

  __u16 referencesize = 0;
  struct ext2_dir_entry current;
  struct ext2_inode * in = NULL;
  //printinode(root);
  while(1)
  {
    lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
    read(fd, &current, sizeof(current));
    in =  findinodeoffile(fd, current, gd);
    //printinode(*in);
    referencesize+=current.rec_len;
    if(referencesize>=root.i_size) return;
    //printdir(current);
    if(S_ISFIFO(in->i_mode)) printf("fifo : %s\n", current.name);
    if(S_ISDEin->i_mode) printf("dev : %s\n", current.name);
    if(in->i_mode&0x4000) printf("directory name : %s\n", current.name);
    if(in->i_mode&0x6000) printf("blockdev : %s\n", current.name);
    if(in->i_mode&0x8000) printf("file : %s\n", current.name);
    if(in->i_mode&0xA000) printf("symlink : %s\n", current.name);
    if(in->i_mode&0xC000) printf("unix socket : %s\n", current.name);

    if(strcmp(current.name, "b") == 0) readfolder(fd, *in, 0, gd);

    if(in->i_mode&0x4000 && strcmp(current.name, ".")!=0 && strcmp(current.name, "..")!=0)
    {
      //printf("NEW DIR\n");
      //readfolder(fd, *in, 0, gd);
    }
  }
  /*
  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  struct ext2_inode * in = findinodeoffile(fd, current, gd);
  printinode(*in);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;

  lseek(fd, root.i_block[0]*1024 + referencesize, SEEK_SET);
  read(fd, &current, sizeof(current));
  printdir(current);
  referencesize+=current.rec_len;
  */
}

void printdir(struct ext2_dir_entry dir)
{
  printf("inode %u = %08x\n", dir.inode, dir.inode);
  printf("reclen %u = %04x\n", dir.rec_len, dir.rec_len);
  printf("namelen %u = %02x\n", dir.name_len, dir.name_len);
  printf("file type %u = %02x\n", dir.file_type, dir.file_type);
  printf("name: %s\n", dir.name);
}

struct ext2_inode * findinodeoffile(int fd, struct ext2_dir_entry dir, struct ext2_group_desc * gd)
{

  struct ext2_super_block sb;
  readsuperblock(fd, &sb);
  struct ext2_inode * res = (struct ext2_inode *)malloc(sizeof(struct ext2_inode));
  __u32 bg = (dir.inode-1)/sb.s_inodes_per_group;
  __u32 index = (dir.inode-1) % sb.s_inodes_per_group;

  lseek(fd, gd[bg].bg_inode_table * 1024 + index * 128, SEEK_SET);
  read(fd, res, sizeof(struct ext2_inode));
  return res;
  /*
  if(dir.inode < sb.s_inodes_per_group)
  {
    readgroupdesc(fd, &gd);
    lseek(fd, (gd.bg_inode_table * 1024) + (128*dir.inode), SEEK_SET);
    read(fd, &res, sizeof(res));
    //return res;
  }
  else
  {
    unsigned int gdnum =(dir.inode-1)/sb.s_inodes_per_group;
    unsigned int index = (dir.inode-1)%sb.s_inodes_per_group;
    unsigned int block = index*sizeof(struct ext2_inode)/1024;
    lseek(fd, ((sb.s_blocks_per_group+2)*1024),SEEK_SET);
  }
  */
  return res;

}
