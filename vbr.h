#ifndef _NTFS_VBR_H_
#define _NTFS_VBR_H_


#include <stdint.h>


#define OEM_ID	"NTFS    "
#define ESM		0x55AA

#pragma pack(push)
#pragma pack(1)

typedef struct {
	uint16_t bps;			// Bytes Per Sector
	uint8_t spc;			// Sectors Per Cluster
	uint16_t rs;			// Reserved Sectors
	uint8_t zero[3];		// always 0
	uint16_t not_used;		// not used by NTFS
	uint8_t md;				// Media Descriptor
	uint16_t zero2;			// always 0
	uint16_t spt;			// Sectors Per Track
	uint16_t noh;			// Number Of Heads
	uint32_t hs;			// Hidden Sectors
	uint32_t not_used2;		// not used by NTFS 0x20
	uint32_t not_used3;		// not used by NTFS
	uint64_t ts;			// Total Sectors
	uint64_t mft_cluster;	// Logical Cluster Number for the file $MFT
	uint64_t mirr_cluster;	// Logical Cluster Number for the file $MFTMirr
	uint32_t cpfrs;			// Clusters Per File Record Segment
	uint8_t cpib;			// Clusters Per Index Buffer
	uint8_t not_used4[3];	// not used by NTFS
	uint64_t vsn;			// Volume Serial Number
	uint32_t checksum;		// Checksum
} bpb_t;

typedef struct {
	uint8_t jump[3];		// Jump Instruction
	uint8_t oem_id[8];		// OEM ID
	bpb_t bpb;				// BPB + Extended BPB
	uint8_t bootstrap[426];	// Bootstrap Code
	uint16_t esm;			// End of Sector Marker
} vbr_t;

#pragma pack(pop)


vbr_t *create_vbr(void *mm);


#endif

