#!/usr/bin/python


import struct


def unpack(fmt, data):
	l = struct.calcsize(fmt)
	print l
	return struct.unpack(fmt, data[:l])

FAT_STRUCT = (	('name', '8s'),
				('ext', '3s'),
				('attr', 'B'),
				('nt_res', 'B'),
				('crt_time_tenth', 'B'),
				('crt_time', 'H'),
				('crt_date', 'H'),
				('last_access_date', 'H'),
				('first_cluster_hi', 'H'),
				('wrt_time', 'H'),
				('wrt_date', 'H'),
				('first_cluster_lo', 'H'),
				('filesize', 'I'),
			)

class Fat:
	def __init__(self, data):
		names, lens = zip(*FAT_STRUCT)
		values = unpack('=' + ''.join(lens), data)
		print values

		for name, val in zip(names, values):
			if not name:
				continue
			print name, val


#struct Bpb {
  #uint8_t  BS_jmpBoot[3];    /* jump instruction to boot code */
  #uint8_t  BS_OEMName[8];    /* "MSWIN4.1" */
  #uint16_t BPB_BytsPerSec;  512 /* bytes per sector (512, 1k, 2k, 4k) */
  #uint8_t  BPB_SecPerClus;  8 /* sectors per cluster (2^n, 0<=n<=7) */
  #uint16_t BPB_RsvdSecCnt;  32 /* number of reserved sectors */
  #uint8_t  BPB_NumFATs;     2 /* count of FATs on the volume (usually 2) */
  #uint16_t BPB_RootEntCnt;  0 /* count of root directory entries (0 if FAT32) */
  #uint16_t BPB_TotSec16;    0 /* total count of sectors (0 if FAT32) */
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