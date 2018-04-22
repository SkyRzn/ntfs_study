#include "file_record.h"
#include <endian.h>
#include <string.h>
#include <errno.h>


int create_file_record(void *mm, file_record_t *fr)
{
	int i, offs;
	attribute_t *attr;

	fr->hdr = mm;
	offs = fr->hdr->fao;

	if (memcmp(fr->hdr->sign, FILE_RECORD_SIGN, 4) != 0)
		return -EINVAL;

	fr->file_name = NULL;

	for (i = 0; i < MAX_ATTR_CNT; i++) {
		attr = &fr->attrs[i];
		create_attribute(mm + offs, attr);
		if (attr->hdr->type == 0xFFFFFFFF) {
			fr->attrs_cnt = i;
			break;
		}

		switch(attr->hdr->type) {
			case 0x30:
				fr->file_name = attr->data;
				break;
			case 0x90:
				create_index_root(attr->data, &fr->index_root); //FIXME check return
				break;

		}

		offs += attr->hdr->length;
	}

	return 0;
}


