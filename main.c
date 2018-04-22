#include "vbr.h"
#include "file_record.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "routines.h" //TEST


int main()
{
	void *mm, *filep;
	int fd;
	struct stat sb;
	vbr_t *vbr;
	file_record_t fr;

	fd = open("NTFS", O_RDONLY);
	if (fd == -1)
		return -1;

	if (fstat(fd, &sb) == -1)
		return -1;

	mm = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	vbr = create_vbr(mm);
	if (!vbr)
		goto end;

	filep = mm + vbr->bpb.bps*vbr->bpb.spc*vbr->bpb.mft_cluster;

	for (int i = 0; i < 100; i++) {
		if (create_file_record(filep, &fr) != 0) {
			printf("END: %d\n", i);
			goto end;
		}
		if (fr.file_name) {
			printf("%03d: ", i);
			print_utf8(fr.file_name->name, fr.file_name->name_len);
			printf("\t\t\t %lx\n", fr.file_name->parent_dir);
			if (i == 64) {
				printf("********** %x\n", fr.index_root.hdr->attr_type);
				print_utf8(fr.index_root.file_names[0].name, 8);
				printf("\n");
				for (int j = 0; j < fr.attrs_cnt; j++) {
					printf("-------------- %x\n", fr.attrs[j].hdr->type);
					dump(fr.attrs[j].hdr, sizeof(attribute_header_t));
					printf("-------------- DATA\n");
					dump(fr.attrs[j].data, fr.attrs[j].hdr->res.value_length);
				// 				printf(" %02x", fr.attrs[j].hdr->type);
				}
			}


		}

		filep += 1024;
	}


end:
	munmap(mm, sb.st_size);
	return 0;
}
