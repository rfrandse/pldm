#include <endian.h>
#include <string.h>

#include "fru.h"

int encode_get_fru_record_table_metadata_req(uint8_t instance_id,
					     struct pldm_msg *msg)
{
	if (msg == NULL) {
		return PLDM_ERROR_INVALID_DATA;
	}

	struct pldm_header_info header = {0};
	header.instance = instance_id;
	header.msg_type = PLDM_REQUEST;
	header.pldm_type = PLDM_FRU;
	header.command = PLDM_GET_FRU_RECORD_TABLE_METADATA;
	int rc = pack_pldm_header(&header, &(msg->hdr));
	if (PLDM_SUCCESS != rc) {
		return rc;
	}
	return PLDM_SUCCESS;
}

int decode_get_fru_record_table_metadata_resp(
    const struct pldm_msg *msg, size_t payload_length, uint8_t *completion_code,
    uint8_t *fru_data_major_version, uint8_t *fru_data_minor_version,
    uint32_t *fru_table_maximum_size, uint32_t *fru_table_length,
    uint16_t *total_record_set_identifiers, uint16_t *total_table_records,
    uint32_t *checksum)
{
	if (msg == NULL || completion_code == NULL ||
	    fru_data_major_version == NULL || fru_data_minor_version == NULL ||
	    fru_table_maximum_size == NULL || fru_table_length == NULL ||
	    total_record_set_identifiers == NULL ||
	    total_table_records == NULL || checksum == NULL) {
		return PLDM_ERROR_INVALID_DATA;
	}

	if (payload_length != PLDM_GET_FRU_RECORD_TABLE_METADATA_RESP_BYTES) {
		return PLDM_ERROR_INVALID_LENGTH;
	}

	struct pldm_get_fru_record_table_metadata_resp *response =
	    (struct pldm_get_fru_record_table_metadata_resp *)msg->payload;
	*completion_code = response->completion_code;
	if (PLDM_SUCCESS != *completion_code) {
		return PLDM_SUCCESS;
	};

	*fru_data_major_version = response->fru_data_major_version;
	*fru_data_minor_version = response->fru_data_minor_version;
	*fru_table_maximum_size = le32toh(response->fru_table_maximum_size);
	*fru_table_length = le32toh(response->fru_table_length);
	*total_record_set_identifiers =
	    le16toh(response->total_record_set_identifiers);
	*total_table_records = le16toh(response->total_table_records);
	*checksum = le32toh(response->checksum);

	return PLDM_SUCCESS;
}

int encode_get_fru_record_table_metadata_resp(
    uint8_t instance_id, uint8_t completion_code,
    uint8_t fru_data_major_version, uint8_t fru_data_minor_version,
    uint32_t fru_table_maximum_size, uint32_t fru_table_length,
    uint16_t total_record_set_identifiers, uint16_t total_table_records,
    uint32_t checksum, struct pldm_msg *msg)
{

	if (msg == NULL) {
		return PLDM_ERROR_INVALID_DATA;
	}

	struct pldm_header_info header = {0};
	header.msg_type = PLDM_RESPONSE;
	header.instance = instance_id;
	header.pldm_type = PLDM_FRU;
	header.command = PLDM_GET_FRU_RECORD_TABLE_METADATA;
	int rc = pack_pldm_header(&header, &(msg->hdr));
	if (PLDM_SUCCESS != rc) {
		return rc;
	}

	struct pldm_get_fru_record_table_metadata_resp *response =
	    (struct pldm_get_fru_record_table_metadata_resp *)msg->payload;
	response->completion_code = completion_code;
	if (response->completion_code == PLDM_SUCCESS) {
		response->fru_data_major_version = fru_data_major_version;
		response->fru_data_minor_version = fru_data_minor_version;
		response->fru_table_maximum_size =
		    htole32(fru_table_maximum_size);
		response->fru_table_length = htole32(fru_table_length);
		response->total_record_set_identifiers =
		    htole16(total_record_set_identifiers);
		response->total_table_records = htole16(total_table_records);
		response->checksum = htole32(checksum);
	}

	return PLDM_SUCCESS;
}