#include "attribute.h"
#include <endian.h>
#include <string.h>


int create_attribute(void *mm, attribute_t *attr)
{
	unsigned int offs;

	attr->hdr = mm;

	if (attr->hdr->form_code == 0)
		offs = (attr->hdr->res.value_offset); // be16toh ?????? FIXME
	else
		offs = 0; //FIXME

	attr->data = mm + offs;

	return 0;
}

int create_index_root(void *mm, attribute_index_root_t *ir)
{
	ir->hdr = mm;
	ir->file_names = mm + sizeof(attribute_index_root_header_t) + ir->hdr->start_ie;
	return 0;
}

