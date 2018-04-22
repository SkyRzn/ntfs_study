#ifndef _NTFS_FILE_RECORD_H_
#define _NTFS_FILE_RECORD_H_


#include "attribute.h"
#include <stdint.h>


#define FILE_RECORD_SIGN	"FILE"
#define MAX_ATTR_CNT		16

#define MFT_FLAG_NOT_USED	0x00
#define MFT_FLAG_FILE		0x01
#define MFT_FLAG_DIR		0x02
#define MFT_FLAG_UNKNOWN1	0x04
#define MFT_FLAG_UNKNOWN2	0x08


#pragma pack(push)
#pragma pack(1)

typedef struct {
	uint8_t sign[4];	// Signature
	uint16_t usn_offs;	// Update Sequence Number Offset
	uint16_t usn_size;	// Update Sequence Number and Array Size
	uint64_t lsn;		// $LogFile Sequence Number
	uint16_t sn;		// Sequence Number
	uint16_t hlc;		// Hard Link Counter
	uint16_t fao;		// Fist Attribute Offset
	uint16_t flags;		// Sequence Number
	uint32_t real_size;	// Real Size
	uint64_t ref;		// File Reference
	uint16_t nai;		// Next Attribute ID
	uint16_t align;		// Alignment
	uint32_t ntmr;		// number of this MFT record
	uint16_t usn;		// Update Sequence Number
	uint16_t usa;		// Update Sequence Array
} file_record_header_t;

#pragma pack(pop)

typedef struct {
	file_record_header_t *hdr;
	attribute_t attrs[MAX_ATTR_CNT];
	int attrs_cnt;
	attribute_file_name_t *file_name;
	attribute_index_root_t index_root;
} file_record_t;


int create_file_record(void *mm, file_record_t *fr);


#endif

