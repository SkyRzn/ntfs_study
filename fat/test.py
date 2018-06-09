#!/usr/bin/python

from bpb import Bpb
from fat import Fat

import mmap
from hexdump import hexdump



#def print_dump_str(data):
	#for i, b in enumerate(data[:16]):
		#print '%02x' % (ord(b)),
		#if i > 0 and (i+1)%8 == 0:
			#print '  ',
	#print '      ',
	#for i, b in enumerate(data[:16]):
		#print '%c' % (b),
		#if i > 0 and (i+1)%8 == 0:
			#print '  ',

def dump(data, start, end):
	hexdump(data[start:start+end])
	#for i, b in enumerate(data[start:start+end]):
		#print '%02x' % (ord(b)),
		##print '%c' % (b),
		#if i > 0:
			#if (i+1)%16 == 0:
				#print
			#elif (i+1)%8 == 0:
					#print '  ',


def read_bpb():
	with open('disk', 'r+b') as f:
		mm = mmap.mmap(f.fileno(), 0)

	root = 0x4000 + 0x1ff000 + 0x1ff000
	dump(mm, root, 256)
	dump(mm, root, 256)
	print

	#bpb = Bpb(mm)
	fat = Fat(mm[root+0x80+1:root + 10000])

read_bpb()


#struct Bpb {
  #uint8_t  BS_jmpBoot[3];    /* jump instruction to boot code */
  #uint8_t  BS_OEMName[8];    /* "MSWIN4.1" */
  #uint16_t BPB_BytsPerSec;   /* bytes per sector (512, 1k, 2k, 4k) */
  #uint8_t  BPB_SecPerClus;   /* sectors per cluster (2^n, 0<=n<=7) */
  #uint16_t BPB_RsvdSecCnt;   /* number of reserved sectors */
  #uint8_t  BPB_NumFATs;      /* count of FATs on the volume (usually 2) */
  #uint16_t BPB_RootEntCnt;   /* count of root directory entries (0 if FAT32) */
  #uint16_t BPB_TotSec16;     /* total count of sectors (0 if FAT32) */
  #uint8_t  BPB_Media;        /* media type, usally 0xf8 */
  #uint16_t BPB_FATSz16;      /* sectors occupied by one fat (FAT12 / FAT16) */
  #uint16_t BPB_SecPerTrk;    /* sectors per track for Int 0x13 */
  #uint16_t BPB_NumHeads;     /* numbers of heads for Int 0x13 */
  #uint32_t BPB_HiddSec;      /* count of sectors preceding the partition */
  #uint32_t BPB_TotSec32;     /* total count of all sectors of the volume */
#} __attribute__ ((packed));


#struct msdos_sb_info {
	#unsigned short sec_per_clus; /* sectors/cluster */
	#unsigned short cluster_bits; /* log2(cluster_size) */
	#unsigned int cluster_size;   /* cluster size */
	#unsigned char fats,fat_bits; /* number of FATs, FAT bits (12 or 16) */
	#unsigned short fat_start;
	#unsigned long fat_length;    /* FAT start & length (sec.) */
	#unsigned long dir_start;
	#unsigned short dir_entries;  /* root dir start & entries */
	#unsigned long data_start;    /* first data sector */
	#unsigned long max_cluster;   /* maximum cluster number */
	#unsigned long root_cluster;  /* first cluster of the root directory */
	#unsigned long fsinfo_sector; /* sector number of FAT32 fsinfo */
	#struct mutex fat_lock;
	#unsigned int prev_free;      /* previously allocated cluster number */
	#unsigned int free_clusters;  /* -1 if undefined */
	#unsigned int free_clus_valid; /* is free_clusters valid? */
	#struct fat_mount_options options;
	#struct nls_table *nls_disk;  /* Codepage used on disk */
	#struct nls_table *nls_io;    /* Charset used for input and display */
	#const void *dir_ops;		     /* Opaque; default directory operations */
	#int dir_per_block;	     /* dir entries per block */
	#int dir_per_block_bits;	     /* log2(dir_per_block) */

	#int fatent_shift;
	#struct fatent_operations *fatent_ops;
	#struct inode *fat_inode;

	#spinlock_t inode_hash_lock;
	#struct hlist_head inode_hashtable[FAT_HASH_SIZE];
#};