#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disp_s30.h"
#include "disp_json_generic.h"

/**
 * @brief Programme de test de l'encodage/décodage JSON pour DISP/S30
 */
int main() {
    DispS30StatusResponse response;
    response.msgIdCount = 2;
    response.msgIdList = malloc(response.msgIdCount * sizeof(char*));
    response.msgIdList[0] = strdup("HELLO_WORLD");
    response.msgIdList[1] = strdup("SECOND_MESSAGE");

    struct json_object* json = encode_disp_s30_status_response(&response);
    printf("JSON généré :\n%s\n", json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY));

    const char* json_str = json_object_to_json_string(json);
    DispS30StatusResponse decoded;
    decode_disp_s30_status_response(json_str, &decoded);

    printf("Message décodé :\n");
    for (size_t i = 0; i < decoded.msgIdCount; ++i) {
        printf("- %s\n", decoded.msgIdList[i]);
    }

    free_disp_s30_status_response(&response);
    free_disp_s30_status_response(&decoded);
    json_object_put(json);
    return 0;
}
