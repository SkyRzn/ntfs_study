#ifndef _NTFS_ATTRIBUTE_H_
#define _NTFS_ATTRIBUTE_H_


#include <stdint.h>


#define IE_FLAG_SMALL	0x00
#define IE_FLAG_LARGE	0x01


#pragma pack(push)
#pragma pack(1)

typedef struct {
	uint32_t type;
	uint32_t length;
	uint8_t form_code;
	uint8_t name_length;
	uint16_t name_offset;
	uint16_t flags;
	uint16_t instance;
	union {
		struct {
			uint32_t value_length;
			uint16_t value_offset;
			uint8_t reserved[2];
		} res;
		struct {
			uint64_t vcn_low;
			uint64_t vcn_high;
			uint16_t mapping_pairs_offset;
			uint8_t reserved[6];
			uint64_t allocated_length;
			uint64_t file_size;
			uint64_t valid_data_length;
			uint64_t total_allocated;
		} nres;
	};
} attribute_header_t;

// 0x00: 30 00 00 00 - type
// 0x04: 68 00 00 00  -len
// 0x08: 00 - resident
// 0x09: 00 - name len
// 0x0A: 18 00 - name offs
// 0x0C: 00 00 - flags
// 0x0E: 02 00 - instance
// 0x10: 4a 00 00 00 - val len
// 0x14: 18 00 - val offs
// 0x16: 01 00 - reserved
// 0x18: 05 00 00 00 00 00 05 00 - parent dir
// 0x20: 00 46 cd c7 1a da d3 01 - time
// 0x28: 00 46 cd c7 1a da d3 01 - time
// 0x30: 00 46 cd c7 1a da d3 01 - time
// 0x38: 00 46 cd c7 1a da d3 01 - time
// 0x40: 00 70 00 00 00 00 00 00 - alloc size
// 0x48: 00 6c 00 00 00 00 00 00 - real size
// 0x50: 06 00 00 00 - flags
// 0x54: 00 00 00 00 - eas
// 0x58: 04 - name len
// 0x59: 03 - namespace
// 0x60: 24 00 4d 00 46 00 54 00
// 0x68: 00 00 00 00 00 00   80 00 00 00 48 00 00 00   01 00 40 00 00 00 01 00   00 00 00 00 00 00 00 00

typedef struct {
	uint64_t parent_dir;	// File reference to the parent directory.
	uint64_t ctime;			// File Creation
	uint64_t atime;			// File Altered
	uint64_t mtime;			// MFT Changed
	uint64_t rtime;			// File Read
	uint64_t alloc_size;	// Allocated size of the file
	uint64_t real_size;		// Real size of the file
	uint32_t flags;			// Flags, e.g. Directory, compressed, hidden
	uint32_t eas;			// Used by EAs and Reparse
	uint8_t name_len;	// Filename length in characters (L)
	uint8_t namespace;		// Filename namespace
	uint16_t name[];		// File name in Unicode (not null terminated)
} attribute_file_name_t;

typedef struct {
	uint32_t attr_type;		// Attribute Type
	uint32_t coll_rule;		// Collation Rule
	uint32_t bpi_rec;		// Bytes per Index Record
	uint8_t cpi_rec;		// Clusters per Index Record
	uint8_t unused[3];		// padding
	uint32_t start_ie;		// start of the index entry list
	uint32_t end_used_ie;	// end of the used index entry list
	uint32_t end_alloc_ie;	// end of the allocated index entry list
	uint8_t ie_large;		// 0 - small index, 1 - large index
	uint8_t unused2[3];		// padding
} attribute_index_root_header_t;

// struct {
// 	uint64_t ctime;		// File Creation
// 	uint64_t atime;		// File Altered
// 	uint64_t mtime;		// MFT Changed
// 	uint64_t rtime;		// File Read
// 	uint32_t dos_perm;	// DOS File Permissions
//
// 	uint32_t max_ver;	// Maximum Number of Versions
// 	uint32_t ver;		// Version Number
// 	uint32_t class_id;	// Class Id
// 	uint32_t owner_id;	// Owner Id
// 	uint32_t sec_id;	// Security Id
// 	uint64_t quota;		// Quota Charged
// 	uint64_t usn;		// Update Sequence Number (USN)
// } standard_information_attribute_t;

#pragma pack(pop)

typedef struct {
	attribute_header_t *hdr;
	void *data;
} attribute_t;

typedef struct {
	attribute_index_root_header_t *hdr;
	attribute_file_name_t *file_names;
} attribute_index_root_t;


int create_attribute(void *mm, attribute_t *attr);
int create_index_root(void *mm, attribute_index_root_t *ir);


#endif

