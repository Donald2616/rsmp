#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disp_s40.h"
#include "disp_json_generic.h"

int main() {
    // Création d'une structure de test
    DispS40StatusResponse response;
    response.displayPoolCount = 1;
    response.displayPoolList = calloc(1, sizeof(DisplayPoolElementObject));

    strcpy(response.displayPoolList[0].msgId, "HELLO_WORLD");
    response.displayPoolList[0].maxWaitTime = 0;
    response.displayPoolList[0].displayDuration = 0;
    response.displayPoolList[0].displayPriority = 100;
    strcpy(response.displayPoolList[0].dynamicData, "");

    // Encodage JSON
    struct json_object* j = encode_disp_s40_status_response(&response);
    const char* json_str = json_object_to_json_string_ext(j, JSON_C_TO_STRING_PRETTY);
    printf("JSON généré :\n%s\n", json_str);

    // Décodage
    DispS40StatusResponse decoded;
    decode_disp_s40_status_response(json_str, &decoded);
    printf("Message décodé : %s\n", decoded.displayPoolList[0].msgId);

    // Nettoyage
    free_disp_s40_status_response(&response);
    free_disp_s40_status_response(&decoded);
    json_object_put(j);
    return 0;
}
