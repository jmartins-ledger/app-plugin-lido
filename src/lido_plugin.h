#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

#define PARAMETER_LENGTH 32
#define SELECTOR_SIZE    4

#define RUN_APPLICATION 1

#define NUM_LIDO_SELECTORS 3

#define PLUGIN_NAME "Lido"

#define TOKEN_SENT_FOUND     1
#define TOKEN_RECEIVED_FOUND 1 << 1

#define STETH_TICKER "stETH"
#define STETH_DECIMALS WEI_TO_ETHER

#define WSTETH_TICKER "wstETH"
#define WSTETH_DECIMALS WEI_TO_ETHER

typedef enum {
    STAKE,
    WRAP,
    UNWRAP,
} lidoSelector_t;

typedef enum {
    TOKEN_SENT,
    TOKEN_RECEIVED,
    AMOUNT_SENT,
    AMOUNT_RECEIVED,
    REFERRAL,
    NONE,
} selectorField;

extern const uint8_t *const LIDO_SELECTORS[NUM_LIDO_SELECTORS];

// Number of decimals used when the token wasn't found in the CAL.
#define DEFAULT_DECIMAL WEI_TO_ETHER

// Ticker used when the token wasn't found in the CAL.
#define DEFAULT_TICKER ""

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct lido_parameters_t {
    uint8_t amount_sent[INT256_LENGTH];
    char referral[ADDRESS_LENGTH];

    uint8_t next_param;
    uint8_t valid;
    uint8_t selectorIndex;
} lido_parameters_t;

_Static_assert(sizeof(lido_parameters_t) <= 5 * 32, "failed");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);

bool eth_address_is_zero(char *address);