#include <iostream>
#include "sgx_urts.h"
#include "Enclave_u.h" // Headers for untrusted part (autogenerated by edger8r)

using namespace std;

# define MAX_PATH FILENAME_MAX
# define ENCLAVE_FILENAME "enclave.signed.so"

void ocall_print_error(const char *str)
{
    cerr << str << endl;
}

void ocall_println_string(const char *str)
{
    cout << str << endl;
}

/* Application entry */
int main()
{
    sgx_enclave_id_t global_eid = 0;
    char token_path[MAX_PATH] = {'\0'};
    sgx_launch_token_t token = {0};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED; // status flag for enclave calls
    int updated = 0;

    /* Initialize the enclave */
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        cerr << "Error: creating enclave" << endl;
        return -1;
    }

    /* Make an ecall to enclave */
    ret = ecall_open(global_eid);
    if (ret != SGX_SUCCESS) {
        cerr << "Error: Making an ecall_open()" << endl;
        return -1;
    }

    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);
    if (ret != SGX_SUCCESS) {
        cerr << "Error: Destroying enclave" << endl;
        return -1;
    }

    cout << "Info: SampleEnclave successfully returned." << endl;
    return 0;
}
